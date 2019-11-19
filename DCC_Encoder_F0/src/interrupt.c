/*
 * interrupt.c
 *
 *  Created on: 13.11.2019
 *      Author: lukas
 */

#include "stm32f0xx_it.h"

/* ISR */

/* EXTI */

void EXTI0_1_IRQHandler(void){
	go=1;
	//ISR finished
	NVIC_ClearPendingIRQ(EXTI0_1_IRQn);
	EXTI->PR |= EXTI_PR_PR0;
}

void TIM6_DAC_IRQHandler(void){
	//ISR finished
	NVIC_ClearPendingIRQ( TIM6_DAC_IRQn);
	TIM6->SR &= ~TIM_SR_UIF;
}
//
//void TIM7_IRQHandler(void){
//
//
//	//ISR finished
//	NVIC_ClearPendingIRQ(TIM7_IRQn);
//	TIM7->SR &= ~TIM_SR_UIF;
//}

