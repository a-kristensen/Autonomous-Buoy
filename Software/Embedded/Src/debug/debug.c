/*
 * debug.c
 *
 *  Created on: 9. okt. 2017
 *      Author: Neophyte
 */

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "queue.h"
#include <stdarg.h>
#include "debug.h"
#include <string.h>
#include <stdlib.h>


QueueHandle_t xQueueDebug;
SemaphoreHandle_t xSemaphoreDebug;

char strbf1[DBG_BUF_SIZE];
char strbf2[DBG_BUF_SIZE];
char strbf3[DBG_BUF_SIZE];
char strbf4[DBG_BUF_SIZE];
char strbf5[DBG_BUF_SIZE];
char strbf6[DBG_BUF_SIZE];
char strbf7[DBG_BUF_SIZE];
char strbf8[DBG_BUF_SIZE];

//char *pStrBuf[DBG_BUF_ITEMS] = {NULL};
char *pStrBuf[DBG_BUF_ITEMS] = {strbf1, strbf2, strbf3, strbf4, strbf5, strbf6, strbf7, strbf8};

unsigned char cBufCnt = 0;
char DbgRdy = 0;


void DbgMsg ( const char * format, ... )
{
  va_list args;
  va_start (args, format);

  //the queue, mutexes and memory must be initialized before it can be used
  if(DbgRdy)
  {
    if(xSemaphoreTake(xSemaphoreDebug, 100) == pdTRUE)
	{
	  vsnprintf (pStrBuf[cBufCnt++ & 0x07], DBG_BUF_SIZE, format, args);
	  xSemaphoreGive(xSemaphoreDebug);

	  if(xQueueSendToBack(xQueueDebug, &pStrBuf[cBufCnt - 1], 100) != pdTRUE)
	  {
        cBufCnt = 0;
	  }
	}
  }

  va_end (args);
}



void StartDebugTask(void const * argument)
{
  char* str = NULL;

  xQueueDebug = xQueueCreate(DBG_BUF_ITEMS, sizeof(char*));
  if(xQueueDebug == NULL)
  {
	  //TODO error. Should not reach here
  }

  xSemaphoreDebug = xSemaphoreCreateMutex();
  if(xSemaphoreDebug == NULL)
  {
	  //TODO error. Should not reach here
  }

  //init the uart for printing debug messages
  MX_USART3_UART_Init();

  //allocate memory for output
  /*for(i=0; i<DBG_BUF_ITEMS; i++)
    pStrBuf[i] = (char*)malloc(DBG_BUF_SIZE);*/


  DbgRdy = 1;
  for(;;)
  {
    if(xQueueReceive(xQueueDebug, &str, 100) == pdTRUE)
    {
      if(xSemaphoreTake(xSemaphoreDebug, 100) == pdTRUE)
      {
        for(int i=0; i<strlen(str); i++)
          HAL_UART_Transmit(&huart3, (uint8_t*)&str[i], 1, 500);

          cBufCnt--;
    	  xSemaphoreGive(xSemaphoreDebug);
      }
    }
  }
}
