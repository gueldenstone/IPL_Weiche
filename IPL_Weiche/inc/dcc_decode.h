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



 /*Prototypes */
void EXTI_Config(void);
void TIM_Config(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);

#ifdef __cplusplus
}
#endif
#endif
