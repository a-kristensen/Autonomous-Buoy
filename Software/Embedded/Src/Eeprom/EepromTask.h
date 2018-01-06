/*
 * EepromTask.h
 *
 *  Created on: 11. dec. 2017
 *      Author: Neophyte
 */

#ifndef EEPROMTASK_EEPROMTASK_H_
#define EEPROMTASK_EEPROMTASK_H_

#include "cmsis_os.h"
#include "../debug/debug.h"
#include "../RemoteTask/RemoteTask.h"

typedef struct
{
	float val;
	MSG_ID msgId;

} EEPROM_CFG_ITEM;


#define VOLTAGE_RANGE           (uint8_t)VOLTAGE_RANGE_3
#define EEPROM_VALID_DATA				0x96
#define SECT23_ADDR				((uint32_t)(0x081E0000))

osThreadId EepromTaskHandle;
void StartEepromTask(void const * argument);

void EepromSetParam(MSG_ID, Payload);

#endif /* EEPROMTASK_EEPROMTASK_H_ */
