#include "STD_TYPES.h"

#include "NVIC_interface.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SPI_interface.h"

void SPITxCallback(u16 data) {
	static u8 index = 0;

	static u8 str[] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0xaa, 0xbb, 0xcc };

	SPI_voidTransceiveCharAsync(SPI_1, str[index%5], SPITxCallback , NULL, NULL);

	index++;
}
#if 0
int main() {

	RCC_voidInit();
//	RCC_voidPeripheralClockEnable(RCC_Peripherals_AHB_CRC);
	RCC_voidPeripheralClockEnable(RCC_Peripherals_APB2_GPIO_Port_A);
	RCC_voidPeripheralClockEnable(RCC_Peripherals_APB2_SPI1);

	NVIC_u8EnableInterrupt(NVIC_InterruptID_SPI1);

	GPIO_voidSetPinMode(GPIO_Port_Pin_PORTA_PIN0,
			GPIO_Pin_Mode_GP_Output_Push_Pull_10MHz);

	/// master

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

//	USART_voidInit(USARTx_1, USART_Buad_Rate_2_4_Kbps,
//			USART_Frame_1_Start_bit_8_Data_bits_1_Stop_bits);

	SPI_voidInit(SPI_1, SPI_Mode_Master, SPI_Baud_Rate_Fpclk_8,
			SPI_Clk_Polarity_Phase_Idle_Low_Write_Read,
			SPI_Data_Format_8_bit_LSB);



	SPITxCallback(0);
//	SPI_voidTransceiveStringSync(SPI_1, str, NULL, sizeof(str));

	while (1) {

	}

	return 0;
}

#endif