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
	sem_init(&this->ferry_queue, 0, 0);
	sem_init(&this->ferry_boarded, 0, 0);
	pthread_cond_init(&this->ferry_sync_event, NULL);
	lake_cross_ticks = LAKE_CROSS_TICKS;
	/* Ferry sync event and register to observer */
}

Ferry::~Ferry()
{
	sem_destroy(&this->ferry_queue);
	sem_destroy(&this->ferry_boarded);
	pthread_cond_destroy(&this->ferry_sync_event);
}

/** \todo printit */
void Ferry::UseFerry(int customer_id)
{
	/* 1: Wait for ferry to arrive and load */
	printf("Auto %d jonoon\n", customer_id);
	sem_wait(&this->ferry_queue);
	printf("Auto %d sisaan\n", customer_id);
	/* 2: Our turn, board ferry */
	sem_wait(&this->ferry_boarded);
	printf("Auto %d ulos\n", customer_id);
	/* 3: Wait for ferry to arrive at other end and unload */
	/* 4: Inform ferry that we have unloaded */
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
				printf("Lautta laituri\n");
				LoadFerry();
				state = 1;
				break;
			case 1:
				state = 2;
				break;
			case 2:
				printf("Lautta toinen laituri\n");
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
/* Might need re-implementation:
 * waiting = get_count (latch how many vehicles waiting)
 * while(abs(waiting)--)
 * {
 * 		let all latched onboard
 * 		sem_post()
 * }
 */
void Ferry::LoadFerry()
{
	/* Get every waiter on board: release ferry queue */
	/** \todo do we need a block "no more cars allowed in queue"? */
	int vehicles_in = 0,
		vehicles_waiting = -1;
	/* At this point semaphore value is <= 0 */
	while(sem_trywait(&this->ferry_queue) < 0)
	{
		vehicles_waiting++;
		/* If semaphore was 0, release it, and try again
		 * Doesn't matter if someone else snatches semaphore,
		 * simply keep trying until ownership is granted */
		sem_post(&this->ferry_queue);
	}
	printf("Autoja odottamassa %d\n", vehicles_waiting);
	/* Leave semaphore locked ("owned" by ferry) */
	do
	{
		/* Wait until all vehicles have boarded the vessel */
		sem_getvalue(&this->ferry_boarded, &vehicles_in);
		usleep(100);
	} while(vehicles_waiting != abs(vehicles_in));
	printf("Autoja sisassa %d\n", abs(vehicles_in));
}

void Ferry::UnloadFerry()
{
	/* Unload every boarded vehicle */
	while(sem_trywait(&this->ferry_boarded) < 0)
	{
		printf("Autoa ulos\n");
		sem_post(&this->ferry_boarded);
	}
	/* Leave boarded as locked after this */
	/** \todo wait for boarded cars to actually leave the vessel ? */
}


