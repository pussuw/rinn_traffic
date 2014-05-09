/* Rinnakkaisuus 2014
pussuw, r00pe, xzr
*/

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
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
#include "trafficlight.h"
#include "routemanager.h"
#include "ferry.h"
#include "car.h"
#include "randomizer.h"

//delay between every tick in milliseconds
const unsigned int TICK_DELAY = 100;
const unsigned int LIMIT_CARS_PASSED = 100;
const unsigned int MAX_SPAWN_DELAY = 20;

volatile unsigned int g_cars_passed = 0;
volatile unsigned int g_cars_created = 0;


void server_loop()
{
  std::vector<Car*> children;

  //initialize ferry
  Ferry ferry1;
  ferry1.Start();
  TrafficLight traffic_light;
  Randomizer randomizer;
  RouteManager routemanager(&randomizer);

  unsigned int spawn_delay = randomizer.Randomize(MAX_SPAWN_DELAY);
  unsigned int car_id = 0;

  Car* tmp;
  do 
  {
    usleep(TICK_DELAY);
    //send signal to move
    ferry1.GetHeartBeat()->Signal();

    if( spawn_delay == 0 )
    {
      if(g_cars_created < LIMIT_CARS_PASSED)
      {
          tmp = new Car(car_id, &ferry1, &traffic_light, &routemanager);
          tmp->Start();
          children.push_back(tmp);
          tmp = 0;
          spawn_delay = randomizer.Randomize(MAX_SPAWN_DELAY);
          ++car_id;
          g_cars_created++;
      }
    }
    else
    {
      spawn_delay--;
    }
    for( std::vector<Car*>::iterator it = children.begin(); it != children.end(); )
    {
      if( (*it)->IsRunning() )
      {
        (*it)->GetHeartBeat()->Signal();
        it++;
      }
      else
      {
        delete *it;
        it = children.erase(it);
        g_cars_passed++;
      }
    }
  } while( g_cars_passed < LIMIT_CARS_PASSED );
}

int main(void)
{
  server_loop();
  return true;
}

