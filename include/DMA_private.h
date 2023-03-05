/*
 * DMA_private.h
 *
 *  Created on: Aug 23, 2022
 *      Author: Mega Store
 */

#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

typedef struct {

	volatile u32 DMA_CCR;
	volatile u32 DMA_CNDTR;
	volatile u32 DMA_CPAR;
	volatile u32 DMA_CMAR;
	volatile u32 res;

} DMA_Channel_Reg_t;

typedef struct {

	volatile u32 DMA_ISR;
	volatile u32 DMA_IFCR;
	volatile DMA_Channel_Reg_t DMA_channels[7];

} DMA_Reg_t;

// just we have one DMA

#define DMA_BASE_ADDRESS	0x40020000
#define DMA_REG			((volatile DMA_Reg_t*)DMA_BASE_ADDRESS)

#endif /* DMA_PRIVATE_H_ */
