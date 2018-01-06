
//---- Includes ----//
#include "IMUTask.h"

#include "usart.h"


unsigned char rx_char;
HAL_StatusTypeDef status_send;

QueueHandle_t xQueueIMU;

void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN USART2_IRQn 1 */
  //HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
  xQueueSendToBackFromISR(xQueueIMU, &rx_char, NULL);
  HAL_UART_Receive_IT(&huart5, &rx_char, 1);
  /* USER CODE END USART2_IRQn 1 */
}


struct IMU_s getIMUData()
{
	return IMU;
}

void StartIMUTask(void const * argument)
{
	f_IMURelOffset = 0;

  initIMU();
  request(EP_CMD_RPY_);
  xQueueIMU = xQueueCreate(100, sizeof(char));

  MX_UART5_Init();

  HAL_UART_Receive_IT(&huart5, &rx_char, 1);
  int i = 0;
  int status;
  char read;
  for(;;)
  {
		  status = xQueueReceive(xQueueIMU, &read, 500);// Recieve one byte from the IMU and send it to the intepreter
		  if(status == pdTRUE)
		  {
			  SerialPort_DataReceive((char)read,1);
		  }
		  else
		  {
			  osDelay(10);
		  }
		 i++;
		 osDelay(1);
  }
}


/**
 * @brief Sensor::UartSend
 * @param data is the data to send to the UART
 *  	  length is the size of the Data
 * @Desc  Transmits data to the UART in a blocking manner with 1s timeout
 */
void UartSend(char* data, uint length){

	status_send = HAL_UART_Transmit(&huart5,(uint8_t*)(data),length,1000);
	if(status_send != HAL_OK){
		//IMUTask_DbgMsg("Error Transmitting data: %i",(int)status_send);
	}
}

