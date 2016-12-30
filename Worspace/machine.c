


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






void machine_init(MACHINE_STRUCT* machine){
  GPIO_AFIODeInit();
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB)
  GPS_Init();
  GSM_Init();
  machine_Disable_Sync(machine,0);
  machine_Disable_Sync(machine,1);
  machine_Disable_Sync(machine,2);
}


void machine_Enable_Sync(MACHINE_STRUCT* machine,uint8_t flag){
  if (flag==0)
       machine->GPSPeriodic_FLAG=1;
  else if (flag == 1)
       machine->GPSPeriodic_FLAG=1;
  else if (flag == 2)
       machine->GPSPeriodic_FLAG=1;
}

void machine_Disable_Sync(MACHINE_STRUCT* machine,uint8_t){
    if (flag==0)
       machine->GPSPeriodic_FLAG=0;
    else if (flag == 1)
       machine->GPSPeriodic_FLAG=0;
    else if (flag == 2)
       machine->GPSPeriodic_FLAG=0;
  
}
