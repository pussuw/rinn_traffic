/*
 * ferry.h
 *
 *  Created on: 4.5.2014
 *      Author: Ville
 */

#ifndef FERRY_H_
#define FERRY_H_

#include "genericsignal.h"
#include "genericthread.h"
#include <semaphore.h>
#include <pthread.h>

/** \todo Ferry state (direction) */
typedef enum
{
	FERRY_DIR_L,
	FERRY_DIR_D,
	FERRY_LOADING,
	FERRY_UNLOADING,
}EFerryState;

/* How many ticks to cross the lake */
#define LAKE_CROSS_TICKS 10

class Ferry : public GenThread
{
	public:
							Ferry();
		virtual 			~Ferry();
		void 				UseFerry(int);
		GenSignal *			GetFerryHeartBeat();
	private:
		void 				Execute();
		void 				LoadFerry();
		void 				UnloadFerry();
		GenSignal			vehicle_ready;
		GenSignal			ferry_hearbeat;
	protected:
		static const int	lake_cross_ticks = LAKE_CROSS_TICKS;
		sem_t 				ferry_load; /* Cars waiting at L */
		sem_t				ferry_unload; /* Cars to be unloaded at D */
};

#endif /* FERRY_H_ */
