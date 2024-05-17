/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: RCC *******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef RCC_Private
#define RCC_Private

/** CR Register Bits **/
#define	HSION		0	// Internal high-speed clock enable
#define	HSIRDY		1	// Internal high-speed clock ready flag
#define	HSEON		16	// HSE clock enable
#define	HSERDY		17	// HSE clock ready flag
#define	HSEBYP		18	// HSE clock bypass
#define	CSSON		19	// Clock security system enable
#define	PLLON		24	// Main PLL (PLL) enable
#define	PLLRDY		25	// Main PLL (PLL) clock ready flag
#define	PLLI2SON	26	// PLLI2S enable
#define	PLLI2SRDY	27	// PLLI2S clock ready flag

/** PLLCFGR Register Bits **/
#define	PLLP0		16	//  Main PLL(PLL) division factor for main system clock Bit 16
#define	PLLP1		17	//  Main PLL(PLL) division factor for main system clock Bit 17
#define PLLSRC		22	// Main PLL(PLL) and audio PLL (PLLI2S) entry clock source Bit 22

/** CFGR Register Bits **/
#define	SW0		    0	//  System clock switch Bit 0
#define	SW1		    1	//  System clock switch Bit 1
#define	SWS0	    2	//  System clock switch status Bit 0
#define	SWS1	    3	//  System clock switch status Bit 1
#define	HPRE0	    4   //  AHB PreScaler Bit 0
#define	HPRE1	    5   //  AHB PreScaler Bit 1
#define	HPRE2	    6   //  AHB PreScaler Bit 2
#define	HPRE3	    7   //  AHB PreScaler Bit 3
#define PPRE10	    10	//  APB1 PreScaler Bit 0
#define PPRE11	    11	//  APB1 PreScaler Bit 1
#define PPRE12	    12	//  APB1 PreScaler Bit 2
#define PPRE20	    13	//  APB2 PreScaler Bit 0
#define PPRE21	    14	//  APB2 PreScaler Bit 1
#define PPRE22	    15	//  APB2 PreScaler Bit 2
#define MCO10	    21	// MicroController clock output 1 Bit 0
#define MCO11	    22	// MicroController clock output 1 Bit 1
#define I2SSRC	    23	// I2S clock selection
#define MCO1PRE0	24	// MCO1 PreScaler Bit 0
#define MCO1PRE1	25	// MCO1 PreScaler Bit 1
#define MCO1PRE2	26	// MCO1 PreScaler Bit 2
#define MCO2PRE0	27	// MCO2 PreScaler Bit 0
#define MCO2PRE1	28	// MCO2 PreScaler Bit 1
#define MCO2PRE2	29	// MCO2 PreScaler Bit 2
#define MCO20		30	// MicroController clock output 2 Bit 0
#define MCO21		31	// MicroController clock output 2 Bit 1

#endif
