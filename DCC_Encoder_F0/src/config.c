/* Includes ------------------------------------------------------------------*/
#include <config.h>
/* Code ------------------------------------------------------------------*/


void RCC_Config(void){
	/* PLL Config
	 *
	 */
	RCC->CR &= ~(RCC_CR_PLLON); 																	//deactivate PLL
	while(RCC->CR & RCC_CR_PLLRDY){} 																//wait for PLL to stop
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL)); 	//Reset PLL configs
	RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL12);							//Set PLL to input HSI, Multiplicator = 9
 	RCC->CR |= RCC_CR_PLLON; 																		//activate PLL
 	while(!(RCC->CR & RCC_CR_PLLRDY)); 																//Wait for PLL to lock

 	/*FLASH wait states
 	 *
 	 */
 	FLASH->ACR &= ~(FLASH_ACR_LATENCY_Msk);			//Reset Flash Wait states
 	FLASH->ACR |= 1 << FLASH_ACR_LATENCY_Pos;	//Set Flash wait states to 2

  	/*SysClock anpassen
  	 *
  	 */
  	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));								//Reset RCC->CFGR Switch
  	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;											//Set PLL as Sysclock
  	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL){} 	//Wait for switch to PLL as clock source

  	SystemCoreClockUpdate();

	/*Peripherie Clock
	 *
	 */

  	//Timer
  	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; //Enable Timer6 Clock

	//GPIO
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //GPIO A

	//Sonsitiges
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //Clock to SYSCFG


}


void GPIO_Config(void){

	/* ########## GPIO MODES ##########
	 *GPIOx -> MODER
	 *
	 * GPIOx_MODER_INPUT
	 * GPIOx_MODER_OUTPUT
	 * GPIOx_MODER_ALT
	 * GPIOx_MODER_ANALOG
	 */

	GPIOA->MODER |= (GPIOx_MODER_OUTPUT << GPIO_MODER_MODER1_Pos);

	/* ########## GPIO Output Types ##########
	 * GPIOx -> OTYPER
	 *
	 * GPIOx_OTYPER_PP
	 * GPIOx_OTYPER_OD
	 */

	/* ########## GPIO Output Speed ##########
	 * GPIOx -> OSPEEDR
	 *
	 * GPIOx_OSPEEDR_LOW
	 * GPIOx_OSPEEDR_MED
	 * GPIOx_OSPEEDR_HIGH
	 */

	/* ########## GPIO Pull-up/-down ##########
	 * GPIOx -> PUPDR
	 *
	 * GPIOx_PUPDR_NO
	 * GPIOx_PUPDR_PU
	 * GPIOx_PUPDR_PD
	 */

	/* Reset Pins to Default
	 * Port Reset		GPIO<port>->ODR &= ~(0xFFFF)
	 * Port Set			GPIO<port>->ODR |= 0xFFFF
	 * Pin Reset		GPIOA->ODR &= ~(GPIO_ODR_<pin>);
	 * Pin Set			GPIOA->ODR |= GPIO_ODR_<pin>;
	 */


}


void TIM_Config(void){
	TIM6->ARR = 0; //set counter value
	TIM6->PSC = 47;
	TIM6->CR1 |= TIM_CR1_OPM; //Enable one-pulse Mode
//	TIM6->CR1 |= TIM_CR1_ARPE; //enable auto reload preload
	TIM6->DIER |= TIM_DIER_UIE; //Enable Interrupt on Update
	NVIC_EnableIRQ(TIM6_DAC_IRQn); //Enable NVIC on TIM6
	TIM6->CR1 &= ~TIM_CR1_CEN;
}

void EXTI_Config(void){
	EXTI->IMR |= EXTI_IMR_IM0; 		//Maske Pin Interrupt 0
	EXTI->RTSR |= EXTI_FTSR_FT0;	//Rising Edge Trigger ausgewählt
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; //Connect EXTI1 mit Port A
	NVIC_EnableIRQ(EXTI0_1_IRQn); //Enable NVIC on EXTI0_1
}
