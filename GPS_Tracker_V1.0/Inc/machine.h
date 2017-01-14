


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
  MAC_CALC,
  MAC_SYNC,
  MAC_CONF,
  MAC_SEND,
}MACHINEState_TypeDef;
  


typedef struct {
  GSM_Struct GSM_module;
  GPS_Struct GPS_module;
  MACHINEState_TypeDef MACHINE_State;
  //uint8_t NETPeriodic_FLAG;
  uint8_t SMSPeriodic_FLAG;
  uint8_t SYNC_CountDown;
  uint8_t SYNC_Period;
  }MACHINE_STRUCT;


void MAC_init(MACHINE_STRUCT*);
void MAC_EP(MACHINE_STRUCT*);
void MAC_DP(MACHINE_STRUCT*);
void MAC_Set_State(MACHINE_STRUCT*,MACHINEState_TypeDef);
void MAC_Get_State(MACHINE_STRUCT);
void MAC_Routine(MACHINE_STRUCT);
void MAC_Dec_Delay(MACHINE_STRUCT);

