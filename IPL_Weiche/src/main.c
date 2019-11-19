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
volatile int8_t t=0, i=8; //received;
volatile uint8_t package[3], byte, parity, switch_address;
volatile uint16_t dcc_address, package_address;
volatile _Bool received, bit, newbit;
volatile TypeDefTurnout turnout;


int main(void)
{
	__disable_irq();				//Interrupts ausschalten
	/* Configuration */
	RCC_Config();					//Clock Config
	GPIO_Config(); 					//GPIO Config
	EXTI_Config();					//Config Interrupts
	TIM_Config();					//Config Timer

	/* Initialisierung/Kalibrierung */
	GPIOA->ODR |= GPIO_ODR_3;

	__enable_irq();					//Interrupts einschalten

	//Schleife
	while(1){

	/* DCC Decode */
	dcc_address = 0x1A2;		//Adresse auslesen

		if(received){
			turnout.address=(package[1] & 0x6)>>1;
			turnout.direction=(package[1] & 0x1);
			/*	byte 1		byte 2
				10AAAAAA  	1AA11BBR

				A=address
				B=turnout
				R=direction
			*/

			package_address = ((package[0] & 0x3F)<<3) | ((package[1] & 0x70)>>4);
			//Pariät prüfen
			if((package[0]^package[1])==package[2]){
				parity = 1;
			}
			if(package_address==dcc_address && parity){
				GPIOA->ODR |= GPIO_ODR_5;
				received=0;
				GPIOA->ODR |= GPIO_ODR_2;
			}
			else received=0;
		}
	}
}


//noch buggy
uint8_t get_address(void){
	uint8_t address=0;
	address |= (GPIOB->IDR & GPIO_IDR_3)<<7;
	address |= (GPIOB->IDR & GPIO_IDR_4)<<6;
	address |= (GPIOB->IDR & GPIO_IDR_5)<<5;
	address |= (GPIOB->IDR & GPIO_IDR_6)<<4;
	address |= (GPIOB->IDR & GPIO_IDR_7)<<3;
	address |= (GPIOB->IDR & GPIO_IDR_8)<<2;
	address |= (GPIOB->IDR & GPIO_IDR_9)<<1;
	address |= (GPIOB->IDR & GPIO_IDR_10)<<0;
	return address;
}
