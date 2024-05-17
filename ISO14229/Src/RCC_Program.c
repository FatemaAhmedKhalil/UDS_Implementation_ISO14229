/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: RCC *******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "RCC_Config.h"
#include "RCC_Private.h"
#include "RCC_Register.h"
#include "RCC_Interface.h"


void RCC_u8SystemClkInitialization (void)
{
	/** Initialize CSS **/
	#if CSSBit == 1
	SET_BIT(RCC->CR, CSSON);
	
	#elif CSSBit == 0
	CLR_BIT(RCC->CR, CSSON);
	
	#else
	#error "Wrong CSS Initialization"
	#endif
	
	/** Initialize HSE Clock Bypass **/
	#if HSEBYPBit == 1
	SET_BIT(RCC->CR, HSEBYP);
	
	#elif HSEBYPBit == 0
	CLR_BIT(RCC->CR, HSEBYP);
	
	#else
	#error "Wrong HSE Bypass Initialization"
	#endif
	
	/** Select System Clock **/
	// HSI
	#if HSIBit == 1
	SET_BIT(RCC->CR, HSION);
	
	#elif HSIBit == 0
	CLR_BIT(RCC->CR, HSION);
	
	#else
	#error "Wrong HSI Initialization"
	#endif
	
	// HSE
	#if HSEBit == 1
	SET_BIT(RCC->CR, HSEON);
	
	#elif HSEBit == 0
	CLR_BIT(RCC->CR, HSEON);
	
	#else
	#error "Wrong HSE Initialization"
	#endif
	
	// PLL
	#if PLLBit == 1
	SET_BIT(RCC->CR, PLLON);
	
	#elif PLLBit == 0
	CLR_BIT(RCC->CR, PLLON);
	
	#else
	#error "Wrong PLL Initialization"
	#endif
	
	// PLLI2S
	#if PLLI2SBit == 1
	SET_BIT(RCC->CR, PLLI2SON);
	
	#elif PLLI2SBit == 0
	CLR_BIT(RCC->CR, PLLI2SON);
	
	#else
	#error "Wrong PLLI2S Initialization"
	#endif
	
	/** Initialize Bus PreScalers **/
	// HPRE
	#if AHBPreScaler == 2
	SET_BIT(RCC->CFGR, HPRE3);
	CLR_BIT(RCC->CFGR, HPRE2);
	CLR_BIT(RCC->CFGR, HPRE1);
	CLR_BIT(RCC->CFGR, HPRE0);
	
	#elif AHBPreScaler == 4
	SET_BIT(RCC->CFGR, HPRE3);
	CLR_BIT(RCC->CFGR, HPRE2);
	CLR_BIT(RCC->CFGR, HPRE1);
	SET_BIT(RCC->CFGR, HPRE0);
	
	#elif AHBPreScaler == 8
	SET_BIT(RCC->CFGR, HPRE3);
	CLR_BIT(RCC->CFGR, HPRE2);
	SET_BIT(RCC->CFGR, HPRE1);
	CLR_BIT(RCC->CFGR, HPRE0);
	
	#elif AHBPreScaler == 16
	SET_BIT(RCC->CFGR, HPRE3);
	CLR_BIT(RCC->CFGR, HPRE2);
	SET_BIT(RCC->CFGR, HPRE1);
	SET_BIT(RCC->CFGR, HPRE0);
	
	#elif AHBPreScaler == 64
	SET_BIT(RCC->CFGR, HPRE3);
	SET_BIT(RCC->CFGR, HPRE2);
	CLR_BIT(RCC->CFGR, HPRE1);
	CLR_BIT(RCC->CFGR, HPRE0);
	
	#elif AHBPreScaler == 128
	SET_BIT(RCC->CFGR, HPRE3);
	SET_BIT(RCC->CFGR, HPRE2);
	CLR_BIT(RCC->CFGR, HPRE1);
	SET_BIT(RCC->CFGR, HPRE0);
	
	#elif AHBPreScaler == 256
	SET_BIT(RCC->CFGR, HPRE3);
	SET_BIT(RCC->CFGR, HPRE2);
	SET_BIT(RCC->CFGR, HPRE1);
	CLR_BIT(RCC->CFGR, HPRE0);
	
	#elif AHBPreScaler == 512
	SET_BIT(RCC->CFGR, HPRE3);
	SET_BIT(RCC->CFGR, HPRE2);
	SET_BIT(RCC->CFGR, HPRE1);
	SET_BIT(RCC->CFGR, HPRE0);
	
	#elif AHBPreScaler == 1 // clock not divided
	CLR_BIT(RCC->CFGR, HPRE3);
	
	#else
	#error "Wrong HPRE Configuration"
	#endif
	
	// PPRE1
	#if APB1PreScaler == 2
	SET_BIT(RCC->CFGR, PPRE12);
	CLR_BIT(RCC->CFGR, PPRE11);
	CLR_BIT(RCC->CFGR, PPRE10);
	
	#elif APB1PreScaler == 4
	SET_BIT(RCC->CFGR, PPRE12);
	CLR_BIT(RCC->CFGR, PPRE11);
	SET_BIT(RCC->CFGR, PPRE10);
	
	#elif APB1PreScaler == 8
	SET_BIT(RCC->CFGR, PPRE12);
	SET_BIT(RCC->CFGR, PPRE11);
	CLR_BIT(RCC->CFGR, PPRE10);
	
	#elif APB1PreScaler == 16
	SET_BIT(RCC->CFGR, PPRE12);
	SET_BIT(RCC->CFGR, PPRE11);
	SET_BIT(RCC->CFGR, PPRE10);
	
	#elif APB1PreScaler == 1 // clock not divided
	CLR_BIT(RCC->CFGR, PPRE12);
	
	#else
	#error "Wrong PPRE1 Configuration"
	#endif
	
	// PPRE2
	#if APB2PreScaler == 2
	SET_BIT(RCC->CFGR, PPRE22);
	CLR_BIT(RCC->CFGR, PPRE21);
	CLR_BIT(RCC->CFGR, PPRE20);
	
	#elif APB2PreScaler == 4
	SET_BIT(RCC->CFGR, PPRE22);
	CLR_BIT(RCC->CFGR, PPRE21);
	SET_BIT(RCC->CFGR, PPRE20);
	
	#elif APB2PreScaler == 8
	SET_BIT(RCC->CFGR, PPRE22);
	SET_BIT(RCC->CFGR, PPRE21);
	CLR_BIT(RCC->CFGR, PPRE20);
	
	#elif APB2PreScaler == 16
	SET_BIT(RCC->CFGR, PPRE22);
	SET_BIT(RCC->CFGR, PPRE21);
	SET_BIT(RCC->CFGR, PPRE20);
	
	#elif APB2PreScaler == 1 // clock not divided
	CLR_BIT(RCC->CFGR, PPRE22);
	
	#else
	#error "Wrong PPRE2 Configuration"
	#endif
		
	/** Initialize PLL Configuration **/
	// PLLM
	RCC->PLLCFGR &= 0b11111111111111111111111111000000; // use bit masking
	
	#if DivisionPLLM < 2
	#error "Wrong PLLM Configuration"
	
	#elif  DivisionPLLM > 63
	#error "Wrong PLLM Configuration"

	#else
	RCC->PLLCFGR |= DivisionPLLM;
	#endif
		
	// PLLN
	RCC->PLLCFGR &= 0b11111111111111111000000000111111; // use bit masking
	
	#if MultiplicationPLLN < 192
	#error "Wrong PLLN Configuration"
	
	#elif MultiplicationPLLN > 432
	#error "Wrong PLLN Configuration"
	
	#else
	RCC->PLLCFGR |= (MultiplicationPLLN << 6); // left shifted by 6 to apply bit masking
	#endif
	
	// PLLP
	#if DivisionPLLP == 2
	CLR_BIT(RCC->PLLCFGR, PLLP0);
	CLR_BIT(RCC->PLLCFGR, PLLP1);
	
	#elif DivisionPLLP == 4
	SET_BIT(RCC->PLLCFGR, PLLP0);
	CLR_BIT(RCC->PLLCFGR, PLLP1);
	
	#elif DivisionPLLP == 6
	CLR_BIT(RCC->PLLCFGR, PLLP0);
	SET_BIT(RCC->PLLCFGR, PLLP1);
	
	#elif DivisionPLLP == 8
	SET_BIT(RCC->PLLCFGR, PLLP0);
	SET_BIT(RCC->PLLCFGR, PLLP1);
	
	#else
	#error "Wrong PLLP Configuration"
	#endif
	
	/** Initialize PLL Clock Source **/
	#if PLLSource == 0
	CLR_BIT(RCC->PLLCFGR, PLLSRC);
	
	#elif PLLSource == 1
	SET_BIT(RCC->PLLCFGR, PLLSRC);
	
	#else
	#error "Wrong PLLSRC Configuration"
	#endif

	/** Initialize MCO1PRE **/
	#if MCO1PreScaler == 0
	CLR_BIT(RCC->CFGR, MCO1PRE2);
	
	#elif MCO1PreScaler == 2
	SET_BIT(RCC->CFGR, MCO1PRE2);
	CLR_BIT(RCC->CFGR, MCO1PRE1);
	CLR_BIT(RCC->CFGR, MCO1PRE0);
	
	#elif MCO1PreScaler == 3
	SET_BIT(RCC->CFGR, MCO1PRE2);
	CLR_BIT(RCC->CFGR, MCO1PRE1);
	SET_BIT(RCC->CFGR, MCO1PRE0);
	
	#elif MCO1PreScaler == 4
	SET_BIT(RCC->CFGR, MCO1PRE2);
	SET_BIT(RCC->CFGR, MCO1PRE1);
	CLR_BIT(RCC->CFGR, MCO1PRE0);
	
	#elif MCO1PreScaler == 5
	SET_BIT(RCC->CFGR, MCO1PRE2);
	SET_BIT(RCC->CFGR, MCO1PRE1);
	SET_BIT(RCC->CFGR, MCO1PRE0);
	
	#else
	#error "Wrong MCO1PRE Configuration"
	#endif
	
	/** Initialize MCO2PRE **/
	#if MCO2PreScaler == 0
	CLR_BIT(RCC->CFGR, MCO2PRE2);
	
	#elif MCO2PreScaler == 2
	SET_BIT(RCC->CFGR, MCO2PRE2);
	CLR_BIT(RCC->CFGR, MCO2PRE1);
	CLR_BIT(RCC->CFGR, MCO2PRE0);
	
	#elif MCO2PreScaler == 3
	SET_BIT(RCC->CFGR, MCO2PRE2);
	CLR_BIT(RCC->CFGR, MCO2PRE1);
	SET_BIT(RCC->CFGR, MCO2PRE0);
	
	#elif MCO2PreScaler == 4
	SET_BIT(RCC->CFGR, MCO2PRE2);
	SET_BIT(RCC->CFGR, MCO2PRE1);
	CLR_BIT(RCC->CFGR, MCO2PRE0);
	
	#elif MCO2PreScaler == 5
	SET_BIT(RCC->CFGR, MCO2PRE2);
	SET_BIT(RCC->CFGR, MCO2PRE1);
	SET_BIT(RCC->CFGR, MCO2PRE0);
	
	#else
	#error "Wrong MCO2PRE Configuration"
	#endif
	
	/** Initialize MCON1 **/
	#if MCO1CLK == 0
	CLR_BIT(RCC->CFGR, MCO10);
	CLR_BIT(RCC->CFGR, MCO11);
	
	#elif MCO1CLK == 1
	SET_BIT(RCC->CFGR, MCO10);
	CLR_BIT(RCC->CFGR, MCO11);
	
	#elif MCO1CLK == 2
	CLR_BIT(RCC->CFGR, MCO10);
	SET_BIT(RCC->CFGR, MCO11);
	
	#elif MCO1CLK == 3
	SET_BIT(RCC->CFGR, MCO10);
	SET_BIT(RCC->CFGR, MCO11);
	
	#else
	#error "Wrong MCON1 Configuration"
	#endif
	
	/** Initialize MCON2 **/
	#if MCO2CLK == 0
	CLR_BIT(RCC->CFGR, MCO20);
	CLR_BIT(RCC->CFGR, MCO21);

	#elif MCO2CLK == 1
	SET_BIT(RCC->CFGR, MCO20);
	CLR_BIT(RCC->CFGR, MCO21);

	#elif MCO2CLK == 2
	CLR_BIT(RCC->CFGR, MCO20);
	SET_BIT(RCC->CFGR, MCO21);

	#elif MCO2CLK == 3
	SET_BIT(RCC->CFGR, MCO20);
	SET_BIT(RCC->CFGR, MCO21);

	#else
	#error "Wrong MCON2 Configuration"
	#endif
	
	/** Enable The Selected Clock **/
	// SW
	#if SysClkSw == 0
	CLR_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);
	
	#elif SysClkSw == 1
	SET_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);
	
	#elif SysClkSw == 2
	CLR_BIT(RCC->CFGR, SW0);
	SET_BIT(RCC->CFGR, SW1);
	
	#else
	#error "Wrong SW Configuration"
	#endif
}

u8 RCC_u8Enable (u8 u8Bus, u8 u8Peripheral)
{
	u8 u8ErrorState = 0;
	
	if(u8Peripheral < 32) // Check Range
	{
		switch (u8Bus)
		{
			case RCC_AHB1: SET_BIT(RCC->AHB1ENR, u8Peripheral); break;
			case RCC_AHB2: SET_BIT(RCC->AHB2ENR, u8Peripheral); break;
			case RCC_APB1: SET_BIT(RCC->APB1ENR, u8Peripheral); break;
			case RCC_APB2: SET_BIT(RCC->APB2ENR, u8Peripheral); break;
			case RCC_AHB1LPENR: SET_BIT(RCC->AHB1LPENR, u8Peripheral); break;
			default: u8ErrorState = RCC_ErrorBusRangeRCC; break;
		}
	}
	
	else
		u8ErrorState = RCC_ErrorPeripheralRangeRCC; // Out of Range
		
	return u8ErrorState;
}
u8 RCC_u8Disable (u8 u8Bus, u8 u8Peripheral)
{
	u8 u8ErrorState = 0;
	
	if(u8Peripheral < 32) // Check Range
	{
		switch (u8Bus)
		{
			case RCC_AHB1: CLR_BIT(RCC->AHB1ENR, u8Peripheral); break;
			case RCC_AHB2: CLR_BIT(RCC->AHB2ENR, u8Peripheral); break;
			case RCC_APB1: CLR_BIT(RCC->APB1ENR, u8Peripheral); break;
			case RCC_APB2: CLR_BIT(RCC->APB2ENR, u8Peripheral); break;
			case RCC_AHB1LPENR: CLR_BIT(RCC->AHB1LPENR, u8Peripheral); break;
			default: u8ErrorState = RCC_ErrorBusRangeRCC; break;
		}
	}
	
	else 
		u8ErrorState = RCC_ErrorPeripheralRangeRCC; // Out of Range
	
	return u8ErrorState;
}
