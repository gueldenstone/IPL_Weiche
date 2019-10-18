/**
  ******************************************************************************
  * @author  Lukas Güldemstein
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "main.h"
#include "gpio.h"
#include "rcc.h"
#include "stm32f3xx.h"


int main(void)
{
	RCCConfig();					//Clock Config
	GPIO_Config(); 					//GPIO Config
	SysTick_Config(40000);			//SysTick Config

//	volatile int i=0, t=0, p=0;
//	volatile uint8_t byte=0x4CU;
//	volatile char bit;
//	for(i=10;i>=0;i--){
//		GPIOC->ODR |= GPIO_ODR_8;
//		for(t=5;t>=0;t--){
//			p = 65536;
//			while(p--)
//				;
//		}
//		GPIOC->ODR &= ~(GPIO_ODR_8);
//		for(t=5;t>=0;t--){
//			p = 65536;
//			while(p--)
//						;
//		}
//	}
//	for(i=7;i>=0;i--){
//		bit=(byte>>i)&1;
//		if(bit){
//			GPIOC->ODR |= GPIO_ODR_8;
//			for(t=5;t>=0;t--){
//				p = 65536;
//				while(p--)
//					;
//			}
//			GPIOC->ODR &= ~(GPIO_ODR_8);
//			for(t=5;t>=0;t--){
//				p = 65536;
//				while(p--)
//					;
//			}
//		}
//		else
//		GPIOC->ODR |= GPIO_ODR_8;
//		for(t=10;t>=0;t--){
//			p = 65536;
//			while(p--)
//				;
//		}
//		GPIOC->ODR &= ~(GPIO_ODR_8);
//		for(t=10;t>=0;t--){
//			p = 65536;
//			while(p--)
//				;
//		}
//	}

//	for(;;){
//		volatile unsigned int i = 65536;
//		while(i--)
//			;
//		GPIOA->ODR ^= GPIO_ODR_5;
//	}


}
