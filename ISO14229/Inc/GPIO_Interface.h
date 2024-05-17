/***********************************************************************************************/
/***********************************************************************************************/
/*********************************** Author: Fatema Ahmed **************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: GPIO ******************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/************* Error States *************/
#define GPIO_ErrorCheckPerphiralRange 4
#define GPIO_ErrorPinsOutPut          5

/********************************************************/
/* Define                                               */
/*    1) For Port A Pins = (0 : 15)                     */
/*    2) For Port B Pins = (1 : 15)                     */
/*    3) For Port C Pins = (13 : 15)                    */
/********************************************************/
#define GPIO_HIGH  1
#define GPIO_LOW   0

#define GPIO_PORTA	1
#define GPIO_PORTB	2
#define GPIO_PORTC	3

#define GPIO_PIN0	0
#define GPIO_PIN1	1
#define GPIO_PIN2	2
#define GPIO_PIN3	3
#define GPIO_PIN4	4
#define GPIO_PIN5	5
#define GPIO_PIN6	6
#define GPIO_PIN7	7
#define GPIO_PIN8	8
#define GPIO_PIN9	9
#define GPIO_PIN10	10
#define GPIO_PIN11	11
#define GPIO_PIN12	12
#define GPIO_PIN13	13
#define GPIO_PIN14	14
#define GPIO_PIN15	15

// GPIO MODER MODES
#define GPIO_MODER_INPUT        0b00
#define GPIO_MODER_OUTPUT       0b01
#define GPIO_MODER_ALTERNATE    0b10
#define GPIO_MODER_ANALOG       0b11

// GPIO OTYPER Modes
#define GPIO_OTYPER_PUSH_PULL   0
#define GPIO_OTYPER_OPEN_DRAIN  1

// GPIO PUPDR Modes
#define GPIO_PUPDR_NO           0b00
#define GPIO_PUPDR_PULLUP       0b01
#define GPIO_PUPDR_PULLDOWN     0b10

// GPIO Speed
#define Low_Speed               00
#define Medium_Speed            01
#define High_Speed              10
#define Very_High_Speed         11

 /********************************************************************************************************************
 * @fn             : GPIO_u8SetPinValue
 * @brief          : Set Pin Value
 * @param[in]      : u8Port  --> get Port number
 * @param[in]      : u8Pin  --> get Pin number
 * @param[in]      : u8Value  --> get Pin Value High or Low
 * @retval         : Error State
 **********************************************************************************************************************
 * @attention
 *
 *
 **********************************************************************************************************************/
u8 GPIO_u8SetPinValue (u8 u8Port, u8 u8Pin, u8 u8Value);

/********************************************************************************************************************
* @fn             : GPIO_u8FastControlPinValue
* @brief          : Set Pin Value by Direct Register Access
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Pin  --> get Pin number
* @param[in]      : u8Value  --> get Pin Value High or Low
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_u8FastControlPinValue (u8 u8Port, u8 u8Pin, u8 u8Status);

/********************************************************************************************************************
* @fn             : GPIO_u8SetPortValue
* @brief          : Set Port Value
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Value  --> get Port Value
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_u8SetPortValue (u8 u8Port, u8 u8Value);

/********************************************************************************************************************
* @fn             : GPIO_u8GetPinValue
* @brief          : Get Pin Value
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Pin  --> get Pin number
* @param[in]      : *pu8Value  --> pointer to variable to store pin Value
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_u8GetPinValue (u8 u8Port, u8 u8Pin, u8* ptru8Value);

/********************************************************************************************************************
* @fn             : GPIO_u8TogglePinValue
* @brief          : Toggle Port Value
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Pin  --> get Pin number
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_u8TogglePinValue(u8 u8Port, u8 u8Pin);

/********************************************************************************************************************
* @fn             : GPIO_u8SetGPIOPinMode
* @brief          : Set Pin Mode
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Pin  --> get Pin number
* @param[in]      : u8Mode  --> get Pin Mode from 'GPIO MODER MODES' defines
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_u8SetGPIOPinMode(u8 u8Port, u8 u8Pin, u8 u8Mode);

/********************************************************************************************************************
* @fn             : GPIO_u8SetOutputPinMode
* @brief          : Set Output Pin Mode
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Pin  --> get Pin number
* @param[in]      : u8Mode  --> get Pin Output Mode from 'GPIO OTYPER Modes' defines
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_u8SetOutputPinMode(u8 u8Port, u8 u8Pin, u8 u8Mode);

/********************************************************************************************************************
* @fn             : GPIO_u8SetPullResMode
* @brief          : Set Registers Mode
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Pin  --> get Pin number
* @param[in]      : u8Mode  --> get Registers Mode from 'GPIO PUPDR Modes' defines
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_u8SetPullResMode(u8 u8Port, u8 u8Pin, u8 u8Mode);

/********************************************************************************************************************
* @fn             : GPIO_u8SetPinOutputSpeed
* @brief          : Set Pin Output Speed
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Pin  --> get Pin number
* @param[in]      : u8Mode  --> get Pin Output Speed from 'GPIO Speed' defines
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_u8SetPinOutputSpeed(u8 u8Port, u8 u8Pin, u8 u8OutputSpeed);

/*********************************************************************/
/*  Select Alternative Function                                      */
/*        SYSTEM: AF0       USART6: AF8                              */
/*    TIM1/TIM2: AF1      I2C2..3: AF9                              */
/*       TIM3..5: AF2       OTG_FS: AF10                             */
/*      TIM9..11: AF3             : AF11                             */
/*       I2C1..3: AF4         SDIO: AF12                             */
/*       SPI1..4: AF5             : AF13                             */
/*          SPI3: AF6             : AF14                             */
/*     USART1..2: AF7     EVENYOUT: AF15                             */
/*********************************************************************/
#define AF0   0b0000
#define AF1   0b0001
#define AF2   0b0010
#define AF3   0b0011
#define AF4   0b0100
#define AF5   0b0101
#define AF6   0b0110
#define AF7   0b0111
#define	AF8   0b1000
#define	AF9   0b1001
#define	AF10  0b1010
#define	AF11  0b1011
#define	AF12  0b1100
#define	AF13  0b1101
#define	AF14  0b1110
#define	AF15  0b1111

/********************************************************************************************************************
* @fn             : GPIO_voidSetAlternativeFunction
* @brief          : Set Pin Alternative Function
* @param[in]      : u8Port  --> get Port number
* @param[in]      : u8Pin  --> get Pin number
* @param[in]      : u8Mode  --> get Pin Alternative Function
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 GPIO_voidSetAlternativeFunction(u8 u8Port, u8 u8Pin, u8 u8AlternateFunction);

#endif
