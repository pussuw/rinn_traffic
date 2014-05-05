/*
 * genericsignal.h
 *
 *  Created on: 5.5.2014
 *      Author: Ville
 */

#ifndef GENERICSIGNAL_H_
#define GENERICSIGNAL_H_

#include <stdbool.h>
#include <pthread.h>

class GenSignal
{
	public:
						GenSignal();
		virtual 		~GenSignal();
		void 			WaitSignal(void);
		void			Signal(void);
	protected:
		bool			signaled;
		pthread_cond_t	signal;
		pthread_mutex_t	signal_guard;
};


#endif /* GENERICSIGNAL_H_ */
