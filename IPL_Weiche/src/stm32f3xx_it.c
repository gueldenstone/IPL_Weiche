/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t t = 7;
volatile uint8_t byte=0xAAU;
volatile char bit;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void SysTick_Handler(void){
	//GPIOC->ODR ^= GPIO_ODR_8; //Toggle Pin
	if(t>=0){
		switch((byte>>t)&1){
		case 1:
			GPIOC->ODR |= GPIO_ODR_8;
			GPIOC->ODR ^= GPIO_ODR_9;
			break;
		case 0:
			GPIOC->ODR &= ~(GPIO_ODR_8);
			GPIOC->ODR ^= GPIO_ODR_9;
			break;
		}
		t--;
	}

}

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

