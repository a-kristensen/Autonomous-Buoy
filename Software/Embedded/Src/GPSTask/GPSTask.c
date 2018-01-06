/*
 * GPSTask.c
 *
 *  Created on: 30. okt. 2017
 *      Author: Neophyte
 */

#include "GPSTask.h"

#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//remember to always include the file FreeRTOS.h before any other API headers
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

//include additional header files here


//do not make calls to PrintDbgMsg. Use ExampleTask_DbgMsg instead !
//this can disable debug messages for each module individually

#define GPSTASK_DBG
#ifdef GPSTASK_DBG
  #define GPSTask_DbgMsg PrintDbgMsg
#else
  #define GPSTask_DbgMsg
#endif

#define MAX_BUFFER 	   128
#define MAX_PREP 	   150


enum readMode {
	WAITFOR_LF,
	WAITFOR_CR,
	WAITFOR_$
};

//char* prepData;
char prepData[MAX_PREP];
int prepLength;
char *ptrBuff;
char* ptrprepData;
//char testMessage[] = {"$GPRMC,,V,,,,,,,,,,N*53\r\n"};

struct nmea_data_s gps_data;
SemaphoreHandle_t xSemaphoreGPSData;

unsigned char readGPS;

QueueHandle_t xQueueGPS;

//void USART2_IRQHandler(void)
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  //HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  xQueueSendToBackFromISR(xQueueGPS, &readGPS, NULL);
  /* USER CODE BEGIN USART2_IRQn 1 */
  //HAL_GPIO_TogglePin(GPIOB, LD2_Pin);
  HAL_UART_Receive_IT(&huart4, &readGPS, 1);
  /* USER CODE END USART2_IRQn 1 */
}

/*
 * @brief: returns the newest datastruct containing GPS data
 */
struct nmea_data_s getGPSData()
{
	struct nmea_data_s temp;
	if(xSemaphoreTake(xSemaphoreGPSData, 100) == pdTRUE)
	{
		temp = gps_data;
		xSemaphoreGive(xSemaphoreGPSData);

	}
	return temp;
}



/*
 * @brief: Parses af GPRMC message and updates the correct data fields in the gps_data struct
 */
void ParseRMC()
{
  int i = 0;
  float f_temp;
  int sign;
  int degs;

  ptrBuff = strtok_r(prepData,",",&ptrprepData);
  if(xSemaphoreTake(xSemaphoreGPSData, 100) == pdTRUE)
  {
	  while(ptrBuff && i<12)
	  {
		  switch(i){

			  case 1://time in RMC sentence, raw format, as float
					gps_data.time = strtof(ptrBuff, NULL);
			  break;

			  case 2://Fix status
					gps_data.fix_valid = strcmp(ptrBuff, "A") ? GPS_FALSE:GPS_TRUE;
			  break;

			  case 3://latitude field in RMC sentence
					f_temp = strtof(ptrBuff, NULL);
					ptrBuff = strtok_r(NULL,",",&ptrprepData);
					i++;

					//these next few lines convert
					//degs and mins to decimal degree seconds
					sign = strcmp(ptrBuff,"N") ? -1:1;  //create a sign multiplier from N/S
					degs = (int)f_temp/100;   //grab the whole number of degrees
					f_temp -= (degs*100);     //remove the degrees from the calculation
					gps_data.lat_dds = sign*((f_temp/60)+degs);  //calculate decimal degrees from remaining minutes, then add back degrees and apply the sign
			  break;

			  case 5:
					f_temp = strtof(ptrBuff, NULL); //longitude field in RMC sentence
					ptrBuff = strtok_r(NULL,",",&ptrprepData);
					i++;

					//these next few lines convert
					//degs and mins to decimal degree seconds
					sign = strcmp(ptrBuff,"E") ? -1:1;  //create a sign multiplier from E/W
					degs = (int)f_temp/100;   //grab the whole number of degrees
					f_temp -= (degs*100);     //remove the degrees from the calculation
					gps_data.lon_dds = sign*((f_temp/60)+degs);  //calculate decimal degrees from remaining minutes, then add back degrees and apply the sign
			  break;

			  case 7:
				  gps_data.velocity = strtof(ptrBuff, NULL)* 0.5144; //speed field in RMC sentence, in m/s
			  break;

			  case 8:
				  gps_data.cog = strtof(ptrBuff, NULL); //heading angle in RMC sentence, in degrees
			  break;

			  case 9:
				  gps_data.date = strtof(ptrBuff, NULL); //date in RMC sentence, raw format, as integer
			  break;

			  case 10:
				  gps_data.mag_var = strtof(ptrBuff, NULL); //magnetic variation in RMC sentence, in degrees
			  break;
		  }
		  ptrBuff = strtok_r(NULL,",",&ptrprepData);
		  i++;
		  }
	  xSemaphoreGive(xSemaphoreGPSData);
	}
}
/*
 * @brief: Private helper function to add ascii 0's to empty strings in the rxed NMEA sentence
 * needed by strtok_r so as not to skip over empty strings.
 * @param data[]: The data recieved from the GPS sensor
 * @param length: The length of the data recieved from the GPSsensor
 * @retval: 0 if succes, -1 otherwise
 */
int PrepBuff(unsigned char data[], uint length)
{
  //this is a private helper function to add ascii 0's to empty strings in the rxed NMEA sentence
  //this is needed by strtok_r so as not to skip over empty strings.
  int prevch=0, i, j = 0;
  unsigned char ch;
  prepLength = length;

  //memset(prepData, 0, MAX_PREP * sizeof(char));

  for(i=0; i<length; i++)
  {
    ch = data[i];
    if(ch == ',' && prevch == ',')  //have we seen two ',' in a row?
    {
      prepData[j] = '0';
      j++;
      prepData[j] = ch;
      j++;
      prevch = ',';
      prepLength++;     //we grew the buffer's length, so account for it
    }
    else
    {
      prepData[j] = ch;
      j++;
      prevch = ch;  //remember this byte as the last byte seen
    }
  }

  return 0;
}


/* "@brief Interprets messages from the bouys windsensor
 *  @param data: The data recieved from the GPSsensor as a array of char
 *  @param length: The length of the data recieved from the GPSsensor
 *  @retval: 0 if succes, -1 otherwise
 */
int GPSInterPreter(unsigned char data[], uint length)
{
	if(data[0] != '$')// Did not get the first part of the message
	{
		return -1;
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

	if(recChk == checksum) // Checksum is correct -> use message
	{
		if(strncmp((char*)data, "$GPRMC", 6) == 0)
		{
			if(PrepBuff(data,length) >= 0) // Data is ready to interpret
			{
			 ParseRMC();
			 return 1;
			}

		}
		else
		{
			return -1;
		}

	}
	else
	{
	    return -1;
	}

	return -1;

}

void StartGPSTask(void const * argument)
{
  unsigned char b[MAX_BUFFER];
  uint msgLen = 0;
  unsigned char read;
  uint state = WAITFOR_$;
  int recStatus = 1;
  ptrprepData = prepData;


  //MX_USART2_UART_Init();
  MX_UART4_Init();

  xQueueGPS = xQueueCreate(10, sizeof(char));

  HAL_UART_Receive_IT(&huart4, &readGPS, 1);


  xSemaphoreGPSData = xSemaphoreCreateMutex();
  if(xSemaphoreGPSData == NULL)
  {
	  //TODO error. Should not reach here
  }

  //prepData = pvPortMalloc(MAX_PREP * sizeof(char));
  //memset(prepData, 0, MAX_PREP * sizeof(char));

  while(1)
  {

	recStatus = xQueueReceive(xQueueGPS, &read, 500);
	if(recStatus == pdTRUE )
	{
		switch(state) // Reads one byte at a time until CR/LF (\r\n) is found
		{
		case WAITFOR_$:
			if(read == '$')
			{
				b[msgLen] = read;
				msgLen++;
				state = WAITFOR_CR;
			}
			break;
		case WAITFOR_CR:
			if(read == '\r'){ // Read \r
				state = WAITFOR_LF;
			} else if(msgLen < MAX_BUFFER)
			{
				b[msgLen] = read;
				msgLen++;
			} else // Exeeded MAX_BUFFER size before reading \n. ---> Try again
			{
				msgLen = 0;
				state = WAITFOR_$;
			}
			break;
		case WAITFOR_LF:
			if(read == '\n'){ //Read \n meaning end of message is found
				//Interpret message
				if(GPSInterPreter(b,msgLen) >= 0)
				{
					HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
					//osDelay(50);
				}

			}
			state = WAITFOR_$;
			memset(b, 0, sizeof(b));
			msgLen = 0;
			break;
		}
	} else
	{
	  //osDelay(10);
	}
	osDelay(1);
	//HAL_GPIO_TogglePin(GPIOB, LD2_Pin);
  }

}
