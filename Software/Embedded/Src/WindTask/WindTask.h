/*
 * WindTask.h
 *
 *  Created on: 14. okt. 2017
 *      Author: Michael Aarestrup
 */

#ifndef WINDTASK_WINDTASK_H_
#define WINDTASK_WINDTASK_H_

#include "cmsis_os.h"
#include "../debug/debug.h"



struct WindSensor_s
{
	float direction;
	float speed;
	float temp;
};

//with these two, the task can be started from another file
osThreadId WindTaskHandle;
struct WindSensor_s getWindSensorData();
void StartWindTask(void const * argument);


#endif /* WINDTASK_WINDTASK_H_ */
