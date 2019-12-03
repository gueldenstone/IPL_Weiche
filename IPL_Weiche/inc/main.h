/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx.h"

/* Variables -----------------------------------------------------------------*/
typedef enum{WF_Preamble, WF_Lead0, WF_Byte, WF_Trailer}TypeDefRecstate;
typedef enum{Left,Right}TypeDefPosition;
typedef struct{
	const uint8_t address;
	const _Bool moving;
	const TypeDefPosition position;
}TypeDefTurnout;
typedef struct{
	uint8_t dcc_address;
	uint8_t turnout_address;
	_Bool direction;
}TypeDefPackage;

/* Defines -------------------------------------------------------------------*/
//DCC-Decode
#define DCC_SAMPLEPOINT 86

//Weiche
#define H_BRIDGE_ON	 (GPIOA->BRR |=0x0010); //H_Bridge ON
#define H_BRIDGE_OFF (GPIOA->BSRR|=0x0010); //H_Bridge OFF
#define MOTORPWM_OFF 	TIM1->CCER&=~0x00000011;
#define MOTOR_LEFT 		TIM1->CCER=0x0000005F;
#define MOTOR_RIGHT		TIM1->CCER=0x00000055;
#define blinkonr	TIM3->CCR1=400;
#define blinkonl	TIM3->CCR2=400;
#define LEDonr		TIM3->CCR1=4095;
#define LEDonl		TIM3->CCR2=4095;
#define LEDoffr		TIM3->CCR1=0000;
#define LEDoffl		TIM3->CCR2=0000;

/* Prototypes -----------------------------------------------------------------*/
void Error_Handler(void);
uint8_t getadress(void);


#endif /* __MAIN_H */
