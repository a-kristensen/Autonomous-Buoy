/*
 * GPSTask.c
 *
 *  Created on: 30. okt. 2017
 *      Author: Neophyte
 */

#include "WindTask.h"

#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//remember to always include the file FreeRTOS.h before any other API headers
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
/*
*/

//include additional header files here


//do not make calls to PrintDbgMsg. Use ExampleTask_DbgMsg instead !
//this can disable debug messages for each module individually

#define WINDTASK_DBG
#ifdef WINDTASK_DBG
  #define WindTask_DbgMsg PrintDbgMsg
#else
  #define WindTask_DbgMsg
#endif

#define MAX_BUFFER 40

enum readMode {
	WAITFOR_LF,
	WAITFOR_CR,
	WAITFOR_$
};

//Windsensor data struct
struct WindSensor_s windSensor;

SemaphoreHandle_t xSemaphoreWindData;

unsigned char readWind;

QueueHandle_t xQueueWind;

//void UART4_IRQHandler(void)
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
  //HAL_GPIO_TogglePin(GPIOB, LD2_Pin);
  xQueueSendToBackFromISR(xQueueWind, &readWind, NULL);
  HAL_UART_Receive_IT(&huart2, &readWind, 1);
  /* USER CODE END USART2_IRQn 1 */
}


/*
 * @brief: returns the newest datastruct containing WindSensor data
 */
struct WindSensor_s getWindSensorData()
{
	struct WindSensor_s temp;
	if(xSemaphoreTake(xSemaphoreWindData, 100) == pdTRUE)
	{
		temp = windSensor;
		xSemaphoreGive(xSemaphoreWindData);

	}
	return temp;
}


/* "@brief Interprets messages from the bouys windsensor
 *  @param data: The data recieved from the windsensor as a array of char
 *  @param length: The length of the data recieved from the windsensor
 *  @retval: 0 if succes, 1 if command is not used, -1 otherwise
 */
int windInterPreter(unsigned char data[], uint length)
{
	if(data[1] == 'P')// Recieved PLC command which are not used
	{
		return 1;
	}

	// Calculate Checksum
	uint checksum = 0;
	for(int i = 1; i < length - 3; i++)
	{
		checksum ^= data[i];
	}

	//Find the recieved Checksum;
	uint8_t recChk = (data[length-2] <= '9' ? data[length-2] - '0' : toupper(data[length-2]) - 'A' + 10) << 4;
	recChk |= data[length-1] <= '9' ? data[length-1] - '0' : toupper(data[length-1]) - 'A' + 10;

	if(recChk == checksum) // Checksum is correct
	{
		if(xSemaphoreTake(xSemaphoreWindData, 100) == pdTRUE)
		{
			char buf[5];
			if(data[1] == 'I') // Wind direction message
			{
				memcpy((void*)buf, (void*)&data[7],5); // Copy values from data string
				windSensor.direction = strtof(buf, NULL);

				memcpy((void*)buf, (void*)&data[15],5); // Copy values from data string
				windSensor.speed = strtof(buf, NULL);

				xSemaphoreGive(xSemaphoreWindData);
				return 0;
			}

			if(data[1] == 'W') // Wind temperature recieved
			{
				memcpy((void*)buf, (void*)&data[9],5); // Copy values from data string
				windSensor.temp = strtof(buf, NULL);

				xSemaphoreGive(xSemaphoreWindData);
				return 0;
			}

			xSemaphoreGive(xSemaphoreWindData);
		}


		return -1;
	}
	else
	{
	    return -1;
	}

}

void StartWindTask(void const * argument)
{
  //here you should do initialization
  unsigned char b[MAX_BUFFER];
  uint msgLen = 0;
  unsigned char read;
  uint state = 1;
  int recStatus = 1;
  xQueueWind = xQueueCreate(10, sizeof(char));

  //MX_UART4_Init();
  MX_USART2_UART_Init();

  HAL_UART_Receive_IT(&huart2, &readWind, 1);

  xSemaphoreWindData = xSemaphoreCreateMutex();
  if(xSemaphoreWindData == NULL)
  	{
  	  //TODO error. Should not reach here
    }


  //this loop runs forever
  //this is where the is work done in a thread
  while(1)
  {
	//recStatus = HAL_UART_Receive(&huart2, &read, 1, 10);
	  recStatus = xQueueReceive(xQueueWind, &read, 500);
	if(recStatus == pdTRUE )
	{

		switch(state) // Reads one byte at a time until CR/LF (\r\n) is found
		{
		case WAITFOR_$:
			if(readWind == '$')
			{
				b[msgLen] = read;
				msgLen++;
				state = WAITFOR_CR;
			}
			break;
		case WAITFOR_CR:
			if(readWind == '\r'){ // Read \r
				state = WAITFOR_LF;
			} else if(msgLen < MAX_BUFFER)
			{
				b[msgLen] = read;
				msgLen++;
			} else // Exeeded MAX_BUFFER size before reading \n. ---> Try again
			{
				msgLen = 0;
			}
			break;
		case WAITFOR_LF:
			if(readWind == '\n'){ //Read \n meaning end of message is found

				//Interpret message
				if(windInterPreter(b,msgLen) >= 0)
				{
					// Correct message recieved
					HAL_GPIO_TogglePin(GPIOB, LD2_Pin); // Show that task is Alive
				}

			}
			state = WAITFOR_$;
			memset(b, 0, sizeof(b));
			msgLen = 0;
			break;
		}
	}
	else
	{
		osDelay(10);
	}
	osDelay(1);

  }

}
