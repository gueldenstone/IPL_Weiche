/* Includes ------------------------------------------------------------------*/
#include "rcc.h"

/* Code ------------------------------------------------------------------*/


void RCCConfig(void){

	/* PLL Config
	 *
	 */
	RCC->CR &= ~(RCC_CR_PLLON); //PLL deaktivieren (zur Config)
	RCC->CFGR |= RCC_CFGR_PLLMUL5;	//PLL Multi = 5
	RCC->CFGR2 &= ~(RCC_CFGR2_PREDIV_0);		//No PreDIV
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV;	//PLL Source -> HSI
	RCC->CR |= RCC_CR_PLLON; //PLL aktivieren (zur Config)
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; //PreDiv für ABP1

	RCC->CR |= RCC_CR_HSION;	//HSI ON
	RCC->CFGR |= RCC_CFGR_SW_PLL; //PLL set as SYSCLOCK

}
