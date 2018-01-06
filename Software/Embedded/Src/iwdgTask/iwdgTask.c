/*
 * iwdgTask.c
 *
 *  Created on: 14. okt. 2017
 *      Author: Neophyte
 */

#include "iwdgTask.h"
#include "iwdg.h"


#define IWDGTASK_DBG
#ifdef IWDGTASK_DBG
  #define IWDGTask_DbgMsg PrintDbgMsg
#else
  #define IWDGTask_DbgMsg
#endif



void StartIwdgTask(void const * argument)
{
  MX_IWDG_Init();

  for(;;)
  {
    //kick the dog
	HAL_IWDG_Refresh(&hiwdg);

	/*
	if(HAL_IWDG_Refresh(&hiwdg) != HAL_OK)
	{
	  //refresh error
	  Error_Handler();
	}
	*/

    osDelay(1000);
  }

}
