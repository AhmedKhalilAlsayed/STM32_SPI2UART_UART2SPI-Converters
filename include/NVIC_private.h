/*
 * NVIC_private..h
 *
 *  Created on: Aug 8, 2022
 *      Author: Mega Store
 */

#ifndef NVIC_PRIVATE__H_
#define NVIC_PRIVATE__H_

#define NVIC_BASE_ADDRESS_REG	0xE000E100

// from intruppetID = 0 to 31
#define NVIC_ISER0_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x000))
// from intruppetID = 32 to 63
// and we have only {0 to 59} INT
#define NVIC_ISER1_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x004))

#define NVIC_ICER0_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x080))
#define NVIC_ICER1_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x084))

#define NVIC_ISPR0_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x100))
#define NVIC_ISPR1_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x104))

#define NVIC_ICPR0_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x180))
#define NVIC_ICPR1_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x184))

#define NVIC_IABR0_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x200))
#define NVIC_IABR1_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0x204))

//ASK::: 129 byte >> ARR from 0 to 128
#define NVIC_IPR_ARR_REG ((volatile u8*)(NVIC_BASE_ADDRESS_REG+0x300))


#define NVIC_STIR_REG *((volatile u32*)(NVIC_BASE_ADDRESS_REG+0xE00))

#endif /* NVIC_PRIVATE__H_ */
