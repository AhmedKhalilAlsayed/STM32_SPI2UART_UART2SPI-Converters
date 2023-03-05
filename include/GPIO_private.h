/*
 * GPIO_private.h
 *
 *  Created on: Aug 4, 2022
 *      Author: Mega Store
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

typedef struct{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_Port_Reg_t;


#define GPIO_PORTA_REG	((volatile GPIO_Port_Reg_t*)0x40010800)
#define GPIO_PORTB_REG	((volatile GPIO_Port_Reg_t*)0x40010C00)
#define GPIO_PORTC_REG	((volatile GPIO_Port_Reg_t*)0x40011000)


#endif /* GPIO_PRIVATE_H_ */
