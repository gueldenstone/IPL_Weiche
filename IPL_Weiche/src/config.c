/* Includes ------------------------------------------------------------------*/
#include <config.h>

/* Functions -----------------------------------------------------------------*/
void RCC_Config(void){
	/* PLL Config */
	RCC->CR &= ~(RCC_CR_PLLON); 									// deactivate PLL
	while(RCC->CR & RCC_CR_PLLRDY){} 								// wait for PLL to stop
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV | RCC_CFGR_PLLMUL9;		// Set PLL to input HSI, Multiplicator = 9
 	RCC->CR |= RCC_CR_PLLON; 										// activate PLL
 	while(!(RCC->CR & RCC_CR_PLLRDY)); 								// Wait for PLL to lock

 	/* FLASH wait states */
 	FLASH->ACR &= ~(FLASH_ACR_LATENCY_Msk);			// Reset Flash Wait states
 	FLASH->ACR |= 0b010 << FLASH_ACR_LATENCY_Pos;	// Set Flash wait states to 2

  	/* SysClock anpassen */
  	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; 							// PreDiv für ABP1 /2, da ABP1 36Mhz max.
  	RCC->CFGR &= ~RCC_CFGR_SW;									// Reset RCC->CFGR Switch
  	RCC->CFGR |= RCC_CFGR_SW_PLL;								// Set PLL as Sysclock
  	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL){} 	// Wait for switch to PLL as clock source

  	SystemCoreClockUpdate();

	/* Peripherie Clock */

  	/* Timer */
  	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Enable TIM2 Clock

	/* GPIO */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //GPIO A
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //GPIO B

	/* Other */
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

	/* Inputs */
	GPIOA->MODER &= ~(0b11 << GPIO_MODER_MODER1_Pos); 	// PA1 Pos1 Input
	GPIOA->MODER &= ~(0b11 << GPIO_MODER_MODER2_Pos); 	// PA2 Pos2 Input

	GPIOA->MODER &= ~(0b11 << GPIO_MODER_MODER5_Pos); 	// PA5 DIP-Switch 1
	GPIOA->MODER &= ~(0b11 << GPIO_MODER_MODER6_Pos); 	// PA6 DIP-Switch 2
	GPIOA->MODER &= ~(0b11 << GPIO_MODER_MODER7_Pos); 	// PA7 DIP-Switch 3
	GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODER0_Pos); 	// PB0 DIP-Switch 4
	GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODER2_Pos); 	// PB2 DIP-Switch 5
	GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODER10_Pos); 	// PB10 DIP-Switch 6
	GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODER11_Pos); 	// PB11 DIP-Switch 7
	GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODER12_Pos); 	// PB12 DIP-Switch 8

	/* Outputs */
	GPIOA->MODER |= GPIOx_MODER_OUTPUT<<GPIO_MODER_MODER3_Pos;	// PA3 nSleep

	/* Analog */
	GPIOA->MODER |= GPIOx_MODER_ANALOG<<GPIO_MODER_MODER4_Pos;	// PA4 Fader

	/* Alternate functions */
	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER0_Pos; 	// PA0 DCC Input

	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER11_Pos;	// PA11 LED1 PWM
	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER12_Pos;	// PA12 LED2 PWM

	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER15_Pos;	// PA15 H-Bride 1A
	GPIOB->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER3_Pos;		// PB3 H-Bride 1B
	GPIOB->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER4_Pos;		// PB4 H-Bride 2B
	GPIOB->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER8_Pos;		// PB8 H-Bride 2A

	/* UART */
	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER8_Pos;		// PA8 USART_CK
	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER9_Pos;		// PA9 USART_TX
	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER10_Pos;	// PA10 USART_RX

	/* SWD */
	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER13_Pos;	// PA13 SWDIO
	GPIOA->MODER |= GPIOx_MODER_ALT<<GPIO_MODER_MODER14_Pos;	// PA14 SWCLK

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


	/* ########## GPIO Alternate funtion ########## */
	/*  */
	GPIOA->AFR[0] |= 1<<GPIO_AFRL_AFRL0_Pos;	// PA0 AF1 TIM2 Ext.Trig.
	GPIOA->AFR[1] |= 10<<GPIO_AFRH_AFRH4_Pos;	// PA11 AF10 TIM4_CH1
	GPIOA->AFR[1] |= 10<<GPIO_AFRH_AFRH5_Pos;	// PA12 AF10 TIM4_CH2
	GPIOA->AFR[1] |= 2<<GPIO_AFRH_AFRH7_Pos;	// PA15 AF2 TIM8_CH1
	GPIOB->AFR[0] |= 4<<GPIO_AFRL_AFRL3_Pos;	// PB3 AF4 TIM8_CH1N
	GPIOB->AFR[1] |= 10<<GPIO_AFRH_AFRH0_Pos;	// PB8 AF10 TIM8_CH2
	GPIOB->AFR[0] |= 4<<GPIO_AFRL_AFRL4_Pos;	// PB4 AF4 TIM8_CH2N

	/* UART */
	GPIOA->AFR[1] |= 7<<GPIO_AFRH_AFRH0_Pos;	// PA8 AF7 USART_CK
	GPIOA->AFR[1] |= 7<<GPIO_AFRH_AFRH1_Pos;	// PA9 AF7 USART_TX
	GPIOA->AFR[1] |= 7<<GPIO_AFRH_AFRH2_Pos;	// PA10 AF7 USART_RX

	/* ########## Reset Pins to Default ##########
	 * Port Reset		GPIO<port>->ODR &= ~(0xFFFF)
	 * Port Set			GPIO<port>->ODR |= 0xFFFF
	 * Pin Reset		GPIOA->ODR &= ~(GPIO_ODR_<pin>);
	 * Pin Set			GPIOA->ODR |= GPIO_ODR_<pin>;
	 */
}


void TIM_Config(void){

	/* Timer 2 */
	TIM2->CR1 &= ~TIM_CR1_CEN;					// disable TIM2
	TIM2->ARR = DCC_SAMPLEPOINT; 				// set counter value
	TIM2->PSC = (SystemCoreClock/1000000)-1;	// set prescaler value (usec)
	TIM2->CR1 |= TIM_CR1_OPM; 					// Enable one-pulse Mode
	TIM2->DIER |= TIM_DIER_UIE; 				// Enable Interrupt on Update
	TIM2->SMCR |= 0b111 << TIM_SMCR_TS_Pos;		// External Trigger selected
	TIM2->SMCR |= 0b0110 << TIM_SMCR_SMS_Pos;	// Slave Mode = Triggered Mode
	TIM2->CR1 |= TIM_CR1_CEN;					// enable Timer2
	NVIC_EnableIRQ(TIM2_IRQn);					// Enable NVIC on TIM2
}

void ADC_Config(void){
	//ADC zur Strommessung

}
