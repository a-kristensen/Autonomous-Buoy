/*
 * UART.h
 *
 *  Created on: 12. okt. 2017
 *      Author: Michael
 */

#ifndef IMUTASK_H_
#define IMUTASK_H_
// --- Includes -----//
#include "cmsis_os.h"
#include "../debug/debug.h"
#include "stm32f4xx_hal.h"
#include "IMU.h"
// ---- Defines -----//

#define IMUTASK_DBG
#ifdef IMUTASK_DBG
  #define IMUTask_DbgMsg PrintDbgMsg
#else
  #define IMUTask_DbgMsg
#endif




// ---- Variables ----- //


osThreadId IMUTaskHandle;
struct IMU_s getIMUData();
void StartIMUTask(void const * argument);
void UartSend(char* data, uint length);


#endif /* IMUTASK_H_ */
