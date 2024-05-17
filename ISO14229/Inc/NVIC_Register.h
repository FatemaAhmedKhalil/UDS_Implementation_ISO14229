/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: NVIC ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef NVIC_REGISTER_H_
#define NVIC_REGISTER_H_

#define NVIC_BaseAdress			(u32)(0xE000E100)	// NVIC Base Address
typedef struct
{
	volatile u32 ISER[8];		// Interrupt set-enable register
	volatile u32 Reserved1[24];	
	volatile u32 ICER[8];		// Interrupt clear-enable register
	volatile u32 Reserved2[24];	
	volatile u32 ISPR[8];		// Interrupt set-pending register
	volatile u32 Reserved3[24];	
	volatile u32 ICPR[8];		// Interrupt clear-pending register
	volatile u32 Reserved4[24];	
	volatile u32 IABR[8];		// Interrupt active bit register
	volatile u32 Reserved5[56];	
	volatile u8	 IPR[240];		// Interrupt priority register
	volatile u32 Reserved6[400];
	volatile u32 STIR;			// Software trigger interrupt register		
}NVIC_MemoryMap;
#define	NVIC			( (volatile NVIC_MemoryMap *)(NVIC_BaseAdress) )


#define SCB_BaseAdress			(u32)(0xE000ED00)	// SBC Base Address Starting from CPUID Register
typedef struct
{
	u32 CPUID;		// CPUID base register
	u32 ICSR;		// Interrupt control and state register
	u32 VTOR;		// Vector table offset register
	u32 AIRCR;		// -> Application interrupt and reset control register <-
	u32 SCR;		// System control register
	u32	CCR;		// Configuration and control register
	u32 SHPR1;		// -> System handler priority registers 1 <-
	u32 SHPR2;		// -> System handler priority registers 2 <-
	u32 SHPR3;		// -> System handler priority registers 3 <-
	u32 SHCSR;		// System handler control and state register
	u32 CFSR;		// Configurable fault status register (CFSR; UFSR + BFSR + MMFSR)
	u32 HFSR;		// Hard fault status register
	u32 Reserved;
	u32 MMAR;		// Memory management fault address register
	u32 BFAR;		// Bus fault address register
	u32 AFSR;		// Auxiliary fault status register
}SCB_MemoryMap;
#define	SCB			( (volatile SCB_MemoryMap *)(SCB_BaseAdress) )

#endif
