/*
 * UART_program.c
 *
 *  Created on: Aug 19, 2022
 *      Author: Mega Store
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"

static USART_voidReceiveCallback voidReceiveCallback = NULL;

static inline u32 _getREG(USARTx_t Copy_enumUSARTx) {
	switch (Copy_enumUSARTx) {
	case USARTx_1:
		return USART1_ADDRESS_REG;
		break;
	case USARTx_2:
		return USART2_ADDRESS_REG;
		break;
	case USARTx_3:
		return USART3_ADDRESS_REG;
		break;
	default:
		return NULL;
	}
}

void USART_voidInit(USARTx_t Copy_enumUSARTx,
		USART_Buad_Rate_t Copy_enumBuadRate, USART_Frame_t Copy_enumFrame) {

	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);

//	volatile USART_reg_t* USARTx_REG = NULL;
//
//	switch (Copy_enumUSARTx) {
//	case USARTx_1:
//		USARTx_REG = (volatile USART_reg_t*) USART1_ADDRESS_REG;
//		break;
//	case USARTx_2:
//		USARTx_REG = (volatile USART_reg_t*) USART2_ADDRESS_REG;
//		break;
//	case USARTx_3:
//		USARTx_REG = (volatile USART_reg_t*) USART3_ADDRESS_REG;
//		break;
//	}

/// Bit 13 UE: USART enable
	SET_BIT(USARTx_REG->USART_CR1, 13);

/// 27.6.3 Baud rate register (USART_BRR)
// USARTDIV = (Fclk/(16*buadRate))
// *100 just a scale
	u16 tempUSARTDIV = (USART_F_CPU * 100) / (16 * Copy_enumBuadRate);
	u16 tempDIVFraction = ((u16) (16 * (tempUSARTDIV % 100))) / 100;
	u16 tempDIVMantissa = tempUSARTDIV / 100;

	USARTx_REG->USART_BRR = ((tempDIVMantissa << 4) + tempDIVFraction) & 0xFFFF;

	/// Frame shape
	switch (Copy_enumFrame) {
	case USART_Frame_1_Start_bit_8_Data_bits_1_Stop_bits:
		CLR_BIT(USARTx_REG->USART_CR1, 12);	// data
		CLR_BIT(USARTx_REG->USART_CR2, 13);
		CLR_BIT(USARTx_REG->USART_CR2, 12);
		break;

	case USART_Frame_1_Start_bit_9_Data_bits_1_Stop_bits:
		SET_BIT(USARTx_REG->USART_CR1, 12);	// data
		CLR_BIT(USARTx_REG->USART_CR2, 13);
		CLR_BIT(USARTx_REG->USART_CR2, 12);
		break;

	case USART_Frame_1_Start_bit_8_Data_bits_2_Stop_bits:
		CLR_BIT(USARTx_REG->USART_CR1, 12);	// data
		SET_BIT(USARTx_REG->USART_CR2, 13);
		CLR_BIT(USARTx_REG->USART_CR2, 12);
		break;

	case USART_Frame_1_Start_bit_9_Data_bits_2_Stop_bits:
		SET_BIT(USARTx_REG->USART_CR1, 12);	// data
		SET_BIT(USARTx_REG->USART_CR2, 13);
		CLR_BIT(USARTx_REG->USART_CR2, 12);
		break;
	}

}

/// 		DMA

void USART_voidTxDMAEnable(USARTx_t Copy_enumUSARTx) {
	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);
	/// Bit 7 DMAT: DMA enable transmitter
	SET_BIT(USARTx_REG->USART_CR3, 7);

	/// Bit 3 TE: Transmitter enable
	SET_BIT(USARTx_REG->USART_CR1, 3);

}
void USART_voidTxDMADisable(USARTx_t Copy_enumUSARTx) {
	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);
	/// Bit 7 DMAT: DMA enable transmitter
	CLR_BIT(USARTx_REG->USART_CR3, 7);

	/// Bit 3 TE: Transmitter
	CLR_BIT(USARTx_REG->USART_CR1, 3);

}

void USART_voidTxDMAClearTransmissionComplete(USARTx_t Copy_enumUSARTx) {
	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);
	/// Bit 6 TC: Transmission complete
	/// 6. Clear the TC bit in the SR register by writing 0 to it.

	CLR_BIT(USARTx_REG->USART_SR, 6);
}

void USART_voidRxDMAEnable(USARTx_t Copy_enumUSARTx) {
	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);
	/// Bit 6 DMAR: DMA enable receiver
	SET_BIT(USARTx_REG->USART_CR3, 6);
	/// Bit 2 RE: Receiver
	SET_BIT(USARTx_REG->USART_CR1, 2);
}

void USART_voidRxDMADisable(USARTx_t Copy_enumUSARTx) {
	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);
	/// Bit 6 DMAR: DMA enable receiver
	CLR_BIT(USARTx_REG->USART_CR3, 6);
	/// Bit 2 RE: Receiver
	CLR_BIT(USARTx_REG->USART_CR1, 2);
}

void USART_voidRxDMAClearRecevieComplete(USARTx_t Copy_enumUSARTx) {
	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);
	/// Bit 5 RXNE: Read data register not empty
	CLR_BIT(USARTx_REG->USART_SR, 5);
}

/// END 		DMA

//void USART_voidSendInitDMA(USARTx_t Copy_enumUSARTx) {
//	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
//			Copy_enumUSARTx);
//
//	/// Bit 7 DMAT: DMA enable transmitter
//	SET_BIT(USARTx_REG->USART_CR3, 7);
//
//	/// Bit 3 TE: Transmitter enable
//	SET_BIT(USARTx_REG->USART_CR1, 3);
//
//}
//
//void USART_voidCheckTransmissionCompleteDMA(USARTx_t Copy_enumUSARTx) {
//	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
//			Copy_enumUSARTx);
//
//	/// Bit 6 TC: Transmission complete
//	/// 6. Clear the TC bit in the SR register by writing 0 to it.
//
//	CLR_BIT(USARTx_REG->USART_SR, 6);
//
//}

void USART_voidSendCharSync(USARTx_t Copy_enumUSARTx, u16 Copy_u16Data) {
	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);

	/// Bit 3 TE: Transmitter enable
	SET_BIT(USARTx_REG->USART_CR1, 3);

	/// set data
	USARTx_REG->USART_DR = Copy_u16Data & 0x1FF;

	/// Bit 6 TC: Transmission complete
	//**** The TC bit can also be cleared by writing a ‘0’ to it. This clearing sequence is recommended only for Multibuffer communication
	while (!GET_BIT(USARTx_REG->USART_SR, 6)) {
		__asm("NOP");
	}

	/// Bit 3 TE: Transmitter disable
	CLR_BIT(USARTx_REG->USART_CR1, 3);

}

void USART_voidSendStringSync(USARTx_t Copy_enumUSARTx, u8* Copy_u8ptrData) {

	if (Copy_u8ptrData != NULL) {
		volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
				Copy_enumUSARTx);

		/// Bit 3 TE: Transmitter enable
		SET_BIT(USARTx_REG->USART_CR1, 3);

		/// set data

		while (*Copy_u8ptrData != '\0') {
			USARTx_REG->USART_DR = *Copy_u8ptrData & 0x1FF;

			/// Bit 6 TC: Transmission complete
			//**** The TC bit can also be cleared by writing a ‘0’ to it. This clearing sequence is recommended only for Multibuffer communication
			while (!GET_BIT(USARTx_REG->USART_SR, 6)) {
				__asm("NOP");
			}

			Copy_u8ptrData++;
		}

		/// Bit 3 TE: Transmitter disable
		CLR_BIT(USARTx_REG->USART_CR1, 3);
	}

}

u16 USART_u16ReciveCharSync(USARTx_t Copy_enumUSARTx) {

	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);

	u16 tempReceivedData = 0;
	/// Bit 2 RE: Receiver enable
	SET_BIT(USARTx_REG->USART_CR1, 2);

	/// Bit 5 RXNE: Read data register not empty
	while (!GET_BIT(USARTx_REG->USART_SR, 5)) {
		__asm("NOP");
	}

	/// read data
	tempReceivedData = USARTx_REG->USART_DR;

	/// Bit 2 RE: Receiver disable
	CLR_BIT(USARTx_REG->USART_CR1, 2);

	return tempReceivedData;

}

void USART_voidReciveCharAsync(USARTx_t Copy_enumUSARTx,
		USART_voidReceiveCallback voidCallback) {
	volatile USART_reg_t* USARTx_REG = (volatile USART_reg_t*) _getREG(
			Copy_enumUSARTx);

	if (voidCallback != NULL) {

		voidReceiveCallback = voidCallback;

		/// Bit 5 RXNEIE: RXNE interrupt enable
		SET_BIT(USARTx_REG->USART_CR1, 5);
		/// Bit 2 RE: Receiver enable
		SET_BIT(USARTx_REG->USART_CR1, 2);

	}

}

void USART1_IRQHandler(void) {

	// from recevie
	if ((GET_BIT(USART1_REG->USART_SR, 5)) && (voidReceiveCallback != NULL)) {
		/// Bit 5 RXNEIE: RXNE interrupt disable
		CLR_BIT(USART1_REG->USART_CR1, 5);
		/// Bit 2 RE: Receiver disable
		CLR_BIT(USART1_REG->USART_CR1, 2);
		voidReceiveCallback(USART1_REG->USART_DR);
	}
}

