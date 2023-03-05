/*
 * GPIO_interface.h
 *
 *  Created on: Aug 4, 2022
 *      Author: Mega Store
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

typedef enum {
	GPIO_Port_Pin_PORTA_START_OFFSET = 1,

	GPIO_Port_Pin_PORTA_PIN0,
	GPIO_Port_Pin_PORTA_PIN1,
	GPIO_Port_Pin_PORTA_PIN2,
	GPIO_Port_Pin_PORTA_PIN3,
	GPIO_Port_Pin_PORTA_PIN4,
	GPIO_Port_Pin_PORTA_PIN5,
	GPIO_Port_Pin_PORTA_PIN6,
	GPIO_Port_Pin_PORTA_PIN7,
	GPIO_Port_Pin_PORTA_PIN8,
	GPIO_Port_Pin_PORTA_PIN9,
	GPIO_Port_Pin_PORTA_PIN10,
	GPIO_Port_Pin_PORTA_PIN11,
	GPIO_Port_Pin_PORTA_PIN12,
	GPIO_Port_Pin_PORTA_PIN13,
	GPIO_Port_Pin_PORTA_PIN14,
	GPIO_Port_Pin_PORTA_PIN15,

	GPIO_Port_Pin_PORTA_END_OFFSET,

	GPIO_Port_Pin_PORTB_START_OFFSET,

	GPIO_Port_Pin_PORTB_PIN0,
	GPIO_Port_Pin_PORTB_PIN1,
	GPIO_Port_Pin_PORTB_PIN2,
	GPIO_Port_Pin_PORTB_PIN3,
	GPIO_Port_Pin_PORTB_PIN4,
	GPIO_Port_Pin_PORTB_PIN5,
	GPIO_Port_Pin_PORTB_PIN6,
	GPIO_Port_Pin_PORTB_PIN7,
	GPIO_Port_Pin_PORTB_PIN8,
	GPIO_Port_Pin_PORTB_PIN9,
	GPIO_Port_Pin_PORTB_PIN10,
	GPIO_Port_Pin_PORTB_PIN11,
	GPIO_Port_Pin_PORTB_PIN12,
	GPIO_Port_Pin_PORTB_PIN13,
	GPIO_Port_Pin_PORTB_PIN14,
	GPIO_Port_Pin_PORTB_PIN15,

	GPIO_Port_Pin_PORTB_END_OFFSET,

	GPIO_Port_Pin_PORTC_START_OFFSET,

	GPIO_Port_Pin_PORTC_PIN0,
	GPIO_Port_Pin_PORTC_PIN1,
	GPIO_Port_Pin_PORTC_PIN2,
	GPIO_Port_Pin_PORTC_PIN3,
	GPIO_Port_Pin_PORTC_PIN4,
	GPIO_Port_Pin_PORTC_PIN5,
	GPIO_Port_Pin_PORTC_PIN6,
	GPIO_Port_Pin_PORTC_PIN7,
	GPIO_Port_Pin_PORTC_PIN8,
	GPIO_Port_Pin_PORTC_PIN9,
	GPIO_Port_Pin_PORTC_PIN10,
	GPIO_Port_Pin_PORTC_PIN11,
	GPIO_Port_Pin_PORTC_PIN12,
	GPIO_Port_Pin_PORTC_PIN13,
	GPIO_Port_Pin_PORTC_PIN14,
	GPIO_Port_Pin_PORTC_PIN15,

	GPIO_Port_Pin_PORTC_END_OFFSET,
} GPIO_Port_Pin_t;

typedef enum {
	GPIO_Pin_Mode_Input_Analog,
	GPIO_Pin_Mode_GP_Output_Push_Pull_10MHz,
	GPIO_Pin_Mode_GP_Output_Push_Pull_2MHz,
	GPIO_Pin_Mode_GP_Output_Push_Pull_50MHz,
	GPIO_Pin_Mode_Input_Floating,
	GPIO_Pin_Mode_GP_Output_Open_Drain_10MHz,
	GPIO_Pin_Mode_GP_Output_Open_Drain_2MHz,
	GPIO_Pin_Mode_GP_Output_Open_Drain_50MHz,
	GPIO_Pin_Mode_Input_Pull_Up,
	GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz,
	GPIO_Pin_Mode_Al_Output_Push_Pull_2MHz,
	GPIO_Pin_Mode_Al_Output_Push_Pull_50MHz,
	GPIO_Pin_Mode_Al_Output_Open_Drain_10MHz = 13,
	GPIO_Pin_Mode_Al_Output_Open_Drain_2MHz,
	GPIO_Pin_Mode_Al_Output_Open_Drain_50MHz,
	GPIO_Pin_Mode_Input_Pull_Down
} GPIO_Pin_Mode_t;

typedef enum {
	GPIO_PortA,
	GPIO_PortB,
	GPIO_PortC,
	GPIO_PortD,
	GPIO_PortE,
	GPIO_PortF,
	GPIO_PortG,
} GPIO_Port_t;


void GPIO_voidSetPinMode(GPIO_Port_Pin_t Copy_enumPortPin,
		GPIO_Pin_Mode_t Copy_enumPinMode);

void GPIO_voidPortMaskWrite(GPIO_Port_t Copy_enumPort, u16 Copy_u16MaskPins, u16 Copy_u8PinsValue);

void GPIO_voidSetPinValue(GPIO_Port_Pin_t Copy_enumPortPin, u8 Copy_u8PinValue);

u8 GPIO_u8GetPinValue(GPIO_Port_Pin_t Copy_enumPortPin);

#endif /* GPIO_INTERFACE_H_ */
