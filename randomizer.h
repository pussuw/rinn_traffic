#ifndef randomizerH
#define randomizerH
#include <pthread.h>

class Randomizer
{
	public:
			Randomizer();
			virtual			~Randomizer();
			unsigned int				Randomize(unsigned int);
	private:
			unsigned int				seed;
	protected:
			pthread_mutex_t randomlock;
};

#endif
