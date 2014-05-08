#include "genericthread.h"
#include <unistd.h>
#include <signal.h>
/** \todo kirjoita kommentit :D */
GenThread::GenThread()
{
	threadID = 0;
	pthread_mutex_init(&this->thread_mutex, NULL);
}

GenThread::~GenThread()
{
	Terminate();
	usleep(200000);
	threadID = 0;
	pthread_mutex_destroy(&this->thread_mutex);
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

bool GenThread::Terminate(void)
{
	bool ret = false;
	if(IsRunning() == false)
		return true;
	pthread_mutex_lock(&this->thread_mutex);
	Terminated = true;
	if(pthread_join(threadID, NULL) == 0)
	{
		threadID = 0;
		ret = true;
	}
	pthread_mutex_unlock(&this->thread_mutex);
	return ret;
}

void *GenThread::_threadProc(void * ptr)
{
	((GenThread*)ptr)->Execute();
	return ((void*)0);
}

bool GenThread::IsRunning(void)
{
	bool running = false;
	pthread_mutex_lock(&this->thread_mutex);
	running = ((threadID != 0) && (Terminated == false));
	pthread_mutex_unlock(&this->thread_mutex);
	return running;
}
