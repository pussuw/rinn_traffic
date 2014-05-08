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

int Randomizer::Randomize(int range)
{
	int random;
	pthread_mutex_lock(&this->randomlock);
	//generate a random number
	random = rand_r(&seed) % (range);
	pthread_mutex_unlock(&this->randomlock);
	return random;
}
