/*
 * ferry.cpp
 *
 *  Created on: 4.5.2014
 *      Author: Ville
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include "ferry.h"

Ferry::Ferry()
{
	sem_init(&this->ferry_load, 0, 0);
	sem_init(&this->ferry_unload, 0, 0);
	/** \todo Ferry sync event and register to observer */
}

Ferry::~Ferry()
{
	sem_destroy(&this->ferry_load);
	sem_destroy(&this->ferry_unload);
}

/** \todo printit */
void Ferry::UseFerry(int customer_id)
{
	/* 1: Wait for ferry to arrive and load */
	printf("Auto %d, jonottaa lautalle\n", customer_id);
	sem_wait(&this->ferry_load);
	/* 2: Our turn, board ferry */
	printf("Auto %d, nousee lautalle\n", customer_id);
	/* 3: Wait for ferry to arrive at other end and unload */
	sem_wait(&this->ferry_unload);
	/* 4: Inform ferry that we have unloaded */
	printf("Auto %d, poistuu lautalta\n", customer_id);
	vehicle_ready.Signal();
	/* 5: Return from this function -> ferry travel complete !*/
}

/** \todo utilize synch method and actual state machine */
void Ferry::Execute()
{
	int ticks = lake_cross_ticks;
	EFerryState state = FERRY_L;
	while(!Terminated)
	{
		heartbeat.WaitSignal();
		ticks--;
		if(ticks == 0)
		{
			ticks = lake_cross_ticks;
			switch(state)
			{
			default:
			case FERRY_L:
				printf("Lautta saapuu L\n");
				UnloadFerry();
				LoadFerry();
				state = FERRY_D;
				break;
			case FERRY_D:
				printf("Lautta saapuu D\n");
				UnloadFerry();
				LoadFerry();
				state = FERRY_L;
				break;
			}
		}
	}
}

void Ferry::LoadFerry()
{
	/* Get every car on board */
	int vehicles_in = 0,
		vehicles_boarding = -1;
	/* At this point semaphore value is <= 0 */
	while(sem_trywait(&this->ferry_load) < 0)
	{
		vehicles_boarding++;
		/* If semaphore was 0, release it, and try again
		 * Doesn't matter if someone else snatches semaphore,
		 * simply keep trying until ownership is granted */
		sem_post(&this->ferry_load);
	}
	/* Leave semaphore locked ("owned" by ferry) => no more cars can get in */
	do
	{
		/* Wait until all vehicles have boarded the vessel */
		sem_getvalue(&this->ferry_unload, &vehicles_in);
		/* Give cars some time to inform about their status */
		usleep(10);
	} while(vehicles_boarding != abs(vehicles_in));
}

void Ferry::UnloadFerry()
{
	/* Get every car off board*/
	int vehicles_waiting = 0;
	/* See how many cars are on board */
	sem_getvalue(&this->ferry_unload, &vehicles_waiting);
	if(vehicles_waiting == 0)
		return;
	/* At this point semaphore value is < 0 */
	vehicles_waiting = abs(vehicles_waiting);
	while(vehicles_waiting--)
	{
		/* Let one car out */
		sem_post(&this->ferry_unload);
		/* Wait for current car to get off board */
		vehicle_ready.WaitSignal();
	}
}
