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
extern GPS_Struct GPS ;

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

  GPS_UART_HANDLE.Init.BaudRate         = GPS_Baudrate;
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

int GPS_intercomma_parser(char *buffer,char struct_field[])
{
  int i = 0;
  int flag_comma=0 ;
  while(*buffer!=',')
  {
    flag_comma=1 ;
        struct_field[i]=*buffer;
        i++;
        buffer++;
  }
  if(flag_comma==0)
    strcpy(struct_field,"N/A\0");
  else 	struct_field[i]='\0';
  return (i+1);

}

void GPS_GPGGA_Parser(char buffer_GPS_Rx[] )
{
  char *GPGGA_msg ;
  char *NMEA_type="$GPGGA";
  int i = 0;
  GPGGA_msg=strstr(buffer_GPS_Rx,NMEA_type);
  GPGGA_msg+=7;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.UTC_Time);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.latitude);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.N_S_Indicator);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.longitude);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.E_W_Indicator);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.Position_Fix_Indicator);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.Satellites_Used);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.HDOP);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.MSL_Altitude);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,GPS.GPS_Info.Units);
  GPGGA_msg+=i;
}

void ClearBufferRxGPS(void)
{      
      GPS_UART_HANDLE.pRxBuffPtr=buffer_GPS_Rx;
}

