


/**
  ******************************************************************************
  * @file    main.h 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    04/01/2011
  * @brief   Main program body
  ******************************************************************************
 */ 



#include "GSM.h"
#include "GPS.h"
#include "cons_config.h"

typedef enum {
  IDLE = 1,
  MSG_SEND,
  MSG_RECEIVE,
  NET_REQUEST
}MACHINEState_TypeDef;
  


typrdef struct {
  GSM_Struct GSM_module;
  GPS_Struct GPS_module;
  MACHINEState_TypeDef MACHINE_State; 
  uint8_t GPSPeriodic_FLAG;
  uint8_t NETPeriodic_FLAG;
  uint8_t SMSPeriodic_FLAG;
}MACHINE_STRUCT


void machine_init(MACHINE_STRUCT*);
void machine_Enable_Sync(MACHINE_STRUCT*,uint8_t);
void machine_Disable_Sync(MACHINE_STRUCT*,uint8_t);
void machine_Routine(MACHINE_STRUCT*);
void machine_decrementDelay(MACHINE_STRUCT*);