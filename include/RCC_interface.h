/*
 * RCC_interface.h
 *
 *  Created on: Aug 2, 2022
 *      Author: Mega Store
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/*

 #define RCC_HSE			0
 #define RCC_HSI			1
 #define RCC_PLL			2
 #define RCC_NO			3

 #define RCC_MCO_SRC_NO				000
 #define RCC_MCO_SRC_SYSCLK			1
 #define RCC_MCO_SRC_HSI				2
 #define RCC_MCO_SRC_HSE				3
 #define RCC_MCO_SRC_PLL_DIV_2		4

 #define RCC_AHB_PRE_NO		0
 #define RCC_AHB_PRE_2		1
 #define RCC_AHB_PRE_4		2
 #define RCC_AHB_PRE_8		3
 #define RCC_AHB_PRE_16		4
 #define RCC_AHB_PRE_64		5
 #define RCC_AHB_PRE_128		6
 #define RCC_AHB_PRE_256		7
 #define RCC_AHB_PRE_512		8

 #define RCC_APB1_PRE_NO		0
 #define RCC_APB1_PRE_2		1
 #define RCC_APB1_PRE_4		2
 #define RCC_APB1_PRE_8		3
 #define RCC_APB1_PRE_16		4

 #define RCC_APB2_PRE_NO		0
 #define RCC_APB2_PRE_2		1
 #define RCC_APB2_PRE_4		2
 #define RCC_APB2_PRE_8		3
 #define RCC_APB2_PRE_16		4

 #define RCC_ADC_PRE_2		0
 #define RCC_ADC_PRE_4		1
 #define RCC_ADC_PRE_6		2
 #define RCC_ADC_PRE_8		3


 #define RCC_PLL_MUL_2		0
 #define RCC_PLL_MUL_3		1
 #define RCC_PLL_MUL_4		2
 #define RCC_PLL_MUL_5		3
 #define RCC_PLL_MUL_6		4
 #define RCC_PLL_MUL_7		5
 #define RCC_PLL_MUL_8		6
 #define RCC_PLL_MUL_9		7
 #define RCC_PLL_MUL_10		8
 #define RCC_PLL_MUL_11		9
 #define RCC_PLL_MUL_12		10
 #define RCC_PLL_MUL_13		11
 #define RCC_PLL_MUL_14		12
 #define RCC_PLL_MUL_15		13
 #define RCC_PLL_MUL_16		14

 #define RCC_PLL_HSE_DIV_NO		0
 #define RCC_PLL_HSE_DIV_2		1


 */

//in binary form
#define RCC_HSE			00
#define RCC_HSI			01
#define RCC_PLL			10
#define RCC_NO			11

#define RCC_MCO_SRC_NO				000
#define RCC_MCO_SRC_SYSCLK			100
#define RCC_MCO_SRC_HSI				101
#define RCC_MCO_SRC_HSE				110
#define RCC_MCO_SRC_PLL_DIV_2		111

#define RCC_AHB_PRE_NO		0000
#define RCC_AHB_PRE_2		1000
#define RCC_AHB_PRE_4		1001
#define RCC_AHB_PRE_8		1010
#define RCC_AHB_PRE_16		1011
#define RCC_AHB_PRE_64		1100
#define RCC_AHB_PRE_128		1101
#define RCC_AHB_PRE_256		1110
#define RCC_AHB_PRE_512		1111

#define RCC_APB1_PRE_NO		000
#define RCC_APB1_PRE_2		100
#define RCC_APB1_PRE_4		101
#define RCC_APB1_PRE_8		110
#define RCC_APB1_PRE_16		111

#define RCC_APB2_PRE_NO		000
#define RCC_APB2_PRE_2		100
#define RCC_APB2_PRE_4		101
#define RCC_APB2_PRE_8		110
#define RCC_APB2_PRE_16		111

#define RCC_ADC_PRE_2		00
#define RCC_ADC_PRE_4		01
#define RCC_ADC_PRE_6		10
#define RCC_ADC_PRE_8		11

#define RCC_PLL_MUL_2		0000
#define RCC_PLL_MUL_3		0001
#define RCC_PLL_MUL_4		0010
#define RCC_PLL_MUL_5		0011
#define RCC_PLL_MUL_6		0100
#define RCC_PLL_MUL_7		0101
#define RCC_PLL_MUL_8		0110
#define RCC_PLL_MUL_9		0111
#define RCC_PLL_MUL_10		1000
#define RCC_PLL_MUL_11		1001
#define RCC_PLL_MUL_12		1010
#define RCC_PLL_MUL_13		1011
#define RCC_PLL_MUL_14		1100
#define RCC_PLL_MUL_15		1101
#define RCC_PLL_MUL_16		1111

#define RCC_PLL_HSE_DIV_NO		0
#define RCC_PLL_HSE_DIV_2		1

#define RCC_PLL_SRC_HSI_DIV_2   0
#define RCC_PLL_SRC_HSE		    1
//end

/*
 typedef enum{

 RCC_Peripherals_AHB_START_OFFSET,

 RCC_Peripherals_AHB_DMA1,
 RCC_Peripherals_AHB_DMA2,
 RCC_Peripherals_AHB_SRAM,
 RCC_Peripherals_AHB_res3,
 RCC_Peripherals_AHB_FSMC,
 RCC_Peripherals_AHB_USB_OTG_FS,
 RCC_Peripherals_AHB_Ethernet,
 RCC_Peripherals_AHB_CRC,
 RCC_Peripherals_AHB_Flash_memory_interface,
 //RCC_Peripherals_AHB_reset_and_clock_control_RCC,
 RCC_Peripherals_AHB_SDIO,

 RCC_Peripherals_AHB_END_OFFSET,

 RCC_Peripherals_APB2_START_OFFSET,

 RCC_Peripherals_APB2_TIM11,
 RCC_Peripherals_APB2_TIM10,
 RCC_Peripherals_APB2_TIM9,
 RCC_Peripherals_APB2_ADC3,
 RCC_Peripherals_APB2_USART1,
 RCC_Peripherals_APB2_TIM8,
 RCC_Peripherals_APB2_SPI1,
 RCC_Peripherals_APB2_TIM1,
 RCC_Peripherals_APB2_ADC2,
 RCC_Peripherals_APB2_GPIO_Port_G,
 RCC_Peripherals_APB2_GPIO_Port_F,
 RCC_Peripherals_APB2_GPIO_Port_E,
 RCC_Peripherals_APB2_GPIO_Port_D,
 RCC_Peripherals_APB2_GPIO_Port_C,
 RCC_Peripherals_APB2_GPIO_Port_B,
 RCC_Peripherals_APB2_GPIO_Port_A,
 RCC_Peripherals_APB2_EXTI,
 RCC_Peripherals_APB2_AFIO,

 RCC_Peripherals_APB2_END_OFFSET,

 RCC_Peripherals_APB1_START_OFFSET,

 RCC_Peripherals_APB1_DAC,
 RCC_Peripherals_APB1_Power_control_PWR,
 RCC_Peripherals_APB1_Backup_registers_BKP,
 RCC_Peripherals_APB1_bxCAN1,
 RCC_Peripherals_APB1_bxCAN2,
 RCC_Peripherals_APB1_SharedUSB_CAN_SRAM_512_bytes,
 RCC_Peripherals_APB1_USB_device_FS_registers,
 RCC_Peripherals_APB1_I2C2,
 RCC_Peripherals_APB1_I2C1,
 RCC_Peripherals_APB1_UART5,
 RCC_Peripherals_APB1_UART4,
 RCC_Peripherals_APB1_USART3,
 RCC_Peripherals_APB1_USART2,
 RCC_Peripherals_APB1_SPI3_I2S,
 RCC_Peripherals_APB1_SPI2_I2S,
 RCC_Peripherals_APB1_Independent_watchdog_IWDG,
 RCC_Peripherals_APB1_Window_watchdog_WWDG,
 RCC_Peripherals_APB1_TIM14,
 RCC_Peripherals_APB1_TIM13,
 RCC_Peripherals_APB1_TIM12,
 RCC_Peripherals_APB1_TIM7,
 RCC_Peripherals_APB1_TIM6,
 RCC_Peripherals_APB1_TIM5,
 RCC_Peripherals_APB1_TIM4,
 RCC_Peripherals_APB1_TIM3,
 RCC_Peripherals_APB1_TIM2,

 RCC_Peripherals_APB1_END_OFFSET,

 }RCC_Peripherals;
 */

typedef enum {
	RCC_Peripherals_AHB_START_OFFSET = 1,

	RCC_Peripherals_AHB_DMA1,
	RCC_Peripherals_AHB_DMA2,
	RCC_Peripherals_AHB_SRAM,
	RCC_Peripherals_AHB_res3,
	RCC_Peripherals_AHB_FLITF,
	RCC_Peripherals_AHB_res5,
	RCC_Peripherals_AHB_CRC,
	RCC_Peripherals_AHB_res7,
	RCC_Peripherals_AHB_FSMC,
	RCC_Peripherals_AHB_res9,
	RCC_Peripherals_AHB_SDIO,

	RCC_Peripherals_AHB_END_OFFSET,

	RCC_Peripherals_APB2_START_OFFSET,

	RCC_Peripherals_APB2_AFIO,
	RCC_Peripherals_APB2_res1,
	RCC_Peripherals_APB2_GPIO_Port_A,
	RCC_Peripherals_APB2_GPIO_Port_B,
	RCC_Peripherals_APB2_GPIO_Port_C,
	RCC_Peripherals_APB2_GPIO_Port_D,
	RCC_Peripherals_APB2_GPIO_Port_E,
	RCC_Peripherals_APB2_GPIO_Port_F,
	RCC_Peripherals_APB2_GPIO_Port_G,
	RCC_Peripherals_APB2_ADC1,
	RCC_Peripherals_APB2_ADC2,
	RCC_Peripherals_APB2_TIM1,
	RCC_Peripherals_APB2_SPI1,
	RCC_Peripherals_APB2_TIM8,
	RCC_Peripherals_APB2_USART1,
	RCC_Peripherals_APB2_ADC3,
	RCC_Peripherals_APB2_res16,
	RCC_Peripherals_APB2_res17,
	RCC_Peripherals_APB2_res18,
	RCC_Peripherals_APB2_TIM9,
	RCC_Peripherals_APB2_TIM10,
	RCC_Peripherals_APB2_TIM11,

	RCC_Peripherals_APB2_END_OFFSET,

	RCC_Peripherals_APB1_START_OFFSET,

	RCC_Peripherals_APB1_TIM2,
	RCC_Peripherals_APB1_TIM3,
	RCC_Peripherals_APB1_TIM4,
	RCC_Peripherals_APB1_TIM5,
	RCC_Peripherals_APB1_TIM6,
	RCC_Peripherals_APB1_TIM7,
	RCC_Peripherals_APB1_TIM12,
	RCC_Peripherals_APB1_TIM13,
	RCC_Peripherals_APB1_TIM14,
	RCC_Peripherals_APB1_res9,
	RCC_Peripherals_APB1_res10,
	RCC_Peripherals_APB1_WWDG,
	RCC_Peripherals_APB1_res12,
	RCC_Peripherals_APB1_res13,
	RCC_Peripherals_APB1_SPI2,
	RCC_Peripherals_APB1_SPI3,
	RCC_Peripherals_APB1_res16,
	RCC_Peripherals_APB1_USART2,
	RCC_Peripherals_APB1_USART3,
	RCC_Peripherals_APB1_UART4,
	RCC_Peripherals_APB1_UART5,
	RCC_Peripherals_APB1_I2C1,
	RCC_Peripherals_APB1_I2C2,
	RCC_Peripherals_APB1_USB,
	RCC_Peripherals_APB1_res24,
	RCC_Peripherals_APB1_CAN,
	RCC_Peripherals_APB1_res26,
	RCC_Peripherals_APB1_BKP,
	RCC_Peripherals_APB1_PWR,
	RCC_Peripherals_APB1_DAC,

	RCC_Peripherals_APB1_END_OFFSET,

} RCC_Peripherals;

/*
 * Args: void
 * desc: init RCC with config file
 * */
void RCC_voidInit(void);

/*
 * Args: RCC_Peripherals -> enum vaalue
 * desc: to connect the clk for Peripheral before enable
 * */
void RCC_voidPeripheralClockEnable(RCC_Peripherals Copy_enumPeripheralName);

/*
 * Args: RCC_Peripherals -> enum vaalue
 * desc: disable clk to disable Peripheral
 * */
void RCC_voidPeripheralClockDisable(RCC_Peripherals Copy_enumPeripheralName);

/// NOTES ///

/*
 * When the peripheral clock is not active, the peripheral register values may not be readable
 * by software and the returned value is always 0x0.
 */

#endif /* RCC_INTERFACE_H_ */
