/*
 * syncthread.h
 *
 *  Created on: 7.5.2014
 *      Author: Ville
 */

#ifndef SYNCTHREAD_H_
#define SYNCTHREAD_H_

#include "genericsignal.h"
#include "genericthread.h"

class SyncThread : public GenThread
{
	public:
		GenSignal *			GetHeartBeat();
	private:
<<<<<<< HEAD
		GenSignal			hearbeat;
=======
		GenSignal			heartbeat;
>>>>>>> 14650c849ddb6fa9e34d4d4af5c444bc042f6c66
};

#endif /* SYNCTHREAD_H_ */
