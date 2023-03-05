/*
 * SPI_program.c
 *
 *  Created on: Aug 24, 2022
 *      Author: Mega Store
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "D:\programs system\imt_sdk\ARM_SPI\include\SPI_interface.h"
#include "D:\programs system\imt_sdk\ARM_SPI\include\SPI_config.h"
#include "D:\programs system\imt_sdk\ARM_SPI\include\SPI_private.h"

static SPI_voidCallbacku16 voidTransmitCallbacks[2] = { NULL, NULL };
static SPI_voidCallbacku16 voidReceiveCallbacks[2] = { NULL, NULL };
static SPI_voidCallback voidErrorCallbacks[2] = { NULL, NULL };

static u32 _getREG(SPIx_t Copy_enumSPIx) {
	switch (Copy_enumSPIx) {
	case SPI_1:
		return SPI1_BASE_ADDRESS;
		break;

	case SPI_2:
		return SPI2_BASE_ADDRESS;
		break;

	default:
		return NULL;
	}
}

void SPI_voidInit(SPIx_t Copy_enumSPIx, SPI_Mode_t Copy_enumMasterSlave,
		SPI_Baud_Rate_t Copy_enumBaudRate,
		SPI_Clk_Polarity_Phase_t Copy_enumClkPolarityPhase,
		SPI_Data_Format_t Copy_enumDataFormat) {

	volatile SPI_Reg_t* SPIx_REG = (volatile SPI_Reg_t*) _getREG(Copy_enumSPIx);

	/// reset value
	SPIx_REG->SPI_CR1 = 0;

	/// Bits 5:3 BR[2:0]: Baud rate control
	SPIx_REG->SPI_CR1 |= Copy_enumBaudRate << 3;

	/// Bit1 CPOL: Clock polarity
	/// Bit 0 CPHA: Clock phase
	// polarity & phase

	SPIx_REG->SPI_CR1 |= Copy_enumClkPolarityPhase << 0;
//	SET_BIT(SPIx_REG->SPI_CR1, 1);
//	SET_BIT(SPIx_REG->SPI_CR1, 0);

	/// data format
	switch (Copy_enumDataFormat) {

	/// Bit 11 DFF: Data frame format
	/// Bit 7 LSBFIRST: Frame format

	case SPI_Data_Format_8_bit_LSB:
		CLR_BIT(SPIx_REG->SPI_CR1, 11);
		SET_BIT(SPIx_REG->SPI_CR1, 7);
		break;
	case SPI_Data_Format_8_bit_MSB:
		CLR_BIT(SPIx_REG->SPI_CR1, 11);
		CLR_BIT(SPIx_REG->SPI_CR1, 7);
		break;
	case SPI_Data_Format_16_bit_LSB:
		SET_BIT(SPIx_REG->SPI_CR1, 11);
		SET_BIT(SPIx_REG->SPI_CR1, 7);
		break;
	case SPI_Data_Format_16_bit_MSB:
		SET_BIT(SPIx_REG->SPI_CR1, 11);
		CLR_BIT(SPIx_REG->SPI_CR1, 7);
		break;
	}

	/// todo : NSS hardware & software ??!

	/// Bit 2 MSTR: Master selection
	SPIx_REG->SPI_CR1 |= Copy_enumMasterSlave << 2;

	/// Bit 2 SSOE: SS output enable, one master only multimaster is disable
	if (Copy_enumMasterSlave == SPI_Mode_Master) {
		SET_BIT(SPIx_REG->SPI_CR2, 2);
	}

	/// Bit 6 SPE: SPI enable
	/// When disabling the SPI, follow the procedure described in Section 25.3.8.

	SET_BIT(SPIx_REG->SPI_CR1, 6);

}

u16 SPI_u16TransceiveCharSync(SPIx_t Copy_enumSPIx, u16 Copy_u16Data) {

	volatile SPI_Reg_t* SPIx_REG = (volatile SPI_Reg_t*) _getREG(Copy_enumSPIx);

	if (GET_BIT(SPIx_REG->SPI_CR1, 11) == 0) {
		/// 8-bit mode
	} else {
		/// 16-bit mode
	}

	/// write data
	SPIx_REG->SPI_DR = Copy_u16Data;

	/// Bit 1 TXE: Transmit buffer empty
	/// Bit 0 RXNE: Receive buffer not empty, means that there is new data to be read

	while ((GET_BIT(SPIx_REG->SPI_SR, 1) == 0)
			|| (GET_BIT(SPIx_REG->SPI_SR, 0) == 0))
		;

	/// read data
	return SPIx_REG->SPI_DR;
}

void SPI_voidTransceiveStringSync(SPIx_t Copy_enumSPIx,
		u8* Copy_u8u16ptrTransmitData, u8* Copy_u8u16ptrReceiveData,
		u16 Copy_u16length) {

	if ((Copy_u8u16ptrTransmitData != NULL)
			|| (Copy_u8u16ptrReceiveData != NULL)) {

		volatile SPI_Reg_t* SPIx_REG = (volatile SPI_Reg_t*) _getREG(
				Copy_enumSPIx);

		if (GET_BIT(SPIx_REG->SPI_CR1, 11) == 0) {
			/// 8-bit mode

			while (Copy_u16length-- > 0) {

				/// write data
				if (Copy_u8u16ptrTransmitData != NULL) {
					SPIx_REG->SPI_DR = *Copy_u8u16ptrTransmitData++;
				} else {
					SPIx_REG->SPI_DR = 0;
				}

				/// Bit 1 TXE: Transmit buffer empty
				/// Bit 0 RXNE: Receive buffer not empty, means that there is new data to be read

				while ((GET_BIT(SPIx_REG->SPI_SR, 1) == 0)
						|| (GET_BIT(SPIx_REG->SPI_SR, 0) == 0))
					;

				/// read data
				if (Copy_u8u16ptrReceiveData != NULL) {
					*Copy_u8u16ptrReceiveData = SPIx_REG->SPI_DR;
					Copy_u8u16ptrReceiveData++;
				} else {
					SPIx_REG->SPI_DR;
				}

			}

		} else {
			/// 16-bit mode

			while (Copy_u16length-- > 0) {

				/// write data
				if (Copy_u8u16ptrTransmitData != NULL) {
					SPIx_REG->SPI_DR = *((u16*) Copy_u8u16ptrTransmitData);
					(u16*) Copy_u8u16ptrReceiveData++;
				} else {
					SPIx_REG->SPI_DR = 0;
				}

				/// Bit 1 TXE: Transmit buffer empty
				/// Bit 0 RXNE: Receive buffer not empty, means that there is new data to be read

				while ((GET_BIT(SPIx_REG->SPI_SR, 1) == 0)
						|| (GET_BIT(SPIx_REG->SPI_SR, 0) == 0))
					;

				/// read data
				if (Copy_u8u16ptrReceiveData != NULL) {
					*((u16*) Copy_u8u16ptrReceiveData) = SPIx_REG->SPI_DR;
					(u16*) Copy_u8u16ptrReceiveData++;
				} else {
					SPIx_REG->SPI_DR;
				}

			}

		}

	}

	/// read data
//	return SPIx_REG->SPI_DR;
}

void SPI_voidTransceiveCharAsync(SPIx_t Copy_enumSPIx, u16 Copy_u16Data,
		SPI_voidCallbacku16 voidTransmitCallbacku16,
		SPI_voidCallbacku16 voidReceiveCallbacku16,
		SPI_voidCallback voidErrorCallback) {

	volatile SPI_Reg_t* SPIx_REG = (volatile SPI_Reg_t*) _getREG(Copy_enumSPIx);

	// check which INT will be needed

	if (voidTransmitCallbacku16 != NULL) {
		/// Bit 7 TXEIE: Tx buffer empty interrupt enable
		SET_BIT(SPIx_REG->SPI_CR2, 7);

		// set callback

		voidTransmitCallbacks[Copy_enumSPIx] = voidTransmitCallbacku16;

	}

	if (voidReceiveCallbacku16 != NULL) {

		/// Bit 6 RXNEIE: RX buffer not empty interrupt enable
		SET_BIT(SPIx_REG->SPI_CR2, 6);

		// set callback

		voidReceiveCallbacks[Copy_enumSPIx] = voidReceiveCallbacku16;

	}

	if (voidErrorCallback != NULL) {
		/// Bit 5 ERRIE: Error interrupt enable
		SET_BIT(SPIx_REG->SPI_CR2, 5);

		// set callback

		voidErrorCallbacks[Copy_enumSPIx] = voidErrorCallback;
	}

	// set data
	SPIx_REG->SPI_DR = Copy_u16Data;

}

///		DMA


void SPI_voidTxDMAEnable(SPIx_t Copy_enumSPIx){

	volatile SPI_Reg_t* SPIx_REG = (volatile SPI_Reg_t*) _getREG(Copy_enumSPIx);

	/// Bit 1 TXDMAEN: Tx buffer DMA enable
	SET_BIT(SPIx_REG->SPI_CR2 , 1);
}
void SPI_voidTxDMADisable(SPIx_t Copy_enumSPIx){

	volatile SPI_Reg_t* SPIx_REG = (volatile SPI_Reg_t*) _getREG(Copy_enumSPIx);

	/// Bit 1 TXDMAEN: Tx buffer DMA enable
	CLR_BIT(SPIx_REG->SPI_CR2 , 1);
}
void SPI_voidRxDMAEnable(SPIx_t Copy_enumSPIx){

	volatile SPI_Reg_t* SPIx_REG = (volatile SPI_Reg_t*) _getREG(Copy_enumSPIx);

	/// Bit 0 RXDMAEN: Rx buffer DMA enable
	SET_BIT(SPIx_REG->SPI_CR2 , 0);
}
void SPI_voidRxDMADisable(SPIx_t Copy_enumSPIx){

	volatile SPI_Reg_t* SPIx_REG = (volatile SPI_Reg_t*) _getREG(Copy_enumSPIx);

	/// Bit 0 RXDMAEN: Rx buffer DMA enable
	CLR_BIT(SPIx_REG->SPI_CR2 , 0);
}


/// 	end DMA

/// ISRs

void SPI1_IRQHandler(void) {

	///
	/// the arrange of Rx flag & Tx flag is important
	///

	if (GET_BIT(SPI1_REG->SPI_SR, 0)) {
		// Receive

		/// Bit 6 RXNEIE: RX buffer not empty interrupt enable
		CLR_BIT(SPI1_REG->SPI_CR2, 6);

		voidReceiveCallbacks[0]((u16) SPI1_REG->SPI_DR);
	}

	if (GET_BIT(SPI1_REG->SPI_SR, 1)) {
		// Transmit

		/// Bit 7 TXEIE: Tx buffer empty interrupt enable
		CLR_BIT(SPI1_REG->SPI_CR2, 7);

		voidTransmitCallbacks[0]((u16) SPI1_REG->SPI_DR);

	}

	/// Errors
	/// there is sequence to clear them ...

	if (GET_BIT(SPI1_REG->SPI_SR, 4)) {

		/// Overrun flag (OVR)

		voidErrorCallbacks[0]();

		SPI1_REG->SPI_DR;
		SPI1_REG->SPI_SR;

	}

	if (GET_BIT(SPI1_REG->SPI_SR, 5)) {
		/// Master mode fault (MODF)
		/// there is sequence to clear them ...
	}

	if (GET_BIT(SPI1_REG->SPI_SR, 6)) {
		/// Bit 4 CRCERR: CRC error flag
		/// there is sequence to clear them ...
	}

}

//void SPI2_IRQHandler(void) {
//
//	if (GET_BIT(SPI2_REG->SPI_SR, 1) || GET_BIT(SPI2_REG->SPI_SR, 0)) {
//		// Transceive
//
//		voidTransceiveCallbacks[1]((u16) SPI2_REG->SPI_DR);
//
//	}
//
//	/// Errors
//	/// there is sequence to clear them ...
//
//	if (GET_BIT(SPI2_REG->SPI_SR, 4)) {
//
//		/// Overrun flag (OVR)
//
//		voidErrorCallbacks[1]();
//
//		SPI2_REG->SPI_DR;
//		SPI2_REG->SPI_SR;
//
//	}
//
//	if (GET_BIT(SPI2_REG->SPI_SR, 5)) {
//		/// Master mode fault (MODF)
//		/// there is sequence to clear them ...
//	}
//
//	if (GET_BIT(SPI2_REG->SPI_SR, 6)) {
//		/// Bit 4 CRCERR: CRC error flag
//		/// there is sequence to clear them ...
//	}
//
//}
