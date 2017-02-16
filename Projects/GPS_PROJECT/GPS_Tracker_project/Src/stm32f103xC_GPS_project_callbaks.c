
#include "main.h"
#include "usbd_cdc_if.h"

extern  uint8_t buffer_GSM_Rx[200];
extern uint8_t buffer_GPS_Rx[200];


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    
  
  if (huart->Instance==GSM_UART)
    ClearBufferRxGSM();
  else if (huart->Instance==GPS_UART)
    ClearBufferRxGPS();   
      
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  
    if (huart->Instance==GSM_UART)
  { 
    
    ClearBufferRxGSM();
  }
  else if (huart->Instance==GPS_UART)
  {
    
    ClearBufferRxGPS();  
  }
 
}