/*
 * DMA_program.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Mega Store
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_config.h"
#include "DMA_private.h"

static DMA_voidCallback voidChannelsCompleteCallback[7] = { NULL, NULL, NULL,
NULL,
NULL, NULL, NULL };
static DMA_voidCallback voidChannelsHalfCompleteCallback[7] = { NULL, NULL,
NULL, NULL,
NULL, NULL, NULL };
static DMA_voidCallback voidChannelsErrorCallback[7] = { NULL, NULL, NULL, NULL,
NULL, NULL, NULL };

void DMA_voidInitChannel(DMA_Channelx_t Copy_enumChannelx,
		DMA_Channel_Priority_t Copy_enumPriority, DMA_Mode_t Copy_enumMode,
		DMA_Pointers_Mode_t Copy_enumDMAPointersMode,
		DMA_Block_Size_t Copy_enumPeripheralSize,
		DMA_Block_Size_t Copy_enumMemorySize) {

	/// force stop channel for re-init
	// reset value
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR = 0x0;

	/// channel priority

	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR &= ~(0b11 << 12);
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR |=
			(Copy_enumPriority << 12);

	/// DMA mode

	switch (Copy_enumMode) {
	case DMA_Mode_Memory_To_Memory:
		SET_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 14);
		CLR_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 5);
		break;
	case DMA_Mode_Peripheral_And_Memory:
//		CLR_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 14);
//		CLR_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 5);
//		break;
	case DMA_Mode_Peripheral_To_Peripheral:
		CLR_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 14);
		CLR_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 5);
		break;
	case DMA_Mode_Peripheral_And_Memory_Circular_Mode:
//		CLR_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 14);
//		SET_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 5);
//		break;
	case DMA_Mode_Peripheral_To_Peripheral_Circular_Mode:
		CLR_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 14);
		SET_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 5);
		break;
	}

	/// pointers mode

	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR &= ~(0b11 << 6);
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR |=
			(Copy_enumDMAPointersMode << 6);

	/// block size
	// memory
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR &= ~(0b11 << 10);
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR |= (Copy_enumMemorySize
			<< 10);
	// Peripheral
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR &= ~(0b11 << 8);
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR |= (Copy_enumPeripheralSize
			<< 8);

}

void DMA_voidStartChannelSync(DMA_Channelx_t Copy_enumChannelx,
		u32 Copy_u32PeripheralAddress, u32 Copy_u32MemoryAddress,
		u16 Copy_u16BlockLength, DMA_Data_Mode_t Copy_enumDataMode) {

	/// PeripheralAddress
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CPAR =
			Copy_u32PeripheralAddress;

	/// MemoryAddress
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CMAR = Copy_u32MemoryAddress;

	/// length
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CNDTR = Copy_u16BlockLength;

	/// data direction
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR &= ~(0b1 << 4);
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR |=
			(Copy_enumDataMode << 4);

	/// channel enable
	SET_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 0);

	/// polling
	// on global flag

	while (!GET_BIT(DMA_REG->DMA_ISR, (4 * Copy_enumChannelx))) {
		__asm("NOP");
	}

	if (GET_BIT(DMA_REG->DMA_ISR, ((4 * Copy_enumChannelx) + 1))) {
		// transfer complete

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * Copy_enumChannelx) + 2))) {
		// half transfer flag

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * Copy_enumChannelx) + 3))) {
		//  transfer error flag
	}

	/// clear the global flag to clear others
	// atomic access
	SET_BIT(DMA_REG->DMA_IFCR, (4 * Copy_enumChannelx));

}

void DMA_voidStartChannelAsync(DMA_Channelx_t Copy_enumChannelx,
		DMA_Peripheralx_t Copy_u32PeripheralAddress, u32 Copy_u32MemoryAddress,
		u16 Copy_u16BlockLength, DMA_Data_Mode_t Copy_enumDataMode,
		DMA_voidCallback voidCompleteCallback,
		DMA_voidCallback voidHalfCompleteCallback,
		DMA_voidCallback voidErrorCallback) {

	/// PeripheralAddress
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CPAR =
			Copy_u32PeripheralAddress;

	/// MemoryAddress
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CMAR = Copy_u32MemoryAddress;

	/// length
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CNDTR = Copy_u16BlockLength;

	/// data direction
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR &= ~(0b1 << 4);
	DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR |=
			(Copy_enumDataMode << 4);

	/// set callbacks

	/// Bit 1 TCIE: Transfer complete interrupt enable
	if (voidCompleteCallback != NULL) {

		voidChannelsCompleteCallback[Copy_enumChannelx] = voidCompleteCallback;

		SET_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 1);
	}

	/// Bit 3 TEIE: Transfer error interrupt enable
	if (voidErrorCallback != NULL) {

		voidChannelsErrorCallback[Copy_enumChannelx] = voidErrorCallback;

		SET_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 3);
	}

	/// Bit 2 HTIE: Half transfer interrupt enable
	if (voidHalfCompleteCallback != NULL) {
		voidChannelsHalfCompleteCallback[Copy_enumChannelx] =
				voidHalfCompleteCallback;
		SET_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 2);
	}

	/// channel enable
	SET_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 0);

}

void DMA_voidStopChannel(DMA_Channelx_t Copy_enumChannelx) {

	/// channel disable
	CLR_BIT(DMA_REG->DMA_channels[Copy_enumChannelx].DMA_CCR, 0);
}

/// ISRs

#define CHANNEL_ID	(0)
void DMA1_Channel1_IRQHandler(void) {

	/// callbacks

	if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 1))) {
		// transfer complete

		///check circular or not
		// if not so disable the INT and channel
		if (GET_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 5)) {

			/// Bit 5 CIRC: Circular mode

		} else {

			/// Bit 3 TEIE: Transfer error interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 3);

			/// Bit 2 HTIE: Half transfer interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 2);

			/// Bit 1 TCIE: Transfer complete interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 1);

			/// channel disable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 0);

		}

		if (voidChannelsCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 2))) {
		// half transfer flag
		if (voidChannelsHalfCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsHalfCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 3))) {
		//  transfer error flag
		if (voidChannelsErrorCallback[CHANNEL_ID] != NULL) {

			voidChannelsErrorCallback[CHANNEL_ID]();
		}
	}

	/// clear the global flag to clear others
	// atomic access
	SET_BIT(DMA_REG->DMA_IFCR, (4 * CHANNEL_ID));

}
#undef CHANNEL_ID

#define CHANNEL_ID	(1)
void DMA1_Channel2_IRQHandler(void) {

	/// callbacks

	if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 1))) {
		// transfer complete

		///check circular or not
		// if not so disable the INT and channel
		if (GET_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 5)) {

			/// Bit 5 CIRC: Circular mode

		} else {

			/// Bit 3 TEIE: Transfer error interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 3);

			/// Bit 2 HTIE: Half transfer interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 2);

			/// Bit 1 TCIE: Transfer complete interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 1);

			/// channel disable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 0);

		}

		if (voidChannelsCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 2))) {
		// half transfer flag
		if (voidChannelsHalfCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsHalfCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 3))) {
		//  transfer error flag
		if (voidChannelsErrorCallback[CHANNEL_ID] != NULL) {

			voidChannelsErrorCallback[CHANNEL_ID]();
		}
	}

	/// clear the global flag to clear others
	// atomic access
	SET_BIT(DMA_REG->DMA_IFCR, (4 * CHANNEL_ID));

}
#undef CHANNEL_ID

#define CHANNEL_ID	(2)
void DMA1_Channel3_IRQHandler(void) {

	/// callbacks

	if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 1))) {
		// transfer complete

		///check circular or not
		// if not so disable the INT and channel
		if (GET_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 5)) {

			/// Bit 5 CIRC: Circular mode

		} else {

			/// Bit 3 TEIE: Transfer error interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 3);

			/// Bit 2 HTIE: Half transfer interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 2);

			/// Bit 1 TCIE: Transfer complete interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 1);

			/// channel disable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 0);

		}

		if (voidChannelsCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 2))) {
		// half transfer flag
		if (voidChannelsHalfCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsHalfCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 3))) {
		//  transfer error flag
		if (voidChannelsErrorCallback[CHANNEL_ID] != NULL) {

			voidChannelsErrorCallback[CHANNEL_ID]();
		}
	}

	/// clear the global flag to clear others
	// atomic access
	SET_BIT(DMA_REG->DMA_IFCR, (4 * CHANNEL_ID));

}
#undef CHANNEL_ID

#define CHANNEL_ID	(3)
void DMA1_Channel4_IRQHandler(void) {

	/// callbacks

	if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 1))) {
		// transfer complete

		///check circular or not
		// if not so disable the INT and channel
		if (GET_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 5)) {

			/// Bit 5 CIRC: Circular mode

		} else {

			/// Bit 3 TEIE: Transfer error interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 3);

			/// Bit 2 HTIE: Half transfer interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 2);

			/// Bit 1 TCIE: Transfer complete interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 1);

			/// channel disable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 0);

		}

		if (voidChannelsCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 2))) {
		// half transfer flag
		if (voidChannelsHalfCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsHalfCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 3))) {
		//  transfer error flag
		if (voidChannelsErrorCallback[CHANNEL_ID] != NULL) {

			voidChannelsErrorCallback[CHANNEL_ID]();
		}
	}

	/// clear the global flag to clear others
	// atomic access
	SET_BIT(DMA_REG->DMA_IFCR, (4 * CHANNEL_ID));

}
#undef CHANNEL_ID

#define CHANNEL_ID	(4)
void DMA1_Channel5_IRQHandler(void) {

	/// callbacks

	if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 1))) {
		// transfer complete

		///check circular or not
		// if not so disable the INT and channel
		if (GET_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 5)) {

			/// Bit 5 CIRC: Circular mode

		} else {

			/// Bit 3 TEIE: Transfer error interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 3);

			/// Bit 2 HTIE: Half transfer interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 2);

			/// Bit 1 TCIE: Transfer complete interrupt enable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 1);

			/// channel disable
			CLR_BIT(DMA_REG->DMA_channels[CHANNEL_ID].DMA_CCR, 0);

		}

		if (voidChannelsCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 2))) {
		// half transfer flag
		if (voidChannelsHalfCompleteCallback[CHANNEL_ID] != NULL) {

			voidChannelsHalfCompleteCallback[CHANNEL_ID]();
		}

	} else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * CHANNEL_ID) + 3))) {
		//  transfer error flag
		if (voidChannelsErrorCallback[CHANNEL_ID] != NULL) {

			voidChannelsErrorCallback[CHANNEL_ID]();
		}
	}

	/// clear the global flag to clear others
	// atomic access
	SET_BIT(DMA_REG->DMA_IFCR, (4 * CHANNEL_ID));

}
#undef CHANNEL_ID

/*
 void DMA1_Channel4_IRQHandler(void) {

 /// callbacks

 if (GET_BIT(DMA_REG->DMA_ISR, ((4 * 3) + 1))) {
 // transfer complete

 ///check circular or not
 // if not so disable the INT and channel
 if (GET_BIT(DMA_REG->DMA_channels[3].DMA_CCR, 5)) {

 /// Bit 5 CIRC: Circular mode

 } else {

 /// Bit 3 TEIE: Transfer error interrupt enable
 CLR_BIT(DMA_REG->DMA_channels[3].DMA_CCR, 3);

 /// Bit 2 HTIE: Half transfer interrupt enable
 CLR_BIT(DMA_REG->DMA_channels[3].DMA_CCR, 2);

 /// Bit 1 TCIE: Transfer complete interrupt enable
 CLR_BIT(DMA_REG->DMA_channels[3].DMA_CCR, 1);

 /// channel disable
 CLR_BIT(DMA_REG->DMA_channels[3].DMA_CCR, 0);

 }

 if (voidChannelsCompleteCallback[3] != NULL) {

 voidChannelsCompleteCallback[3]();
 }

 } else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * 3) + 2))) {
 // half transfer flag
 if (voidChannelsHalfCompleteCallback[3] != NULL) {

 voidChannelsHalfCompleteCallback[3]();
 }

 } else if (GET_BIT(DMA_REG->DMA_ISR, ((4 * 3) + 3))) {
 //  transfer error flag
 if (voidChannelsErrorCallback[3] != NULL) {

 voidChannelsErrorCallback[3]();
 }
 }

 /// clear the global flag to clear others
 // atomic access
 SET_BIT(DMA_REG->DMA_IFCR, (4 * 3));

 }
 */
