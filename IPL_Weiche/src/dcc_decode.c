#include "main.h"
#include "dcc_decode.h"


//Variablen
TypeDefRecstate recstate=WF_Preamble;
volatile uint8_t bit=0, t=0, i=7, b=0, received=0;
volatile uint8_t paket[3]={0,0,0};

void EXTI_Config(void){
	EXTI->IMR |= EXTI_IMR_IM1; 		//Maske Pin Interrupt 1
	EXTI->RTSR |= EXTI_RTSR_RT1;	//Rising Edge Trigger ausgewählt
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB; //Connect EXTI1 mit Port B
	NVIC_EnableIRQ(EXTI1_IRQn); //Enable NVIC on EXTI1
}

void TIM_Config(uint32_t count){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; //Enable Timer6 Clock
	TIM6->ARR = (count*470); //set counter value
	TIM6->PSC = 12;
	TIM6->CR1 |= TIM_CR1_ARPE; //enable auto reload preload
	//TIM6->CR1 |= TIM_CR1_URS; //Update source only at overflow
	TIM6->CR1 |= TIM_CR1_OPM; //Enable one-pulse Mode
	TIM6->DIER |= TIM_DIER_UIE; //Enable Interrupt on Update
	NVIC_EnableIRQ(TIM6_DAC_IRQn); //Enable NVIC on TIM6
}


void EXTI1_IRQHandler(void){
 	NVIC_ClearPendingIRQ(EXTI1_IRQn);
	EXTI->PR |= EXTI_PR_PR1;
	GPIOC->ODR ^= GPIO_ODR_8;

}

void TIM6_DAC_IRQHandler(void){
	bit= ~(GPIOB->IDR & GPIO_IDR_1);
	switch(recstate){
	case WF_Preamble:
		if((bit==1) && (t<=10)) t++;
		if((bit==1) && (t>10)) recstate=WF_Lead0;
		else t=0;
		break;
	case WF_Lead0:
		if (bit==0) recstate=WF_Byte;
		break;
	case WF_Byte:
		paket[b] |= bit<<i;
		i--;
		if(i<=0) recstate=WF_Trailer;
		break;
	case WF_Trailer:
		if(b==0){
			recstate=WF_Byte;
			b++;
		}
		if(bit==1){
			received=1;
			b=0;
			i=7;
			t=0;
			bit=0;
			recstate=WF_Preamble;
		}

		break;
	}

 }
