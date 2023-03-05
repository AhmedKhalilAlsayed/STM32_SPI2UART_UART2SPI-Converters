/*
 * DMA_interface.h
 *
 *  Created on: Aug 23, 2022
 *      Author: Mega Store
 */

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

typedef void (*DMA_voidCallback)(void);

typedef enum {

	DMA_Channel_Priority_Low,
	DMA_Channel_Priority_Medium,
	DMA_Channel_Priority_High,
	DMA_Channel_Priority_Very_High,

} DMA_Channel_Priority_t;

typedef enum {

	DMA_Block_Size_8_bits, DMA_Block_Size_16_bits, DMA_Block_Size_32_bits,

} DMA_Block_Size_t;

typedef enum {

	DMA_Mode_Memory_To_Memory,
	DMA_Mode_Peripheral_And_Memory,
	DMA_Mode_Peripheral_To_Peripheral,
	DMA_Mode_Peripheral_And_Memory_Circular_Mode,
	DMA_Mode_Peripheral_To_Peripheral_Circular_Mode,

} DMA_Mode_t;

typedef enum {

	DMA_Pointers_Mode_MemoryInc_Off_PeripheralInc_Off,
	DMA_Pointers_Mode_MemoryInc_Off_PeripheralInc_On,
	DMA_Pointers_Mode_MemoryInc_On_PeripheralInc_Off,
	DMA_Pointers_Mode_MemoryInc_On_PeripheralInc_On,

} DMA_Pointers_Mode_t;

typedef enum {

	DMA_Data_Mode_ReadFromPripheral, DMA_Data_Mode_ReadFromMemory,

} DMA_Data_Mode_t;

typedef enum {

	DMA_Channel_1,
	DMA_Channel_2,
	DMA_Channel_3,
	DMA_Channel_4,
	DMA_Channel_5,
	DMA_Channel_6,
	DMA_Channel_7,

} DMA_Channelx_t;

typedef enum {

	DMA_Peripheral_ADC1_Channel1,
	DMA_Peripheral_TIM2_CH3_Channel1,
	DMA_Peripheral_TIM4_CH1_Channel1,

	DMA_Peripheral_SPI1_RX_Channel2 = (0x40013000 + 0x0C),
	DMA_Peripheral_USART3_TX_Channel2,
	DMA_Peripheral_TIM1_CH1_Channel2,
	DMA_Peripheral_TIM2_UP_Channel2,
	DMA_Peripheral_TIM3_CH3_Channel2,

	DMA_Peripheral_SPI1_TX_Channel3 = (0x40013000 + 0x0C),
	DMA_Peripheral_USART3_RX_Channel3,
	DMA_Peripheral_TIM3_CH4_Channel3,
	DMA_Peripheral_TIM3_UP_Channel3,

	DMA_Peripheral_SPI2_RX_Channel4 = (0x40003800 + 0x0C),
	DMA_Peripheral_I2S2_RX_Channel4,
	DMA_Peripheral_USART1_TX_Channel4 = (0x40013800 + 0x04),
	DMA_Peripheral_I2C2_TX_Channel4,
	DMA_Peripheral_TIM1_CH4_Channel4,
	DMA_Peripheral_TIM1_TRIG_Channel4,
	DMA_Peripheral_TIM1_COM_Channel4,
	DMA_Peripheral_TIM4_CH2_Channel4,

	DMA_Peripheral_SPI2_TX_Channel5 = (0x40003800 + 0x0C),
	DMA_Peripheral_I2S2_TX_Channel5,
	DMA_Peripheral_USART1_RX_Channel5 = (0x40013800 + 0x04),
	DMA_Peripheral_I2C2_RX_Channel5,
	DMA_Peripheral_TIM1_UP_Channel5,
	DMA_Peripheral_TIM2_CH1_Channel5,
	DMA_Peripheral_TIM4_CH3_Channel5,

	DMA_Peripheral_USART2_RX_Channel6,
	DMA_Peripheral_I2C1_TX_Channel6,
	DMA_Peripheral_TIM1_CH3_Channel6,
	DMA_Peripheral_TIM3_CH1_Channel6,
	DMA_Peripheral_TIM3_TRIG_Channel6,

	DMA_Peripheral_USART2_TX_Channel7,
	DMA_Peripheral_I2C1_RX_Channel7,
	DMA_Peripheral_TIM2_CH2_Channel7,
	DMA_Peripheral_TIM2_CH4_Channel7,
	DMA_Peripheral_TIM4_UP_Channel7,

} DMA_Peripheralx_t;

void DMA_voidInitChannel(DMA_Channelx_t Copy_enumChannelx,
		DMA_Channel_Priority_t Copy_enumPriority, DMA_Mode_t Copy_enumMode,
		DMA_Pointers_Mode_t Copy_enumDMAPointersMode,
		DMA_Block_Size_t Copy_enumPeripheralSize,
		DMA_Block_Size_t Copy_enumMemorySize);

void DMA_voidStartChannelSync(DMA_Channelx_t Copy_enumChannelx,
		u32 Copy_u32PeripheralAddress, u32 Copy_u32MemoryAddress,
		u16 Copy_u16BlockLength, DMA_Data_Mode_t Copy_enumDataMode);

void DMA_voidStartChannelAsync(DMA_Channelx_t Copy_enumChannelx,
		DMA_Peripheralx_t Copy_u32PeripheralAddress, u32 Copy_u32MemoryAddress,
		u16 Copy_u16BlockLength, DMA_Data_Mode_t Copy_enumDataMode,
		DMA_voidCallback voidCompleteCallback,
		DMA_voidCallback voidHalfCompleteCallback,
		DMA_voidCallback voidErrorCallback);

void DMA_voidStopChannel(DMA_Channelx_t Copy_enumChannelx);

#endif /* DMA_INTERFACE_H_ */
