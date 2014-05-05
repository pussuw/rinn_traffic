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
/* How many ticks to cross the lake */
#define LAKE_CROSS_TICKS 10

Ferry::Ferry()
{
	sem_init(&this->ferry_load, 0, 0);
	sem_init(&this->ferry_unload, 0, 0);
	//ferry_sync_mutex = PTHREAD_MUTEX_INITIALIZER;
	//vehicle_ready_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&this->ferry_sync_mutex, NULL);
	pthread_mutex_init(&this->vehicle_ready_mutex, NULL);
	pthread_cond_init(&this->ferry_sync_event, NULL);
	pthread_cond_init(&this->vehicle_ready_event, NULL);
	lake_cross_ticks = LAKE_CROSS_TICKS;
	/* Ferry sync event and register to observer */
}

Ferry::~Ferry()
{
	sem_destroy(&this->ferry_load);
	sem_destroy(&this->ferry_unload);
	pthread_mutex_destroy(&this->ferry_sync_mutex);
	pthread_mutex_destroy(&this->vehicle_ready_mutex);
	pthread_cond_destroy(&this->ferry_sync_event);
	pthread_cond_destroy(&this->vehicle_ready_event);
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
	pthread_cond_signal(&this->vehicle_ready_event);
	/* 5: Return from this function -> ferry travel complete !*/
}

pthread_cond_t *Ferry::GetFerryEvent(void)
{
	return &(this->ferry_sync_event);
}

void Ferry::Execute()
{
	int jepalow = LAKE_CROSS_TICKS;
	int state = 0;
	while(1)
	{
		usleep(100000);
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
		usleep(100);
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
		/* Let everyone out */
		sem_post(&this->ferry_unload);
		/* Wait for current car to get off board */
		pthread_cond_wait(&this->vehicle_ready_event,
						  &this->vehicle_ready_mutex);
	}
}


#if 0
void Ferry::LoadFerry()
{
	/* Get every car on board */
	int vehicles_waiting = 0;
	/* See if anyone is waiting to board (at this point) */
	sem_getvalue(&this->ferry_load, &vehicles_waiting);
	/* If a vehicle arrives after the query, too bad, he's out of the ferry */
	if(vehicles_waiting == 0)
		return;
	/* At this point semaphore value is < 0 */
	vehicles_waiting = abs(vehicles_waiting);
	while(vehicles_waiting--)
	{
		/* Let everyone in */
		sem_post(&this->ferry_load);
		/* Wait for current car to get onboard */
		pthread_cond_wait(&this->vehicle_ready_event,
						  &this->vehicle_ready_mutex);
	}
}
#endif

#if 0
printf("Autoja odottamassa %d\n", vehicles_waiting);
/* Leave semaphore locked ("owned" by ferry) */
do
{
	/* Wait until all vehicles have boarded the vessel */
	sem_getvalue(&this->ferry_unload, &vehicles_in);
	usleep(100);
} while(vehicles_waiting != abs(vehicles_in));
printf("Autoja sisassa %d\n", abs(vehicles_in));


/* Unload every boarded vehicle */
while(sem_trywait(&this->ferry_unload) < 0)
{
	printf("Autoa ulos\n");
	sem_post(&this->ferry_unload);
}
#endif
