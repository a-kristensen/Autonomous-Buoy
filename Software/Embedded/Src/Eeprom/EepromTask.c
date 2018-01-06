/*
 * EepromTask.c
 *
 *  Created on: 11. dec. 2017
 *      Author: Neophyte
 */

#include "EepromTask.h"
#include "stm32f4xx_hal.h"
#include "../RemoteTask/RemoteTask.h"
#include "../IMUTask/IMU.h"


#define EEPROMTASK_DBG
#ifdef EEPROMTASK_DBG
  #define EepromTask_DbgMsg PrintDbgMsg
#else
  #define EepromTask_DbgMsg
#endif


typedef enum
{
	IDLE,
	DATA_RCV,
	STORE_DATA
} EEPROM_STATE;

typedef struct
{
	uint8_t		ValidData;
	uint32_t 	config;
	float		MOTCTRL_P;
	float 		MOTCTRL_I;
	float 		MOTCTRL_D;
	float 		SAILCTRL_GAIN_P;
	float 		SAILCTRL_GAIN_I;
	float 		SAILCTRL_GAIN_PM;
	float 		SAILCTRL_SP_LONG;
	float 		SAILCTRL_SP_LAT;
	float 		SAILCTRL_CAL_VAL;
	float		IMU_YawOffset;
} MEM_CFG;


QueueHandle_t xQueueEeprom;

void EepromSetParam(MSG_ID id, Payload d)
{
	EEPROM_CFG_ITEM item = {*(float*)&d, id};
	xQueueSendToBack(xQueueEeprom, &item, 100);
}



HAL_StatusTypeDef prgmByte(uint32_t offset, uint8_t* data)
{
	return HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, SECT23_ADDR + offset, *data);
}

HAL_StatusTypeDef prgmBytes(uint32_t offset, uint8_t* data, uint16_t size)
{
	HAL_StatusTypeDef HalStatus;

	while(size--)
	{
		HalStatus = prgmByte(offset++, data++);
		if(HalStatus != HAL_OK)
			return HalStatus;
	}

	return HalStatus;
}

HAL_StatusTypeDef readBytes(uint32_t offset, uint8_t* data, uint16_t size)
{
	while(size--)
		*data++ = (*(__IO uint8_t*)(SECT23_ADDR + offset++));

	return HAL_OK;
}

HAL_StatusTypeDef eraseSect23(void)
{
    uint32_t SectorError = 0;
    FLASH_EraseInitTypeDef pEraseInit;

    pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    pEraseInit.Sector = FLASH_SECTOR_23;
    pEraseInit.NbSectors = 1;
    pEraseInit.VoltageRange = VOLTAGE_RANGE;

	return HAL_FLASHEx_Erase(&pEraseInit, &SectorError);
}


void StartEepromTask(void const * argument)
{
	uint8_t datRcvFlag = 0;
	MEM_CFG MemCfg = { 0 };
    uint32_t tck = 0;
    EEPROM_CFG_ITEM qItem;

	xQueueEeprom = xQueueCreate(10, sizeof(EEPROM_CFG_ITEM));


	//read configuration from memory
	readBytes(0, (uint8_t*)&MemCfg, sizeof(MEM_CFG));

	//if it is first time after flashing, the data are erased, and hence invalid
	if(MemCfg.ValidData == EEPROM_VALID_DATA)
	{
		MemCfg.config &= ~CFG_CAL_MOTOR;
		remoteSetParameter(ID_CONFIG, *(Payload*)&MemCfg.config);

		remoteSetParameter(ID_MOTCTRL_P, *(Payload*)&MemCfg.MOTCTRL_P);
		remoteSetParameter(ID_MOTCTRL_I, *(Payload*)&MemCfg.MOTCTRL_I);
		remoteSetParameter(ID_MOTCTRL_D, *(Payload*)&MemCfg.MOTCTRL_D);
		remoteSetParameter(ID_SAILCTRL_GAIN_P, *(Payload*)&MemCfg.SAILCTRL_GAIN_P);
		remoteSetParameter(ID_SAILCTRL_GAIN_I, *(Payload*)&MemCfg.SAILCTRL_GAIN_I);
		remoteSetParameter(ID_SAILCTRL_GAIN_PM, *(Payload*)&MemCfg.SAILCTRL_GAIN_PM);
		remoteSetParameter(ID_SAILCTRL_SP_LONG, *(Payload*)&MemCfg.SAILCTRL_SP_LONG);
		remoteSetParameter(ID_SAILCTRL_SP_LAT, *(Payload*)&MemCfg.SAILCTRL_SP_LAT);
		remoteSetParameter(ID_SAILCTRL_CAL_VAL, *(Payload*)&MemCfg.SAILCTRL_CAL_VAL);

		if( (*(uint32_t*)&MemCfg.IMU_YawOffset) == ~(uint32_t)0)
			MemCfg.IMU_YawOffset = 0;

		IMU_setYawOffset(MemCfg.IMU_YawOffset);
	}


	for(;;)
	{
		//wait for data from remotetask
		if(xQueueReceive(xQueueEeprom, &qItem, 100) == pdTRUE )
		{
			//this stores the value in the local config struct
			switch(qItem.msgId)
			{
			case ID_CONFIG:

				switch(*(uint32_t*)&qItem.val)
				{
				case CFG_MANUAL:
				case CFG_AUTOMATIC:
					MemCfg.config = ( MemCfg.config & (~(CFG_MANUAL | CFG_AUTOMATIC)) )  | *(uint32_t*)&qItem.val;
				break;
				case CFG_CAL_CTRL_ON:
				case CFG_CAL_CTRL_OFF:
					MemCfg.config = ( MemCfg.config & (~(CFG_CAL_CTRL_ON | CFG_CAL_CTRL_OFF)) )  | *(uint32_t*)&qItem.val;
				break;
				case CFG_CAL_SETNORTH:
					MemCfg.IMU_YawOffset = IMU_getYawOffset();
				break;
				}

			break;
			case ID_MOTCTRL_P:			MemCfg.MOTCTRL_P = qItem.val;		 break;
			case ID_MOTCTRL_I:			MemCfg.MOTCTRL_I = qItem.val;		 break;
			case ID_MOTCTRL_D:			MemCfg.MOTCTRL_D = qItem.val;		 break;
			case ID_SAILCTRL_GAIN_P:	MemCfg.SAILCTRL_GAIN_P = qItem.val;	 break;
			case ID_SAILCTRL_GAIN_I:	MemCfg.SAILCTRL_GAIN_I = qItem.val;	 break;
			case ID_SAILCTRL_GAIN_PM:	MemCfg.SAILCTRL_GAIN_PM = qItem.val; break;
			case ID_SAILCTRL_SP_LONG:	MemCfg.SAILCTRL_SP_LONG = qItem.val; break;
			case ID_SAILCTRL_SP_LAT:	MemCfg.SAILCTRL_SP_LAT = qItem.val;	 break;
			case ID_SAILCTRL_CAL_VAL:	MemCfg.SAILCTRL_CAL_VAL = qItem.val; break;
			default: 					continue;
			}

			datRcvFlag = 1;
			tck = HAL_GetTick() + 5000;
		}

		//if data has been received, and it is more than 5 sec ago, store in flash
		if(datRcvFlag)
		{
			if(HAL_GetTick() > tck)
			{
				datRcvFlag = 0;
				MemCfg.ValidData = EEPROM_VALID_DATA;
				eraseSect23();
				prgmBytes(0, (uint8_t*)&MemCfg, sizeof(MEM_CFG));
			}
		}

	}

}
