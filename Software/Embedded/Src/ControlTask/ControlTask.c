/*
 * ControlTask.c
 *
 *  Created on: 30. nov. 2017
 *      Author: Neophyte
 */

#include "ControlTask.h"
#include <math.h>
#include "../SPITask/SPITask.h"
#include "../GPSTask/GPSTask.h"
#include "../IMUTask/IMUTask.h"
#include "../WindTask/WindTask.h"



#define CONTROLTASK_DBG
#ifdef CONTROLTASK_DBG
  #define ControlTask_DbgMsg PrintDbgMsg
#else
  #define ControlTask_DbgMsg
#endif





float integrator = 0;
ControlParam_t ctrl_p;
SemaphoreHandle_t xMutexCtrlParam;
CONTROLLER_STATE CtrlState;

void setCtrlState(CONTROLLER_STATE s)
{
	if(s == CTRL_AUTOMATIC)
		CtrlState = CTRL_AUTOMATIC;
	else if(s == CTRL_MANUAL)
		CtrlState = CTRL_MANUAL;
}

void setCtrlParam(ControlParam_t* c)
{
	if(xSemaphoreTake(xMutexCtrlParam, 100) == pdTRUE)
	{
		ctrl_p = *c;
		xSemaphoreGive(xMutexCtrlParam);
	}
}

ControlParam_t getCtrlParam(void)
{
	ControlParam_t c;
	if(xSemaphoreTake(xMutexCtrlParam, 100) == pdTRUE)
	{
		c = ctrl_p;
		xSemaphoreGive(xMutexCtrlParam);
	}

	return c;
}


float set_mass_pos(float* tilt, float* tilt_d)
{
	return (*tilt_d - *tilt) * ctrl_p.gain_pm;
}

float set_tilt(float* latitude, float* longitude, float* course)
{
	float dir = atan2 (ctrl_p.sp_lat - *latitude, ctrl_p.sp_long - *longitude) * 180 / M_PI;
	float err;
    static uint32_t tck = 0;
    float ret;

	if(dir < 0)
		dir = 90 + dir * -1;
	else if(dir >= 0 && dir <= 90)
		dir = 90 - dir;
	else
		dir = 450 - dir;

	err = dir - *course;

	//this makes the buoy turn the shortest way around
	if(err > 180)
		err = err - 360;
	else if(err < -180)
		err = 360 + err;

	integrator += err;

	if(integrator > 50)
		integrator = 50;
	else if(integrator < -50)
		integrator = -50;

	ret = ctrl_p.gain_p * err + ctrl_p.gain_i * integrator * (HAL_GetTick() - tck);
	tck = HAL_GetTick();

	if(ret > 50)
		ret = 50;
	else if(ret < -50)
		ret = -50;

	return ret;
}


float set_course(float* latitude,
		float* longitude,
		float* course,
		float* heading,
		float* speed,
		float* tilt )
{
	float d_tilt;

	if(*speed > 1)
	{
		d_tilt = set_tilt(latitude, longitude, course);
	}
	else
	{
		d_tilt = set_tilt(latitude, longitude, heading);
	}
	if(ctrl_p.do_calib == 0)
	{
		return set_mass_pos(tilt, &d_tilt);
	}
	else
	{
		return set_mass_pos(tilt, &ctrl_p.calib_val);
	}
}





void StartControlTask(void const * argument)
{
	float course_sp = 0;
	struct nmea_data_s 	  gps;
	struct IMU_s 		  imu;
	//struct WindSensor_s   wind;

	CtrlState = CTRL_MANUAL;

	xMutexCtrlParam = xSemaphoreCreateMutex();
	if(xMutexCtrlParam == NULL)
	{
		//TODO error. Should not reach here
	}


	ctrl_p.gain_p = 0.5;
	ctrl_p.gain_i = 0.004;
	ctrl_p.gain_pm = 4;
	ctrl_p.sp_long = 0;
	ctrl_p.sp_lat = 0;
	ctrl_p.calib_val = 0;
	ctrl_p.do_calib = 0;


	for(;;)
	{
		switch(CtrlState)
		{
		case CTRL_AUTOMATIC:
			gps = getGPSData();
			imu = getIMUData();
			//wind = getWindSensorData();

			course_sp = set_course(&gps.lat_dds, &gps.lon_dds, &gps.cog, &imu.yaw, &gps.velocity, &imu.roll );

			if(course_sp > 100)
				course_sp = 100;
			if(course_sp < -100)
				course_sp = -100;

			SPI_setPosition(course_sp);
		break;
		}

		osDelay(100);
	}

}
