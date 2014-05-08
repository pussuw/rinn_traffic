/*
 * syncthread.cpp
 *
 *  Created on: 7.5.2014
 *      Author: Ville
 */

#include "syncthread.h"

GenSignal *	SyncThread::GetHeartBeat()
{
	return &this->heartbeat;
}
