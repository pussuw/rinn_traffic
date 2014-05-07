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

GenSignal *	Ferry::GetFerryHeartBeat()
{
	return &this->ferry_hearbeat;
}

/** \todo utilize synch method and actual state machine */
void Ferry::Execute()
{
	int jepalow = LAKE_CROSS_TICKS;
	int state = 0;
	while(!Terminated)
	{
		ferry_hearbeat.WaitSignal();
		jepalow--;
		if(jepalow == 0)
		{
			jepalow = LAKE_CROSS_TICKS;
			switch(state)
			{
			case 0:
				printf("Lautta saapuu L\n");
				LoadFerry();
				state = 1;
				break;
			case 1:
				state = 2;
				break;
			case 2:
				printf("Lautta saapuu D\n");
				UnloadFerry();
				state = 3;
				break;
			case 3:
			default:
				state = 0;
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
