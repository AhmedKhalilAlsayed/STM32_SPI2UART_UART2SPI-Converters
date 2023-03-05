/*
 * RCC_program.c
 *
 *  Created on: Aug 2, 2022
 *      Author: Mega Store
 *      Version: 1
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_config.h"
#include "RCC_private.h"

/// finsih the prebuilding config
#ifndef RCC_HSITRIM
#define RCC_HSITRIM		16
#endif

#ifndef RCC_HSE_BYPASS
#define RCC_HSE_BYPASS		FALSE
#endif

#ifndef RCC_PLL_SRC
#define RCC_PLL_SRC			RCC_PLL_SRC_HSE
#endif

#ifndef RCC_PLL_HSE_DIV
#define RCC_PLL_HSE_DIV		RCC_PLL_HSE_DIV_NO
#endif

#ifndef RCC_PLL_MUL
#define RCC_PLL_MUL			RCC_PLL_MUL_NO
#endif
//end

#define RCC_CFGR_CONFIG_VALUE(MCO,USB,PLLMUL,PLLXTPRE,PLLSRC,ADCPRE,PPRE2,PPRE1,HPRE,SW) 			RCC_CFGR_CONFIG_VALUE_HELP(MCO,USB,PLLMUL,PLLXTPRE,PLLSRC,ADCPRE,PPRE2,PPRE1,HPRE,SW)
#define RCC_CFGR_CONFIG_VALUE_HELP(MCO,USB,PLLMUL,PLLXTPRE,PLLSRC,ADCPRE,PPRE2,PPRE1,HPRE,SW)  		0b##00000##MCO##0##USB##PLLMUL##PLLXTPRE##PLLSRC##ADCPRE##PPRE2##PPRE1##HPRE##00##SW

void RCC_voidInit(void) {

	RCC_CR = 0;

#if RCC_HSE_ON == TRUE
	SET_BIT(RCC_CR, 16);
#endif

#if RCC_HSI_ON == TRUE
	SET_BIT(RCC_CR, 0);
#endif

#if RCC_CSS_ON == TRUE
	SET_BIT(RCC_CR, 19);
#endif

	RCC_CR |= RCC_HSITRIM << 3;

	RCC_CFGR = RCC_CFGR_CONFIG_VALUE(RCC_MCO_SRC, 0, RCC_PLL_MUL,
			RCC_PLL_HSE_DIV, RCC_PLL_SRC, RCC_ADC_PRESCALER, RCC_APB2_PRESCALER,
			RCC_APB1_PRESCALER, RCC_AHB_PRESCALER, RCC_SYSTEM_CLOCK_SWITCH);

#if RCC_PLL_ON == TRUE
	SET_BIT(RCC_CR, 24);
#endif

}

void RCC_voidPeripheralClockEnable(RCC_Peripherals Copy_enumPeripheralName) {
	if (Copy_enumPeripheralName > RCC_Peripherals_APB1_START_OFFSET
			&& Copy_enumPeripheralName < RCC_Peripherals_APB1_END_OFFSET) {
		SET_BIT(RCC_APB1ENR,
				(Copy_enumPeripheralName - RCC_Peripherals_APB1_START_OFFSET -1));

	} else if (Copy_enumPeripheralName > RCC_Peripherals_APB2_START_OFFSET
			&& Copy_enumPeripheralName < RCC_Peripherals_APB2_END_OFFSET) {
		SET_BIT(RCC_APB2ENR,
				(Copy_enumPeripheralName - RCC_Peripherals_APB2_START_OFFSET -1));

	} else if (Copy_enumPeripheralName > RCC_Peripherals_AHB_START_OFFSET
			&& Copy_enumPeripheralName < RCC_Peripherals_AHB_END_OFFSET) {
		SET_BIT(RCC_AHBENR,
				(Copy_enumPeripheralName - RCC_Peripherals_AHB_START_OFFSET -1));

	} else {
		// error
	}
}
void RCC_voidPeripheralClockDisable(RCC_Peripherals Copy_enumPeripheralName) {
	if (Copy_enumPeripheralName > RCC_Peripherals_APB1_START_OFFSET
			&& Copy_enumPeripheralName < RCC_Peripherals_APB1_END_OFFSET) {
		CLR_BIT(RCC_APB1ENR,
				(Copy_enumPeripheralName - RCC_Peripherals_APB1_START_OFFSET -1));

	} else if (Copy_enumPeripheralName > RCC_Peripherals_APB2_START_OFFSET
			&& Copy_enumPeripheralName < RCC_Peripherals_APB2_END_OFFSET) {
		CLR_BIT(RCC_APB2ENR,
				(Copy_enumPeripheralName - RCC_Peripherals_APB2_START_OFFSET -1));

	} else if (Copy_enumPeripheralName > RCC_Peripherals_AHB_START_OFFSET
			&& Copy_enumPeripheralName < RCC_Peripherals_AHB_END_OFFSET) {
		CLR_BIT(RCC_AHBENR,
				(Copy_enumPeripheralName - RCC_Peripherals_AHB_START_OFFSET -1));

	} else {
		// error
	}
}
