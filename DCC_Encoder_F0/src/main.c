/**
  ******************************************************************************
  * @author  Lukas Güldemstein
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

//58
//116


#include "main.h"
#include "config.h"
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"


volatile uint8_t t=0, bit=0, byte1, byte2,byte3, weiche_adresse, richtung;
volatile uint16_t dcc_adresse;
volatile uint32_t time=DCC_TIME_1, usec, preambel;
volatile _Bool go;

int main(void)
{
	RCC_Config();					//Clock Config
	GPIO_Config(); 					//GPIO Config
	EXTI_Config();					//EXTI Config
	TIM_Config();					//Timer Config


	/*				MSB 	Adresse (LSB fällt bei 8-Bit Adresse weg) */
	dcc_adresse = 	0x1A2;
	/* Adresse der Weiche (2Bits)*/
	weiche_adresse = 1;
	/* Richtung der Weiche (1Bit, 0=gerade, 1=links/rechts) */
	richtung = 1;

	/* Preambel  (32-Bit 1en) */
	preambel=0xFFFF;

	/* A=Adressbit, W=Weichenadressbits, D=Richtung */
	/* Byte1 0b10AAAAAA */
	byte1 = 0x80 | ((dcc_adresse & 0x1F8)>>3);
	/* Byte2 0b1AAA1WWD */
	byte2 = 0x80 | ((dcc_adresse & 0x7)<<4) | weiche_adresse<<1 | richtung;
	/* Paritätsberechnung  */
	byte3 =(byte2 ^ byte1);


	while(1){
		if(go){						//Wenn Button gedrückt
		EXTI->IMR &= ~EXTI_IMR_IM0; //Maskiere EXTI0
		send_preambel(preambel);	//Preambel
		sendbit(0);					//Lead 0
		send_byte(byte1);			//sende byte1
		sendbit(0);					//Trailer
		send_byte(byte2);			//sende byte2
		sendbit(0);					//Trailer
		send_byte(byte3);			//sende byte3 (Parität)
		sendbit(1);					//Stopbit
		go=0;						//Startbedingung zurücksetzten
		EXTI->IMR |= EXTI_IMR_IM0;  //Demaskiere EXTI0
		}
		else{
			send_byte(0xFF); 		//Idle Message
		}
	}
}


//functions
void delay(uint32_t usec){
	TIM6->ARR = usec;
	TIM6->CR1 |= TIM_CR1_CEN;
	__WFI();
}

void sendbit(_Bool bit){
	usec=(2*time-bit*time)-1;
	GPIOA->ODR |= GPIO_ODR_1;
	delay(usec);
	GPIOA->ODR &= ~(GPIO_ODR_1);
	delay(usec);
}
void send_preambel(uint32_t p){
	int i;
	for(i=12;i>=0;i--){
		sendbit((p>>i)&1);
	}
}
void send_byte(uint8_t b){
	int i;
	for(i=7;i>=0;i--){
		sendbit((b>>i)&1);
	}
}
