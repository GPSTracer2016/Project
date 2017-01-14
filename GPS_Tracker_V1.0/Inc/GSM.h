/**
  ******************************************************************************
  * @file    GSM.h 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  ******************************************************************************
 */ 



#include "stm32f1xx_hal.h"


// GSM_MODULE: SIM800H PINS

#define GSM_GPIO                                GPIOB 
#define GSM_UART                                USART3 
#define GSM_Baudrate                            115200
#define GSM_PIN_TXD                             GPIO_PIN_10
#define GSM_PIN_RXD                             GPIO_PIN_11
#define GSM_PIN_DTR                             GPIO_PIN_3               
#define GSM_PIN_RESET                           GPIO_PIN_12
#define GSM_PIN_PWR                             GPIO_PIN_1
#define GSM_PIN_STATUS                          GPIO_PIN_0
#define GSM_RCC_UART_CLK_ENABLE                 __HAL_RCC_USART3_CLK_ENABLE
#define GSM_RCC_UART_CLK_DISABLE                __HAL_RCC_USART3_CLK_DISABLE
#define GSM_RCC_GPIOA_CLK_ENABLE                __HAL_RCC_GPIOA_CLK_ENABLE
#define GSM_RCC_GPIOB_CLK_ENABLE                __HAL_RCC_GPIOB_CLK_ENABLE
#define GSM_RCC_GPIOD_CLK_ENABLE                __HAL_RCC_GPIOD_CLK_ENABLE
#define GSM_IRQn                                USART3_IRQn
#define GSM_UART_ENABLE_IT_TC                   __HAL_UART_ENABLE_IT(&GSM_UART_HANDLE, UART_IT_TC)
#define GSM_UART_ENABLE_IT_RXNE                 __HAL_UART_ENABLE_IT(&GSM_UART_HANDLE, UART_IT_RXNE)
#define USART_GSM_IRQHandler                    USART3_IRQHandler


#define GSM_LED_PIN                             GPIO_PIN_8
#define GSM_LED_GPIO                            GPIOA
#define GSM_LED_RCC                             RCC_APB2Periph_GPIOA

#define TARGET_NUMBER                         "50231000"
#define AT_SMS_SEND                           "AT+CMGF=1\r"
#define AT_SMS_TO                             "AT + CMGS = \"+21650231000\""
#define AT_MSG                                "Hello"
#define AT_END_MSG                            (char)26

typedef enum {
  GSM_IDLE = 1,
  MSG_SEND,
  MSG_RECV,
  NET_SYNC
}GSMState_TypeDef;
  
typedef enum {
  GSM_FULL = 1,
  MINIMUM,
  FLIGHT
}GSMMode_TypeDef;

typedef struct {
  char* GSM_Imei;
  char* GSM_Numb;
  char* GSM_Url;
}GSM_Info_TypeDef;

typedef struct{  
  GSMState_TypeDef GSM_State ;
  GSMMode_TypeDef GSM_Mode ; 
}GSM_Struct; 


void GSM_Init(void);

//Power functions 
uint8_t GSM_Pwr_On(void);
uint8_t GSM_Pwr_Off(void);
uint8_t GSM_Reset(void);

void GSM_HttpRequest(void);
void ClearBufferRxGSM(void);
void GSM_SendSMS(uint8_t *msg);
void sendAtchar(char atc);
void SendPosSMS(void);
//communication functions
void sendAtcmd(char *ATcmd);
void GSM_AT_cmd(uint8_t *ATcmd);
void GSM_Net_Sync(char* url);
void GSM_Send_Msg(char* msg,char* numb); 
void GSM_Get_Numb(GSM_Struct*,char* numb);
void GSM_Get_URL(GSM_Struct,char* URL);
void GSM_Set_Numb(GSM_Struct*,char* numb);
void GSM_Set_URL(GSM_Struct*,char* URL);
GSM_Info_TypeDef GSM_Get_Info(GSM_Struct);
GSMMode_TypeDef GSM_Get_Mode(GSM_Struct);
GSMState_TypeDef GSM_Get_State(GSM_Struct);
void GSM_Set_Mode(GSM_Struct*,GSMMode_TypeDef Mode);
void GSM_Set_State(GSM_Struct*,GSMState_TypeDef State);
void GSM_Get_Imei(char*Imei,GSM_Struct);