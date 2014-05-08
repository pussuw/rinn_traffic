#ifndef randomizerH
#define randomizerH
#include <pthread.h>

class Randomizer
{
	public:
			Randomizer();
			virtual			~Randomizer();
			int				Randomize(int);
	private:
			int				seed;
	protected:
			pthread_mutex_t randomlock;
};

#endif
