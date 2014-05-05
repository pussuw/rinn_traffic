/*
 * genericsignal.cpp
 *
 *  Created on: 5.5.2014
 *      Author: Ville
 */

#include "genericsignal.h"

GenSignal::GenSignal()
{
	signaled = false;
	pthread_mutex_init(&this->signal_guard, NULL);
	pthread_cond_init(&this->signal, NULL);
}

GenSignal::~GenSignal()
{
	pthread_mutex_destroy(&this->signal_guard);
	pthread_cond_destroy(&this->signal);
	signaled = false;
}

void GenSignal::WaitSignal(void)
{
	pthread_mutex_lock(&this->signal_guard);
	while(!signaled)
	{
		pthread_cond_wait(&this->signal,
						  &this->signal_guard);
	}
	signaled = false;
	pthread_mutex_unlock(&this->signal_guard);
}

void GenSignal::Signal(void)
{
	pthread_mutex_lock(&this->signal_guard);
	signaled = true;
	pthread_cond_signal(&this->signal);
	pthread_mutex_unlock(&this->signal_guard);
}


