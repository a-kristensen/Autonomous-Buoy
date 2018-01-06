/*
 * IMU.h
 *
 *  Created on: 12. okt. 2017
 *      Author: Michael
 */

#ifndef IMU_H_
#define IMU_H_

#include "EasyProfile/EasyObjectDictionary.h"
#include "EasyProfile/EasyProfile.h"
#include "IMUTask.h"


struct IMU_s
{
	float roll;
	float pitch;
	float yaw;
	unsigned int timeStamp;
};

extern struct IMU_s IMU; // Declared in IMU.cd
extern float f_IMURelOffset; // Declared in IMU.c

void initIMU();
void request(uint cmd);
void SerialPort_DataReceive(char rxData, int rxSize);

void IMU_SetNorth(void);
float IMU_getYawOffset(void);
void IMU_setYawOffset(float);

#endif /* IMU_H_ */
