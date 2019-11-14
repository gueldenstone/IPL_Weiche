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
	RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_PREDIV | RCC_CFGR_PLLMUL9);							//Set PLL to input HSI, Multiplicator = 9
 	RCC->CR |= RCC_CR_PLLON; 																		//activate PLL
 	while(!(RCC->CR & RCC_CR_PLLRDY)); 																//Wait for PLL to lock

 	/*FLASH wait states
 	 *
 	 */
 	FLASH->ACR &= ~(FLASH_ACR_LATENCY_Msk);			//Reset Flash Wait states
 	FLASH->ACR |= 0b010 << FLASH_ACR_LATENCY_Pos;	//Set Flash wait states to 2

  	/*SysClock anpassen
  	 *
  	 */
  	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; 												//PreDiv für ABP1
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
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //GPIO B
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //GPIO C

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
	//Inputs
//	GPIOA->MODER |= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER1_Pos); //PA1 DCC Input
//	GPIOA->MODER |= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER2_Pos); //PA2 Pos1 Input
//	GPIOA->MODER |= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER3_Pos); //PA3 Pos2 Input
//
//	GPIOB->MODER &= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER3_Pos); //PB2 DIP-Switch 1
//	GPIOB->MODER &= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER4_Pos); //PB2 DIP-Switch 2
//	GPIOB->MODER &= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER5_Pos); //PB2 DIP-Switch 3
//	GPIOB->MODER &= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER6_Pos); //PB2 DIP-Switch 4
//	GPIOB->MODER &= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER7_Pos); //PB2 DIP-Switch 5
//	GPIOB->MODER &= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER8_Pos); //PB2 DIP-Switch 6
//	GPIOB->MODER &= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER9_Pos); //PB2 DIP-Switch 7
//	GPIOB->MODER &= ~(~GPIOx_MODER_INPUT << GPIO_MODER_MODER10_Pos); //PB2 DIP-Switch 8

	GPIOB->MODER |= (GPIOx_MODER_ANALOG << GPIO_MODER_MODER3_Pos); //PB1 Strommessung ADC3_IN1


	//Outputs
	GPIOA->MODER |= (GPIOx_MODER_OUTPUT << GPIO_MODER_MODER3_Pos); //PA3 Spule 1
	GPIOA->MODER |= (GPIOx_MODER_OUTPUT << GPIO_MODER_MODER4_Pos); //PA4 Spule 2
	GPIOA->MODER |= (GPIOx_MODER_OUTPUT << GPIO_MODER_MODER5_Pos); //PA5 Spule 3
	GPIOA->MODER |= (GPIOx_MODER_OUTPUT << GPIO_MODER_MODER6_Pos); //PA6 Spule 4
	GPIOA->MODER |= (GPIOx_MODER_OUTPUT << GPIO_MODER_MODER7_Pos); //PA7 Stepper !Enable
	GPIOB->MODER |= (GPIOx_MODER_OUTPUT << GPIO_MODER_MODER12_Pos); //PB12 LED 1
	GPIOB->MODER |= (GPIOx_MODER_OUTPUT << GPIO_MODER_MODER13_Pos); //PB13 LED 2



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
	//PA3 bis PA6 high-speed  switching
	GPIOA->MODER |= (GPIOx_OSPEEDR_HIGH << GPIO_MODER_MODER3_Pos);
	GPIOA->MODER |= (GPIOx_OSPEEDR_HIGH << GPIO_MODER_MODER4_Pos);
	GPIOA->MODER |= (GPIOx_OSPEEDR_HIGH << GPIO_MODER_MODER5_Pos);
	GPIOA->MODER |= (GPIOx_OSPEEDR_HIGH << GPIO_MODER_MODER6_Pos);

	/* ########## GPIO Pull-up/-down ##########
	 * GPIOx -> PUPDR
	 *
	 * GPIOx_PUPDR_NO
	 * GPIOx_PUPDR_PU
	 * GPIOx_PUPDR_PD
	 */
	//GPIOA->PUPDR |= GPIOx_PUPDR_PD<<GPIO_PUPDR_PUPDR0_Pos;	//Pulldown für PA0

	/* Reset Pins to Default
	 * Port Reset		GPIO<port>->ODR &= ~(0xFFFF)
	 * Port Set			GPIO<port>->ODR |= 0xFFFF
	 * Pin Reset		GPIOA->ODR &= ~(GPIO_ODR_<pin>);
	 * Pin Set			GPIOA->ODR |= GPIO_ODR_<pin>;
	 */
}


void TIM_Config(void){

	/* Timer 6 */
	TIM6->CR1 &= ~TIM_CR1_CEN;		//disable Timer6
	TIM6->ARR = DCC_SAMPLEPOINT; 	//set counter value
	TIM6->PSC = PSC_USEC;			//set prescaler value
	TIM6->CR1 |= TIM_CR1_ARPE; 		//enable auto reload preload
	TIM6->CR1 |= TIM_CR1_OPM; 		//Enable one-pulse Mode
	TIM6->DIER |= TIM_DIER_UIE; 	//Enable Interrupt on Update
	NVIC_EnableIRQ(TIM6_DAC_IRQn);	//Enable NVIC on TIM6
}

void EXTI_Config(void){
	EXTI->IMR |= EXTI_IMR_IM0; 						//Maske Pin Interrupt PA0
	EXTI->RTSR |= EXTI_RTSR_RT0;					//Rising Edge Trigger ausgewählt
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; 	//Connect EXTI0 mit Port A
	NVIC_EnableIRQ(EXTI0_IRQn); 					//Enable NVIC on EXTI0
}
