/*
 * car.h
 *
 *  Created on: 8.5.2014
 *      Author: Atte
 */
#ifndef CAR_H_
#define CAR_H_

#include <vector>
#include "routemanager.h"
#include "ferry.h"
#include "trafficlight.h"

class Car : public SyncThread
{
	public:
                Car(unsigned int id, Ferry* ferry_h, TrafficLight* traffic_light_h, RouteManager* routemanager_h);
		virtual 	  ~Car();
	private:
		void 				Execute();
	protected:
		static const unsigned int	TICKS_PER_BLOCK = 2;
    
    unsigned int car_id;
    Ferry* ferry;
    TrafficLight* traffic_light;
    RouteManager* routemanager;
    
    unsigned int pos_route;
    unsigned int pos_block;

    std::vector<ERouteBlock> route;
};

#endif
