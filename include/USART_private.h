/*
 * UART_private.h
 *
 *  Created on: Aug 19, 2022
 *      Author: Mega Store
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

typedef struct {
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;
} USART_reg_t;

#define USART1_ADDRESS_REG		0x40013800
#define USART2_ADDRESS_REG		0x40004400
#define USART3_ADDRESS_REG		0x40004800

#define USART1_REG ((volatile USART_reg_t*)USART1_ADDRESS_REG)
#define USART2_REG ((volatile USART_reg_t*)USART2_ADDRESS_REG)
#define USART3_REG ((volatile USART_reg_t*)USART3_ADDRESS_REG)

#endif /* UART_PRIVATE_H_ */
