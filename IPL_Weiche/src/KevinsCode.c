/**
  ******************************************************************************
  * @file    main.c
  * @author  Kevin Heidenreich
  * @version V346.0
  * @date    27-NOVEMBER-2019
  * @brief   IPL_WEICHE_FINAL_PIN
  ******************************************************************************
*/

#include "stm32f30x.h"
#include "stdlib.h"
#include "math.h"

void CLOCK_CONFIG (void)
{
	RCC->AHBENR		|= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_ADC12EN |RCC_AHBENR_GPIOCEN;
	RCC->APB1ENR    |= RCC_APB1ENR_TIM4EN;												//LED's
	RCC->APB2ENR	|= RCC_APB2ENR_TIM8EN |RCC_APB2ENR_SYSCFGEN;											//PWM OUT
}

void EXTI13_CONFIG (void)
{
	SYSCFG->EXTICR[3] 		|= 0x0020; //PC_13
	EXTI->IMR				|= EXTI_IMR_MR13;
	EXTI->FTSR				|= EXTI_FTSR_TR13;

	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI1_CONFIG (void)
{
	SYSCFG->EXTICR[0] 		|= 0x0001; //PA_1
	EXTI->IMR				|= EXTI_IMR_MR1;
	EXTI->RTSR				|= EXTI_RTSR_TR1;

	NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI0_CONFIG (void)
{
	SYSCFG->EXTICR[0] 		|= 0x0000; //PB_0
	EXTI->IMR				|= EXTI_IMR_MR0;
	EXTI->RTSR				|= EXTI_RTSR_TR0;

	NVIC_EnableIRQ(EXTI0_IRQn);
}

void GPIOx_CONFIG (void)

{
	GPIOA->MODER	|= 0x92800340;			 //PA3 OUTPUT;PA4 ANALOG(ADC); PA11/12/15 ALTERNATE_FUNCTIO
	GPIOA->PUPDR	 = 0x00000028;			 //Pulldown for PA1/2 (ButtonL_R)
	GPIOA->AFR[1]	|= 0x200AA000;			//TIM_4_CH_1(PA11),CH_2(PA12);TIM8CH1 (PA15)

	GPIOB->MODER	|= 0x00020280;			 //PB3/4/8 ALTERNATE TIM_CH_1N(PB3) CH_2N(PB4) CH_2(PB8)
	GPIOB->PUPDR	|= 0x00000002;			 //PB0 PuLLDOWN (TEST,BUTTON)
	GPIOB->AFR[0]	|= 0x00044000;			 //TIM8 CH_1N/2N
	GPIOB->AFR[1]	|= 0x0000000A;			 //TIM_CH_2

	GPIOC->MODER	|= 0x00000001;
#define BUTTON_LEFT (GPIOA->IDR & 0x2)
#define BUTTON_RIGHT (GPIOB->IDR & 0x1)




#define H_BRIDGE_OFF	(GPIOC->BRR |=0x0001) //H_Bridge OFF PA3/(PC0 für test)
#define H_BRIDGE_ON 	(GPIOC->BSRR|=0x0001) //H_Bridge ON  PA3/(PC0 für test)
	H_BRIDGE_OFF;
}

void ADC2_CONFIG (void)
{
	ADC1_2->CCR		|= 0x00010000; 			 // Synchroner ADC-Clock ,Vorteiler 1
	ADC2->SQR1		|= 0x00000040; 			 // 1st conv. in regular sequence: Channel 1 (PA4)
	ADC2->CR 	    &=~0x30000000; 		     // Voltage regulator: Intermediate state (0b11 << 28), 10 resetstate
	ADC2->CR 		|= 0x50000000; 			 // Voltage regulator: Enabled (0b01 << 28) DifferentialMode
	ADC2->SMPR1		|= 0x00000000;			 //601.5 clockcycles
	for (volatile int x = 0; x < 60; x++){}  // Warte 10 us
	ADC2->CR 		|= 0x80000000; 			 // Kalibriere den ADC
	while ((ADC2->CR & 0x80000000) != 0){}   // Warte bis Kalibrierung abgeschlossen
	ADC2->IER		 = 0x0080; 				 //INTERRUPT enable analog watchdog1
	ADC2->TR1		 = 0xFFD00014;			 	 //0x007C [H]->124->bei 100mA über 1 OHM
	ADC2->CFGR		 = 0x04C03000;			 //Watchdog Enable on regular channels(23),AWD1CH 2(29-26),continuous (13),overrunmode(12)

	ADC2->CR 		|= 0x00000001; 		 	 // Enable ADC
	while((ADC2->ISR & 0x00000001) == 0){} 	 // Warte bis ADC bereit
	ADC2->CR		|= 0x00000004;			 //start regular conversation
	NVIC_EnableIRQ (ADC1_2_IRQn);

	#define POTI ADC2->DR
	//4095 links;0 rechts

}

void TIM4_CONFIG (void)
{
	TIM4->CCMR1		 = 0x6060;					//PWM MODE 1, reference manual->CNT<CCRx HIGH
	TIM4->CCER		 = 0x0011;					//Chanels ON

#define blinkonr	TIM4->CCR1=2000;
#define blinkonl	TIM4->CCR2=2000;
#define LEDonr		TIM4->CCR1=4095;
#define LEDonl		TIM4->CCR2=4095;
#define LEDoffr		TIM4->CCR1=0000;
#define LEDoffl		TIM4->CCR2=0000;

	TIM4->PSC		 = 1999;					//alle 0.1ms
	TIM4->ARR		 = 4095;					//Max counternum.
	TIM4->CCR1		 = 2000;					//Ontime LEDon (undefinierter zustand) BEIDE LEDs BLINKEN
	TIM4->CCR2		 = 2000;					//Ontime LEDon (undefinierter zustand) BEIDE LEDs BLINKEN
	TIM4->CR1		 = 0x0001;					//COUNTER (TIM4) ENABLE
}

void TIM8_CONFIG (void)
{
	TIM8->CCMR1		= 0x00003030;			//PWM Mode1 CH1/2 TOGGLE_MODE PA7/8/9/12
	TIM8->CCER		= 0x00000044;			//CH1/2&1n/2n enable, polarity

#define MOTORPWM_OFF 	TIM8->CCER&=~0x00000011;
#define MOTOR_LEFT 		TIM8->CCER=0x0000005F;
#define MOTOR_RIGHT		TIM8->CCER=0x00000055;

	TIM8->BDTR		= 0x0000CC00;			//MOE/AOE/OSSR/OSSI ON
	TIM8->PSC		= 7999;					//1ms
	TIM8->ARR		= 9999;
	TIM8->CCR1		= 4999;
	TIM8->CCR2 		= 0;
	TIM8->CR1		= 0x00000001;			//counter enable
	//#define changedirection ^= 0x
	MOTORPWM_OFF;
}

void SET_COURSE (void)
  {
	int fail=0;
	int i;
	int posstart =0;
	if (BUTTON_LEFT)			//wenn knopf gedrückt wurde PA1
	{
		posstart = POTI;

		i=0;

		while (POTI>5)
		{
		//ADC2->TR=0x00000005;		//INTERRUPT wenn POTI unter 5->MOTOR aus
		i++;
		LEDoffl;						//LED andere Seite off A6 links, GPIOA->BRR  |=0x0040;
	    blinkonr;						//stellstatusblinken
		H_BRIDGE_ON;					//H Bridge ON
		MOTOR_RIGHT;

		if(i==2000 && (POTI&posstart))
		{
		fail=1;
		break;
		}

		}
		if (fail==0)
		{
		LEDoffl;
		MOTORPWM_OFF;
	    H_BRIDGE_OFF;					//H_Bridge OFF
		LEDonr;
		}
		else if (fail==1)
		{
			blinkonl;
			blinkonr;
			MOTORPWM_OFF;
			H_BRIDGE_OFF;
			for (int j =0;j<=800000;j++){}
			fail=0;
			LEDoffl;
			LEDoffr;
		}
	}

	  else if	(BUTTON_RIGHT)				//links
	  {
		  posstart=POTI;

		  i=0;
		  //ADC->TR=0xFFFA0000;		//INTERRUPT bei POTI 4090 MOTOR aus...
		  while(POTI<=4090)
		  {
		  i++;
		  H_BRIDGE_ON;					//H_Bridge ON
		  LEDoffr;
		  blinkonl;
		  MOTOR_LEFT;

		  if(i==2000&&(POTI&posstart))
		  {
			  fail=1;
			  break;
		  }
		  }

		  if(fail==0)
		  {
		  LEDoffr;
		  MOTORPWM_OFF;
		  H_BRIDGE_OFF;						//H_Bridge OFF
		  LEDonl;

	      }else if (fail==1)
			{
				blinkonl;
				blinkonr;
				MOTORPWM_OFF;
				H_BRIDGE_OFF;
				for (int j =0;j<=800000;j++){}
				fail=0;
				LEDoffl;
				LEDoffr;
			}
	  }

	}

volatile static int set;
int j=2000000;
void CHECK_POS (void)
	{
	if ((set==1) || (set==2))
	{
	int fader_old=POTI;
	int fader_sub50 = fader_old-50;
	int fader_add50 = fader_old+50;
	for (int i=0;i<=j;i++){}
	if ((POTI>(abs(fader_sub50)))& (POTI<(fader_add50)))
	{
		MOTORPWM_OFF;
		H_BRIDGE_OFF;
		blinkonl;
		blinkonr;
		set=3;
	}
	}

}


int main(void)
{
	CLOCK_CONFIG();
	GPIOx_CONFIG();
	TIM8_CONFIG();
	TIM4_CONFIG();
	ADC2_CONFIG();
	EXTI1_CONFIG();
	EXTI0_CONFIG();

	/**/

	while(1)
	{
		CHECK_POS();

		/*if ((POTI<10) && (set==3))
				{
					LEDoffl;
					LEDonr;

				}
				else if ((POTI>4075) && (set==3))
				{
					LEDoffr;
					LEDonl;

				}*/
	}
}

void EXTI0_IRQHandler (void)			//button links
{
LEDoffr;
blinkonl;
H_BRIDGE_ON;
MOTOR_LEFT;
ADC2->TR1=0xFFD00000;
set=2;
NVIC_ClearPendingIRQ(EXTI0_IRQn);
EXTI->PR = 0x1;
}

void EXTI1_IRQHandler (void)			//button rechts
{
	LEDoffl;
	blinkonr;
	H_BRIDGE_ON;
	MOTOR_RIGHT;
	ADC2->TR1=0xFFFF000A;
	set=1;
	NVIC_ClearPendingIRQ(EXTI1_IRQn);
	EXTI->PR = 0x2;
}



void ADC1_2_IRQHandler(void)
{
	if (/*(set==1)||*/(POTI<10))
	{
		ADC2->TR1 =0xFFFF0000;
		LEDoffl;
		LEDonr;
		set=3;
	}
	else if (/*(set==2)||*/(POTI>4085))
	{
		ADC2->TR1 =0xFFFF0000;
		LEDoffr;
		LEDonl;
		set=3;
	}

	//ADC2->TR1 =0xFFFF0000;
	H_BRIDGE_OFF;
	//MOTORPWM_OFF;
	NVIC_ClearPendingIRQ(ADC1_2_IRQn); //Interruptflag cleared
	ADC2->ISR		|= 0x0080;		   //ADC interruptflag cleared

}

