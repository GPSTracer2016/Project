/**
  ******************************************************************************
  * @file    main.c 
  * @author  Hamza Meddeb / Nour Laaribi / Safwen Baroudi
  * @version V1.0.0
  * @date    28/12/2016
  * @brief   Main program body
  ******************************************************************************
 */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "machine.h"

/* Global Declaration --------------------------------------------------------*/
   
    
extern volatile MACHINE_STRUCT machine;

    
/* main function ------------------------------------------------------*/

int main(void)
{    
  machine_init(&machine);
  
  while (1)
  {
    
  }
}
/******************* (C) ENSI 2016 *****END OF FILE****************************/