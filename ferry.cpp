/*
 * ferry.cpp
 *
 *  Created on: 4.5.2014
 *      Author: Ville
 */

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include "ferry.h"

Ferry::Ferry()
{
    cars_in_ferry = 0;
    cars_in_queue = 0;
    sem_init(&this->ferry_load, 0, 0);
    sem_init(&this->ferry_unload, 0, 0);
    sem_init(&this->ferry_onboard, 0, 0);
    pthread_mutex_init(&this->ferry_queue_mutex, NULL);
}

Ferry::~Ferry()
{
    sem_destroy(&this->ferry_load);
    sem_destroy(&this->ferry_unload);
    sem_destroy(&this->ferry_onboard);
    pthread_mutex_destroy(&this->ferry_queue_mutex);
}

void Ferry::UseFerry(int customer_id)
{
    /* 1: Wait for ferry to arrive and load */
    mycerr("Auto %d, jonottaa lautalle\n", customer_id);
    pthread_mutex_lock(&this->ferry_queue_mutex);
    cars_in_queue++;
    pthread_mutex_unlock(&this->ferry_queue_mutex);
    sem_wait(&this->ferry_load);
    vehicle_loaded.Signal();
    /* 2: Our turn, board ferry */
    mycerr("Auto %d, nousee lautalle\n", customer_id);
    sem_post(&this->ferry_onboard);
    pthread_mutex_lock(&this->ferry_queue_mutex);
    cars_in_queue--;
    pthread_mutex_unlock(&this->ferry_queue_mutex);
    /* 3: Wait for ferry to arrive at other end and unload */
    sem_wait(&this->ferry_unload);
    /* 4: Inform ferry that we have unloaded */
    mycerr("Auto %d, poistuu lautalta\n", customer_id);
    vehicle_unloaded.Signal();
    /* 5: Return from this function -> ferry travel complete !*/
}

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
                mycerr("Lautta saapuu L\n");
                LoadFerry();
	        state = FERRY_D;
	        break;
	    case FERRY_D:
	        mycerr("Lautta saapuu D\n");
	        UnloadFerry();
	        state = FERRY_L;
	        break;
	    }
	}
    }
}

void Ferry::LoadFerry()
{
    /* Get every car on board */
    int vehicles_in = 0;
    int vehicles_in_queue = 0;
    vehicles_in_queue = cars_in_queue;
    cars_in_ferry = 0;
    /* At this point semaphore value is <= 0 */
    while(vehicles_in_queue--)
    {
    	cars_in_ferry++;
	/* If semaphore was 0, release it, and try again
	 * Doesn't matter if someone else snatches semaphore,
	 * simply keep trying until ownership is granted */
        sem_post(&this->ferry_load);
	vehicle_loaded.WaitSignal();
    }

    /* Leave semaphore locked ("owned" by ferry) => no more cars can get in */
    do
    {
        /* If semaphore can be obtained, it means a vehicle is in */
        if(sem_trywait(&this->ferry_onboard) == 0)
        {
	    vehicles_in++;
	}
    } while(cars_in_ferry != vehicles_in);
}

void Ferry::UnloadFerry()
{
    /* See if anyone is aboard */
    if(cars_in_ferry == 0)
    {
        return;
    }
    /* Get every car off board*/
    while(cars_in_ferry--)
    {
        /* Let one car out */
        sem_post(&this->ferry_unload);
        /* Wait for current car to get off board */
        vehicle_unloaded.WaitSignal();
    }
}
