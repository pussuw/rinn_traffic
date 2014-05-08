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
                Car(unsigned int id, Ferry::Ferry* ferry_h, TrafficLight::TrafficLight* traffic_light_h);
		virtual 	  ~Car();
	private:
		void 				Execute();
	protected:
		static const unsigned int	TICKS_PER_BLOCK = 2;
    
    unsigned int car_id;
    Ferry::Ferry* ferry;
    TrafficLight::TrafficLight* traffic_light;
    
    unsigned int pos_route;
    unsigned int pos_block;

    std::vector<ERouteBlock> route;
};

#endif
