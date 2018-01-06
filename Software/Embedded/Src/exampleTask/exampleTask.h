/*
 * exampleTask.h
 *
 *  Created on: 14. okt. 2017
 *      Author: Neophyte
 */

#ifndef EXAMPLETASK_EXAMPLETASK_H_
#define EXAMPLETASK_EXAMPLETASK_H_

#include "cmsis_os.h"
#include "../debug/debug.h"

//with these two, the task can be started from another file
osThreadId ExampleTaskHandle;
void StartExampleTask(void const * argument);


#endif /* EXAMPLETASK_EXAMPLETASK_H_ */
