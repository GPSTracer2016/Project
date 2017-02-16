
// GSM_MODULE: SIM800H PINS

#define GSM_GPIOx                               GPIOB 
#define GSM_USARTx                              USART3 
#define GSM_Baudrate                            9600
#define GSM_PIN_TXD                             GPIO_PIN_10
#define GSM_PIN_RXD                             GPIO_PIN_11
#define GSM_PIN_DTR                             GPIO_PIN_3               
#define GSM_PIN_RESET                           GPIO_PIN_12
#define GSM_PIN_PWR                             GPIO_PIN_1
#define GSM_PIN_STATUS                          GPIO_PIN_0
#define GSM_RCC_UART                            RCC_APB1Periph_USART3
#define GSM_RCC_GPIO                            RCC_APB2Periph_GPIOB
#define GSM_IRQn                                USART3_IRQn


#define GSM_LED_PIN                             GPIO_PIN_8
#define GSM_LED_GPIO                            GPIOA
#define GSM_LED_RCC                             RCC_APB2Periph_GPIOA

#define TARGET_NUMBER                         "50231000"
#define AT_SMS_SEND                           "AT+CMGF=1\r"
#define AT_SMS_TO                             "AT + CMGS = \"+21650231000\""
#define AT_MSG                                "Hello"
#define AT_END_MSG                            (char)26


// GSM_MODULE: SIM28 PINS
#define GPS_RCC_UART                            RCC_APB1Periph_USART2
#define GPS_RCC_GPIO                            RCC_APB2Periph_GPIOA
#define GPS_GPIOx                               GPIOA 
#define GPS_USARTx                              USART2 
#define GPS_Baudrate                            115200      
#define GPS_PIN_RXD                             GPIO_PIN_2
#define GPS_PIN_TXD                             GPIO_PIN_3
#define GPS_IRQn                                USART2_IRQn
