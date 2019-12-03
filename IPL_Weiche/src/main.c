/**
  ******************************************************************************
  * @author  Kevin Heidenreich & Lukas Güldemstein
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
//Includes
#include <stdio.h>
#include <stdlib.h>

//Private Includes
#include "main.h"
#include "config.h"
#include "interrupts.h"
#include "stm32f3xx.h"

//Variablen initialisieren
volatile uint8_t package[3], parity, switch_address;
volatile uint16_t dcc_address;
volatile _Bool received;
volatile TypeDefTurnout turnout1;	// turnout Data
volatile TypeDefPackage rPackage;	// received Package


int main(void){
	__disable_irq();				//Interrupts ausschalten

	/* Configuration */
	RCC_Config();					//Clock Config auf 72Mhz durch
	GPIO_Config(); 					//GPIO Config
	TIM_Config();					//Config Timer

	/* Initialisierung/Kalibrierung */
	dcc_address = 0x1A2;			//Adresse auslesen

	__enable_irq();					//Interrupts einschalten

	//Schleife
	while(1){

		/* DCC Decode */
		if(received){
			rPackage.turnout_address=(package[1] & 0x6)>>1;		//Weichenadresse auslesen
			rPackage.direction=(package[1] & 0x1);				//Richtung auslesen
			/*	byte 1		byte 2
				10AAAAAA  	1AAA1BBR

				A=address
				B=turnout
				R=direction
			*/
			rPackage.dcc_address = ((package[0] & 0x3F)<<3) | ((package[1] & 0x70)>>4);	//DCC-Adresse auslesen
			//Pariät prüfen
			if((package[0]^package[1])==package[2]){
				parity = 1;
			}
			/* DCC Adresse prüfen */
			if(rPackage.dcc_address==dcc_address && parity){
				switch(rPackage.turnout_address){

				}
				GPIOA->ODR |= GPIO_ODR_5;
				received=0;
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
