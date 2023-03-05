/*
 * NVIC_interface..h
 *
 *  Created on: Aug 8, 2022
 *      Author: Mega Store
 */

#ifndef NVIC_INTERFACE__H_
#define NVIC_INTERFACE__H_

typedef enum {
	NVIC_InterruptID_WWDG,
	NVIC_InterruptID_PVD,
	NVIC_InterruptID_TAMPER,
	NVIC_InterruptID_RTC,
	NVIC_InterruptID_FLASH,
	NVIC_InterruptID_RCC,
	NVIC_InterruptID_EXTI0,
	NVIC_InterruptID_EXTI1,
	NVIC_InterruptID_EXTI2,
	NVIC_InterruptID_EXTI3,
	NVIC_InterruptID_EXTI4,
	NVIC_InterruptID_DMA1_Channel1,
	NVIC_InterruptID_DMA1_Channel2,
	NVIC_InterruptID_DMA1_Channel3,
	NVIC_InterruptID_DMA1_Channel4,
	NVIC_InterruptID_DMA1_Channel5,
	NVIC_InterruptID_DMA1_Channel6,
	NVIC_InterruptID_DMA1_Channel7,
	NVIC_InterruptID_ADC1_2,
	NVIC_InterruptID_USB_HP_CAN_TX,
	NVIC_InterruptID_USB_LP_CAN_RX0,
	NVIC_InterruptID_CAN_RX1,
	NVIC_InterruptID_CAN_SCE,
	NVIC_InterruptID_EXTI9_5,
	NVIC_InterruptID_TIM1_BRK,
	NVIC_InterruptID_TIM1_UP,
	NVIC_InterruptID_TIM1_TRG_COM,
	NVIC_InterruptID_TIM1_CC,
	NVIC_InterruptID_TIM2,
	NVIC_InterruptID_TIM3,
	NVIC_InterruptID_TIM4,
	NVIC_InterruptID_I2C1_EV,
	NVIC_InterruptID_I2C1_ER,
	NVIC_InterruptID_I2C2_EV,
	NVIC_InterruptID_I2C2_ER,
	NVIC_InterruptID_SPI1,
	NVIC_InterruptID_SPI2,
	NVIC_InterruptID_USART1,
	NVIC_InterruptID_USART2,
	NVIC_InterruptID_USART3,
	NVIC_InterruptID_EXTI15_10,
	NVIC_InterruptID_RTCAlarm,
	NVIC_InterruptID_USBWakeup,
	NVIC_InterruptID_TIM8_BRK,
	NVIC_InterruptID_TIM8_UP,
	NVIC_InterruptID_TIM8_TRG_COM,
	NVIC_InterruptID_TIM8_CC,
	NVIC_InterruptID_ADC3,
	NVIC_InterruptID_FSMC,
	NVIC_InterruptID_SDIO,
	NVIC_InterruptID_TIM5,
	NVIC_InterruptID_SPI3,
	NVIC_InterruptID_UART4,
	NVIC_InterruptID_UART5,
	NVIC_InterruptID_TIM6,
	NVIC_InterruptID_TIM7,
	NVIC_InterruptID_DMA2_Channel1,
	NVIC_InterruptID_DMA2_Channel2,
	NVIC_InterruptID_DMA2_Channel3,
	NVIC_InterruptID_DMA2_Channel4_5,
} NVIC_InterruptID_t;

typedef enum {
	NVIC_PriorityLevel_0_Highest,
	NVIC_PriorityLevel_1,
	NVIC_PriorityLevel_2,
	NVIC_PriorityLevel_3,
	NVIC_PriorityLevel_4,
	NVIC_PriorityLevel_5,
	NVIC_PriorityLevel_6,
	NVIC_PriorityLevel_7,
	NVIC_PriorityLevel_8,
	NVIC_PriorityLevel_9,
	NVIC_PriorityLevel_10,
	NVIC_PriorityLevel_11,
	NVIC_PriorityLevel_12,
	NVIC_PriorityLevel_13,
	NVIC_PriorityLevel_14,
	NVIC_PriorityLevel_15_Lowest,
} NVIC_PriorityLevel_t;

typedef enum {
	NVIC_PriorityGrouping_16_Groups_NONE_SubGroups = 0b011,
	NVIC_PriorityGrouping_8_Groups_2_SubGroups,
	NVIC_PriorityGrouping_4_Groups_4_SubGroups,
	NVIC_PriorityGrouping_2_Groups_8_SubGroups,
	NVIC_PriorityGrouping_NONE_Groups_16_SubGroups,
} NVIC_PriorityGrouping_t;

typedef enum {
	NVIC_GroupPriority_0,
	NVIC_GroupPriority_1,
	NVIC_GroupPriority_2,
	NVIC_GroupPriority_3,
	NVIC_GroupPriority_4,
	NVIC_GroupPriority_5,
	NVIC_GroupPriority_6,
	NVIC_GroupPriority_7,
	NVIC_GroupPriority_8,
	NVIC_GroupPriority_9,
	NVIC_GroupPriority_10,
	NVIC_GroupPriority_11,
	NVIC_GroupPriority_12,
	NVIC_GroupPriority_13,
	NVIC_GroupPriority_14,
	NVIC_GroupPriority_15,
	NVIC_GroupPriority_NONE
} NVIC_GroupPriority_t;

typedef enum {
	NVIC_SubPriority_0,
	NVIC_SubPriority_1,
	NVIC_SubPriority_2,
	NVIC_SubPriority_3,
	NVIC_SubPriority_4,
	NVIC_SubPriority_5,
	NVIC_SubPriority_6,
	NVIC_SubPriority_7,
	NVIC_SubPriority_8,
	NVIC_SubPriority_9,
	NVIC_SubPriority_10,
	NVIC_SubPriority_11,
	NVIC_SubPriority_12,
	NVIC_SubPriority_13,
	NVIC_SubPriority_14,
	NVIC_SubPriority_15,
	NVIC_SubPriority_NONE,
} NVIC_SubPriority_t;


void NVIC_voidInit(void (*SCB_voidSetPriorityGrouping)(u8),
		NVIC_PriorityGrouping_t Copy_enumPriorityGrouping);

/*
 * Args: the interrupt ID from enum {NVIC_InterruptID_t}
 * Desc: enable the interrupt
 * Return: the state of flag is it enabled or not?
 * */
u8 NVIC_u8EnableInterrupt(NVIC_InterruptID_t Copy_enumInterruptID);
/*
 * Args: the interrupt ID from enum {NVIC_InterruptID_t}
 * Desc: disable the interrupt
 * Return: the state of flag is it disabled or not?
 * */
u8 NVIC_u8DisableInterrupt(NVIC_InterruptID_t Copy_enumInterruptID);

/*
 * Args: the interrupt ID from enum {NVIC_InterruptID_t}
 * Desc: for pending flag of  interrupt
 * Return: the state of flag is it pended or not?
 * */
u8 NVIC_u8SetPendingFlag(NVIC_InterruptID_t Copy_enumInterruptID);

/*
 * Args: the interrupt ID from enum {NVIC_InterruptID_t}
 * Desc: for pending flag of  interrupt
 * Return: the state of flag is it pended or not?
 * */
u8 NVIC_u8ClearPendingFlag(NVIC_InterruptID_t Copy_enumInterruptID);

/*
 * Args: the interrupt ID from enum {NVIC_InterruptID_t}
 * Desc: to know the state of spacific interrupt by check is it active or not?
 * Return: the state of flag is it enabled or not?
 * */
u8 NVIC_u8GetActiveFlag(NVIC_InterruptID_t Copy_enumInterruptID);


u8 NVIC_u8SetPriorityInterrupt(
		NVIC_InterruptID_t Copy_enumInterruptID,
		NVIC_GroupPriority_t Copy_enumGroupPriority,
		NVIC_SubPriority_t Copy_enumSubPriority);


/*
 * Args: the interrupt ID from enum {NVIC_InterruptID_t}
 * Desc: to frie an interuppt by its ID
 * */
void NVIC_voidTriggerInterrupt(NVIC_InterruptID_t Copy_enumInterruptID);

#endif /* NVIC_INTERFACE__H_ */
