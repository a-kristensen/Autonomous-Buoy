/*
 * exampleTask.c
 *
 *  Created on: 14. okt. 2017
 *      Author: Neophyte
 */

#include "exampleTask.h"

/*
//remember to always include the file FreeRTOS.h before any other API headers
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
*/

//include additional header files here


//do not make calls to PrintDbgMsg. Use ExampleTask_DbgMsg instead !
//this can disable debug messages for each module individually


#define EXAMPLETASK_DBG
#ifdef EXAMPLETASK_DBG
  #define ExampleTask_DbgMsg PrintDbgMsg
#else
  #define ExampleTask_DbgMsg
#endif



void StartExampleTask(void const * argument)
{
  //here you should do initialization
  int i = 0;

  //this loop runs forever
  //this is where the is work done in a thread
  for(;;)
  {

	//use this to print debug strings back to eclipse
	ExampleTask_DbgMsg("test debug: %i", i++);

    //remember delay, so cpu is not occupied entirely
    osDelay(1000);
  }

}
