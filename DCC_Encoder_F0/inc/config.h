/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* BEGIN Private defines */

/* ########## GPIO MODES ########## */
#define GPIOx_MODER_INPUT		0b00
#define GPIOx_MODER_OUTPUT 		0b01
#define GPIOx_MODER_ALT	 		0b10
#define GPIOx_MODER_ANALOG 		0b11

/* ########## GPIO Output Types ########## */
#define GPIOx_OTYPER_PP		0b0
#define GPIOx_OTYPER_OD 		0b1

/* ########## GPIO Output Speed ########## */
#define GPIOx_OSPEEDR_LOW		0b00
#define GPIOx_OSPEEDR_MED		0b01
#define GPIOx_OSPEEDR_HIGH		0b11

/* ########## GPIO Pull-up/-down ########## */
#define GPIOx_PUPDR_NO		0b00
#define GPIOx_PUPDR_PU		0b01
#define GPIOx_PUPDR_PD		0b10

/* END Private defines */

 /* BEGIN Prototypes */
 void GPIO_Config(void);
 void RCC_Config(void);
 void EXTI_Config(void);
 void TIM_Config(void);
/* END Prototypes */

#endif /*__gpio_H */