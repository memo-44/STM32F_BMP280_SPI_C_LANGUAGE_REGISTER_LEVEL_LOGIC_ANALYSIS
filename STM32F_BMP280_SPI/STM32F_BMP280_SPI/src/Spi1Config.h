/*
 * Spi1Config.h
 *
 *  Created on: 3 Kas 2022
 *      Author: mehme
 */

#include "RccConfig.h"

#ifndef SPI1CONFIG_H_
#define SPI1CONFIG_H_

void SPIConfig (void);
void SPITrans(uint8_t *Data,uint8_t Size);
void SPIReceive(uint8_t *Data,uint8_t Size);
void SPIEnable();
void SPIDisable();
void SPICss();
void SPINCss();

//SPI FUNCTIONS DECLARATION


#endif /* SPI1CONFIG_H_ */
