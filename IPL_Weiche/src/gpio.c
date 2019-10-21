/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* Code ------------------------------------------------------------------*/

void GPIO_Config(void){
	// Clock Enable
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //GPIO A
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //GPIO B
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //GPIO C

	/* Mode Config
	 * 00 = Input 		GPIO<port>->MODER &= ~(GPIO_MODER_MODER<pin>_Msk);
	 * 01 = Output		GPIO<port>->MODER |= GPIO_MODER_MODER<pin>_0;
	 * 10 = Alternate	GPIO<port>->MODER |= GPIO_MODER_MODER<pin>_1;
	 * 11 = Analog		GPIO<port>->MODER |= GPIO_MODER_MODER<pin>_Msk;
	 */

	//Outputs
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOC->MODER |= GPIO_MODER_MODER8_0;
	GPIOC->MODER |= GPIO_MODER_MODER9_0;
	GPIOC->MODER |= GPIO_MODER_MODER6_0;

	//Inputs
	GPIOB->MODER &= ~(GPIO_MODER_MODER1_Msk);

	/* Ouput Type
	 * 0 = push/pull	GPIO<port>->OTYPER &= ~(GPIO_OTYPER_OT_<pin>);
	 * 1 = open drain	GPIO<port>->OTYPER |= GPIO_OTYPER_OT_<pin>;
	 */
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_5);
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_8);
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_9);
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_6);

	/* Output Speed
	 * x0 = Low			GPIO<port>->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR<pin>_Msk);
	 * 01 = Medium		GPIO<port>->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR<pin>_0);
	 * 11 = High		GPIO<port>->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR<pin>_Msk;
	 */
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_Msk;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_Msk;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_Msk;

	/* Port pull-up/down
	 * 00 = No PU/PD	GPIO<port>->PUPDR &= ~(GPIO_PUPDR_PUPDR<pin>_Msk);
	 * 01 = PU			GPIO<port>->PUPDR |= GPIO_PUPDR_PUPDR<pin>_0;
	 * 10 = PD			GPIO<port>->PUPDR |= GPIO_PUPDR_PUPDR<pin>_1;
	 * 11 = reserved	GPIO<port>->PUPDR |= GPIO_PUPDR_PUPDR<pin>_Msk;
	 */
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR1_1;
//	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR5_Msk);
//	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR8_Msk);
//	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR9_Msk);
//	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR6_Msk);

	/* Reset Pins to Default
	 * Port Reset		GPIO<port>->ODR &= ~(0xFFFF)
	 * Port Set			GPIO<port>->ODR |= 0xFFFF
	 * Pin Reset		GPIOA->ODR &= ~(GPIO_ODR_<pin>);
	 * Pin Set			GPIOA->ODR |= GPIO_ODR_<pin>;
	 */
	GPIOA->ODR &= ~(0xFFFF);
	GPIOC->ODR &= ~(0xFFFF);
}
