/**
  ******************************************************************************
  * @file    interrupts.c
  * @author  lukas
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include <interrupts.h>
#include "stm32f3xx.h"


/* DCC Interrupt Variablen */
int8_t t=0, i=8;
TypeDefRecstate recstate;
_Bool bit;
uint8_t byte;

/* Globale Variablen */
extern volatile uint8_t package[3];
extern volatile _Bool received;
extern volatile int set;


void SysTick_Handler(void){
}


void TIM2_IRQHandler(void){
	bit = !((_Bool)(GPIOA->IDR & 1));			// Status PA0 auslesen -> inverser Wert ist Bit
	switch(recstate){							// Recstate abfragen
		case WF_Preamble:						// Warten auf die Preambel
			if((bit==1) && (t<10)) t++;			// Preambel noch nicht vorbei
			if((bit==1) && (t>=10)){			// Preambel vorbei
				recstate=WF_Lead0;				// Nächster Status: Warten auf das Trennbit
			}
			if(bit==0) t=0;						// Synchronisierungsfehler, reset
			break;
		case WF_Lead0:							// Auf Trennbit warten
			if (bit==0) recstate=WF_Byte;		// Falls Trennbit erkannt, erstes Byte auslesen
			else recstate=WF_Preamble;
			break;
		case WF_Byte:							// Auf Byte warten
			package[byte] |= bit<<(i-1);		// Bitstelle des Bytes auslesen und speichern
			i--;
			if(i<=0){							// Ende des Bytes erreicht
				recstate=WF_Trailer;			// Warten auf das nächste Trennbit
				byte++;							// nächstes Byte auswählen
				i=8;							// Bitstelle zurücksetzten
			}
			break;
		case WF_Trailer:						// Auf Trenn- oder Stopbit warten
			if(bit==0) recstate=WF_Byte;		// Trennbit erkannt, nächstes Byte auslesen
			if(bit==1){							// Stopbit erkannt, rücksetzten der Indizes
				received=1;						// main() signalisieren, dass package bereit steht
				byte=0;
				i=8;
				t=0;
				recstate=WF_Preamble;			// warten auf nächstes package
				}
			break;
	}
	/* ISR finished */
	TIM2->SR &= ~TIM_SR_UIF;
}

void ADC1_2_IRQHandler(void){
	if (POTI<10)
	{
		ADC2->TR1 =0xFFFF0000;
		LEDoffl;
		LEDonr;
		set=3;
	}
	else if (POTI>4085)
	{
		ADC2->TR1 =0xFFFF0000;
		LEDoffr;
		LEDonl;
		set=3;
	}

	H_BRIDGE_OFF;
	NVIC_ClearPendingIRQ(ADC1_2_IRQn); //Interruptflag cleared
	ADC2->ISR		|= 0x0080;		   //ADC interruptflag cleared

}

void EXTI0_IRQHandler(void){			//button links
	LEDoffr;
	blinkonl;
	H_BRIDGE_ON;
	MOTOR_LEFT;
	ADC2->TR1=0xFFD00000;
	set=2;
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	EXTI->PR = 0x1;
}

void EXTI1_IRQHandler(void){			//button rechts
	LEDoffl;
	blinkonr;
	H_BRIDGE_ON;
	MOTOR_RIGHT;
	ADC2->TR1=0xFFFF000A;
	set=1;
	NVIC_ClearPendingIRQ(EXTI1_IRQn);
	EXTI->PR = 0x2;
}

