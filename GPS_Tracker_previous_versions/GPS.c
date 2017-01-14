/**
  ******************************************************************************
  * @file    GPS.c 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  ******************************************************************************
 */ 


#include "stm32f10x.h"
#include "GPS.h"

void GPS_Init(void){
  
  GPIO_InitTypeDef GPIO_InitStruct;     // this is for the GPIO pins used as TX and RX
  USART_InitTypeDef USART_InitStruct;   // this is for the USART1 initilization
  NVIC_InitTypeDef NVIC_InitStructure;  // this is used to configure the NVIC (nested vector interrupt controller)
  
  RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  
  GPIO_InitStruct.GPIO_Pin = GPS_PIN_TXD | GPS_PIN_RXD;         // Pins 3 (TX) and 2 (RX) are used
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 			// the pins are configured as alternate function so the USART peripheral has access to them
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;		        // this defines the IO speed and has nothing to do with the baudrate!
	
  
  GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
  GPIO_Init(GPS_GPIOx, &GPIO_InitStruct);
  
	/* Now the USART_InitStruct is used to define the 
	 * properties of USART1 
	 */
  
  USART_InitStruct.USART_BaudRate = GPS_Baudrate ;				// the baudrate is set to the value we passed into this init function
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;                        // we want the data frame size to be 8 bits (standard)
  USART_InitStruct.USART_StopBits = USART_StopBits_1;		                // we want 1 stop bit (standard)
  USART_InitStruct.USART_Parity = USART_Parity_No;		                // we don't want a parity bit (standard)
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    // we don't want flow control (standard)
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                    // we want to enable the transmitter and the receiver
  USART_Init(USART1, &USART_InitStruct);					        // again all the properties are passed to the USART_Init function which takes care of all the bit setting
	
	
  
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt 
  
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		         // we want to configure the USART1 interrupts
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;              // this sets the priority group of the USART1 interrupts
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		         // this sets the subpriority inside the group
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 // the USART1 interrupts are globally enabled
  NVIC_Init(&NVIC_InitStructure);					 // the properties are passed to the NVIC_Init function which takes care of the low level stuff	

  // finally this enables the complete USART1 peripheral
  USART_Cmd(USART1, ENABLE);

}


//void GPS_Config(GPS_Struct*, uint8_t);
//void GPS_Sync(GPS_Struct*);
//void GPS_Mode(GPSMode_TypeDef , GPS_Struct *);