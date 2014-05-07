#ifndef randomizerH
#define randomizerH
#include <pthread.h>

class Randomizer
{
	public:
			Randomizer();
			virtual			~Randomizer();
			int				Randomize();
	
	private:
			int				seed;
			int				g_random;
	protected:
			pthread_mutex_t randomlock;

			
};

#endif