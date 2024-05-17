/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: NVIC ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "NVIC_Config.h"
#include "NVIC_Private.h"
#include "NVIC_Register.h"
#include "NVIC_Interface.h"

static u32 u32GLOBAL_PriorityOption;

void SoftwareReset()
{
	SCB->AIRCR =  0x05FA0004;
}

void NVIC_voidEnableInterrupt (u8 u8InterruptID)
{
	NVIC->ISER[u8InterruptID/32] = 1 << u8InterruptID%32;
}
void NVIC_voidDisableInterrupt (u8 u8InterruptID)
{
	NVIC->ICER[u8InterruptID/32] = 1 << u8InterruptID%32;
}

void NVIC_voidSetPendingFlag (u8 u8InterruptID)
{
	NVIC->ISPR[u8InterruptID/32] = 1 << u8InterruptID%32;
}

void NVIC_voidClearPendingFlag (u8 u8InterruptID)
{
	NVIC->ICPR[u8InterruptID/32] = 1 << u8InterruptID%32;
}

u8 NVIC_u8GetActiveFlag (u8 u8InterruptID)
{
	u8 u8Result = 0;
	u8Result = GET_BIT( NVIC->IABR[u8InterruptID/32], u8InterruptID%32 );
	return u8Result;
}

u8 NVIC_u8SetPriority(u8 u8PRIGROUP, s8 s8InterruptVectorPosition, u8 u8GroupPriority, u8 u8SubPriority)
{
	u8 u8ErrorState = 0;
	
	/** Check Ranges **/
	if ( u8PRIGROUP == 0b011 && (u8GroupPriority > 15 || u8SubPriority > 0) )
		u8ErrorState = NVIC_ErrorGroupsORSubsRange;
		
	else if ( u8PRIGROUP == 0b100 && (u8GroupPriority > 7 || u8SubPriority > 1) )
		u8ErrorState = NVIC_ErrorGroupsORSubsRange;
		
	else if ( u8PRIGROUP == 0b101 && (u8GroupPriority > 3 || u8SubPriority > 3) )
		u8ErrorState = NVIC_ErrorGroupsORSubsRange;
		
	else if ( u8PRIGROUP == 0b110 && (u8GroupPriority > 1 || u8SubPriority > 7) )
		u8ErrorState = NVIC_ErrorGroupsORSubsRange;
		
	else if ( u8PRIGROUP == 0b111 && (u8GroupPriority > 0 || u8SubPriority > 15) )
		u8ErrorState = NVIC_ErrorGroupsORSubsRange;
	
	else 
	{
		u32GLOBAL_PriorityOption = 0x05FA0000 | ( u8PRIGROUP << 8);
		SCB->AIRCR = u32GLOBAL_PriorityOption;
		
		u8 Priority = u8SubPriority | ( u8GroupPriority << ((u32GLOBAL_PriorityOption - 0x05FA0300) / 256) );
		
		if (s8InterruptVectorPosition < 0)	// Core Peripheral
		{
			if (s8InterruptVectorPosition == NVIC_MemoryManagementFault || s8InterruptVectorPosition == NVIC_BusFault || s8InterruptVectorPosition == NVIC_UsageFault)
			{
				s8InterruptVectorPosition += 3;
				SCB->SHPR1 = (Priority) << ((8 * s8InterruptVectorPosition) + 4);
			}
			else if (s8InterruptVectorPosition == NVIC_SVCall)
			{
				s8InterruptVectorPosition += 7;
				SCB->SHPR2 = (Priority) << ((8 * s8InterruptVectorPosition) + 4);
			}
			else if (s8InterruptVectorPosition == NVIC_PendSV || s8InterruptVectorPosition == NVIC_SysTick)
			{
				s8InterruptVectorPosition += 8;
				SCB->SHPR3 = (Priority) << ((8 * s8InterruptVectorPosition) + 4);
			}
		}
	
		else if (s8InterruptVectorPosition >= 0)	// External Peripheral
		{
			NVIC->IPR[s8InterruptVectorPosition] = Priority << 4;
		}
	}
	return u8ErrorState;
}
