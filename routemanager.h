/*
 * routemanager.h
 *
 *  Created on: 7.5.2014
 *      Author: Atte
 */
#ifndef ROUTEMANAGER_H_
#define ROUTEMANAGER_H_

#include "genericthread.h"
#include "genericsignal.h"
#include "randomizer.h"
#include <vector>
#include <pthread.h>

typedef enum
{
  BLOCK_A,
  BLOCK_B,
  BLOCK_C,
  BLOCK_D,
  BLOCK_L,
  BLOCK_TRAFFICL,
  BLOCK_ROAD,
  BLOCK_FERRY
}ERouteBlock;

typedef enum
{
  ROUTE_A_C,
  ROUTE_A_D,
  ROUTE_B_C,
  ROUTE_B_D
}ERoute;

class RouteManager
{
  public:
    RouteManager(Randomizer* randomizer_h);
    virtual ~RouteManager();
    
    //fills a vector with routeblocks for a car to use
    void GetRoute(std::vector<ERouteBlock>* route);
  private:
    void ConstructRoutes();
    void AddRoads(std::vector<ERouteBlock>& route, unsigned int amount);
    std::vector<std::vector<ERouteBlock> > routes;
    Randomizer* randomizer;
    pthread_mutex_t	signal_guard;
};

#endif
