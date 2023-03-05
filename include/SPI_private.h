/*
 * SPI_private.h
 *
 *  Created on: Aug 24, 2022
 *      Author: Mega Store
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

typedef struct {
	volatile u32 SPI_CR1;
	volatile u32 SPI_CR2;
	volatile u32 SPI_SR;
	volatile u32 SPI_DR;
	volatile u32 SPI_CRCPR;
	volatile u32 SPI_RXCRCR;
	volatile u32 SPI_TXCRCR;
	volatile u32 SPI_I2SCFGR;
	volatile u32 SPI_I2SPR;
} SPI_Reg_t;

#define SPI1_BASE_ADDRESS	0x40013000
#define SPI2_BASE_ADDRESS	0x40003800

#define SPI1_REG ((volatile SPI_Reg_t*)SPI1_BASE_ADDRESS)
#define SPI2_REG ((volatile SPI_Reg_t*)SPI2_BASE_ADDRESS)

#endif /* SPI_PRIVATE_H_ */
