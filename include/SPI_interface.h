/*
 * SPI_interface.h
 *
 *  Created on: Aug 24, 2022
 *      Author: Mega Store
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

typedef enum {

	SPI_1, SPI_2,

} SPIx_t;

typedef enum {

	SPI_Baud_Rate_Fpclk_2,
	SPI_Baud_Rate_Fpclk_4,
	SPI_Baud_Rate_Fpclk_8,
	SPI_Baud_Rate_Fpclk_16,
	SPI_Baud_Rate_Fpclk_32,
	SPI_Baud_Rate_Fpclk_64,
	SPI_Baud_Rate_Fpclk_128,
	SPI_Baud_Rate_Fpclk_256,

} SPI_Baud_Rate_t;

typedef enum {

	SPI_Clk_Polarity_Phase_Idle_Low_Read_Write,
	SPI_Clk_Polarity_Phase_Idle_Low_Write_Read,
	SPI_Clk_Polarity_Phase_Idle_High_Read_Write,
	SPI_Clk_Polarity_Phase_Idle_High_Write_Read,

} SPI_Clk_Polarity_Phase_t;

typedef enum {

	SPI_Data_Format_8_bit_LSB,
	SPI_Data_Format_16_bit_LSB,
	SPI_Data_Format_8_bit_MSB,
	SPI_Data_Format_16_bit_MSB,

} SPI_Data_Format_t;

typedef enum {

	SPI_Mode_Slave, SPI_Mode_Master,

} SPI_Mode_t;

typedef void (*SPI_voidCallback)(void);

typedef void (*SPI_voidCallbacku16)(u16);

void SPI_voidInit(SPIx_t Copy_enumSPIx, SPI_Mode_t Copy_enumMasterSlave,
		SPI_Baud_Rate_t Copy_enumBaudRate,
		SPI_Clk_Polarity_Phase_t Copy_enumClkPolarityPhase,
		SPI_Data_Format_t Copy_enumDataFormat);

u16 SPI_u16TransceiveCharSync(SPIx_t Copy_enumSPIx, u16 Copy_u16Data);

void SPI_voidTransceiveStringSync(SPIx_t Copy_enumSPIx,
		u8* Copy_u8u16ptrTransmitData, u8* Copy_u8u16ptrReceiveData,
		u16 Copy_u16length);

void SPI_voidTransceiveCharAsync(SPIx_t Copy_enumSPIx, u16 Copy_u16Data,
		SPI_voidCallbacku16 voidTransmitCallbacku16,
		SPI_voidCallbacku16 voidReceiveCallbacku16,
		SPI_voidCallback voidErrorCallback);

///		DMA

void SPI_voidTxDMAEnable(SPIx_t Copy_enumSPIx);
void SPI_voidTxDMADisable(SPIx_t Copy_enumSPIx);
void SPI_voidRxDMAEnable(SPIx_t Copy_enumSPIx);
void SPI_voidRxDMADisable(SPIx_t Copy_enumSPIx);

/// 	end DMA

#endif /* SPI_INTERFACE_H_ */
