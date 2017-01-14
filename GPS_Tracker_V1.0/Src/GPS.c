/**
  ******************************************************************************
  * @file    GPS.c
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  ******************************************************************************
 */ 



#include "main.h"

extern UART_HandleTypeDef GPS_UART_HANDLE;
extern char* buffer_GPS_Tx;
extern uint8_t buffer_GPS_Rx[200];

/*******Init function******/
  /* Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */  /* Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */


static void GPS_USART2_UART_Init(void)
{
  
  GPS_UART_HANDLE.Instance              = GPS_UART;

  GPS_UART_HANDLE.Init.BaudRate         = 115200;
  GPS_UART_HANDLE.Init.WordLength       = UART_WORDLENGTH_8B;
  GPS_UART_HANDLE.Init.StopBits         = UART_STOPBITS_1;
  GPS_UART_HANDLE.Init.Parity           = UART_PARITY_NONE;
  GPS_UART_HANDLE.Init.HwFlowCtl        = UART_HWCONTROL_NONE;
  GPS_UART_HANDLE.Init.Mode             = UART_MODE_TX_RX;
  GPS_UART_HANDLE.Init.OverSampling     = UART_OVERSAMPLING_16;
  if(HAL_UART_Init(&GPS_UART_HANDLE) != HAL_OK)
  {
    Error_Handler();
  }  
}        
        
 void GPS_Init(void){
   
  /*GPS USART init*/
  GPS_USART2_UART_Init();
  
  GPS_UART_ENABLE_IT_TC ;
  GPS_UART_ENABLE_IT_RXNE ;
  
}



/**
  *****Power on function****
  */
void ClearBufferRxGPS(void)
{      
      GPS_UART_HANDLE.pRxBuffPtr=buffer_GPS_Rx;
}

