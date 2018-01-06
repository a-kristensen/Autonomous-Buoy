/*
 * iwdgTask.h
 *
 *  Created on: 14. okt. 2017
 *      Author: Neophyte
 */

#ifndef IWDGTASK_IWDGTASK_H_
#define IWDGTASK_IWDGTASK_H_

#include "cmsis_os.h"
#include "../debug/debug.h"

//with these two, the task can be started from another file
osThreadId IwdgTaskHandle;
void StartIwdgTask(void const * argument);


#endif /* IWDGTASK_IWDGTASK_H_ */
