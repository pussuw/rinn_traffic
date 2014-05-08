/*
 * syncthread.cpp
 *
 *  Created on: 7.5.2014
 *      Author: Ville
 */

#include "syncthread.h"
#include <unistd.h>

SyncThread::~SyncThread()
{
	Terminate();
}

bool SyncThread::Terminate(void)
{
	bool ret = false;
	if(IsRunning() == false)
		return true;
	pthread_mutex_lock(&this->thread_mutex);
	Terminated = true;
	this->heartbeat.Signal();
	if(pthread_join(threadID, NULL) == 0)
	{
		threadID = 0;
		ret = true;
	}
	pthread_mutex_unlock(&this->thread_mutex);
	return ret;
}

GenSignal *	SyncThread::GetHeartBeat()
{
	return &this->heartbeat;
}
