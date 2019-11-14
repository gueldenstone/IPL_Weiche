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
#include "config.h"
#include "main.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

//Variablen initialisieren
TypeDefRecstate recstate;
volatile int8_t t=0, i=7; //received;
volatile uint8_t paket[3], byte, dcc_adress;
_Bool received, bit, newbit;


int main(void)
{
	/*Configuration
	 *
	 */
	RCC_Config();					//Clock Config
	GPIO_Config(); 					//GPIO Config
	EXTI_Config();					//Config Interrupts
	TIM_Config();					//Config Timer

	/*DCC_Decode
	 *
	 */
	dcc_adress = getadress();		//Adresse auslesen
	while(1){
		if(received==1){				GPIOA->ODR |= GPIO_ODR_5; while(1){}}
		else 						GPIOA->ODR &= ~(GPIO_ODR_5);

	/*Stepper
	 *
	 */

	}
}

uint8_t getadress(void){
	uint8_t adress=0;
	adress |= (GPIOB->IDR & GPIO_IDR_3)<<7;
	adress |= (GPIOB->IDR & GPIO_IDR_4)<<6;
	adress |= (GPIOB->IDR & GPIO_IDR_5)<<5;
	adress |= (GPIOB->IDR & GPIO_IDR_6)<<4;
	adress |= (GPIOB->IDR & GPIO_IDR_7)<<3;
	adress |= (GPIOB->IDR & GPIO_IDR_8)<<2;
	adress |= (GPIOB->IDR & GPIO_IDR_9)<<1;
	adress |= (GPIOB->IDR & GPIO_IDR_10)<<0;
	return adress;
}
