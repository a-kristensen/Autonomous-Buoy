/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


/* USER CODE BEGIN Includes */     
#include <stdio.h>
#include "debug/debug.h"
#include "SPITask/SPITask.h"
#include "Remotetask/RemoteTask.h"
#include "exampleTask/exampleTask.h"
#include "GPSTask/GPSTask.h"
#include "WindTask/WindTask.h"
#include "IMUTask/IMUTask.h"
#include "ControlTask/ControlTask.h"
#include "iwdgTask/iwdgTask.h"
#include "Eeprom/EepromTask.h"

/* USER CODE END Includes */


/* Variables -----------------------------------------------------------------*/

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */


  /* Create the thread(s) */

  //osThreadDef(ExampleTask, StartExampleTask, osPriorityNormal, 0, 128);
  //ExampleTaskHandle = osThreadCreate(osThread(ExampleTask), NULL);


  /* USER CODE BEGIN RTOS_THREADS */

  osThreadDef(DebugTask, StartDebugTask, osPriorityNormal, 0, 256);
  DebugTaskHandle = osThreadCreate(osThread(DebugTask), NULL);


  osThreadDef(SPITask, StartSPITask, osPriorityNormal, 0, 128);
  SPITaskHandle = osThreadCreate(osThread(SPITask), NULL);


  osThreadDef(RemoteTask, StartRemoteTask, osPriorityHigh, 0, 256);
  RemoteTaskHandle = osThreadCreate(osThread(RemoteTask), NULL);


  osThreadDef(GPSTask, StartGPSTask, osPriorityNormal, 0, 1000);
  GPSTaskHandle = osThreadCreate(osThread(GPSTask), NULL);


  osThreadDef(IMUTask, StartIMUTask, osPriorityNormal, 0, 512);
  IMUTaskHandle = osThreadCreate(osThread(IMUTask), NULL);


  osThreadDef(WindTask, StartWindTask, osPriorityNormal, 0, 512);
  WindTaskHandle = osThreadCreate(osThread(WindTask), NULL);


  osThreadDef(ControlTask, StartControlTask, osPriorityNormal, 0, 512);
  ControlTaskHandle = osThreadCreate(osThread(ControlTask), NULL);



  osThreadDef(IwdgTask, StartIwdgTask, osPriorityNormal, 0, 128);
  IwdgTaskHandle = osThreadCreate(osThread(IwdgTask), NULL);


  osThreadDef(EepromTask, StartEepromTask, osPriorityNormal, 0, 128);
  EepromTaskHandle = osThreadCreate(osThread(EepromTask), NULL);


  /* USER CODE END RTOS_THREADS */


  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
