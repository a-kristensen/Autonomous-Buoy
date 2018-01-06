/*
 * SPITask.c
 *
 *  Created on: 30. okt. 2017
 *      Author: Neophyte
 */

#include "SPITask.h"
#include "spi.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>


#define SPITask_DBG
#ifdef SPITask_DBG
  #define SPITask_DbgMsg PrintDbgMsg
#else
  #define SPITask_DbgMsg
#endif

#define MTRCTRL_SET_SPEED_DIR 	0
#define MTRCTRL_GET_STATUS		1
#define MTRCTRL_GET_POSITION	2
#define MTRCTRL_SET_RESET_POS	3

#define DIR_LEFT(a)		(a | 0b10000000)
#define DIR_RIGHT(a)	(a & 0b01111111)


#define SW_RIGHT	0b10000000
#define SW_LEFT		0b01000000

#define SOT 		0x96
#define SUCCESS 	0x01
#define ERROR		0x00

#define SS_PORT		GPIOD
#define SS_PIN		GPIO_PIN_14

typedef enum {
	MOTOR_STOPPED = 0,
	MOTOR_RUNNING = 1,
	MOTOR_CALIBRATE = 2
} MOTOR_STATE;

SemaphoreHandle_t xMotCtrlMutex_SetPoint;
SemaphoreHandle_t xMotCtrlMutex_ProcessValue;

uint16_t SP_Position;
uint16_t PV_Position;
uint16_t maxPos;
MOTOR_STATE MotorState;


pid_ctrl_t pid = {0.03, 0.001, 0.01, 0, 100, 0, 0};


unsigned char SPI_getPosition(void)
{
	unsigned char r = 0;

	if(xMotCtrlMutex_ProcessValue != NULL)
	{
		if(xSemaphoreTake(xMotCtrlMutex_ProcessValue, 50) == pdTRUE)
		{
			r = (unsigned char) ( ((float)200/maxPos) * PV_Position );
			xSemaphoreGive(xMotCtrlMutex_ProcessValue);
		}
	}

	return r;
}

pid_ctrl_t SPI_getMotParam(void)
{
	return pid;
}

void SPI_setMotParam(const pid_ctrl_t* const m)
{
	pid = *m;
}


//input: pos: range -100 <-> 0 <-> 100
void SPI_setPosition(signed char pos)
{
	//convert to correct range
	float f = (maxPos/200) * (pos+100);

	if(xMotCtrlMutex_SetPoint != NULL)
	{
		if(xSemaphoreTake(xMotCtrlMutex_SetPoint, 50) == pdTRUE)
		{
			SP_Position = (unsigned int)f;
			xSemaphoreGive(xMotCtrlMutex_SetPoint);
		}
	}
}


float calcPID(pid_ctrl_t *pid, float err)
{
    float out = 0;
    uint32_t tck = HAL_GetTick();

    pid->intg = (pid->intg + err) * pid->i * (tck - pid->prev_tck);

    //set max/min value
    if(pid->intg > pid->intgr_lim)
    	pid->intg = pid->intgr_lim;
    else if(pid->intg < - pid->intgr_lim)
    	pid->intg = - pid->intgr_lim;

    out += pid->p * err;
    out += pid->intg;
    out += pid->d * ((err - pid->prev_err) / (tck - pid->prev_tck));

    pid->prev_tck = tck;
    pid->prev_err = err;
    return out;
}

unsigned char convertPIDVal(float f)
{
	unsigned char c;
	float pid = (f < 0 ? -f : f);

	if(pid > 100)
		pid = 100;

	c = (unsigned char)pid;

	//set direction bit
	c = f < 0 ? DIR_RIGHT(c) : DIR_LEFT(c);

	return c;
}

unsigned char CalcCRC(unsigned char* data, unsigned char size)
{
	unsigned char crc = 0;

	while(size--)
	   crc ^= *data++;

	return crc;
}

unsigned char MotCtrlSendRecv(unsigned char id, unsigned char TxVal, unsigned char* RxData)
{
	unsigned char tx[4], rx[5], r=ERROR;
	static unsigned int errCnt=0;

	tx[0] = SOT;
	tx[1] = id;
	tx[2] = TxVal;
	tx[3] = CalcCRC(tx, 3);

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);



	//retry send and receive for up to 3 times
	for(unsigned int rty=0; rty<3; rty++)
	{
		HAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_RESET);
		osDelay(1);

		if(HAL_SPI_Transmit(&hspi1, tx, 4, 100) == HAL_OK)
		{
			osDelay(1);
			for(unsigned char i=0; i<10; i++)
			{
				//wait for the first byte, SOT
				HAL_SPI_Receive(&hspi1, rx, 1, 100);
				if(rx[0] == SOT)
				{
					if(HAL_SPI_Receive(&hspi1, &rx[1], 4, 100) == HAL_OK)
					{
						if(tx[1] == rx[1] && rx[4] == CalcCRC(rx, 4))
						{
							//successfully received package
							if(RxData != NULL)
							{
								RxData[0] = rx[2];
								RxData[1] = rx[3];
							}

							errCnt = 0;
							r = SUCCESS;
							break; //for
						}
					}
				}
			}
		}

		HAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_SET);

		if(r == SUCCESS)
			break;

		errCnt++;
	}

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	/*if(errCnt > 10)
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);*/

	return r;
}

void SPI_startCalibrate(void)
{
	MotorState = MOTOR_CALIBRATE;
}

unsigned char Calibrate(void)
{
	unsigned char rx[2] = { 0 };
	unsigned char i;

	maxPos = 0;

	//run to the right switch
	MotCtrlSendRecv(MTRCTRL_SET_SPEED_DIR, DIR_RIGHT(50), NULL);

	//run for max 5 seconds or until switch is activated
	for(i=0; i<20; i++)
	{
		osDelay(500);
		MotCtrlSendRecv(MTRCTRL_GET_STATUS, 0, rx);
		if(rx[0] & SW_RIGHT)
			break;
	}

	if(i >= 20)
		return ERROR;

	//mass in one end. Reset position
	MotCtrlSendRecv(MTRCTRL_SET_RESET_POS, 0, NULL);

	//run to the left switch
	MotCtrlSendRecv(MTRCTRL_SET_SPEED_DIR, DIR_LEFT(50), NULL);

	//run for max 5 seconds or until switch is activated
	for(i=0; i<20; i++)
	{
		osDelay(500);
		MotCtrlSendRecv(MTRCTRL_GET_STATUS, 0, rx);
		if(rx[0] & SW_LEFT)
			break;
	}

	if(i >= 20)
		return ERROR;


	//get the maximum position
	if( MotCtrlSendRecv(MTRCTRL_GET_POSITION, 0, rx) == SUCCESS)
	{
		maxPos = *(uint16_t*)rx;
		return SUCCESS;
	}

	return ERROR;
}

void StartSPITask(void const * argument)
{
	float PIDout;

	MotorState = MOTOR_RUNNING;
	maxPos = 7300;
	/*pid.p = 0.2;
	pid.i = 0.03;
	pid.d = 0;
	pid.intgr_lim = 100;*/

	MX_SPI1_Init();

	xMotCtrlMutex_SetPoint = xSemaphoreCreateMutex();
	if(xMotCtrlMutex_SetPoint == NULL)
	{
	  //TODO error. Should not reach here
	}

	xMotCtrlMutex_ProcessValue = xSemaphoreCreateMutex();
	if(xMotCtrlMutex_ProcessValue == NULL)
	{
	  //TODO error. Should not reach here
	}


	for(;;)
	{
		switch(MotorState)
		{
		case MOTOR_STOPPED:
		break;
		case MOTOR_RUNNING:
			//get position
			if(xSemaphoreTake(xMotCtrlMutex_ProcessValue, 50) == pdTRUE)
			{
				MotCtrlSendRecv(MTRCTRL_GET_POSITION, 0, (unsigned char*)&PV_Position);
				xSemaphoreGive(xMotCtrlMutex_ProcessValue);
			}

			//calculate pid value
			if(xSemaphoreTake(xMotCtrlMutex_SetPoint, 50) == pdTRUE)
			{
				PIDout = calcPID(&pid, SP_Position - PV_Position);
				xSemaphoreGive(xMotCtrlMutex_SetPoint);
			}

			//set speed of motor
			MotCtrlSendRecv(MTRCTRL_SET_SPEED_DIR, convertPIDVal(PIDout), NULL);

			osDelay(10);
		break;
		case MOTOR_CALIBRATE:
			Calibrate();
			MotCtrlSendRecv(MTRCTRL_SET_SPEED_DIR, 0, NULL);
			SPI_setPosition(0);
			osDelay(500);
			MotorState = MOTOR_RUNNING;
		break;
		}



	}

}


