/* v1 :D */
#include <stdlib.h>
#include "randomizer.h"
#include <time.h>

Randomizer::Randomizer()
{
	//initialize seed for future use
    seed = time(NULL);
	pthread_mutex_init(&this->randomlock, NULL);
}

Randomizer::~Randomizer()
{
	pthread_mutex_destroy(&this->randomlock);
}

unsigned int Randomizer::Randomize(unsigned int range)
{
	unsigned int random;
	pthread_mutex_lock(&this->randomlock);
	//generate a random number
	random = (unsigned int)rand_r(&seed) % (range);
	pthread_mutex_unlock(&this->randomlock);
	return random;
}
