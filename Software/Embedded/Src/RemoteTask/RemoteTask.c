/*
 * RemoteTask.c
 *
 *  Created on: 27. nov. 2017
 *      Author: Neophyte
 */

#include "RemoteTask.h"
#include "usart.h"

#include "../SPITask/SPITask.h"
#include "../GPSTask/GPSTask.h"
#include "../IMUTask/IMUTask.h"
#include "../WindTask/WindTask.h"
#include "../ControlTask/ControlTask.h"
#include "../Eeprom/EepromTask.h"

#define RemoteTask_DBG
#ifdef RemoteTask_DBG
  #define RemoteTask_DbgMsg PrintDbgMsg
#else
  #define RemoteTask_DbgMsg
#endif

#define SOT 			0x96
#define MSG_LEN			8

#define SET_GET_MASK	0x01
#define SYNC_MSG_BIT	0x02
#define ASYNC_MSG_BIT	0x04

const Payload STAT_STARTUP = { {0, 0, 0, 0x80} };

enum STATE
{
	WAIT_FOR_SOT,
	RCV_7_BYTES,
	WAIT_FOR_PROC
};


SemaphoreHandle_t xSemaphoreWindData;
QueueHandle_t xQueueRemote;
unsigned char rxByte;
volatile unsigned char rxState;
unsigned char rxBuf[MSG_LEN];
unsigned char rxCnt;


//forward declarations
unsigned char getCRC(unsigned char*, unsigned char);
HAL_StatusTypeDef SendMsg(SYNC snc, unsigned char id, Payload d);



void UART7_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart7);

	switch(rxState)
	{
	case WAIT_FOR_SOT:
		if(rxByte == SOT)
		{
			rxBuf[0] = SOT;
			rxCnt = 1;
			rxState = RCV_7_BYTES;
		}
	break;
	case RCV_7_BYTES:
		rxBuf[rxCnt++] = rxByte;
		if(rxCnt >= 8)
		{
			rxState = WAIT_FOR_PROC;
			xQueueSendToBackFromISR(xQueueRemote, &rxBuf[7], NULL);
		}
	break;
	case WAIT_FOR_PROC:
	break;
	}

	HAL_UART_Receive_IT(&huart7, &rxByte, 1);
}

void doConfig(uint32_t cfg)
{
	ControlParam_t ctrl_param;

	if(cfg & CFG_MANUAL)
		setCtrlState(CTRL_MANUAL);
	else if(cfg & CFG_AUTOMATIC)
		setCtrlState(CTRL_AUTOMATIC);


	if(cfg & CFG_CAL_CTRL_ON)
	{
		ctrl_param = getCtrlParam();
		ctrl_param.do_calib = 1;
		setCtrlParam(&ctrl_param);
	}
	else if(cfg & CFG_CAL_CTRL_OFF)
	{
		ctrl_param = getCtrlParam();
		ctrl_param.do_calib = 0;
		setCtrlParam(&ctrl_param);
	}


	if(cfg & CFG_CAL_MOTOR)
		SPI_startCalibrate();

	if(cfg & CFG_CAL_SETNORTH)
		IMU_SetNorth();
}

void remoteSetParameter(MSG_ID id, Payload d)
{
	ControlParam_t 	ctrl_param;
	pid_ctrl_t		motor_param;

	switch(id)
	{
	case ID_CONFIG:
		doConfig( *(uint32_t*)&d );
	break;
	case ID_MOTCTRL_P:
		motor_param = SPI_getMotParam();
		motor_param.p = *(float*)&d;
		SPI_setMotParam(&motor_param);
	break;
	case ID_MOTCTRL_I:
		motor_param = SPI_getMotParam();
		motor_param.i = *(float*)&d;
		SPI_setMotParam(&motor_param);
	break;
	case ID_MOTCTRL_D:
		motor_param = SPI_getMotParam();
		motor_param.d = *(float*)&d;
		SPI_setMotParam(&motor_param);
	break;
	case ID_MOTCTRL_POSITION:
		SPI_setPosition( *(signed char*)((void*)(&d.c[0])) -100 );
	break;
	case ID_SAILCTRL_GAIN_P:
		ctrl_param = getCtrlParam();
		ctrl_param.gain_p = *(float*)&d;
		setCtrlParam(&ctrl_param);
	break;
	case ID_SAILCTRL_GAIN_I:
		ctrl_param = getCtrlParam();
		ctrl_param.gain_i = *(float*)&d;
		setCtrlParam(&ctrl_param);
	break;
	case ID_SAILCTRL_GAIN_PM:
		ctrl_param = getCtrlParam();
		ctrl_param.gain_pm = *(float*)&d;
		setCtrlParam(&ctrl_param);
	break;
	case ID_SAILCTRL_SP_LONG:
		ctrl_param = getCtrlParam();
		ctrl_param.sp_long = *(float*)&d;
		setCtrlParam(&ctrl_param);
	break;
	case ID_SAILCTRL_SP_LAT:
		ctrl_param = getCtrlParam();
		ctrl_param.sp_lat = *(float*)&d;
		setCtrlParam(&ctrl_param);
	break;
	case ID_SAILCTRL_CAL_VAL:
		ctrl_param = getCtrlParam();
		ctrl_param.calib_val = *(float*)&d;
		setCtrlParam(&ctrl_param);
	break;
	default:
		id = ID_ERROR;
		*(unsigned int*)&d = 0;
	break;
	}
}



HAL_StatusTypeDef GetId(SYNC snc, MSG_ID id)
{
	Payload d;

	switch(id)
	{
	case ID_STATUS:
		*(unsigned int*)&d = 0;
	break;
	case ID_WIND_SPEED:
		*(float*)&d = getWindSensorData().speed;
	break;
	case ID_WIND_DIRECTION:
		*(float*)&d = getWindSensorData().direction;
	break;
	case ID_WIND_TEMP:
		*(float*)&d = getWindSensorData().temp;
	break;
	case ID_GPS_LONGITUDE:
		*(float*)&d = getGPSData().lon_dds;
	break;
	case ID_GPS_LATTITUDE:
		*(float*)&d = getGPSData().lat_dds;
	break;
	case ID_GPS_SOG:
		*(float*)&d = getGPSData().velocity;
	break;
	case ID_GPS_COG:
		*(float*)&d = getGPSData().cog;
	break;
	case ID_GPS_FIX:
		*(float*)&d = getGPSData().fix_valid;
	break;
	case ID_IMU_ROLL:
		*(float*)&d = getIMUData().roll;
	break;
	case ID_IMU_PITCH:
		*(float*)&d = getIMUData().pitch;
	break;
	case ID_IMU_YAW:
		*(float*)&d = getIMUData().yaw;
	break;
	case ID_MOTCTRL_P:
		*(float*)&d = SPI_getMotParam().p;
	break;
	case ID_MOTCTRL_I:
		*(float*)&d = SPI_getMotParam().i;
	break;
	case ID_MOTCTRL_D:
		*(float*)&d = SPI_getMotParam().d;
	break;
	case ID_MOTCTRL_POSITION:
		*(float*)&d = SPI_getPosition();
	break;
	case ID_SAILCTRL_GAIN_P:
		*(float*)&d = getCtrlParam().gain_p;
	break;
	case ID_SAILCTRL_GAIN_I:
		*(float*)&d = getCtrlParam().gain_i;
	break;
	case ID_SAILCTRL_GAIN_PM:
		*(float*)&d = getCtrlParam().gain_pm;
	break;
	case ID_SAILCTRL_SP_LONG:
		*(float*)&d = getCtrlParam().sp_long;
	break;
	case ID_SAILCTRL_SP_LAT:
		*(float*)&d = getCtrlParam().sp_lat;
	break;
	case ID_SAILCTRL_CAL_VAL:
		*(float*)&d = getCtrlParam().calib_val;
	break;
	default:
		id = ID_ERROR;
	break;
	}


	//send reply
	return SendMsg(snc, id, d);
}

HAL_StatusTypeDef SetId(SYNC snc, MSG_ID id, Payload d)
{
	//distribute to other tasks
	remoteSetParameter(id, d);

	//these values must be stored on eeprom
	switch(id)
	{
	case ID_CONFIG:
	case ID_MOTCTRL_P:
	case ID_MOTCTRL_I:
	case ID_MOTCTRL_D:
	case ID_SAILCTRL_GAIN_P:
	case ID_SAILCTRL_GAIN_I:
	case ID_SAILCTRL_GAIN_PM:
	case ID_SAILCTRL_SP_LONG:
	case ID_SAILCTRL_SP_LAT:
	case ID_SAILCTRL_CAL_VAL:
		EepromSetParam(id, d);
	break;
	}

	//send reply
	return SendMsg(snc, id, d);
}


HAL_StatusTypeDef SendMsg(SYNC snc, unsigned char id, Payload d)
{
	Msg m;

	m.sot = SOT;
	m.cmd = (snc == ASYNC_MSG ? SYNC_MSG_BIT : ASYNC_MSG_BIT);
	m.id = id;
	m.d = d;
	m.crc = getCRC((unsigned char*)&m, MSG_LEN - 1);

	return HAL_UART_Transmit(&huart7, (uint8_t*)&m, MSG_LEN, 100);
	//return HAL_UART_Transmit_IT(&huart7, (uint8_t*)&m, MSG_LEN);
}



unsigned char getCRC(unsigned char* data, unsigned char size)
{
	unsigned char crc = 0;

	while(size--)
	   crc ^= *data++;

	return crc;
}

void ProcessMsg(Msg m)
{
	//is the message valid
	if( (m.sot == SOT) && (getCRC((unsigned char*)&m, MSG_LEN-1) == m.crc) )
	{
		if(m.cmd & SET_GET_MASK)
			SetId(SYNC_MSG, m.id, m.d);
		else
			GetId(SYNC_MSG, m.id);
	}

	//otherwise, drop the message
}


void StartRemoteTask(void const * argument)
{
    static uint32_t tck = 0;
	unsigned char rcvByte = 0;

	unsigned char async_cnt = 0;
	const MSG_ID async_msg[] = {
		ID_WIND_SPEED,		ID_WIND_DIRECTION,	ID_WIND_TEMP,
		ID_GPS_LONGITUDE,	ID_GPS_LATTITUDE,	ID_GPS_SOG,
		ID_GPS_COG,			ID_GPS_FIX,			ID_IMU_ROLL,
		ID_IMU_PITCH,		ID_IMU_YAW,			ID_MOTCTRL_POSITION };

	rxState = WAIT_FOR_SOT;
	rxCnt= 1;


	MX_UART7_Init();


	//inform host about the startup
	SendMsg(ASYNC_MSG, ID_STATUS, STAT_STARTUP);

	xQueueRemote = xQueueCreate(MSG_LEN * 1, sizeof(unsigned char));
	HAL_UART_Receive_IT(&huart7, &rxByte, 1);

	for(;;)
	{
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

		//is full pacakge received?
		if( xQueueReceive(xQueueRemote, &rcvByte, 100) == pdTRUE )
		{
			//process it
			ProcessMsg( *(Msg*)rxBuf );
			rxState = WAIT_FOR_SOT;
		}

		//handle sending of async messages
		if(HAL_GetTick() >= tck)
		{

			HAL_NVIC_DisableIRQ(UART7_IRQn);

			GetId(ASYNC_MSG, async_msg[async_cnt++]);

			HAL_NVIC_EnableIRQ(UART7_IRQn);
			HAL_UART_Receive_IT(&huart7, &rxByte, 1);


			if(async_cnt >= sizeof(async_msg))
			{
				async_cnt = 0;
				tck = HAL_GetTick() + 0;
			}

			//RemoteTask_DbgMsg("Msg: %i", sizeof(async_msg));
		}

		//osDelay(10);
	}

}


