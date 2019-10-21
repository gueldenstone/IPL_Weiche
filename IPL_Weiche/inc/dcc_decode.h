/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __dcc_decode_H
#define __dcc_decode_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Variablen */
 typedef enum{WF_Preamble, WF_Lead0, WF_Byte, WF_Trailer}TypeDefRecstate;
 TypeDefRecstate recstate;
 volatile uint8_t bit, t, i, b, received;
 volatile uint8_t paket[3];


 /*Prototypes */
void EXTI_Config(void);
void TIM_Config(uint32_t count);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);

#ifdef __cplusplus
}
#endif
#endif
