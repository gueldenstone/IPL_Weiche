/**
  ******************************************************************************
  * @author  Lukas Güldemstein
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
//Includes
#include <stdio.h>
#include <stdlib.h>

//Private Includes
#include "dcc_decode.h"
#include "main.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32f3xx.h"

//Variablen

int main(void)
{
	/*Configuration
	 *
	 */
	RCC_Config();					//Clock Config
	GPIO_Config(); 					//GPIO Config
	EXTI_Config();					//Config Interrupts
	TIM_Config(1);				//Config Timer

	/*DCC_Decode
	 *
	 */
	uint8_t dcc_address=0x01;
	while(1)
	{
		if(received==1 && paket[1]==dcc_address)	GPIOA->ODR |= GPIO_ODR_5;
		else 										GPIOA->ODR &= ~(GPIO_ODR_5);

	}
	/*Stepper
	 *
	 */
}


