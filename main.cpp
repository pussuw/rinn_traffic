/* Rinnakkaisuus 2014
 pussuw, r00pe, xzr
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include "genericthread.h"
#include <unistd.h>
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
  
  std::vector<GenThread*> children;
  
  //initialize ferry
  
  //use some rand for this stuff later, for now a static value
  unsigned int spawn_timer = 5;
  do 
  {
    usleep(TICK_DELAY);
    //send signal to move
    
    spawn_timer--;
    
    if( spawn_timer == 0 )
    {
      //spawn a car, give it a route, add it to children
      spawn_timer = 5;
    }
    
    for( unsigned int i = 0; i < children.size(); ++i )
    {
      children.at(i)->Execute();
    }
    
    std::cout << "herpderp" << std::endl;
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
#include <stdlib.h>
int main(void)
{
	unsigned int spawn_timer = 100;
	Ferry ferry;
	srand(47);
	setvbuf (stdout, NULL, _IONBF, 1024);
	ferry.Start();
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

	//server_loop();
	while(ferry.IsRunning())
	{

		    usleep(TICK_DELAY);
		    //send signal to move

		    spawn_timer--;

		    if( spawn_timer == 0 )
		    {
		      //spawn a car, give it a route, all the cool jazz
		      spawn_timer = 100;
		      ferry.UseFerry((rand() % 1000));
		    }

	}
	return 0;
}
