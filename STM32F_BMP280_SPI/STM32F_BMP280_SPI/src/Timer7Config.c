/*
 * Timer7Config.c
 *
 *  Created on: 3 Kas 2022
 *      Author: mehme
 */


#include "Timer7Config.h"

/*****************THE PROCEDURE OF SPI CONFIGURATION ARE GIVEN FOLLOWING****************/
/*
 * 1-ENABLE CLOCK BUS OF TIMER7.
 * 2-SET PRESCALE VALUE.
 * 3-SET AUTORELOAD VALUE..
 * 4-ENABLE TIMER7.
 * 5-CHECK TIMER7 UPDATE EVENT FLAG.
 */


void Timer7_Config(void){


	RCC->APB1ENR |=(1<<5);       //TIMER7 clock bus enable

	TIM7->PSC =39;               //40MHZ/39+1 = 1us -->> errorrr
	TIM7->ARR=0XFFFF;            //MAX ARR VALUE
	TIM7->CR1 |=(1<<0);          //TIMER7 ENABLE
	while(!(TIM7->SR &(1<<0)));	 //TO CHECK TIMER7 EVENT FLAG

}

void Delay_us(uint16_t us){

	TIM7->CNT=0x0000;
	while(TIM7->CNT<us);
}
void Delay_ms(uint16_t ms){


	for(int i=0;i<=ms;i++){

		Delay_us(1000);

	}
}
