/* Rinnakkaisuus 2014
pussuw, r00pe, xzr
*/

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "genericthread.h"
#include "syncthread.h"
#include "genericsignal.h"
#include "ferry.h"

//delay between every tick in milliseconds
const unsigned int TICK_DELAY = 100000;
const unsigned int LIMIT_CARS_PASSED = 100;
volatile unsigned int g_cars_passed = 0;

//pthread initialization
pthread_mutex_t printerlock = PTHREAD_MUTEX_INITIALIZER;

void printer(std::string printstr)
{
pthread_mutex_lock(&printerlock);
fprintf(stderr, printstr.c_str());
pthread_mutex_lock(&printerlock);

}

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
    //send signal to move
    ferry1.GetHeartBeat()->Signal();
	// call for random generated number here
/*    if( g_random % 15 == 0 )
    {
      printf("Auto luotu NN, reitti X->Y\n");
      //spawn a car, give it a route, add it to children
    }
*/
#if 0
    for( unsigned int i = 0; i < children.size(); ++i )
    {
      //children.at(i)->Execute();
    }
#endif
  } while( g_cars_passed < LIMIT_CARS_PASSED );
}

int main(void)
{
  std::string printstr;
  //initialize routes

  //server loop
  setvbuf (stdout, NULL, _IONBF, 1024);
  server_loop();

  return 0;
}

