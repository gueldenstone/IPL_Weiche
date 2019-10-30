/*
 * set_course.c
 *
 *  Created on: 29.10.2019
 *      Author: Kevin Heidenreich
 */
#include "set_course.h"
//int steps (void)
//{
//	while (stromerkennung<=//schandwiedrstandspannung)
//	{
//	GPIOC->BSRR |=0x0005000A;			HAL_Delay(ms); 					//wie eigenen sekunden z�hler schreiben?
//	GPIOC->BSRR |=0x00040008;			HAL_Delay(ms);
//	GPIOC->BSRR |=0x00090006;			HAL_Delay(ms);
//	GPIOC->BSRR |=0x000B0004;			HAL_Delay(ms);
//    GPIOC->BSRR |=0x000A0005;			HAL_Delay(ms);
//    GPIOC->BSRR |=0x000E0001;			HAL_Delay(ms);
//	GPIOC->BSRR |=0x00060009;			HAL_Delay(ms);
//	GPIOC->BSRR |=0x00070008;			HAL_Delay(ms);
//	}
//
//	while (stromerkennung<=//schandwiedrstandspannung))
//	{
//	GPIOA->BSRR |= 0x00070008;	HAL_Delay(ms);
//	GPIOC->BSRR |= 0x00060009;	HAL_Delay(ms);
//	GPIOC->BSRR |= 0x000E0001;	HAL_Delay(ms);
//	GPIOC->BSRR |= 0x000A0005;	HAL_Delay(ms);
//	GPIOC->BSRR |= 0x000B0004;	HAL_Delay(ms);
//	GPIOC->BSRR |= 0x00090006;	HAL_Delay(ms);
//	GPIOC->BSRR |= 0x00040008;	HAL_Delay(ms);
//	GPIOC->BSRR |= 0x0005000A;	HAL_Delay(ms);
//	steps i++;
//	}
//	return steps;
//}
//
//
//int set_course (_Bool weiche,int steps)
//  {
//	int countsteps =0;
//
//	  if (weiche = 1)//rechts
//	  {
//		  while(steps>countsteps)
//		  {
//		  GPIOC->BSRR |=0x0005000A;countspeps++;			HAL_Delay(ms); 					//wie eigenen sekunden z�hler schreiben?
//		  GPIOC->BSRR |=0x00040008;countspeps++;			HAL_Delay(ms);
//		  GPIOC->BSRR |=0x00090006;countspeps++;			HAL_Delay(ms);
//		  GPIOC->BSRR |=0x000B0004;countspeps++;			HAL_Delay(ms);
//		  GPIOC->BSRR |=0x000A0005;countspeps++;			HAL_Delay(ms);
//		  GPIOC->BSRR |=0x000E0001;countspeps++;			HAL_Delay(ms);
//		  GPIOC->BSRR |=0x00060009;countspeps++;			HAL_Delay(ms);
//		  GPIOC->BSRR |=0x00070008;countspeps++;			HAL_Delay(ms);
//		  }
//		  set=1;
//	      }
//		  //GPIOC->BSRR |=0x0000000F;		//0x00000008, R�cksetzen der Ausg�nge?
//
//	  if (weiche = 0)//links
//	  {
//		  for (int i=2;i<=steps;i++)
//		  {
//		  GPIOA->BSRR |= 0x00070008;	HAL_Delay(ms);
//		  GPIOC->BSRR |= 0x00060009;	HAL_Delay(ms);
//		  GPIOC->BSRR |= 0x000E0001;	HAL_Delay(ms);
//		  GPIOC->BSRR |= 0x000A0005;	HAL_Delay(ms);
//		  GPIOC->BSRR |= 0x000B0004;	HAL_Delay(ms);
//		  GPIOC->BSRR |= 0x00090006;	HAL_Delay(ms);
//		  GPIOC->BSRR |= 0x00040008;	HAL_Delay(ms);
//		  GPIOC->BSRR |= 0x0005000A;	HAL_Delay(ms);
//		  }
//		  set=0;
//		  //GPIOC->BSRR |=0x000F0000;								// R�cksetzen
//		  }
//	  return set;
//	}


