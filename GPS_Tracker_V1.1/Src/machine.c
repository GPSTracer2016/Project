


/*
  ******************************************************************************
  * @file    main.h 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    04/01/2011
  * @brief   Main program body
  ******************************************************************************
 */ 



#include "machine.h"
uint16_t MinDelay=0;
extern MACHINE_STRUCT machine;
extern uint8_t buffer_GPS_Rx[3000];


void MAC_init(MACHINE_STRUCT* machine){
  machine->MACHINE_State=MAC_CONF;
  machine->NETerr_FLAG=0x0;
  machine->Err_Limit=15;
  GSM_Init();
  GPS_Init();
  machine->SYNC_Period= 1; //en minute
  machine->SYNC_CountDown= machine->SYNC_Period;
  MinDelay=60000;
  machine->MACHINE_State=MAC_IDLE;
}

void MAC_Decr_Delay (void){
  machine.SYNC_CountDown--;
  if ( machine.SYNC_CountDown==0 ){
    machine.MACHINE_State=MAC_CALC;
  }else
    MinDelay=60000;
}


void MAC_Routine(void){
  
  switch (machine.MACHINE_State)
  {
      case MAC_IDLE:
        break;
        
      case MAC_CALC:
        machine.GPS_module.GPS_State=GPS_CALC;
        break;
        
      case MAC_SYNC:
        machine.GSM_module.GSM_State=GSM_NET_SYNC;
        if (machine.NETerr_FLAG==machine.Err_Limit)
        {
          machine.MACHINE_State=MAC_ERR;
          machine.GSM_module.GSM_State=GSM_SEND_SMS;
        }
        break;
        
      case MAC_ERR:
        break;
        
      case MAC_RST:
        machine.NETerr_FLAG=0;
        machine.SYNC_CountDown=machine.SYNC_Period;
        MinDelay=60000;
        machine.MACHINE_State=MAC_IDLE;
        machine.GPS_module.GPS_State=GPS_IDLE;
        machine.GSM_module.GSM_State=GSM_IDLE;
        break;
        
      }
  
  
  
  
    switch (machine.GPS_module.GPS_State)
  {
      case GPS_IDLE:
        break;
        
      case GPS_CALC:
        GPS_GPGGA_Parser(buffer_GPS_Rx);
        machine.MACHINE_State=MAC_SYNC;
        machine.GPS_module.GPS_State=GPS_IDLE;
        break;
      }
  
  
  
  
    switch (machine.GSM_module.GSM_State)
  {
      case GSM_IDLE:
        break;
        
      case GSM_SEND_SMS:
        SendPosSMS();
        machine.GSM_module.GSM_State=GSM_IDLE;
        machine.MACHINE_State=MAC_RST;
        break;
        
      case GSM_NET_SYNC:
        if (!GSM_HttpRequest())
          machine.NETerr_FLAG++;
        else
          machine.MACHINE_State=MAC_RST;
        break;
      }


}