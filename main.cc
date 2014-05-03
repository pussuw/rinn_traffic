/* Rinnakkaisuus 2014
 pussuw, r00pe, xzr
*/

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

/*
#include "random.hh"
#include "car.hh"
#include "ferry.hh"
#include "trafficlight.hh"
*/

//delay between every tick in milliseconds
const unsigned int TICK_DELAY = 100000;
const unsigned int LIMIT_CARS_PASSED = 100;

volatile unsigned int G_CARS_PASSED = 0;

enum M_TYPE = { CAR, FERRY };
enum M_ACTION = { CREATE, CROSS_ENTER, CROSS, CROSS_EXIT, FERRY_ARRIVE, FERRY_QUEUE, FERRY_ENTER, FERRY_EXIT, EXIT };


void server_loop()
{
  //if x time has passed, spawn a car, give it a route and send it off
  //then reset the counter until next car
  
  //on every cycle
  //delay 
  //send timer tick to all child threads which tells them to do their thing
  
  //use some rand for this stuff later, for now a static value
  unsigned int spawn_timer = 5;
  do 
  {
    usleep(TICK_DELAY);
    //send signal to move
    
    spawn_timer--;
    
    if( spawn_timer == 0 )
    {
      //spawn a car, give it a route, all the cool jazz
      spawn_timer = 5;
    }
    
    std::cout << "herpderp" << std::endl;
  } while( G_CARS_PASSED < LIMIT_CARS_PASSED );
}

int main() {
  //initialize routes
  
  //server loop
  
  server_loop();

  
  return 0;
}