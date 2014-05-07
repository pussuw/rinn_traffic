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
		GenSignal			hearbeat;
};

#endif /* SYNCTHREAD_H_ */
