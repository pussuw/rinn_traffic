#include "genericthread.h"
#include <unistd.h>
#include <signal.h>
/** \todo kirjoita kommentit :D */
GenThread::GenThread()
{
	threadID = 0;
}

GenThread::~GenThread()
{
	Terminate(true);
	usleep(200000);
	threadID = 0;
}

void GenThread::Start(void)
{
	if(IsRunning())
		return;
	threadID = 0;
	Terminated = false;
	_threadObj = this;
	pthread_create(&threadID, NULL, _threadProc, (void*)_threadObj);
}

bool GenThread::Terminate(bool Forced)
{
	if(IsRunning() == false)
		return true;

	Terminated = true;
	if(pthread_join(threadID, NULL) == 0)
	{
		threadID = 0;
		return true;
	}

	if(Forced == true && threadID != 0)
	{
		if(pthread_cancel(threadID) == 0)
			return true;
	}

	return false;
}

void *GenThread::_threadProc(void * ptr)
{
	((GenThread*)ptr)->Execute();
	return ((void*)0);
}

bool GenThread::IsRunning(void)
{
	return ((threadID != 0) && (Terminated == false));
}
