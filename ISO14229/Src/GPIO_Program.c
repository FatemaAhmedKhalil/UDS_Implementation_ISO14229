/***********************************************************************************************/
/***********************************************************************************************/
/*********************************** Author: Fatema Ahmed **************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: GPIO ******************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "GPIO_Config.h"
#include "GPIO_Private.h"
#include "GPIO_Register.h"
#include "GPIO_Interface.h"

u8 GPIO_u8SetGPIOPinMode(u8 u8Port, u8 u8Pin, u8 u8Mode)
{
	u8 u8ErrorState = 0;
	if ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) // Check Ranges
	{
		u8Pin<<=1; // Multiply by 2
		switch (u8Port)
		{
			case GPIO_PORTA:
				GPIOA->MODER &= (~(0b11<<u8Pin)); // Resets the two Values
				GPIOA->MODER |= u8Mode<<u8Pin;
				break;

			case GPIO_PORTB:
				GPIOB->MODER &= (~(0b11<<u8Pin)); // Resets the two Values
				GPIOB->MODER |= u8Mode<<u8Pin;
				break;
			case GPIO_PORTC:
				GPIOC->MODER &= (~(0b11<<u8Pin)); // Resets the two Values
				GPIOC->MODER |= u8Mode<<u8Pin;
			default:
				u8ErrorState = GPIO_ErrorCheckPerphiralRange;
				break;
		}
	}
	else
		u8ErrorState = GPIO_ErrorCheckPerphiralRange;
	return u8ErrorState;
}

u8 GPIO_u8SetOutputPinMode(u8 u8Port, u8 u8Pin, u8 u8Mode)
{
	u8 u8ErrorState = 0;
	
	if ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) // Check Ranges
	{
		if (u8Mode == GPIO_OTYPER_PUSH_PULL)
		{
			switch (u8Port)
			{
				case GPIO_PORTA: CLR_BIT(GPIOA->OTYPER, u8Pin); break;
				case GPIO_PORTB: CLR_BIT(GPIOB->OTYPER, u8Pin); break;
				case GPIO_PORTC: CLR_BIT(GPIOC->OTYPER, u8Pin); break;
				default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
			}
		}
		
		else if (u8Mode == GPIO_OTYPER_OPEN_DRAIN)
		{
			switch (u8Port)
			{
				case GPIO_PORTA: SET_BIT(GPIOA->OTYPER, u8Pin); break;
				case GPIO_PORTB: SET_BIT(GPIOB->OTYPER, u8Pin); break;
				case GPIO_PORTC: SET_BIT(GPIOC->OTYPER, u8Pin); break;
				default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
			}
		}
		
		else
		u8ErrorState = GPIO_ErrorPinsOutPut;
	}
	
	else
	u8ErrorState = GPIO_ErrorCheckPerphiralRange;
	
	return u8ErrorState;
}

u8 GPIO_u8SetPinValue (u8 u8Port, u8 u8Pin, u8 u8Value)
{
	u8 u8ErrorState = 0;
	
	if ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) // Check Ranges
	{
		if (u8Value == GPIO_LOW)
		{
			switch (u8Port)
			{
				case GPIO_PORTA: CLR_BIT(GPIOA->ODR, u8Pin); break;
				case GPIO_PORTB: CLR_BIT(GPIOB->ODR, u8Pin); break;
				case GPIO_PORTC: CLR_BIT(GPIOC->ODR, u8Pin); break;
				default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
			}
		}
		
		else if (u8Value == GPIO_HIGH)
		{
			switch (u8Port)
			{
				case GPIO_PORTA: SET_BIT(GPIOA->ODR, u8Pin); break;
				case GPIO_PORTB: SET_BIT(GPIOB->ODR, u8Pin); break;
				case GPIO_PORTC: SET_BIT(GPIOC->ODR, u8Pin); break;
				default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
			}
		}
		
		else
		u8ErrorState = GPIO_ErrorPinsOutPut;
	}
	
	else
	u8ErrorState = GPIO_ErrorCheckPerphiralRange;
	
	return u8ErrorState;
}

u8 GPIO_u8FastControlPinValue (u8 u8Port, u8 u8Pin, u8 u8Status)
{
	u8 u8ErrorState = 0;
	
	if ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) // Check Ranges
	{
		if (u8Status == GPIO_LOW)
		{
			switch (u8Port)
			{
				case GPIO_PORTA: GPIOA->BRR = 1 << u8Pin; break;
				case GPIO_PORTB: GPIOB->BRR = 1 << u8Pin; break;
				case GPIO_PORTC: GPIOC->BRR = 1 << u8Pin; break;
				default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
			}
		}
		
		else if (u8Status == GPIO_HIGH)
		{
			switch (u8Port)
			{
				case GPIO_PORTA: GPIOA->BSR = 1 << u8Pin; break;
				case GPIO_PORTB: GPIOB->BSR = 1 << u8Pin; break;
				case GPIO_PORTC: GPIOC->BSR = 1 << u8Pin; break;
				default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
			}
		}
		
		else
		u8ErrorState = GPIO_ErrorPinsOutPut;
	}
	
	else
	u8ErrorState = GPIO_ErrorCheckPerphiralRange;
	
	return u8ErrorState;
}

u8 GPIO_u8SetPortValue (u8 u8Port, u8 u8Value)
{
	u8 u8ErrorState = 0;
	
	switch (u8Port)
	{
		case GPIO_PORTA: GPIOA->ODR = u8Value; break;
		case GPIO_PORTB: GPIOB->ODR = u8Value; break;
		case GPIO_PORTC: GPIOC->ODR = u8Value; break;
		default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
	}
	
	return u8ErrorState;
}

u8 GPIO_u8GetPinValue (u8 u8Port, u8 u8Pin, u8* ptru8Value)
{
	u8 u8ErrorState = 0;
	if ( ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) && ptru8Value != 0 ) // Check Ranges
	{
		switch (u8Port)
		{
			case GPIO_PORTA: *ptru8Value = GET_BIT(GPIOA->IDR, u8Pin); break;
			case GPIO_PORTB: *ptru8Value = GET_BIT(GPIOB->IDR, u8Pin); break;
			case GPIO_PORTC: *ptru8Value = GET_BIT(GPIOC->IDR, u8Pin); break;
			default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
		}
	}
	else
	u8ErrorState = GPIO_ErrorCheckPerphiralRange;
	
	return u8ErrorState;
}

u8 GPIO_u8TogglePinValue(u8 u8Port, u8 u8Pin)
{
	u8 u8ErrorState = 0;
	if ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) // Check Ranges
	{
		switch(u8Port)
		{
			case GPIO_PORTA : TOGGLE_BIT(GPIOA->ODR,u8Pin); break;
			case GPIO_PORTB : TOGGLE_BIT(GPIOB->ODR,u8Pin); break;
			case GPIO_PORTC : TOGGLE_BIT(GPIOC->ODR,u8Pin); break;
			default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
		}
	}
	else
	u8ErrorState = GPIO_ErrorCheckPerphiralRange;

	return u8ErrorState;
}

u8 GPIO_u8SetPullResMode(u8 u8Port, u8 u8Pin, u8 u8Mode)
{
	u8 u8ErrorState = 0;
	if ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) // Check Ranges
	{
		u8Pin<<=1; // Multiply by 2
		switch (u8Port)
		{
			case GPIO_PORTA:
				GPIOA->PUPDR &= (~(0b11<<u8Pin)); // Resets the two Values
				GPIOA->PUPDR |= u8Mode<<u8Pin;
				break;

			case GPIO_PORTB:
				GPIOB->PUPDR &= (~(0b11<<u8Pin)); // Resets the two Values
				GPIOB->PUPDR |= u8Mode<<u8Pin;
				break;
			case GPIO_PORTC:
				GPIOC->PUPDR &= (~(0b11<<u8Pin)); // Resets the two Values
				GPIOC->PUPDR |= u8Mode<<u8Pin;
			default:
				u8ErrorState = GPIO_ErrorCheckPerphiralRange;
				break;
		}
	}
	else
		u8ErrorState = GPIO_ErrorCheckPerphiralRange;
	return u8ErrorState;
}

u8 GPIO_voidSetAlternativeFunction(u8 u8Port, u8 u8Pin, u8 u8AlternateFunction)
{
	u8 u8ErrorState = 0;
	if ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) // Check Ranges
	{
		if (u8Pin < 8)
		{
			switch (u8Port)
			{
				case GPIO_PORTA:
					GPIOA->AFRL &= ~(0b1111<<(u8Pin*4));
					GPIOA->AFRL |= (u8AlternateFunction<<(u8Pin*4));
					break;

				case GPIO_PORTB:
					GPIOB->AFRL &= ~(0b1111<<(u8Pin*4));
					GPIOB->AFRL |= (u8AlternateFunction<<(u8Pin*4));
					break;

				case GPIO_PORTC:
					GPIOC->AFRL &= ~(0b1111<<(u8Pin*4));
					GPIOC->AFRL |= (u8AlternateFunction<<(u8Pin*4));
					break;
				default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
			}
		}

		else if (u8Pin >= 8)
		{
			switch (u8Port)
			{
				case GPIO_PORTA:
					GPIOA->AFRH &= ~(0b1111<<((u8Pin-8)*4));
					GPIOA->AFRH |= (u8AlternateFunction<<(u8Pin-8)*4);
					break;

				case GPIO_PORTB:
					GPIOB->AFRH &= ~(0b1111<<(u8Pin-8)*4);
					GPIOB->AFRH |= (u8AlternateFunction<<(u8Pin-8)*4);
					break;

				case GPIO_PORTC:
					GPIOC->AFRH &= ~(0b1111<<(u8Pin-8)*4);
					GPIOC->AFRH |= (u8AlternateFunction<<(u8Pin-8)*4);
				break;
				default: u8ErrorState = GPIO_ErrorCheckPerphiralRange; break;
			}
		}
	}

	else
		u8ErrorState = GPIO_ErrorCheckPerphiralRange;

	return u8ErrorState;
}

u8 GPIO_u8SetPinOutputSpeed(u8 u8Port, u8 u8Pin, u8 u8OutputSpeed)
{
	u8 u8ErrorState = 0;
	if ( (u8Port == GPIO_PORTA && u8Pin <= GPIO_PIN15 ) || (u8Port == GPIO_PORTB && u8Pin <= GPIO_PIN15 ) || ( u8Port == GPIO_PORTC && ( u8Pin >= GPIO_PIN13 ||  u8Pin <= GPIO_PIN15 ) ) ) // Check Ranges
	{
		switch(u8Port)
		{
			case GPIO_PORTA:
				GPIOA->OSPEEDR &= ~(0b11<<(u8Pin*2));
				GPIOA->OSPEEDR |= (u8OutputSpeed << (u8Pin*2));
				break;

			case GPIO_PORTB:
				GPIOB->OSPEEDR &= ~(0b11<<(u8Pin*2));
				GPIOB->OSPEEDR |= (u8OutputSpeed << (u8Pin*2));
				break;

			case GPIO_PORTC:
				GPIOC->OSPEEDR &= ~(0b11<<(u8Pin*2));
				GPIOC->OSPEEDR |= (u8OutputSpeed << (u8Pin*2));
				break;
		}
	}
	else
		u8ErrorState = GPIO_ErrorCheckPerphiralRange;

	return u8ErrorState;
}
