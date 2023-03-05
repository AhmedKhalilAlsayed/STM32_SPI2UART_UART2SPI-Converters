/*
 * GPIO_program.c
 *
 *  Created on: Aug 4, 2022
 *      Author: Mega Store
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "GPIO_private.h"

void GPIO_voidPortMaskWrite(GPIO_Port_t Copy_enumPort, u16 Copy_u16MaskPins, u16 Copy_u8PinsValue) {
	switch (Copy_enumPort) {
	case GPIO_PortA:
//		GPIO_PORTA_REG->BSRR = (Copy_u16MaskPins << 16) | (Copy_u16MaskPins & Copy_u8PinsValue);
		GPIO_PORTA_REG->BRR = Copy_u16MaskPins & (~Copy_u8PinsValue);
		GPIO_PORTA_REG->BSRR = Copy_u16MaskPins & Copy_u8PinsValue;
		break;
	case GPIO_PortB:
		GPIO_PORTB_REG->BRR = Copy_u16MaskPins & (~Copy_u8PinsValue);
		GPIO_PORTB_REG->BSRR = Copy_u16MaskPins & Copy_u8PinsValue;
		break;
	case GPIO_PortC:
		GPIO_PORTC_REG->BRR = Copy_u16MaskPins & (~Copy_u8PinsValue);
		GPIO_PORTC_REG->BSRR = Copy_u16MaskPins & Copy_u8PinsValue;
		break;
	case GPIO_PortD:
		break;
	case GPIO_PortE:
		break;
	case GPIO_PortF:
		break;
	case GPIO_PortG:
		break;
	}
}

void GPIO_voidSetPinMode(GPIO_Port_Pin_t Copy_enumPortPin,
		GPIO_Pin_Mode_t Copy_enumPinMode) {
	u8 temp_u8Pin = 0;

	if (Copy_enumPortPin < GPIO_Port_Pin_PORTA_END_OFFSET) {
		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTA_START_OFFSET - 1;

		if (Copy_enumPinMode == GPIO_Pin_Mode_Input_Pull_Up) {
			GPIO_PORTA_REG->BSRR = (1 << temp_u8Pin);
		} else if (Copy_enumPinMode == GPIO_Pin_Mode_Input_Pull_Down) {
			GPIO_PORTA_REG->BRR = (1 << temp_u8Pin);
			Copy_enumPinMode = GPIO_Pin_Mode_Input_Pull_Up;
		}

		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTA_PIN7) {
			GPIO_PORTA_REG->CRL &= ~(0b1111 << (4 * temp_u8Pin));
			GPIO_PORTA_REG->CRL |= (Copy_enumPinMode << (4 * temp_u8Pin));
		} else if (Copy_enumPortPin <= GPIO_Port_Pin_PORTA_PIN15) {
			GPIO_PORTA_REG->CRH &= ~(0b1111 << (4 * (temp_u8Pin - 8)));
			GPIO_PORTA_REG->CRH |= (Copy_enumPinMode << (4 * (temp_u8Pin - 8)));
		}

	} else if (Copy_enumPortPin < GPIO_Port_Pin_PORTB_END_OFFSET) {
		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTB_START_OFFSET - 1;

		if (Copy_enumPinMode == GPIO_Pin_Mode_Input_Pull_Up) {
			GPIO_PORTB_REG->BSRR = (1 << temp_u8Pin);
		} else if (Copy_enumPinMode == GPIO_Pin_Mode_Input_Pull_Down) {
			GPIO_PORTB_REG->BRR = (1 << temp_u8Pin);
			Copy_enumPinMode = GPIO_Pin_Mode_Input_Pull_Up;
		}

		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTB_PIN7) {
			GPIO_PORTB_REG->CRL &= ~(0b1111 << (4 * temp_u8Pin));
			GPIO_PORTB_REG->CRL |= (Copy_enumPinMode << (4 * temp_u8Pin));
		} else if (Copy_enumPortPin <= GPIO_Port_Pin_PORTB_PIN15) {
			GPIO_PORTB_REG->CRH &= ~(0b1111 << (4 * (temp_u8Pin - 8)));
			GPIO_PORTB_REG->CRH |= (Copy_enumPinMode << (4 * (temp_u8Pin - 8)));

		}
	} else if (Copy_enumPortPin < GPIO_Port_Pin_PORTC_END_OFFSET) {
		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTC_START_OFFSET - 1;

		if (Copy_enumPinMode == GPIO_Pin_Mode_Input_Pull_Up) {
			GPIO_PORTC_REG->BSRR = (1 << temp_u8Pin);
		} else if (Copy_enumPinMode == GPIO_Pin_Mode_Input_Pull_Down) {
			GPIO_PORTC_REG->BRR = (1 << temp_u8Pin);
			Copy_enumPinMode = GPIO_Pin_Mode_Input_Pull_Up;
		}

		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTC_PIN7) {
			GPIO_PORTC_REG->CRL &= ~(0b1111 << (4 * temp_u8Pin));
			GPIO_PORTC_REG->CRL |= (Copy_enumPinMode << (4 * temp_u8Pin));
		} else if (Copy_enumPortPin <= GPIO_Port_Pin_PORTC_PIN15) {
			GPIO_PORTC_REG->CRH &= ~(0b1111 << (4 * (temp_u8Pin - 8)));
			GPIO_PORTC_REG->CRH |= (Copy_enumPinMode << (4 * (temp_u8Pin - 8)));

		}
	} else {
		// error
	}

}
/*
 void GPIO_voidSetPinValue(GPIO_Port_Pin_t Copy_enumPortPin, u8 Copy_u8PinValue) {
 u8 temp_u8Pin = 0;

 if (Copy_enumPortPin < GPIO_Port_Pin_PORTA_END_OFFSET) {
 temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTA_START_OFFSET - 1;
 if (Copy_u8PinValue) {
 SET_BIT(GPIO_PORTA_REG->BSRR, temp_u8Pin);
 } else {
 SET_BIT(GPIO_PORTA_REG->BRR, temp_u8Pin);
 }
 } else if (Copy_enumPortPin < GPIO_Port_Pin_PORTB_END_OFFSET) {
 temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTB_START_OFFSET - 1;
 if (Copy_u8PinValue) {
 SET_BIT(GPIO_PORTB_REG->BSRR, temp_u8Pin);
 } else {
 SET_BIT(GPIO_PORTB_REG->BRR, temp_u8Pin);
 }
 } else if (Copy_enumPortPin < GPIO_Port_Pin_PORTC_END_OFFSET) {
 temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTC_START_OFFSET - 1;
 if (Copy_u8PinValue) {
 SET_BIT(GPIO_PORTC_REG->BSRR, temp_u8Pin);
 } else {
 SET_BIT(GPIO_PORTC_REG->BRR, temp_u8Pin);
 }
 } else {
 // error from wrong port
 }

 }
 */

void GPIO_voidSetPinValue(GPIO_Port_Pin_t Copy_enumPortPin, u8 Copy_u8PinValue) {
	u8 temp_u8Pin = 0;
	u8 temp_u8PinMode = 0;

	if (Copy_enumPortPin < GPIO_Port_Pin_PORTA_END_OFFSET) {

		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTA_START_OFFSET - 1;

		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTA_PIN7) {
			temp_u8PinMode = (GPIO_PORTA_REG->CRL >> (temp_u8Pin * 4)) & 0b1111;
		} else {
			temp_u8PinMode = (GPIO_PORTA_REG->CRH >> ((temp_u8Pin - 8) * 4))
					& 0b1111;
		}

		if (temp_u8PinMode < GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz) {

			if (Copy_u8PinValue) {
				//SET_BIT(GPIO_PORTA_REG->ODR,temp_u8Pin);
				GPIO_PORTA_REG->BSRR = (1 << temp_u8Pin);
			} else {
//				CLR_BIT(GPIO_PORTA_REG->ODR,temp_u8Pin);
				GPIO_PORTA_REG->BRR = (1 << temp_u8Pin);
			}

		} else {
			//error from pin mode
		}

	} else if (Copy_enumPortPin < GPIO_Port_Pin_PORTB_END_OFFSET) {

		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTB_START_OFFSET - 1;

		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTB_PIN7) {
			temp_u8PinMode = (GPIO_PORTB_REG->CRL >> (temp_u8Pin * 4)) & 0b1111;
		} else {
			temp_u8PinMode = (GPIO_PORTB_REG->CRH >> ((temp_u8Pin - 8) * 4))
					& 0b1111;
		}

		if (temp_u8PinMode < GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz) {

			if (Copy_u8PinValue) {
				GPIO_PORTB_REG->BSRR = (1 << temp_u8Pin);
			} else {
				GPIO_PORTB_REG->BRR = (1 << temp_u8Pin);
			}

		} else {
			//error from pin mode
		}

	} else if (Copy_enumPortPin < GPIO_Port_Pin_PORTC_END_OFFSET) {

		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTC_START_OFFSET - 1;

		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTC_PIN7) {
			temp_u8PinMode = (GPIO_PORTC_REG->CRL >> (temp_u8Pin * 4)) & 0b1111;
		} else {
			temp_u8PinMode = (GPIO_PORTC_REG->CRH >> ((temp_u8Pin - 8) * 4))
					& 0b1111;
		}

		if (temp_u8PinMode < GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz) {

			if (Copy_u8PinValue) {
				GPIO_PORTC_REG->BSRR = (1 << temp_u8Pin);
			} else {
				GPIO_PORTC_REG->BRR = (1 << temp_u8Pin);
			}

		} else {
			//error from pin mode
		}

	} else {
		// error from wrong port
	}

}

u8 GPIO_u8GetPinValue(GPIO_Port_Pin_t Copy_enumPortPin) {
	u8 temp_u8PinValue = 0;
	u8 temp_u8Pin = 0;
//	u8 temp_u8PinMode = 0;

	if (Copy_enumPortPin < GPIO_Port_Pin_PORTA_END_OFFSET) {

		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTA_START_OFFSET - 1;

		/// read pin mode
//		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTA_PIN7) {
//			temp_u8PinMode = (GPIO_PORTA_REG->CRL >> (temp_u8Pin * 4)) & 0b1111;
//		} else {
//			temp_u8PinMode = (GPIO_PORTA_REG->CRH >> ((temp_u8Pin - 8) * 4))
//					& 0b1111;
//		}

//		if (temp_u8PinMode < GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz) {
//			if (temp_u8PinMode % 4) {
//				// output
//				temp_u8PinValue = GET_BIT(GPIO_PORTA_REG->ODR, (temp_u8Pin));
//			} else {
//				// input
//				temp_u8PinValue = GET_BIT(GPIO_PORTA_REG->IDR, (temp_u8Pin));
//			}
//		} else {
//			//error from pin mode
//		}

/// input circuit is connected for this pin so if output circuit pushes HIGH the <IDR> can read
		temp_u8PinValue = GET_BIT(GPIO_PORTA_REG->IDR, (temp_u8Pin));

	} else if (Copy_enumPortPin < GPIO_Port_Pin_PORTB_END_OFFSET) {

		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTB_START_OFFSET - 1;

//		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTB_PIN7) {
//			temp_u8PinMode = (GPIO_PORTB_REG->CRL >> (temp_u8Pin * 4)) & 0b1111;
//		} else {
//			temp_u8PinMode = (GPIO_PORTB_REG->CRH >> ((temp_u8Pin - 8) * 4))
//					& 0b1111;
//		}
//
//		if (temp_u8PinMode < GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz) {
//
//		} else {
//			//error from pin mode
//		}

/// input circuit is connected for this pin so if output circuit pushes HIGH the <IDR> can read
		temp_u8PinValue = GET_BIT(GPIO_PORTB_REG->IDR, (temp_u8Pin));

	} else if (Copy_enumPortPin < GPIO_Port_Pin_PORTC_END_OFFSET) {

		temp_u8Pin = Copy_enumPortPin - GPIO_Port_Pin_PORTC_START_OFFSET - 1;

//		if (Copy_enumPortPin <= GPIO_Port_Pin_PORTC_PIN7) {
//			temp_u8PinMode = (GPIO_PORTC_REG->CRL >> (temp_u8Pin * 4)) & 0b1111;
//		} else {
//			temp_u8PinMode = (GPIO_PORTC_REG->CRH >> ((temp_u8Pin - 8) * 4))
//					& 0b1111;
//		}
//
//		if (temp_u8PinMode < GPIO_Pin_Mode_Al_Output_Push_Pull_10MHz) {
//
//		} else {
//			//error from pin mode
//		}

/// input circuit is connected for this pin so if output circuit pushes HIGH the <IDR> can read
		temp_u8PinValue = GET_BIT(GPIO_PORTC_REG->IDR, (temp_u8Pin));

	} else {
		// error from wrong port
	}

	return temp_u8PinValue;

}
