/*
 * SPITask.h
 *
 *  Created on: 30. okt. 2017
 *      Author: Neophyte
 */

#ifndef SPITASK_SPITASK_H_
#define SPITASK_SPITASK_H_

#include "cmsis_os.h"
#include "../debug/debug.h"


typedef struct {
    float p;
    float i;
    float d;
    float intg;
    float intgr_lim;
    float prev_err;
    uint32_t prev_tck;
} pid_ctrl_t;



//with these two, the task can be started from another file
osThreadId SPITaskHandle;
void StartSPITask(void const * argument);

//input: pos: range -100 <-> 0 <-> 100
void SPI_setPosition(signed char);
unsigned char SPI_getPosition(void);
void SPI_startCalibrate(void);

pid_ctrl_t SPI_getMotParam(void);
void SPI_setMotParam(const pid_ctrl_t* const);


#endif /* SPITASK_SPITASK_H_ */
