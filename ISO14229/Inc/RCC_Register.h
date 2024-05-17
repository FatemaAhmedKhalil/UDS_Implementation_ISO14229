/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: RCC *******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef RCC_Register
#define RCC_Register

#define	RCC_BaseAddress	 (u32)(0x40023800)

typedef struct 
{
	u32 CR;				// RCC clock control register
	u32 PLLCFGR;		// RCC PLL configuration register
	u32 CFGR;			// RCC clock configuration register
	u32 CIR ;			// RCC clock interrupt register
	u32 AHB1RSTR;		// RCC AHB1 peripheral reset register
	u32 AHB2RSTR;		// RCC AHB2 peripheral reset register
	u32 Reserved1;
	u32 Reserved2;
	u32 APB1RSTR;		// RCC APB1 peripheral reset register
	u32 APB2RSTR;		// RCC APB2 peripheral reset register
	u32 Reserved3;
	u32 Reserved4;
	u32 AHB1ENR;		// RCC AHB1 peripheral clock enable register
	u32 AHB2ENR;		// RCC AHB2 peripheral clock enable register
	u32 Reserved5;
	u32 Reserved6;
	u32 APB1ENR;        // RCC APB1 peripheral clock enable register
	u32 APB2ENR;        // RCC APB2 peripheral clock enable register
	u32 Reserved7;
	u32 Reserved8;
	u32 AHB1LPENR;		// RCC AHB1 peripheral clock enable in low power mode register
	u32 AHB2LPENR;		// RCC AHB2 peripheral clock enable in low power mode register
	u32 Reserved9;
	u32 Reserved10;
	u32 APB1LPENR;		// RCC APB1 peripheral clock enable in low power mode register
	u32 APB2LPENR;		// RCC APB2 peripheral clock enabled in low power mode register
	u32 Reserved11;
	u32 Reserved12;
	u32 BDCR;			// RCC Backup domain control register
	u32 CSR;			// RCC clock control & status register
	u32 Reserved13;
	u32 Reserved14;
	u32 SSCGR;			// RCC spread spectrum clock generation register
	u32 PLLI2SCFGR;		// RCC PLLI2S configuration register
	u32 DCKCFGR;		// RCC Dedicated Clocks Configuration Register
}RCC_MemoryMap;

#define	RCC			( (volatile RCC_MemoryMap *)(RCC_BaseAddress) )

#endif