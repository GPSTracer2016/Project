/**
  ******************************************************************************
  * @file    GPS.h 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  ******************************************************************************
 */ 


#ifndef __GPS_H
#define __GPS_H



typedef enum {
  IDLE = 1,
  INFO_REQUEST 
}GPSState_TypeDef;
  
typedef enum {
  FULL = 1,
  SLEEP 
}GPSMode_TypeDef;


typedef struct {
  char* Latitude;
  char* longitude;
  char* UTC_Time;
  char* N_S_Indicator;
  char* E_W_Indicator;
  char* Position_Fix_Indicator;
  char* Satellites Used;
  char* HDOP;
  char* MSL Altitude;
  char* Units;
}GPS_Info_TypeDef;

typedef struct{
  char* GPS_IMEI;
  GPSMode_TypeDef GPS_Mode;
  GPSState_TypeDef GPS_State;
  GPSInfo_TypeDef GPS_Info;
  uint8_t Ready_flag;
  uint8_t countdown;
  uint8_t rate;
 }GPS_Struct;



void GPS_Init(void);
//void GPS_Config(GPS_Struct*, uint8_t);
//void GPS_Sync(GPS_Struct*);
//void GPS_Mode(GPSMode_TypeDef , GPS_Struct *);
