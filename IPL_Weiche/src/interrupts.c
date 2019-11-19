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
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void SysTick_Handler(void){
}

void EXTI0_IRQHandler(void){
 	NVIC_ClearPendingIRQ(EXTI1_IRQn);
	EXTI->PR |= EXTI_PR_PR1;
	TIM6->CR1 |= TIM_CR1_CEN;
	//ISR finished


}

void TIM6_DAC_IRQHandler(void){
	bit = !((_Bool)(GPIOA->IDR & 1));
	GPIOA->ODR &= ~GPIO_ODR_5;
	switch(recstate){
		case WF_Preamble:
			if((bit==1) && (t<10)) t++;
			if((bit==1) && (t>=10)){
				recstate=WF_Lead0;
			}
			if(bit==0) t=0;
			break;
		case WF_Lead0:
			if (bit==0) recstate=WF_Byte;
			break;
		case WF_Byte:
			package[byte] |= bit<<(i-1);
			i--;
			if(i<=0){
				recstate=WF_Trailer;
				byte++;
				i=8;}
			break;
		case WF_Trailer:
			if(bit==0) recstate=WF_Byte;
			if(bit==1){
				received=1;
				byte=0;
				i=8;
				t=0;
				recstate=WF_Preamble;
				}
			break;
	}

//ISR finished
NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
TIM6->SR &= ~TIM_SR_UIF;
}
