/*
 * car.cpp
 *
 *  Created on: 8.5.2014
 *      Author: Atte
 */

#include "car.h"
#include <string>
#include <stdio.h>

Car::Car(unsigned int id, Ferry* ferry_h, TrafficLight* traffic_light_h, 
         RouteManager* routemanager_h)
         : car_id(id), ferry(ferry_h), 
           traffic_light(traffic_light_h),
           routemanager(routemanager_h), route()
{
  routemanager->GetRoute( &route );
  pos_route = 0;
  pos_block = 0;
  
  char start;
  switch (route.at(0))
  {
    case BLOCK_A:
    {
      start = 'A';
      break;
    }
    case BLOCK_B:
    {
      start = 'B';
      break;
    }
    default:
      break;
  }

  char end;
  switch (route.at(route.size()-1))
  {
    case BLOCK_C:
    {
      end = 'C';
      break;
    }
    case BLOCK_D:
    {
      end = 'D';
      break;
    }
    default:
      break;
  }
  printf("Auto luotu %i, reitti %c->%c\n", car_id, start, end);
}

Car::~Car()
{
}

void Car::Execute()
{
  while(!Terminated)
  {
    heartbeat.WaitSignal();
    //take the block and act on it
    if( pos_block < TICKS_PER_BLOCK )
    {
      pos_block++;
      continue;
    }
    pos_block = 0;
    pos_route++;
    //move the car to new routeblock
    switch (route.at(pos_route))
    {
      case BLOCK_A:
      case BLOCK_B:
      case BLOCK_ROAD:
      case BLOCK_L:
      {
        //do nothing
        break;
      }
      //the destroy case
      case BLOCK_C:
      {
        printf("Auto %u, poistuu C\n", car_id);
        Terminate();
        break;
      }
      case BLOCK_D:
      {
        //derp
        printf("Auto %u, poistuu D\n", car_id);
        Terminate();
        break;
      }
      case BLOCK_TRAFFICL:
      {
        traffic_light->TrafficLightWait(*&this->car_id);
        break;
      }
      case BLOCK_FERRY:
      {
        ferry->UseFerry(*&this->car_id);
        break;
      }
      default:
        break;
    }
    pos_block++;
  }
}
