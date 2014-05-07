/* v1 :D */

#include "randomizer.h"
#include <time.h>

Randomizer::Randomizer()
{
	//initialize seed for future use
    srand( (unsigned) time(NULL));
	unsigned int random = 0;
	pthread_mutex_init(&this->randomlock, NULL);
}

Randomizer::~Randomizer()
{
	pthread_mutex_destroy(&this->randomlock);
}

void Randomizer::Randomize()
{
	pthread_mutex_lock(&this->randomlock);
	//generate a random number
	g_random = rand_r() % (RAND_MAX);
	pthread_mutex_unlock(&this->randomlock);
}