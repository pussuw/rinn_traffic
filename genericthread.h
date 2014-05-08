#ifndef genericthreadH
#define genericthreadH
#include <pthread.h>
#include <stdbool.h>

class GenThread
{
	public:
		GenThread(); //create only
		virtual 		~GenThread();
		void 			Start(void);
		virtual bool    Terminate(void);
		bool 			IsRunning(void);
		int 			ExitCode;
	private:
		virtual void 	Execute() = 0;
	protected:
		bool 			Terminated;
		static void 	*_threadProc(void*);
		GenThread 		*_threadObj;
		pthread_t    	threadID;
		pthread_mutex_t	thread_mutex;
 };

#endif
