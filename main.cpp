/* Rinnakkaisuus 2014
 pussuw, r00pe, xzr
*/

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <list>
#include <unistd.h>
#include <pthread.h>
#include "genericthread.h"
#include "genericsignal.h"
#include "ferry.h"



/*
#include "random.hh"
#include "car.hh"
#include "ferry.hh"
#include "trafficlight.hh"
*/

//delay between every tick in milliseconds
const unsigned int TICK_DELAY = 100000;
const unsigned int LIMIT_CARS_PASSED = 100;

//pthread initialization
pthread_mutex_t randomizer = PTHREAD_MUTEX_INITIALIZER;

unsigned int random = 0;
volatile unsigned int g_cars_passed = 0;
#if 0
enum M_TYPE { CAR, FERRY };
enum M_ACTION { CREATE, CROSS_ENTER, CROSS, CROSS_EXIT, FERRY_ARRIVE, FERRY_QUEUE, FERRY_ENTER, FERRY_EXIT, EXIT };
#endif

void server_loop()
{
  //if x time has passed, spawn a car, give it a route and send it off
  //then reset the counter until next car
  
  //on every cycle
  //delay 
  //send timer tick to all child threads which tells them to do their thing
#if 0
  std::vector<GenThread*> children;
#endif
  //initialize ferry
  Ferry ferry1;
  ferry1.Start();


  do 
  {
    usleep(TICK_DELAY);
	//generate a random number for car spawn
	pthread_mutex_lock(&randomizer);
	random = rand() % (2000000);
	pthread_mutex_unlock(&randomizer);
    //send signal to move
    ferry1.GetFerryHeartBeat();
    
    if( random % 7 == 0 )
    {
      //spawn a car, give it a route, add it to children
    }
#if 0
    for( unsigned int i = 0; i < children.size(); ++i )
    {
      //children.at(i)->Execute();
    }
#endif
  } while( g_cars_passed < LIMIT_CARS_PASSED );
}

#if 0
class MainThread : public GenThread
{
	void Execute()
	{
		while(!Terminated)
		{
			printf("Hello\n");
			sleep(1);
		}
	}
};
#endif
int main(void)
{
//initialize seed for future use
srand( (unsigned) time(NULL));
#if 0
	int del = 10;
	MainThread test;
	test.Start();
	while(del--)
	{
		sleep(1);
	}
	del = 10;
	while(del--)
	{
		sleep(1);
	}
	test.Terminate(true);
#endif
	//initialize routes

	//server loop

	server_loop();

	return 0;
}
