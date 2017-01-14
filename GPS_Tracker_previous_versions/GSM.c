/**
  ******************************************************************************
  * @file    GSM.c
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  ******************************************************************************
 */ 


#include "stm32f10x.h"
#include "GSM.h"



void GSM_Init(void){
  
  GPIO_InitTypeDef GPIO_InitStruct;     
  USART_InitTypeDef USART_InitStruct;   
  NVIC_InitTypeDef NVIC_InitStructure;  

  SysTick_Config(SystemCoreClock / 1000);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  
  GPIO_InitStruct.GPIO_Pin = GSM_PIN_TXD | GSM_PIN_RXD | GSM_PIN_DTR;                 
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                   
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_PinRemapConfig(GPIO_PartialRemap_USART3 , ENABLE);
  GPIO_Init(GSM_GPIOx, &GPIO_InitStruct);

  
  USART_InitStruct.USART_BaudRate = GSM_Baudrate ;                               
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;                       
  USART_InitStruct.USART_StopBits = USART_StopBits_1;                            
  USART_InitStruct.USART_Parity = USART_Parity_No;                                
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                    
  USART_Init(USART3 , &USART_InitStruct);                                         
  
  
  
  USART_ITConfig(USART3 , USART_IT_RXNE, ENABLE);                       
  
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;           
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;             
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      
  NVIC_Init(&NVIC_InitStructure);          


  USART_Cmd(USART3 , ENABLE);
  
  
  GPIO_InitStruct.GPIO_Pin = GSM_PIN_PWR | GSM_PIN_RESET;         
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_Init(GSM_GPIOx, &GPIO_InitStruct);
  
  GPIO_InitStruct.GPIO_Pin = GSM_PIN_DTR;         
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;    
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;            
  GPIO_Init(GSM_GPIOx, &GPIO_InitStruct);
}


//void GSM_Power_On(void);
//void GSM_Power_Reset(void);
//void GSM_Config(GSM_Struct*, uint8_t);
//void GSM_Net_Sync(GSM_Struct*);
//void GSM_Tel_Sync(GSM_Struct*);
//void GSM_Mode(GSM_Struct*,GSMMode_TypeDef);