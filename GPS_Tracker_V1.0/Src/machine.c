


/**
  ******************************************************************************
  * @file    main.h 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    04/01/2011
  * @brief   Main program body
  ******************************************************************************
 */ 



#include "machine.h"


void MAC_init(MACHINE_STRUCT* machine){
  machine->MACHINE_State=MAC_IDLE;
  machine->SMSPeriodic_FLAG=0x1;
  machine->SYNC_Period= 255;
  machine->SYNC_CountDown= machine->SYNC_Period;
  //GSM_init(&(machine->GSM_module));
  //GPS_init(&(machine->GPS_module));
}
