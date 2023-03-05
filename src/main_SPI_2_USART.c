#include "STD_TYPES.h"

#include "NVIC_interface.h"
#include "DMA_interface.h"
#include "USART_interface.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SPI_interface.h"

void TOG_PIN() {

	static u8 x = 1;

	GPIO_voidSetPinValue(GPIO_Port_Pin_PORTA_PIN0, x);

	x = 1 - x;

}

void DMA_SPI2USART_Callback() {

	/// neet to be sure of clearing flags
	USART_voidTxDMAClearTransmissionComplete(USARTx_1);

	TOG_PIN();

}

void DMA_USART2SPI_Callback() {

	/// neet to be sure of clearing flags
	USART_voidRxDMAClearRecevieComplete(USARTx_1);

	TOG_PIN();

}

#define MODE_USART2SPI 		0
#define MODE_SPI2USART 		1

/// CHOOSE the MODE of converter {USART2SPI - SPI2USART}

#define CONVERT_MODE	MODE_USART2SPI

int main() {

	RCC_voidInit();
	RCC_voidPeripheralClockEnable(RCC_Peripherals_AHB_DMA1);
	RCC_voidPeripheralClockEnable(RCC_Peripherals_APB2_USART1);
	RCC_voidPeripheralClockEnable(RCC_Peripherals_APB2_GPIO_Port_A);
	RCC_voidPeripheralClockEnable(RCC_Peripherals_APB2_SPI1);

//	NVIC_u8EnableInterrupt(NVIC_InterruptID_SPI1);
	NVIC_u8EnableInterrupt(NVIC_InterruptID_DMA1_Channel2);
	NVIC_u8EnableInterrupt(NVIC_InterruptID_DMA1_Channel5);

	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN0,
			GPIO_Pin_Mode_GP_Output_Push_Pull_10MHz);
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN1,
			GPIO_Pin_Mode_GP_Output_Push_Pull_10MHz);

	/// USART Tx pin
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN9,
			GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz);

	/// USART Rx pin
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN10,
			GPIO_Pin_Mode_Input_Floating);

	USART_voidInit(USARTx_1, USART_Buad_Rate_9_6_Kbps,
			USART_Frame_1_Start_bit_8_Data_bits_1_Stop_bits);

	///
	USART_voidRxDMAEnable(USARTx_1);

	///
	SPI_voidRxDMAEnable(SPI_1);

#if (CONVERT_MODE == MODE_USART2SPI)

	/// SPI MASTER pins

	// NSS1
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN4,
			GPIO_Pin_Mode_GP_Output_Push_Pull_10MHz);
	// SCK1
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN5,
			GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz);
	// MISO1
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN6, GPIO_Pin_Mode_Input_Floating);
	// MOSI1
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN7,
			GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz);

	///
	SPI_voidInit(SPI_1, SPI_Mode_Master, SPI_Baud_Rate_Fpclk_8,
			SPI_Clk_Polarity_Phase_Idle_Low_Write_Read,
			SPI_Data_Format_8_bit_LSB);

	/// init DMA channel

	/// USART Rx to SPI Tx
	DMA_voidInitChannel(DMA_Channel_5, DMA_Channel_Priority_High,
			DMA_Mode_Peripheral_To_Peripheral_Circular_Mode,
			DMA_Pointers_Mode_MemoryInc_Off_PeripheralInc_Off,
			DMA_Block_Size_8_bits, DMA_Block_Size_8_bits);

	/// USART to SPI
	DMA_voidStartChannelAsync(DMA_Channel_5, DMA_Peripheral_USART1_RX_Channel5,
			DMA_Peripheral_SPI1_TX_Channel3, 1, DMA_Data_Mode_ReadFromPripheral,
			DMA_USART2SPI_Callback,
			NULL, NULL);

#endif

#if (CONVERT_MODE == MODE_SPI2USART)

	/// SPI slave pins

	// NSS1
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN4, GPIO_Pin_Mode_Input_Floating);
	// SCK1
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN5, GPIO_Pin_Mode_Input_Floating);
	// MISO1
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN6,
			GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz);
	// MOSI1
	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN7, GPIO_Pin_Mode_Input_Floating);

	///
	SPI_voidInit(SPI_1, SPI_Mode_Slave, SPI_Baud_Rate_Fpclk_8,
			SPI_Clk_Polarity_Phase_Idle_Low_Write_Read,
			SPI_Data_Format_8_bit_LSB);

	/// init DMA channel

	/// SPI Rx to USART Tx
	DMA_voidInitChannel(DMA_Channel_2, DMA_Channel_Priority_High,
			DMA_Mode_Peripheral_To_Peripheral_Circular_Mode,
			DMA_Pointers_Mode_MemoryInc_Off_PeripheralInc_Off,
			DMA_Block_Size_8_bits, DMA_Block_Size_8_bits);

	/// SPI to USART
	DMA_voidStartChannelAsync(DMA_Channel_2, DMA_Peripheral_SPI1_RX_Channel2,
			DMA_Peripheral_USART1_TX_Channel4, 1,
			DMA_Data_Mode_ReadFromPripheral, DMA_SPI2USART_Callback,
			NULL, NULL);

#endif

	/// The normal code, DMA will translate (to/from -SPI- from/to -USART-) in background
	/// ...

	while (1) {

		/**
		 TOG_PIN();
		 for (u32 i = 0; i < 1000000 / 2; i++)
		 ;

		 TOG_PIN();
		 for (u32 i = 0; i < 1000000 / 2; i++)
		 ;
		 */
	}

	return 0;
}
