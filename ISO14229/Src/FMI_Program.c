/***********************************************************************************************/
/***********************************************************************************************/
/*********************************** Author: Fatema Ahmed **************************************/
/***************************************** Layer: MCAL *****************************************/
/********************************* SWC: Flash Memory Interface *********************************/
/**************************************** Version: 1.00 ****************************************/
/*************************************** Date: 5/02/2024 ***************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "FMI_Interface.h"
#include "FMI_Register.h"
#include "FMI_Private.h"

void FMI_voidLock(void)
{
	FMI->CR |= 1 << LOCK;
}

void FMI_voidUnlock(void)
{
	if (GET_BIT(FMI->CR, LOCK) == 1)
	{
		FMI->KEYR = FPECKEY1 ;
		FMI->KEYR = FPECKEY2 ;
	}
}

void FMI_voidLockOTP(void)
{
	FMI->OPTCR |= 1;
}

void FMI_voidUnlockOTP(void)
{
	FMI->OPTKEYR = OPTKEY1;
	FMI->OPTKEYR = OPTKEY2;
}

void FMI_voidErase(FMI_EraseTypeDef* FlashErase)
{
	// Wait for Busy Flag
	while(GET_BIT(FMI->SR, BSY) == 1) {}

	if(FlashErase->EraseType == FMI_SectorErase)
	{
		// Set the parallelism
		FMI->CR &=~((u32)(0b11<<PSIZE)) ;
		FMI->CR |= ((FlashErase->Parallelism)<<PSIZE);

		for(u8 Sector = FlashErase->StartSector; Sector < FlashErase->EndSector; Sector++)
		{
			// Select Sector Number to erase
			FMI->CR &=~((u32)(0b1111 << SNB));
			FMI->CR |= (Sector << SNB);

			// Select Sector Erase operation
			SET_BIT(FMI->CR, SER);

			// Start erase operation
			SET_BIT(FMI->CR, STRT);
		}
	}

	else if(FlashErase->EraseType == FMI_MassErase)
	{
		// Select Mass Erase operation
		SET_BIT(FMI->CR, MER);

		// Start erase operation
		SET_BIT(FMI->CR, STRT);
	}

	// Wait for Busy Flag
	while(GET_BIT(FMI->SR, BSY) == 1) {}

	// Clear EOP flag   */
	SET_BIT(FMI->SR, EOP);

	// DeSelect Erase Operation
	CLR_BIT(FMI->CR, SER);
}

u8 FMI_u8FlashWrite(FMI_WriteTypeDef *FlashProgram)
{
	u8 ErrorState = 0;

	// Wait if Flash is Busy
	while(GET_BIT(FMI->SR, BSY) == 1) {};

	// Set the parallelism
	FMI->CR &=~((u32)(0b11<<PSIZE)) ;
	FMI->CR |= ((FlashProgram->Parallelism)<<PSIZE);

	// Activate Programming Mode
	SET_BIT(FMI->CR, PG);

	// Check the data size according to parallelism
	switch(FlashProgram->Parallelism)
	{
		//Start writing
		case FMI_PAR_BYTE	:
			if (*((volatile u8*)FlashProgram->BaseAddress) != 0xFF)
				ErrorState = FMI_WritingError;
			else
				*((volatile u8*)FlashProgram->BaseAddress) = (u8)FlashProgram->Data;	
		break;

		case FMI_PAR_HWORD 	:
			if (*((volatile u16*)FlashProgram->BaseAddress) != 0xFFFF)
				ErrorState = FMI_WritingError;
			else
				*((volatile u16*)FlashProgram->BaseAddress) = (u16)FlashProgram->Data;
			break;
		case FMI_PAR_WORD 	:
			if (*((volatile u32*)FlashProgram->BaseAddress) != 0xFFFFFFFF)
				ErrorState = FMI_WritingError;
			else
				*((volatile u32*)FlashProgram->BaseAddress) = (u32)FlashProgram->Data;
			break;
		case FMI_PAR_DWORD 	:
			if ( (*((volatile u32*)FlashProgram->BaseAddress) != 0xFFFFFFFF) || (*((volatile u32*)FlashProgram->BaseAddress+4) != 0xFFFFFFFF))
				ErrorState = FMI_WritingError;
			else
			{
				*(u32*)FlashProgram->BaseAddress = (u32*)FlashProgram->Data;
				*(u32*)(FlashProgram->BaseAddress+4) = (u32*)(FlashProgram->Data >> 32);
			}
			break;

		default : ErrorState = FMI_ParallelismError;
	}

	// Wait for Busy Flag
	while(GET_BIT(FMI->SR, BSY) == 1) {}

	// Clear EOP flag
	SET_BIT(FMI->SR, EOP);

	// Deactivate programming mode
	CLR_BIT(FMI->CR, PG);

	return ErrorState;
}
