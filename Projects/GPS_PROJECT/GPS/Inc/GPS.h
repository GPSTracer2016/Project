/**
  ******************************************************************************
  * @file    GPS.h 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  ******************************************************************************
 */ 


#include "stm32f1xx_hal.h"


// GSM_MODULE: SIM28 PINS
#define GPS_RCC_UART_CLK_ENABLE                 __HAL_RCC_USART2_CLK_ENABLE
#define GPS_RCC_UART_CLK_DISABLE                __HAL_RCC_USART2_CLK_DISABLE
#define GPS_RCC_GPIO                            RCC_APB2Periph_GPIOA
#define GPS_GPIO                                GPIOA 
#define GPS_UART                                USART2 
#define GPS_Baudrate                            115200      
#define GPS_PIN_RXD                             GPIO_PIN_3
#define GPS_PIN_TXD                             GPIO_PIN_2
#define GPS_IRQn                                USART2_IRQn
#define GPS_UART_ENABLE_IT_TC                   __HAL_UART_ENABLE_IT(&GPS_UART_HANDLE, UART_IT_TC)
#define GPS_UART_ENABLE_IT_RXNE                 __HAL_UART_ENABLE_IT(&GPS_UART_HANDLE, UART_IT_RXNE)



typedef enum {
  GPS_IDLE = 1,
  GPS_CALC = 2
}GPSState_TypeDef;



typedef struct {
  char latitude [11];
  char longitude[12];
  char UTC_Time[13] ;
  char N_S_Indicator[4];
  char E_W_Indicator[4];
  char Position_Fix_Indicator[4];
  char Satellites_Used[4];
  char HDOP[10];
  char MSL_Altitude[10];
  char Units[5];
}GPSInfo_TypeDef;

typedef struct{
  GPSState_TypeDef GPS_State;
  GPSInfo_TypeDef  GPS_Info;
 }GPS_Struct;

void GPS_Init(void);
int GPS_intercomma_parser(char *,char []);
void GPS_GPGGA_Parser(char [] );
void ClearBufferRxGPS(void);
void GPS_Sync(GPS_Struct*);
void GPS_Sleep(GPS_Struct*);
void GPS_Ready(GPS_Struct);
GPSInfo_TypeDef GPS_Get_Pos(GPS_Struct);
GPSState_TypeDef GPS_Get_State(GPS_Struct);
void GPS_Set_State(GPS_Struct*);
void GPS_Set_Mode(GPS_Struct*);
void GPS_To_GSM(char*,GPS_Struct);



