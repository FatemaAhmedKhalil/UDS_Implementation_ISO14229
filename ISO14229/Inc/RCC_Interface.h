/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: RCC *******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef RCC_Interface
#define RCC_Interface

/************ Error States ************/
#define RCC_ErrorPeripheralRangeRCC	1
#define RCC_ErrorBusRangeRCC		2
#define RCC_ErrorConfigPLLRCC		3

/********************************************************************************************************************
* @fn             : RCC_u8SystemClkInitialization
* @brief          : System RCC Clock Initialization
* @param[in]      :
* @retval         :
**********************************************************************************************************************
* @attention
* Configurations at RCC_Config.h
*
**********************************************************************************************************************/
void RCC_u8SystemClkInitialization (void);

/****************************************************/
/* Define											*/
/*		1) RCC Bus									*/
/* 				- AHB1								*/
/* 				- AHB2								*/
/* 				- APB1								*/
/* 				- APB2								*/
/****************************************************/
#define	RCC_AHB1		1
#define	RCC_AHB2		2
#define	RCC_APB1		3
#define	RCC_APB2		4
#define RCC_AHB1LPENR	5

/************************************************************************************/
/* Define RCC Peripheral															*/
/*		1) RCC AHB1 peripheral clock enable\disable register						*/
/*			  *** PORTS Enable\Disable ***											*/
/* 				GPIOA --> Perphiral = 0												*/
/* 				GPIOB --> Perphiral = 1												*/
/* 				GPIOC --> Perphiral = 2												*/
/*				CRC	  --> Perphiral = 12											*/
/*																					*/
/*		2) RCC AHB2 peripheral clock enable\disable register						*/
/* 				OTGFS --> Perphiral = 7												*/
/*																					*/
/*		3) RCC APB1 peripheral clock enable\disable register						*/
/* 				TIM2 --> Perphiral = 0												*/
/* 				TIM3 --> Perphiral = 1												*/
/* 				TIM4 --> Perphiral = 2												*/
/* 				TIM5 --> Perphiral = 3												*/
/* 				WWDG --> Perphiral = 11												*/
/* 				SPI2 --> Perphiral = 14												*/
/* 				SPI3 --> Perphiral = 15												*/
/* 				USART2 --> Perphiral = 17											*/
/* 				I2C1 --> Perphiral = 21												*/
/* 				I2C2 --> Perphiral = 22												*/
/* 				I2C3 --> Perphiral = 23												*/
/* 				PWR --> Perphiral = 28												*/
/*																					*/
/*		4) RCC APB2 peripheral clock enable\disable register						*/
/* 				TIM1 --> Perphiral = 0												*/
/* 				USART1 --> Perphiral = 4											*/
/* 				USART6 --> Perphiral = 5											*/
/* 				ADC1 --> Perphiral = 8												*/
/* 				SDIO --> Perphiral = 11												*/
/* 				SPI1 --> Perphiral = 12												*/
/* 				SPI4 --> Perphiral = 13												*/
/* 				SYSCFG --> Perphiral = 14 (EXTI)									*/
/* 				TIM9 --> Perphiral = 16												*/
/* 				TIM10 --> Perphiral = 17											*/
/* 				TIM11 --> Perphiral = 18											*/
/*		5) RCC AHB1LPENR peripheral clock enable in low power mode register			*/
/*				FLITFLPEN --> Perphiral = 15										*/
//						Flash interface clock enable during Sleep mode				*/
/************************************************************************************/
#define RCC_GPIOA	 	0
#define RCC_GPIOB	 	1
#define RCC_GPIOC	 	2
#define RCC_CRCEN		12

#define RCC_OTGFS		7

#define RCC_TIM2		0
#define RCC_TIM3		1
#define RCC_TIM4		2
#define RCC_TIM5		3
#define RCC_WWDG		11
#define RCC_SPI2		14
#define RCC_SPI3		15
#define RCC_USART2		17
#define RCC_I2C1		21
#define RCC_I2C2		22
#define RCC_I2C3		23
#define RCC_PWR			28

#define RCC_TIM1		0
#define RCC_USART1		4
#define RCC_USART6		5
#define RCC_ADC1		8
#define RCC_SDIO		11
#define RCC_SPI1		12
#define RCC_SPI4		13
#define RCC_SYSCFG		14
#define RCC_TIM9		16
#define RCC_TIM10		17
#define RCC_TIM11		18

#define RCC_FLITFLPEN	15
/********************************************************************************************************************
* @fn             : RCC_u8Enable
* @brief          : Enable Peripheral
* @param[in]      : u8Bus  --> get option from RCC Bus
* @param[in]      : u8Perphiral  --> get option from 'RCC Peripheral' defines
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 RCC_u8Enable (u8 u8Bus, u8 u8Peripheral);

/********************************************************************************************************************
* @fn             : RCC_u8Disable
* @brief          : Disable Peripheral
* @param[in]      : u8Bus  --> get option from RCC Bus
* @param[in]      : u8Perphiral  --> get option from 'RCC Peripheral' defines
* @retval         : Error State
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 RCC_u8Disable (u8 u8Bus, u8 u8Peripheral);

#endif
