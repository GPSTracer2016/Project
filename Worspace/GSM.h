/**
  ******************************************************************************
  * @file    GSM.h 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  ******************************************************************************
 */ 


#ifndef __GSM_H
#define __GSM_H

typedef enum {
  IDLE = 1,
  MSG_SEND,
  MSG_RECEIVE,
  NET_REQUEST
}GPSState_TypeDef;
  
typedef enum {
  FULL = 1,
  MINIMUM,
  FLIGHT
}GPSMode_TypeDef;

typedef struct {
  char* GSM_Imei;
  char* GSM_Number;
  char* GSM_Address;
  Char* GSM_message;
}GPS_Info_TypeDef;

typedef struct{  
  char* GSM_Imei ;
  char* GSM_Number_Target ;
  GSMState_TypeDef GSM_State ;
  GSMState_TypeDef GSM_Mode ;
  uint8_t SMScountdown;
  uint8_t SMSrate;
  uint8_t NETcountdown;
  uint8_t NETrate;
}GSM_Struct;


void GSM_Init(void);
void GSM_Power_On(void);
//void GSM_Power_Reset(void);
//void GSM_Config(GSM_Struct*, uint8_t);
//void GSM_Net_Sync(GSM_Struct*);
//void GSM_Tel_Sync(GSM_Struct*);
//void GSM_Mode(GSM_Struct*,GSMMode_TypeDef);

