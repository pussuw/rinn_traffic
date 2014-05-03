#ifndef observerH
#define observerH

#include <vector>
#include <list>
#include "genericthread.cpp"

class Observer : GenThread
{
	public:
		Observer();
		virtual 		~Observer();
		bool				Add(GenThread* thread);
		bool				Remove(GenThread* thread);
		void 				Tick();
		
	private:
		std::vector<GenThread*> children;
		
 };

#endif
