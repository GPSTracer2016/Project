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
  
  machine.GPS_module.GPS_State=GPS_CALC;  
  
  while (
   strcmp(machine.GPS_module.GPS_Info.latitude,"N/A")==0 ||
   strcmp(machine.GPS_module.GPS_Info.latitude,"")==0)
  {
      HAL_Delay(10000);  
      GPS_GPGGA_Parser(buffer_GPS_Rx);
  }

  machine.GPS_module.GPS_State=GPS_IDLE; 
  
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
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.UTC_Time);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.latitude);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.N_S_Indicator);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.longitude);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.E_W_Indicator);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.Position_Fix_Indicator);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.Satellites_Used);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.HDOP);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.MSL_Altitude);
  GPGGA_msg+=i;
  i=GPS_intercomma_parser(GPGGA_msg,machine.GPS_module.GPS_Info.Units);
  GPGGA_msg+=i;
  
  if(strcmp(machine.GPS_module.GPS_Info.latitude,"N/A")!=0 && strcmp(machine.GPS_module.GPS_Info.E_W_Indicator,"N/A")!=0)
    GPS_feet(machine.GPS_module.GPS_Info.latitude,machine.GPS_module.GPS_Info.E_W_Indicator);
  
  if(strcmp(machine.GPS_module.GPS_Info.longitude,"N/A")!=0 && strcmp(machine.GPS_module.GPS_Info.N_S_Indicator,"N/A")!=0)
     GPS_feet(machine.GPS_module.GPS_Info.longitude,machine.GPS_module.GPS_Info.N_S_Indicator);
  
}

void ClearBufferRxGPS(void)
{      
      GPS_UART_HANDLE.pRxBuffPtr=buffer_GPS_Rx;
}


void GPS_feet(char* nmea,char* type){
	/*double l=0;
	char* loc ;
	double sec=0;


        
        l= atof(num);
	loc = strchr(num,'.');
	sec = strtod(loc+1, NULL);
	l = (double) ((atoi(num)/100)%100)  + (double) ((double) ( atoi(num)/100)/60) + (double) ( (double)(sec/100)/3600);
        

*/
  /*
      int d1,d2;
      int dd;
      double mm;
      char cdd[5], cmm[10];
      int idx, dot = 0;
      double dec = 0;
      
      for (idx=0; idx<strlen(nmea);idx++){
          if (nmea[idx] == '.'){
              dot = idx;
              break;
          }
      }

      memset(&cdd, 0, 5);
      memset(&cmm, 0, 10);
      strncpy(cdd, nmea, dot-2);
      strcpy(cmm, nmea+dot-2);
      dd = atoi(cdd);
      mm = atof(cmm);
      dec = dd + (mm/60);

      if (strcmp(type,"S")==0 || strcmp(type,"W")==0)
          dec=-dec;
      d1 = dec;
      dec=dec-d1;
      d2 = dec*1000000000;
      
      
      
      
      
      if (((int)(dec*10)%10)==0)
      {
      memset(nmea,'\0',strlen(nmea));
      sprintf(nmea,"%d.0%d",d1,d2);
      }
      else 
      {
      memset(nmea,'\0',strlen(nmea));
      sprintf(nmea,"%d.%d",d1,d2);
      }*/
        int d1,d2;
      int dd;
      double mm;

      char cdd[5], cmm[10];
      int idx, dot = 0;
      double dec = 0;
            
      char zeros[32]="";
      for (idx=0; idx<strlen(nmea);idx++){
          if (nmea[idx] == '.'){
              dot = idx;
              break;
          }
      }

      memset(&cdd, 0, 5);
      memset(&cmm, 0, 10);
      strncpy(cdd, nmea, dot-2);
      strcpy(cmm, nmea+dot-2);
      dd = atoi(cdd);
      mm = atof(cmm);
      dec = dd + (mm/60);
      double temp=dec;
      if (strcmp(type,"S")==0 || strcmp(type,"W")==0)
          dec=-dec;
      d1 = dec;
      dec=dec-d1;
      d2 = dec*1000000000;
      
int counter=0;
      while ( (int)(temp*10)% 10==0){
	temp*=10;
	++counter;
      }
      
int iii;
for(iii=0;iii<counter;++iii){
	zeros[iii]='0';
}
      zeros[iii]='\0';
      memset(nmea,'\0',strlen(nmea));
      sprintf(nmea,"%d.%s%d",d1,zeros,d2);
      
  
  
}