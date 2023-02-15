/*
 * Spi1Config.c
 *
 *  Created on: 3 Kas 2022
 *      Author: mehme
 */


#include "Spi1Config.h"
#include "RccConfig.h"
#include "Timer7Config.h"

/*****************THE PROCEDURE OF SPI CONFIGURATION ARE GIVEN FOLLOWING****************/
/*
 * 1-ENABLE CLOCK BUS OF SPI1.
 * 2-SET CLOCK POLARITY AND CLOCK PHASE.
 * 3-SELECT MASTER OR SLAVE MODE.
 * 4-CONFIGURE BAUD RATE CONTROL.
 * 5-SET FRAME FORMAT.
 * 6-ENABLE SOFTWARE SLAVE MANAGEMENET.
 * 7-SET SPI INTERFACE MODE (ONLY RECEIVE OR RECEIVE AND TRANSMIT)
 * 8-SET DATA FRAME FORMAT
 * 9-CONFIGURE DMA,INTERRUPTS OF SPI1.(I DONT USE DMA AND INTERRUPTS)
 */


void SPIConfig (void)
{
	RCC->APB2ENR |=(1<<12);       //SPI1 CLOCK BUS ENABLE

	SPI1->CR1 |= (1<<0)|(1<<1);   //CPOL=1, CPHA=1

	SPI1->CR1 |= (1<<2); 		  //MASTER MODE

	SPI1->CR1 |= (3<<3);		  //BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI CLK = 5MHz

	SPI1->CR1 &= ~(1<<7);  		  //MSB FIRST

	SPI1->CR1 |= (1<<8) | (1<<9); //SSM=1, SSi=1 ->>SOFTWARE SLAVE MANAGEMENET

	SPI1->CR1 &= ~(1<<10);  	  //RXONLY = 0, FULL-DUPLEX

	SPI1->CR1 &= ~(1<<11);  	  //DFF=0, 8 bit data

	SPI1->CR2 = 0;
}

void SPIEnable(){

	SPI1->CR1 |=(1<<6);
	Delay_us(1);
	SPICss();//LEVEL OF SLAVE SELECT IS LOW,AFTER TO CONFIGURE GPIOA.WE SET HIGH LEVEL OF SLAVE SELECT for
			 //COMMUNICATION in a HEALTHY WAY.
}
void SPIDisable(){

	SPI1->CR1 &= ~(1<<6);
}
void SPINCss(){

	GPIOA->ODR &=~(1<<4);
}
void SPICss(){

	GPIOA->BSRRL |=(1<<4);

}


/*****************THE PROCEDURE OF SPI TRANSMIT ARE GIVEN FOLLOWING****************/
/*
 * 1-SPECIFY DATA and DATA SIZE.
 * 2-CREATIVE ANY LOOP.
 * 3-CHECK TRANSMIT BUFFER EMPTY.
 * 4-IF TRANSMIT BUFFER EMPTY,DATA TRANSFERS TO SPI DATA REGISTER.
 * 5-CHECK TRANSMIT BUFFER EMPTY AND BUSY FLAG.
 */

void SPITrans(uint8_t *Data,uint8_t Size){

	uint8_t i;
	for(i=0;i<Size;i++){

		while(!(SPI1->SR & (1<<1)));
		SPI1->DR = Data[i];
	}

	while(!(SPI1->SR & (1<<1)));
	while (((SPI1->SR)&(1<<7)));

	uint8_t temp = SPI1->DR;
	temp = SPI1->SR;
}

/*****************THE PROCEDURE OF SPI RECEIVE ARE GIVEN FOLLOWING****************/
/*
 * 1-SPECIFY DATA and DATA SIZE.
 * 2-CREATIVE ANY LOOP.
 * 3-CHECK BUSY FLAG.
 * 4-ASSING NULL VALUE TO SPI DATA REGISTER.
 * 5-CHECK RECEIVE BUFFER EMPTY.
 * 6-IF RECEIVE BUFFER NOT EMPTY,SPI DATA REGISTER TRANSFERS DATA ARRAYS
 */


void SPIReceive(uint8_t *Data,uint8_t Size){

	uint8_t i;
	for(i=0;i<Size;i++){

		while (((SPI1->SR)&(1<<7)));
		SPI1->DR=0;
		while(!(SPI1->SR&(0x01)));
		Data[i]=SPI1->DR;


	}

}

