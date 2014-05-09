/*
 * routemanager.cpp
 *
 *  Created on: 7.5.2014
 *      Author: Atte
 */

#include "routemanager.h"

#include <stdio.h>
#include <vector>
#include <pthread.h>

#if 0
#include "random.h"
#endif
 
RouteManager::RouteManager(Randomizer* randomizer_h): routes(), randomizer(randomizer_h)
{
  pthread_mutex_init(&this->signal_guard, NULL);
  ConstructRoutes();
}

RouteManager::~RouteManager()
{
  pthread_mutex_destroy(&this->signal_guard);
}

void RouteManager::GetRoute(std::vector<ERouteBlock>* route)
{
  pthread_mutex_lock(&this->signal_guard);
  
  *route = routes.at(randomizer->Randomize((unsigned int)ROUTE_B_D));
  
  pthread_mutex_unlock(&this->signal_guard);
}

void RouteManager::ConstructRoutes()
{
  std::vector<ERouteBlock> empty;
  
  for( int i = ROUTE_A_C; i <= ROUTE_B_D; ++i )
  {
    routes.push_back(empty);
    switch (i)
    {
      case ROUTE_A_C:
      {
        routes.at(i).push_back(BLOCK_A);
        AddRoads( routes.at(i), 4);
        routes.at(i).push_back(BLOCK_TRAFFICL);
        AddRoads( routes.at(i), 7);
        routes.at(i).push_back(BLOCK_C);
      }
      case ROUTE_A_D:
      {
        routes.at(i).push_back(BLOCK_A);
        AddRoads( routes.at(i), 4);
        routes.at(i).push_back(BLOCK_TRAFFICL);
        AddRoads( routes.at(i), 5);
        routes.at(i).push_back(BLOCK_L);
        routes.at(i).push_back(BLOCK_FERRY);
        routes.at(i).push_back(BLOCK_D);
      }
      case ROUTE_B_C:
      {
        routes.at(i).push_back(BLOCK_B);
        AddRoads( routes.at(i), 1);
        routes.at(i).push_back(BLOCK_TRAFFICL);
        AddRoads( routes.at(i), 7);
        routes.at(i).push_back(BLOCK_C);
      }
      case ROUTE_B_D:
      {
        routes.at(i).push_back(BLOCK_B);
        AddRoads( routes.at(i), 1);
        routes.at(i).push_back(BLOCK_TRAFFICL);
        AddRoads( routes.at(i), 5);
        routes.at(i).push_back(BLOCK_L);
        routes.at(i).push_back(BLOCK_FERRY);
        routes.at(i).push_back(BLOCK_D);
      }
#if 0
      case R_ROUTE1:
      {
      }
      case R_ROUTE2:
      {
      }
      case R_ROUTE3:
      {
      }
      case R_ROUTE4:
      {
      }
#endif
      default:
      {
        break;
      }
    }
  }
  return;
}

void RouteManager::AddRoads(std::vector<ERouteBlock>& route, unsigned int amount)
{
  for(unsigned int i = 0; i < amount; ++i )
  {
    route.push_back(BLOCK_ROAD);
  }
  return;
}
