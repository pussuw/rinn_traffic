/*
 * trafficlight.cpp
 *
 *  Created on: 5.5.2014
 *      Author: Ville
 */

#include <stddef.h>
#include <stdio.h>
#include "trafficlight.h"
#include <unistd.h>

TrafficLight::TrafficLight()
{
	pthread_mutex_init(&this->red_light_mutex, NULL);
}

TrafficLight::~TrafficLight()
{
	pthread_mutex_destroy(&this->red_light_mutex);
}

void TrafficLight::TrafficLightWait(int car_id)
{
	/* Check if light is green, if not, stop here */
	printf("Auto %d, saapui liikennevaloihin\n", car_id);
	pthread_mutex_lock(&this->red_light_mutex);
	/* Were through */
	printf("Auto %d, risteysalueella\n", car_id);
	usleep(traffic_light_len);
	/* Were over, release mutex */
	printf("Auto %d, poistui liikennevaloista\n", car_id);
	pthread_mutex_unlock(&this->red_light_mutex);
}
