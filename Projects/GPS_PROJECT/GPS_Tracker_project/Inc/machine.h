


/**
  ******************************************************************************
  * @file    main.h 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    04/01/2011
  * @brief   Main program body
  ******************************************************************************
 */ 

#include "stm32f1xx_hal.h"
#include "GPS.h"
#include "GSM.h"
#include <string.h>
#include <stdio.h>

typedef enum {
  MAC_IDLE = 1,
  MAC_CALC = 2,
  MAC_SYNC = 3,
  MAC_CONF =4,
  MAC_ERR = 5,
  MAC_RST = 6,
}MACHINEState_TypeDef;
  


typedef struct {
  GSM_Struct GSM_module;
  GPS_Struct GPS_module;
  MACHINEState_TypeDef MACHINE_State;
  uint8_t GPSNewFLAG;
  uint8_t NETerr_FLAG;
  uint8_t Err_Limit;
  uint16_t MinDelay;
  uint8_t Activ_Period;
  uint8_t SYNC_CountDown;
  uint8_t SYNC_Period;
  }MACHINE_STRUCT;


void MAC_init(MACHINE_STRUCT*);
void MAC_Routine(void);
void MAC_Decr_Delay (void);

