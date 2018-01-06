/*
 * RemoteTask.h
 *
 *  Created on: 27. nov. 2017
 *      Author: Neophyte
 */

#ifndef REMOTETASK_REMOTETASK_H_
#define REMOTETASK_REMOTETASK_H_

#include "cmsis_os.h"
#include "../debug/debug.h"


typedef struct
{
	unsigned char c[4];
} Payload;

typedef struct
{
	unsigned char 	sot;
	unsigned char 	cmd;
	unsigned char 	id;
	Payload 		d;
	unsigned char 	crc;
} Msg;

typedef enum
{
	ASYNC_MSG,
	SYNC_MSG
} SYNC;


typedef enum
{
	//system
	ID_ERROR					= 0,
	ID_STATUS 					= 1,
	ID_CONFIG 					= 2,

	//wind sensor
	ID_WIND_SPEED 				= 10,
	ID_WIND_DIRECTION			= 11,
	ID_WIND_TEMP				= 12,

	//GPS
	ID_GPS_LONGITUDE			= 20,
	ID_GPS_LATTITUDE			= 21,
	ID_GPS_SOG					= 22,
	ID_GPS_COG					= 23,
	ID_GPS_FIX					= 24,

	//IMU
	ID_IMU_ROLL					= 30,
	ID_IMU_PITCH				= 31,
	ID_IMU_YAW					= 32,

	//motor control
	ID_MOTCTRL_P				= 40,
	ID_MOTCTRL_I				= 41,
	ID_MOTCTRL_D				= 42,
	ID_MOTCTRL_POSITION			= 43,

	//sail control
	ID_SAILCTRL_GAIN_P			= 50,
	ID_SAILCTRL_GAIN_I			= 51,
	ID_SAILCTRL_GAIN_PM			= 52,
	ID_SAILCTRL_SP_LONG			= 53,
	ID_SAILCTRL_SP_LAT			= 54,
	ID_SAILCTRL_CAL_VAL			= 55
} MSG_ID;


osThreadId RemoteTaskHandle;
void StartRemoteTask(void const * argument);


void remoteSetParameter(MSG_ID, Payload);


//config bit masks
#define CFG_MANUAL				((uint32_t)(1 << 24))
#define CFG_AUTOMATIC			((uint32_t)(1 << 25))
#define CFG_CAL_CTRL_ON			((uint32_t)(1 << 16))
#define CFG_CAL_CTRL_OFF		((uint32_t)(1 << 17))
#define CFG_CAL_MOTOR			((uint32_t)(1 << 18))
#define CFG_CAL_SETNORTH		((uint32_t)(1 << 19))
#define CFG_SELF_DESTRUCT_NOW	((uint32_t)(1 << 0))	//this command must be used with care

//status defines



#endif /* REMOTETASK_REMOTETASK_H_ */
