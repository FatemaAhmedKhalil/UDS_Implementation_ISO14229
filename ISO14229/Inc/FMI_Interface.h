/***********************************************************************************************/
/***********************************************************************************************/
/*********************************** Author: Fatema Ahmed **************************************/
/***************************************** Layer: MCAL *****************************************/
/************************************* SWC: Flash Driver ***************************************/
/**************************************** Version: 1.00 ****************************************/
/*************************************** Date: 5/02/2024 ***************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef FMI_INTERFACE_H_
#define FMI_INTERFACE_H_

/*****  Program size *****/
typedef enum
{
	FMI_PAR_BYTE,
	FMI_PAR_HWORD,
	FMI_PAR_WORD,
	FMI_PAR_DWORD
}FMI_Parallelism;

/******  Sector number ******/
typedef enum
{
	FMI_SECTOR_0,
	FMI_SECTOR_1,
	FMI_SECTOR_2,
	FMI_SECTOR_3,
	FMI_SECTOR_4,
	FMI_SECTOR_5,
	FMI_SECTOR_6,
	FMI_SECTOR_7

}FMI_SectorsSelect;

/******  Flash Erase Type ******/
typedef enum
{
	FMI_SectorErase,
	FMI_MassErase
}FMI_EraseType;

/***** Flash Erase Definition *****/
typedef struct
{
	FMI_EraseType 		EraseType;
	FMI_Parallelism 	Parallelism;
	FMI_SectorsSelect	StartSector;
	FMI_SectorsSelect	EndSector;

}FMI_EraseTypeDef;

/***** Flash Write Definition *****/
typedef struct
{
	u32 BaseAddress;
	FMI_Parallelism Parallelism;
	u32 Data;
}FMI_WriteTypeDef;

/***** Flash Error States *****/
#define FMI_ParallelismError	0xA
#define FMI_WritingError	0xB

 /********************************************************************************************************************
 * @fn             : FIM_voidLock
 * @brief          : Lock Flash Control Register
 * @param[in]      :
 * @retval         :
 **********************************************************************************************************************/
void FMI_voidLock(void);

/********************************************************************************************************************
* @fn             : FIM_voidUnLock
* @brief          : Unlock Flash Control Register
* @param[in]      :
* @retval         :
**********************************************************************************************************************/
void FMI_voidUnlock(void);

/********************************************************************************************************************
* @fn             : FMI_voidLockOTP
* @brief          : Lock Flash Option Key Register
* @param[in]      :
* @retval         :
**********************************************************************************************************************/
void FMI_voidLockOTP(void);

/********************************************************************************************************************
* @fn             : FMI_voidUnlockOTP
* @brief          : unlock Flash Option Key Register
* @param[in]      :
* @retval         :
**********************************************************************************************************************/
void FMI_voidUnlockOTP(void);

/********************************************************************************************************************
* @fn             : FMI_voidErase
* @brief          : Flash Erase Operation
* @param[in]      : FlashErase --> get Struct definition from @FIM_EraseTypeDef
* @retval         :
**********************************************************************************************************************/
void FMI_voidErase(FMI_EraseTypeDef* FlashErase);

/********************************************************************************************************************
* @fn             : FMI_voidFlashWrite
* @brief          : Flash Write Operation
* @param[in]      : FlashErase --> get Struct definition from @FIM_WriteTypeDef
* @retval         : Error State
**********************************************************************************************************************/
u8 FMI_u8FlashWrite(FMI_WriteTypeDef *FlashProgram);

#endif
