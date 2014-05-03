#include "observer.h"


Observer::Observer()
{
	threadID = 1;
}

Observer::~Observer()
{
	Terminate(true);
	usleep(200000);
}

void Observer::Add(GenThread::GenThread* thread)
{
	children.push_back(thread);
}

void Observer::Remove(GenThread::GenThread* thread)
{
	children.erase(std::remove(children.begin(), children.end(), thread), children.end());
}

void Observer::Tick()
{
	for( unsigned int i = 0; i < children.size(); ++i )
	{
		//children.at(i)->AWAKENCTHULHU;
	}
}