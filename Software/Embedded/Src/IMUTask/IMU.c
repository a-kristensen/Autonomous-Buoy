#include "IMU.h"

struct IMU_s IMU;
float f_IMURelOffset;
float yawTmp;

/**
 * @brief IMU::request
 * @param cmd can be one of the commands defined in:
 * EasyObjectDictionary.h
 */

void initIMU(){
	// initialize IMU and send a command request
	EasyProfile_C_Interface_Init();
}


void IMU_SetNorth(void)
{
	f_IMURelOffset = yawTmp;
}

float IMU_getYawOffset(void)
{
	return f_IMURelOffset;
}
void IMU_setYawOffset(float f)
{
	f_IMURelOffset = f;
}



void request(uint cmd){
	    uint16 toId = EP_ID_BROADCAST_;
		char*  txData;
		int    txSize;
		int status = EasyProfile_C_Interface_TX_Request(toId, cmd, &txData, &txSize);
		if(status == EP_SUCC_){  // You can request a different data type by changing the EP_CMD_RPY_ to some other value defined in EasyObjectDictionary.h
			UartSend(txData, (uint)txSize);    //Send the request via Serial Port.
		} else
		{
			//IMUTask_DbgMsg("Command for IMU not send: %i",status);
		}

}

/**
 * @brief IMU::SerialPort_DataRecieve
 * @param rxData is the recieved data to send to the IMU packet parser
 *  	  rxSize is the size of the recieved Data
 * @Desc  Parses the recieved data in to valid packages. If a package is complete and correct
 * the command for which the package belongs is selected
 */
void SerialPort_DataReceive(char rxData, int rxSize){
	Ep_Header header; // Then let the EasyProfile do the rest such as data assembling and checksum verification.
	int status = EasyProfile_C_Interface_RX(&rxData, (int)rxSize, &header);
	float tmpclc = 0;

	// If a correct and complete package is recieved, then update the belonging values:
    if( status == EP_SUCC_ ){
    	//HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
        switch (header.cmd) {
            case EP_CMD_RPY_:{
            // Roll Pitch Yaw data received
            HAL_GPIO_TogglePin(GPIOB, LD2_Pin);
            IMU.timeStamp = ep_RPY.timeStamp;
            //IMU.roll  = ep_RPY.roll;        // Note 1, ep_RPY is defined in the EasyProfile library as a global variable
            IMU.roll = (ep_RPY.roll > 180 ? ep_RPY.roll - 360 : ep_RPY.roll);
            IMU.pitch = ep_RPY.pitch;       // Note 2, for the units and meaning of each value, refer to EasyObjectDictionary.h

            yawTmp = (ep_RPY.yaw < 0 ? ep_RPY.yaw + 360 : ep_RPY.yaw);
            tmpclc = yawTmp - f_IMURelOffset;

            if(tmpclc < 0)
            	IMU.yaw =  360 + tmpclc;
            else if(tmpclc > 360)
            	IMU.yaw =  tmpclc - 360;
            else
            	IMU.yaw =  tmpclc;

            IMU.yaw = 360 - IMU.yaw;

            }break;
        }
    }
}
