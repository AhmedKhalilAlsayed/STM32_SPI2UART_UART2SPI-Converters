/*
 * RCC_config.h
 *
 *  Created on: Aug 2, 2022
 *      Author: Mega Store
 */

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/*
 * Args: {TRUE, FALSE}
 *
 * */
#define RCC_HSE_ON		TRUE
#define RCC_HSI_ON		TRUE
#define RCC_PLL_ON		TRUE
#define RCC_CSS_ON		TRUE
//end

/*
 * Args: {RCC_HSE, RCC_HSI, RCC_PLL, RCC_NO}
 *
 * */

#define RCC_SYSTEM_CLOCK_SWITCH		RCC_HSE
//end

/*
 * Args: {RCC_MCO_SRC_NO, RCC_MCO_SRC_SYSCLK, RCC_MCO_SRC_HSI, RCC_MCO_SRC_HSE, RCC_MCO_SRC_PLL_DIV_2}
 * Note: This clock output may have some truncated cycles at startup or during MCO clock source switching
 * When the System Clock is selected to output to the MCO pin, make sure that this clock does not exceed 50 MHz (the maximum IO speed).
 * */
#define RCC_MCO_SRC					RCC_MCO_SRC_NO
//end

#if RCC_HSI_ON == TRUE
/*
 * Args: if add 1 for 16 your clk will be incremented(+) by 40Khz
 * 		 if sub 1 for 16 your clk will be decremneted(-) by 40Khz
 *
 * */
#define RCC_HSITRIM 	16
//end

#endif

#if RCC_HSE_ON == TRUE

/*
 * Args: {TRUE, FAlSE}
 *
 * */
#define RCC_HSE_BYPASS		FALSE
//end

#endif

#if RCC_PLL_ON == TRUE
/*
 * Args: {RCC_PLL_SRC_HSI_DIV_2, RCC_PLL_SRC_HSE}
 *
 * */

#define RCC_PLL_SRC			RCC_PLL_SRC_HSE
//end

/*
 * Args: {RCC_PLL_HSE_DIV_NO, RCC_PLL_HSE_DIV_2}
 * This bit can be written only when PLL is disabled.
 *
 * */

#define RCC_PLL_HSE_DIV		RCC_PLL_HSE_DIV_NO
//end

/*
 * Args: {RCC_PLL_MUL_2, RCC_PLL_MUL_3 ... RCC_PLL_MUL_16}
 * Caution: The PLL output frequency must not exceed 72 MHz.
 *
 * */

#define RCC_PLL_MUL			RCC_PLL_MUL_2
//end

#endif

/*
 * Args:{RCC_AHB_PRE_NO, RCC_AHB_PRE_2, RCC_AHB_PRE_4 ... RCC_AHB_PRE_512}
 * Note: The prefetch buffer must be kept on when using a prescaler different from 1 on the AHB clock. Refer to Reading the Flash memory section for more details
 * */
#define RCC_AHB_PRESCALER	RCC_AHB_PRE_NO
//end

/*
 * Args:{RCC_APB1_PRE_NO, RCC_APB1_PRE_4 ... RCC_APB1_PRE_16}
 * Note: The prefetch buffer must be kept on when using a prescaler different from 1 on the AHB clock. Refer to Reading the Flash memory section for more details
 * */
#define RCC_APB1_PRESCALER	RCC_APB1_PRE_NO
//end

/*
 * Args:{RCC_APB2_PRE_NO, RCC_APB2_PRE_4 ... RCC_APB2_PRE_16}
 * Note: The prefetch buffer must be kept on when using a prescaler different from 1 on the AHB clock. Refer to Reading the Flash memory section for more details
 * */
#define RCC_APB2_PRESCALER	RCC_APB2_PRE_NO
//end

/*
 * Args:{RCC_ADC_PRE_2, RCC_ADC_PRE_4 ... RCC_ADC_PRE_8}
 * Note: The prefetch buffer must be kept on when using a prescaler different from 1 on the AHB clock. Refer to Reading the Flash memory section for more details
 * */
#define RCC_ADC_PRESCALER	RCC_ADC_PRE_2
//end

#endif /* RCC_CONFIG_H_ */
