/*
 * ferry.h
 *
 *  Created on: 4.5.2014
 *      Author: Ville
 */

#ifndef FERRY_H_
#define FERRY_H_

#include "genericsignal.h"
#include "syncthread.h"
#include <semaphore.h>
#include <pthread.h>

/** \todo Ferry state (direction) */
typedef enum
{
	FERRY_L,
	FERRY_D
}EFerryState;

/* How many ticks to cross the lake */
#define LAKE_CROSS_TICKS 10

class Ferry : public SyncThread
{
	public:
							Ferry();
		virtual 			~Ferry();
		void 				UseFerry(int);
	private:
		void 				Execute();
		void 				LoadFerry();
		void 				UnloadFerry();
		GenSignal			vehicle_unloaded;
		GenSignal                       vehicle_loaded;
	protected:
		static const int	lake_cross_ticks = LAKE_CROSS_TICKS;
		int                             cars_in_queue;
		int                             cars_in_ferry;
		sem_t 				ferry_load; /* Cars waiting at L */
		sem_t                           ferry_onboard;
		sem_t				ferry_unload; /* Cars to be unloaded at D */
		pthread_mutex_t                 ferry_queue_mutex;
};

#endif /* FERRY_H_ */
