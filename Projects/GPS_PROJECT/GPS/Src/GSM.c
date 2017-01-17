/**
  ******************************************************************************
  * @file    GSM.c
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  ******************************************************************************
 */ 



#include "main.h"


/* UART handler declared in "main.c" file */
extern UART_HandleTypeDef GSM_UART_HANDLE;
extern char* buffer_GSM_Tx;
extern uint8_t buffer_GSM_Rx[200];
extern char cz;
extern volatile uint8_t msg[60];

extern MACHINE_STRUCT machine;

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

        
static void GSM_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
   GSM_RCC_GPIOA_CLK_ENABLE();                
   GSM_RCC_GPIOB_CLK_ENABLE();                
   GSM_RCC_GPIOD_CLK_ENABLE();
  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GSM_PIN_STATUS;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GSM_GPIO, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB3 */
  GPIO_InitStruct.Pin = GSM_PIN_PWR | GSM_PIN_DTR;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GSM_GPIO, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GSM_GPIO, GSM_PIN_PWR, GPIO_PIN_SET);
  
  GPIO_InitStruct.Pin = GSM_LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GSM_LED_GPIO, &GPIO_InitStruct);
  
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GSM_LED_GPIO, GSM_LED_PIN, GPIO_PIN_RESET);
}

static void GSM_USART3_UART_Init(void)
{
  
  GSM_UART_HANDLE.Instance              = GSM_UART;

  GSM_UART_HANDLE.Init.BaudRate         = 115200;
  GSM_UART_HANDLE.Init.WordLength       = UART_WORDLENGTH_8B;
  GSM_UART_HANDLE.Init.StopBits         = UART_STOPBITS_1;
  GSM_UART_HANDLE.Init.Parity           = UART_PARITY_NONE;
  GSM_UART_HANDLE.Init.HwFlowCtl        = UART_HWCONTROL_NONE;
  GSM_UART_HANDLE.Init.Mode             = UART_MODE_TX_RX;
  GSM_UART_HANDLE.Init.OverSampling     = UART_OVERSAMPLING_16;
  if(HAL_UART_Init(&GSM_UART_HANDLE) != HAL_OK)
  {
    Error_Handler();
  }  
}        


 void GSM_Init(void){
   
  /*GSM GPIO init */
  GSM_GPIO_Init() ;
  /*GSM USART init*/
  GSM_USART3_UART_Init();
  /*GSM Power On*/
  
if (!HAL_GPIO_ReadPin(GSM_GPIO,GSM_PIN_STATUS))
    GSM_Pwr_On();
  else 
    GSM_Reset();
  
  
 GSM_UART_ENABLE_IT_TC ;
 GSM_UART_ENABLE_IT_RXNE ;
 
  HAL_Delay(10000); 
  
    while (strcmp(buffer_GSM_Rx,"\r\nOK\r\n")!=0)
{      
      memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));
      HAL_UART_Transmit_IT(&GSM_UART_HANDLE, "AT\r" , sizeof("AT\r"));
      HAL_Delay(2000);
}

    while (strcmp(buffer_GSM_Rx,"\r\nOK\r\n")!=0)
{      
      memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));
      HAL_UART_Transmit_IT(&GSM_UART_HANDLE, "AT+IPR=115200\r" , sizeof("AT+IPR=115200\r"));
      HAL_Delay(3000);
}

machine.GSM_module.GSM_State=GSM_IDLE;
sprintf(machine.GSM_module.GSM_Info.GSM_Numb,TARGET_NUMBER);
sprintf(machine.GSM_module.GSM_Info.GSM_Url,TARGET_URL );
while (!getImei());
}


/***
  *****Power on function****
  */
   
    
uint8_t GSM_Pwr_On(void){
  
  while(!HAL_GPIO_ReadPin(GSM_GPIO,GSM_PIN_STATUS))
  {
    HAL_GPIO_WritePin(GSM_GPIO,GSM_PIN_PWR,GPIO_PIN_RESET);
    HAL_Delay(2000); 
    //attendre au moins une seconde pour le demarrage du module GSM (PWR->LOW)
  }
  HAL_GPIO_WritePin(GSM_GPIO,GSM_PIN_PWR,GPIO_PIN_SET);
  HAL_Delay(1000); 
  if (HAL_GPIO_ReadPin(GSM_GPIO,GSM_PIN_STATUS))
  {
    HAL_GPIO_WritePin(GSM_LED_GPIO, GSM_LED_PIN , GPIO_PIN_SET);
    machine.GSM_module.GSM_Mode=GSM_ON;
    return 1;
  }
  else 
    return 0;
}


uint8_t GSM_Pwr_Off(void){
  HAL_GPIO_WritePin(GSM_GPIO,GSM_PIN_PWR,GPIO_PIN_RESET);
  HAL_Delay(3000); //attendre au moins une seconde pour l'arret du module GSM (PWR->LOW)
  HAL_GPIO_WritePin(GSM_GPIO,GSM_PIN_PWR,GPIO_PIN_SET);
  HAL_Delay(1000);
  if (HAL_GPIO_ReadPin(GSM_GPIO,GSM_PIN_STATUS))
    return 0;
  else 
  {
    HAL_GPIO_WritePin(GSM_LED_GPIO, GSM_LED_PIN,GPIO_PIN_RESET);
    machine.GSM_module.GSM_Mode=GSM_OFF;
    return 1;
  }
}

uint8_t getImei(void){
       int i=0;
       int r=0;
       
      memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));
      sendAtcmd("AT+CGSN\r");
      HAL_Delay(1000);
      
      if (buffer_GSM_Rx[0]=='\r' && buffer_GSM_Rx[1]=='\n' && buffer_GSM_Rx[17]=='\r' && buffer_GSM_Rx[18]=='\n' ){
        for (i=2;i<=16;i++)
          sprintf(machine.GSM_module.GSM_Info.GSM_Imei,"%s%c",machine.GSM_module.GSM_Info.GSM_Imei,buffer_GSM_Rx[i]);
        
        r=1; 
      }
      
          
          
      return r;
}
  


uint8_t GSM_Reset(void){
 if (GSM_Pwr_Off())
   return GSM_Pwr_On();
 else 
   return 0;
}

void GSM_AT_cmd(uint8_t *ATcmd){
  //memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));
  HAL_UART_Transmit_IT(&GSM_UART_HANDLE, ATcmd , sizeof(ATcmd));
  
}

void ClearBufferRxGSM(void){
      
      GSM_UART_HANDLE.pRxBuffPtr=buffer_GSM_Rx;
}

void GSM_SendSMS(uint8_t *msg){

char smsTo[200]=""; 

 sprintf(smsTo,"AT+CMGS=\"%s\"\r",machine.GSM_module.GSM_Info.GSM_Numb);

memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));
while (strcmp(buffer_GSM_Rx,"\r\nOK\r\n")!=0)
{      
      sendAtcmd("AT+CSCS=\"GSM\"\r");
      HAL_Delay(4000);  
}      


while (strcmp(buffer_GSM_Rx,"\r\nOK\r\n")!=0)
{      
      memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));
      sendAtcmd("AT+CMGF=1\r");
      HAL_Delay(4000);  
}

      sendAtcmd(smsTo);
      HAL_Delay(2000);  
     
while (strcmp(buffer_GSM_Rx,"\r\n> \r\n")!=0);
        
      sendAtcmd(msg);
      HAL_Delay(1000);
      sendAtchar(26);
      HAL_Delay(3000);

}

void sendAtcmd(char* atc){
  uint8_t i=0;
  sprintf((char*)msg,atc);
  while (msg[i] != '\0' )
  {
    i++;
  }
  if (i!=0)
    HAL_UART_Transmit_IT(&GSM_UART_HANDLE, (uint8_t *) atc,i-1);
    HAL_Delay(200);
    if (msg[i-1] == '\r')
      HAL_UART_Transmit_IT(&GSM_UART_HANDLE, "\r",1);
    memset((char*)msg, '\0', sizeof(msg));
      
}

void sendAtchar(char atc){
 
    HAL_UART_Transmit_IT(&GSM_UART_HANDLE, (uint8_t *) &atc,1);
      
}

int GSM_HttpRequest(void){
  int r=0;
  int i=0;
  char url[100];
  memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));  
  while (strcmp(buffer_GSM_Rx,"\r\nOK\r\n")!=0)
{
  memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));  
  sendAtcmd("AT+SAPBR=3,1,\"APN\",\"weborange\"\r");
  HAL_Delay(7000);  
} 

  memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));  

  sendAtcmd("AT+SAPBR=3,1,\"USER\",\"\"\r");
  HAL_Delay(2000);  
  sendAtcmd("AT+SAPBR=3,1,\"PWD\",\"\"\r");
  HAL_Delay(2000); 
  
  while (strcmp(buffer_GSM_Rx,"\r\nOK\r\n")!=0)
{
  sendAtcmd("AT+CGATT?\r");
  HAL_Delay(4000); 
}

  memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));  
  sendAtcmd("AT+SAPBR=1,1\r");
  HAL_Delay(4000);


  sendAtcmd("AT+SAPBR=2,1\r");
  HAL_Delay(4000); 
  
  sendAtcmd("AT+HTTPINIT\r");
  HAL_Delay(4000);
  
  sendAtcmd("AT+HTTPPARA=\"CID\",1\r");
  HAL_Delay(4000);
  
  sprintf(url,"AT+HTTPPARA=\"URL\",\"%simei=%s&lat=%s&long=%s&nsi=%s&ewi=%s&pfi=%s&su=%s&HDOP=%s&msl=%s&Units=%s\"\r",
          machine.GSM_module.GSM_Info.GSM_Url,
          machine.GSM_module.GSM_Info.GSM_Imei,
          machine.GPS_module.GPS_Info.latitude,
          machine.GPS_module.GPS_Info.longitude,
          machine.GPS_module.GPS_Info.N_S_Indicator,
          machine.GPS_module.GPS_Info.E_W_Indicator,
          machine.GPS_module.GPS_Info.Position_Fix_Indicator,
          machine.GPS_module.GPS_Info.Satellites_Used,
          machine.GPS_module.GPS_Info.HDOP,
          machine.GPS_module.GPS_Info.MSL_Altitude,
          machine.GPS_module.GPS_Info.Units);
          
  
  memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));
  sendAtcmd(url);
  HAL_Delay(4000);

  sendAtcmd("AT+HTTPACTION=0\r");  
  HAL_Delay(4000);
  
  memset(buffer_GSM_Rx,'\0',sizeof(buffer_GSM_Rx));
  sendAtcmd("AT+HTTPREAD\r");  
  HAL_Delay(2000);
  
  sendAtcmd("AT+HTTPTERM\r"); 
  HAL_Delay(3000);    
  
  sendAtcmd("AT+SAPBR=0,1\r"); 
  HAL_Delay(3000);
  
  while (buffer_GSM_Rx[i]!='\0' && r==0){
      if (buffer_GSM_Rx[i]=='2' && buffer_GSM_Rx[i+1]=='O' && buffer_GSM_Rx[i+2]=='K')
        r=1;
      else
        i++;
  }
  
return r;  
}

void SendPosSMS(void){
 
  char pos[200]="";
  sprintf(pos,"lat: %s\nlong: %s\ntime: %s\n NS_I: %s\nEW_I: %s\nAlt:%s\nUnit:%s\r", 
          machine.GPS_module.GPS_Info.latitude, 
          machine.GPS_module.GPS_Info.longitude, 
          machine.GPS_module.GPS_Info.UTC_Time, 
          machine.GPS_module.GPS_Info.N_S_Indicator, 
          machine.GPS_module.GPS_Info.E_W_Indicator, 
          machine.GPS_module.GPS_Info.MSL_Altitude, 
          machine.GPS_module.GPS_Info.Units);
  
          GSM_SendSMS((char*)pos);
   
}
