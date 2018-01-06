/*
 * debug.h
 *
 *  Created on: 9. okt. 2017
 *      Author: Neophyte
 */

#ifndef DEBUG_DEBUG_H_
#define DEBUG_DEBUG_H_

#include "cmsis_os.h"



#define GLOBAL_DEBUG

#ifdef GLOBAL_DEBUG
  #define PrintDbgMsg(fmt, ...) DbgMsg("%s:%d:%s(): " fmt"\r\n", __FILE__, __LINE__, __func__, __VA_ARGS__);
#else
  #define PrintDbgMsg(fmt, ...)
#endif

#define DBG_BUF_SIZE 100
#define DBG_BUF_ITEMS 8

osThreadId DebugTaskHandle;
void StartDebugTask(void const * argument);
void DbgMsg(const char * format, ...);

#endif /* DEBUG_DEBUG_H_ */
