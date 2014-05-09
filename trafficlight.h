/*
 * trafficlight.h
 *
 *  Created on: 5.5.2014
 *      Author: Ville
 */

#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include <pthread.h>
#include "printer.h"
/* How long it takes to get over crossing */
#define TRAFFIC_LIGHT_CROSS_TIME	1000

class TrafficLight
{
	public:
							TrafficLight();
		virtual 			~TrafficLight();
		void 				TrafficLightWait(int car_id);
	protected:
		pthread_mutex_t		red_light_mutex;
		static const int	traffic_light_len = TRAFFIC_LIGHT_CROSS_TIME;
};

#endif /* TRAFFICLIGHT_H_ */
