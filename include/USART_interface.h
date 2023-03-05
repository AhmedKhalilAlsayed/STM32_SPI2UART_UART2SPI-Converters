/*
 * UART_interface.h
 *
 *  Created on: Aug 19, 2022
 *      Author: Mega Store
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define USART_F_CPU	8000000UL
//#define USART_SCALE_BUADRATE 100

typedef void (*USART_voidReceiveCallback)(u16 Copy_u16Data);

typedef enum {

	USARTx_1, USARTx_2, USARTx_3,
} USARTx_t;

typedef enum {
	USART_Buad_Rate_2_4_Kbps = 2400,
	USART_Buad_Rate_9_6_Kbps = 9600,
	USART_Buad_Rate_19_2_Kbps = 19200,
	USART_Buad_Rate_57_6_Kbps = 57600,
	USART_Buad_Rate_115_2_Kbps = 115200,
	USART_Buad_Rate_230_4_Kbps = 230400,
	USART_Buad_Rate_460_8_Kbps = 460800,
	USART_Buad_Rate_921_6_Kbps = 921600,
	USART_Buad_Rate_2250_Kbps = 2250000,
	USART_Buad_Rate_4500_Kbps = 4500000,
} USART_Buad_Rate_t;

typedef enum {
	USART_Frame_1_Start_bit_8_Data_bits_1_Stop_bits,
	USART_Frame_1_Start_bit_9_Data_bits_1_Stop_bits,
	USART_Frame_1_Start_bit_8_Data_bits_2_Stop_bits,
	USART_Frame_1_Start_bit_9_Data_bits_2_Stop_bits,
} USART_Frame_t;

// todo: you can add more !!!

void USART_voidInit(USARTx_t Copy_enumUSARTx,
		USART_Buad_Rate_t Copy_enumBuadRate, USART_Frame_t Copy_enumFrame);

/// DMA

//void USART_voidSendInitDMA(USARTx_t Copy_enumUSARTx);
//void USART_voidCheckTransmissionCompleteDMA(USARTx_t Copy_enumUSARTx);

void USART_voidTxDMAEnable(USARTx_t Copy_enumUSARTx);
void USART_voidTxDMADisable(USARTx_t Copy_enumUSARTx);
void USART_voidTxDMAClearTransmissionComplete(USARTx_t Copy_enumUSARTx);
void USART_voidRxDMAEnable(USARTx_t Copy_enumUSARTx);
void USART_voidRxDMADisable(USARTx_t Copy_enumUSARTx);
void USART_voidRxDMAClearRecevieComplete(USARTx_t Copy_enumUSARTx);

/// DMA

void USART_voidSendCharSync(USARTx_t Copy_enumUSARTx, u16 Copy_u16Data);

void USART_voidSendStringSync(USARTx_t Copy_enumUSARTx, u8* Copy_u8ptrData);

u16 USART_u16ReciveCharSync(USARTx_t Copy_enumUSARTx);

void USART_voidReciveCharAsync(USARTx_t Copy_enumUSARTx,
		USART_voidReceiveCallback voidCallback);

#ifdef DMA_INTERFACE_H_

#endif

#endif /* UART_INTERFACE_H_ */
