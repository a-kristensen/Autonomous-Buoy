/*
 * ControlTask.h
 *
 *  Created on: 30. nov. 2017
 *      Author: Neophyte
 */

#ifndef CONTROLTASK_CONTROLTASK_H_
#define CONTROLTASK_CONTROLTASK_H_

#include "cmsis_os.h"
#include "../debug/debug.h"
#include "../SPITask/SPITask.h"
#include "../GPSTask/GPSTask.h"
#include "../IMUTask/IMUTask.h"
#include "../WindTask/WindTask.h"


typedef struct {
	float gain_p;
	float gain_i;
	float gain_pm;
	float sp_long;
	float sp_lat;
	float calib_val;
	unsigned char do_calib;
} ControlParam_t;

typedef enum {
	CTRL_STOPPED = 0,
	CTRL_AUTOMATIC = 1,
	CTRL_MANUAL = 2
} CONTROLLER_STATE;

osThreadId ControlTaskHandle;
void StartControlTask(void const * argument);

void setCtrlParam(ControlParam_t*);
ControlParam_t getCtrlParam(void);
void setCtrlState(CONTROLLER_STATE);


#endif /* CONTROLTASK_CONTROLTASK_H_ */
