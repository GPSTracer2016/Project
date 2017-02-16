


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

extern MACHINE_STRUCT machine;
extern uint8_t buffer_GPS_Rx[3000];


void MAC_init(MACHINE_STRUCT* machine){
  machine->MACHINE_State=MAC_CONF;
  machine->NETerr_FLAG=0x0;
  machine->Err_Limit=5;
  GPS_Init();
  GSM_Init();
  machine->GPSNewFLAG=0;
  machine->Activ_Period=1;
  machine->SYNC_Period= 15; //en minute
  machine->SYNC_CountDown= machine->SYNC_Period;
  machine->MinDelay=60000;
  machine->MACHINE_State=MAC_IDLE;
  GSM_sleep();
}

void MAC_Decr_Delay (void){
  if (machine.Activ_Period!=0)
  {
    if ( machine.MinDelay!=0)
    {
        machine.MinDelay--;
        if (machine.MinDelay == 0)
        {
          if ( machine.SYNC_CountDown!=0 ){
          machine.SYNC_CountDown--;
          }
          
          if ( machine.SYNC_CountDown==0 ){
            machine.MACHINE_State=MAC_CALC;
            machine.Activ_Period=0;
          }
          else
            machine.MinDelay=60000;
        }
    }
    
  }
  
  
  

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
        if (machine.GSM_module.GSM_Mode==GSM_SLEEP)
          GSM_wake();
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
        machine.GPSNewFLAG=0;
        machine.SYNC_CountDown=machine.SYNC_Period;
        machine.MinDelay=60000;
        machine.Activ_Period=1;
        machine.MACHINE_State=MAC_IDLE;
        machine.GPS_module.GPS_State=GPS_IDLE;
        machine.GSM_module.GSM_State=GSM_IDLE;
        GSM_sleep();
        break;
        
      }
  
  
  
  
    switch (machine.GPS_module.GPS_State)
  {
      case GPS_IDLE:
        break;
        
      case GPS_CALC:
        
        GPS_GPGGA_Parser(buffer_GPS_Rx);
         while (strcmp(machine.GPS_module.GPS_Info.latitude,"N/A")==0)
        {
            HAL_Delay(10000);  
            GPS_GPGGA_Parser(buffer_GPS_Rx);
        }
        if (strncmp(machine.GPS_module.GPS_Info.latitude,machine.GPS_module.GPS_OLDInfo.latitude,6)!=0 || 
            strncmp(machine.GPS_module.GPS_Info.longitude,machine.GPS_module.GPS_OLDInfo.longitude,6)!=0)
        {
          machine.GPSNewFLAG=1;
          machine.GPS_module.GPS_OLDInfo= machine.GPS_module.GPS_Info;
        }
        
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
        machine.MACHINE_State=MAC_RST;
        break;
        
      case GSM_NET_SYNC:
        if ( machine.GPSNewFLAG==1)
          GSM_HttpRequest();
        else
          machine.MACHINE_State=MAC_RST;
        break;
   }


}