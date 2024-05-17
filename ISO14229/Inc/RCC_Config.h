/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: RCC *******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef RCC_Config
#define RCC_Config

/************************************************************************/
/* Initialize Clock Security System										*/
/*		1) CSSBit														*/
/*			--> CSS ON		1											*/
/*			--> CSS OFF		0											*/
/************************************************************************/
#define CSSBit	1

/************************************************************************/
/* Initialize HSE Clock Bypass											*/
/*		2) HSEBYPBit													*/
/*			--> Bypass	 		1	 									*/
/*			--> NotBybass		0										*/
/************************************************************************/
#define HSEBYPBit	0

/************************************************************************/
/* Select System Clock			 										*/
/*		3) HSIBit														*/
/* 			--> HSI ON		1											*/
/* 			--> HSI OFF		0											*/
/*		4) HSEBit	 													*/
/* 			--> HSE ON		1											*/
/* 			--> HSE OFF		0											*/
/*		5) PLLBit														*/
/*			--> PLL ON		1											*/
/*			--> PLL OFF		0											*/
/*		6) PLLI2SBit													*/
/*			--> PLLI2S ON		1										*/
/*			--> PLLI2S OFF		0										*/
/************************************************************************/
#define HSIBit		1
#define HSEBit		0
#define	PLLBit		0
#define PLLI2SBit	0

/************************************************************************/
/* Define HPRE: AHB PreScaler											*/
/*       0xxx: system clock not divided	 1								*/
/*       1000: system clock divided by 2								*/
/*       1001: system clock divided by 4								*/
/*       1010: system clock divided by 8								*/
/*       1011: system clock divided by 16								*/
/*       1100: system clock divided by 64								*/
/*       1101: system clock divided by 128								*/
/*       1110: system clock divided by 256								*/
/*       1111: system clock divided by 512								*/
/************************************************************************/
#define AHBPreScaler	1

/********************************************************************************************/
/* Define PPRE1: APB Low speed PreScaler (APB1)												*/
/*  The software has to set these bits correctly not to exceed 42 MHz on this domain		*/
/*       0xx: AHB clock not divided 1														*/
/*		 100: AHB clock divided by 2	                                                    */
/*		 101: AHB clock divided by 4	                                                    */
/*		 110: AHB clock divided by 8	                                                    */
/*		 111: AHB clock divided by 16	                                                    */
/********************************************************************************************/
#define APB1PreScaler	1

/********************************************************************************************/
/* Define PPRE2: APB Low speed PreScaler (APB2)												*/
/*  The software has to set these bits correctly not to exceed 84 MHz on this domain		*/
/*       0xx: AHB clock not divided	1														*/
/*		 100: AHB clock divided by 2	                                                    */
/*		 101: AHB clock divided by 4	                                                    */
/*		 110: AHB clock divided by 8	                                                    */
/*		 111: AHB clock divided by 16	                                                    */
/********************************************************************************************/
#define APB2PreScaler	1

/********************************************************************************************/
/* Define PLLM: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock	*/
/*     These bits can be written only when the PLL and PLLI2S are disabled					*/
/* set these bits to ensure that the VCO input frequency ranges from 1 to 2 MHz				*/
/*		000000: PLLM = 0, wrong configuration											   	*/
/*		000001: PLLM = 1, wrong configuration												*/
/*		000010: PLLM = 2 																	*/
/*		000011: PLLM = 3 																	*/
/*		000100: PLLM = 4 																	*/
/*		...              																	*/
/*		111110: PLLM = 62																	*/
/*		111111: PLLM = 63																	*/
/*																							*/
/* NOTE: Check if there is an Error in Selected Value										*/
/********************************************************************************************/
#define DivisionPLLM		63

/************************************************************************************************/
/* Define PLLN: Multiplication factor for the main PLL (PLL)									*/
/*     These bits can be written only when the PLL is disabled									*/
/* set these bits to ensure that the VCO output frequency is between 192 and 432 MHz			*/
/*		000000: PLLM = 0, wrong configuration													*/
/*		000001: PLLM = 1, wrong configuration													*/
/*		...																						*/
/*		011000000: PLLN = 192																	*/
/*		...																						*/
/*		110110000: PLLN = 432																	*/
/*		110110001: PLLN = 433, wrong configuration												*/
/*		...																						*/
/*		111111111: PLLN = 511, wrong configuration												*/
/*		...																						*/
/*																								*/
/* NOTE: Check if there is an Error in Selected Value											*/
/************************************************************************************************/
#define MultiplicationPLLN	192

/********************************************************************************/
/* Define PLLP: Main PLL (PLL) division factor for main system clock			*/
/*     These bits can be written only if PLL is disabled					    */
/*	set these bits to not exceed 84 MHz on this domain							*/
/*		00: PLLP = 2															*/
/*		01: PLLP = 4															*/
/*		10: PLLP = 6															*/
/*		11: PLLP = 8															*/
/*																				*/
/* NOTE: Check if there is an Error in Selected Value							*/
/********************************************************************************/
#define DivisionPLLP	2

/************************************************************************************************/
/* Define  PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source						*/
/*					0: HSI clock selected as PLL and PLLI2S clock entry							*/
/*					1: HSE oscillator clock selected as PLL and PLLI2S clock entry				*/
/*																								*/
/*			-	IF HSI oscillator clock selected:												*/
/*					Define the input Clock -> 16000000											*/
/*			-	IF HSE oscillator clock selected:												*/
/*					Define the input Clock -> as your system clock								*/
/*																								*/
/* NOTE: Check if there is an Error in Selected Values											*/
/************************************************************************************************/
#define	PLLSource	 0

/************************************************************************************************************************/
/* Define  MCO1PRE: MCO1 PreScaler																						*/
/*					0xx: no division 0																					*/
/*					100: division by 2																					*/
/*					101: division by 3																					*/
/*					110: division by 4																					*/
/*					111: division by 5																					*/
/************************************************************************************************************************/
#define	MCO1PreScaler	 0

/************************************************************************************************************************/
/* Define  MCO2PRE: MCO2 PreScaler																						*/
/*					0xx: no division 0																					*/
/*					100: division by 2																					*/
/*					101: division by 3																					*/
/*					110: division by 4																					*/
/*					111: division by 5																					*/
/************************************************************************************************************************/
#define	MCO2PreScaler	 0

/************************************************************************************************/
/* Define MCO1: MicroController Generate clock output 1											*/
/* configure these bits only after reset before enabling the external oscillators and PLL		*/
/*				00: HSI clock selected						0									*/
/*				01: LSE oscillator selected					1									*/
/*				10: HSE oscillator clock selected			2									*/
/*				11: PLL clock selected						3									*/
/************************************************************************************************/
#define MCO1CLK	0

/************************************************************************************************/
/* Define MCO2: MicroController Generate clock output 2											*/
/* configure these bits only after reset before enabling the external oscillators and PLL		*/
/*				00: System clock (SYSCLK) selected			0									*/
/*				01: PLLI2S clock selected					1									*/
/*				10: HSE oscillator clock selected			2									*/
/*				11: PLL clock selected						3									*/
/************************************************************************************************/
#define MCO2CLK	0

/************************************************************************/
/* Define SW: System clock switch										*/
/*		00: HSI oscillator selected as system clock		0				*/
/*		01: HSE oscillator selected as system clock		1				*/
/*		10: PLL selected as system clock				2				*/
/*		11: not allowed													*/
/************************************************************************/
#define SysClkSw	0

#endif
