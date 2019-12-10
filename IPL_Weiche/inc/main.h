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

/* Weiche */
#define H_BRIDGE_OFF	(GPIOC->BRR |=0x0001) //H_Bridge OFF PA3/(PC0 für test)
#define H_BRIDGE_ON 	(GPIOC->BSRR|=0x0001) //H_Bridge ON  PA3/(PC0 für test)
#define MOTORPWM_OFF 	TIM8->CCER&=~0x00000011;
#define MOTOR_LEFT 		TIM8->CCER=0x0000005F;
#define MOTOR_RIGHT		TIM8->CCER=0x00000055;

/* LEDs */
#define blinkonr	TIM4->CCR1=500
#define blinkonl	TIM4->CCR2=500
#define LEDonr		TIM4->CCR1=1000
#define LEDonl		TIM4->CCR2=1000
#define LEDoffr		TIM4->CCR1=0000
#define LEDoffl		TIM4->CCR2=0000
#define LED_ARR		(1000)

/* Buttons & Poti */
#define BUTTON_LEFT (GPIOA->IDR & 0x2)
#define BUTTON_RIGHT (GPIOB->IDR & 0x1)
#define POTI ADC2->DR //4095 links;0 rechts

/* Prototypes -----------------------------------------------------------------*/
void Error_Handler(void);
uint8_t getadress(void);
void checkpos(void);

#endif /* __MAIN_H */
