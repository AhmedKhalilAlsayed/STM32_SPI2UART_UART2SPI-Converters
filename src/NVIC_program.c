/*
 * NVIC_program.c
 *
 *  Created on: Aug 8, 2022
 *      Author: Mega Store
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"

static NVIC_PriorityGrouping_t Local_enumPriorityGrouping = 0;

//void NVIC_voidInit(u8 Copy_u8PriorityGrouping){
//	Local_u8PriorityGrouping = Copy_u8PriorityGrouping;
//}

void NVIC_voidInit(void (*SCB_voidSetPriorityGrouping)(u8),
		NVIC_PriorityGrouping_t Copy_enumPriorityGrouping) {
	if (SCB_voidSetPriorityGrouping != NULL) {
		SCB_voidSetPriorityGrouping(Copy_enumPriorityGrouping);
		Local_enumPriorityGrouping = Copy_enumPriorityGrouping;
	}
}

u8 NVIC_u8EnableInterrupt(NVIC_InterruptID_t Copy_enumInterruptID) {
	u8 temp_u8Flag = 0;
	if (Copy_enumInterruptID < 32) {
		NVIC_ISER0_REG = 1 << Copy_enumInterruptID;
		temp_u8Flag = GET_BIT(NVIC_ISER0_REG, Copy_enumInterruptID);
	} else if (Copy_enumInterruptID < 60) {
		NVIC_ISER1_REG = 1 << (Copy_enumInterruptID - 32);
		temp_u8Flag = GET_BIT(NVIC_ISER1_REG, (Copy_enumInterruptID - 32));
	} else {
		//error
	}
	return temp_u8Flag;
}

u8 NVIC_u8DisableInterrupt(NVIC_InterruptID_t Copy_enumInterruptID) {
	u8 temp_u8Flag = 0;
	if (Copy_enumInterruptID < 32) {
		NVIC_ICER0_REG = 1 << Copy_enumInterruptID;
		temp_u8Flag = GET_BIT(NVIC_ICER0_REG, (Copy_enumInterruptID));
	} else if (Copy_enumInterruptID < 60) {
		NVIC_ICER1_REG = 1 << (Copy_enumInterruptID - 32);
		temp_u8Flag = GET_BIT(NVIC_ICER1_REG, (Copy_enumInterruptID - 32));
	} else {
		//error
	}
	return temp_u8Flag;
}

u8 NVIC_u8SetPendingFlag(NVIC_InterruptID_t Copy_enumInterruptID) {
	u8 temp_u8Flag = 0;
	if (Copy_enumInterruptID < 32) {
		NVIC_ISPR0_REG = 1 << Copy_enumInterruptID;
		temp_u8Flag = GET_BIT(NVIC_ISPR0_REG, (Copy_enumInterruptID));
	} else if (Copy_enumInterruptID < 60) {
		NVIC_ISPR1_REG = 1 << (Copy_enumInterruptID - 32);
		temp_u8Flag = GET_BIT(NVIC_ISPR1_REG, (Copy_enumInterruptID - 32));
	} else {
		//error
	}
	return temp_u8Flag;
}

u8 NVIC_u8ClearPendingFlag(NVIC_InterruptID_t Copy_enumInterruptID) {
	u8 temp_u8Flag = 0;
	if (Copy_enumInterruptID < 32) {
		NVIC_ICPR0_REG = 1 << Copy_enumInterruptID;
		temp_u8Flag = GET_BIT(NVIC_ICPR0_REG, (Copy_enumInterruptID));
	} else if (Copy_enumInterruptID < 60) {
		NVIC_ICPR1_REG = 1 << (Copy_enumInterruptID - 32);
		temp_u8Flag = GET_BIT(NVIC_ICPR1_REG, (Copy_enumInterruptID - 32));
	} else {
		//error
	}
	return temp_u8Flag;
}

u8 NVIC_u8GetActiveFlag(NVIC_InterruptID_t Copy_enumInterruptID) {
	u8 temp_u8Flag = 0;
	if (Copy_enumInterruptID < 32) {
		temp_u8Flag = GET_BIT(NVIC_IABR0_REG, (Copy_enumInterruptID));
	} else if (Copy_enumInterruptID < 60) {
		temp_u8Flag = GET_BIT(NVIC_IABR1_REG, (Copy_enumInterruptID - 32));
	} else {
		//error
	}
	return temp_u8Flag;
}

u8 NVIC_u8SetPriorityInterrupt(NVIC_InterruptID_t Copy_enumInterruptID,
		NVIC_GroupPriority_t Copy_enumGroupPriority,
		NVIC_SubPriority_t Copy_enumSubPriority) {

	u8 temp_u8State = 0;

	switch (Local_enumPriorityGrouping) {
	case NVIC_PriorityGrouping_NONE_Groups_16_SubGroups:
		if ((Copy_enumGroupPriority == NVIC_GroupPriority_NONE)
				&& (Copy_enumSubPriority <= NVIC_SubPriority_15)) {
			temp_u8State = 1;
			NVIC_IPR_ARR_REG[Copy_enumInterruptID] = (u8) (Copy_enumSubPriority
					<< 4);
		}
		break;
	case NVIC_PriorityGrouping_2_Groups_8_SubGroups:
		if ((Copy_enumGroupPriority < NVIC_GroupPriority_2)
				&& (Copy_enumSubPriority < NVIC_SubPriority_8)) {
			temp_u8State = 1;
			NVIC_IPR_ARR_REG[Copy_enumInterruptID] =
					(u8) (Copy_enumGroupPriority << 7
							| Copy_enumSubPriority << 4);
		}

		break;
	case NVIC_PriorityGrouping_4_Groups_4_SubGroups:
		if ((Copy_enumGroupPriority < NVIC_GroupPriority_4)
				&& (Copy_enumSubPriority < NVIC_SubPriority_4)) {
			temp_u8State = 1;
			NVIC_IPR_ARR_REG[Copy_enumInterruptID] =
					(u8) (Copy_enumGroupPriority << 6
							| Copy_enumSubPriority << 4);
		}

		break;
	case NVIC_PriorityGrouping_8_Groups_2_SubGroups:
		if ((Copy_enumGroupPriority < NVIC_GroupPriority_8)
				&& (Copy_enumSubPriority < NVIC_SubPriority_2)) {
			temp_u8State = 1;
			NVIC_IPR_ARR_REG[Copy_enumInterruptID] =
					(u8) (Copy_enumGroupPriority << 5
							| Copy_enumSubPriority << 4);
		}

		break;
	case NVIC_PriorityGrouping_16_Groups_NONE_SubGroups:
		if ((Copy_enumGroupPriority <= NVIC_GroupPriority_15)
				&& (Copy_enumSubPriority == NVIC_SubPriority_NONE)) {
			temp_u8State = 1;

			NVIC_IPR_ARR_REG[Copy_enumInterruptID] =
					(u8) (Copy_enumGroupPriority << 4);
		}
		break;
	}

	return temp_u8State;
}

void NVIC_voidTriggerInterrupt(NVIC_InterruptID_t Copy_enumInterruptID) {
	NVIC_STIR_REG = Copy_enumInterruptID;
}

