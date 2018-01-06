/*
 * GPSTask.h
 *
 *  Created on: 14. okt. 2017
 *      Author: Neophyte
 */

#ifndef GPSTASK_GPSTASK_H_
#define GPSTASK_GPSTASK_H_

#include "cmsis_os.h"
#include "../debug/debug.h"

#define KNOTS          0
#define MPH            1
#define KPH            2
#define MPS            3

#define GPS_TRUE       1
#define GPS_FALSE      0

struct nmea_data_s
{
  	  int fix_valid;      //boolean indicating a valid GPS fix
  	  float lat_dds;      //current latitude in decimal degress
  	  float lon_dds;      //current longitude in decimal degrees
  	  float cog;      	  //current direction of travel, in degrees, as float
  	  float velocity;     //current speed if travel, in knots, as float
  	  float date;         //current date, raw format with tenths of second, as float
  	  int time;           //current UTC time, raw format, as integer
  	  float mag_var;      //current magnetic variation, as float

};



//with these two, the task can be started from another file
osThreadId GPSTaskHandle;
struct nmea_data_s getGPSData();
void StartGPSTask(void const * argument);
#endif /* GPSTASK_GPSTASK_H_ */
