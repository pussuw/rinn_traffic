/*
 * ferry.h
 *
 *  Created on: 4.5.2014
 *      Author: Ville
 */

#ifndef FERRY_H_
#define FERRY_H_

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

class Ferry : public GenThread
{
	public:
							Ferry();
		virtual 			~Ferry();
		void 				UseFerry(int);
		pthread_cond_t *	GetFerryEvent(void);
	private:
		void 				Execute();
		void 				LoadFerry();
		void 				UnloadFerry();
		pthread_cond_t		ferry_sync_event;
	protected:
		int 				lake_cross_ticks;
		pthread_mutex_t		ferry_sync_mutex;
		sem_t 				ferry_queue; /* Cars waiting at L */
		sem_t				ferry_boarded; /* Cars to be unloaded at D */
};

#endif /* FERRY_H_ */
