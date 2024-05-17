/***********************************************************************************************/
/***********************************************************************************************/
/*********************************** Author: Fatema Ahmed **************************************/
/***************************************** Diagnostics *****************************************/
/**************************************** SWC: ISO14229 ****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "ISO14229_Interface.h"
#include "ISO14229_Private.h"
#include "RCC_Interface.h"
#include "STK_Interface.h"
#include "USART_Interface.h"
#include "FMI_Interface.h"
#include "NVIC_Interface.h"

extern ISO14229_DID_t DID_FF22; // Security Access Const

u8 Global_u8RequestBuffer[128];
u8 Global_u8RequestLength;
u8 Global_u8ResponseBuffer[128];
u8 Global_u8ResponseLength;

u8 Global_SecurityAccessSequence;
u8 Global_ExpectedKey[2];
u8 Global_sendKeyAttempts;
u8 Global_u8CurrentSession = 2;
u8 Global_u8CurrentSecurityLevel;

u8 Global_TransferDataSequence;
u8 Global_TransferDataCounter;

static u32 Global_MemoryAddress;
static u32 Global_MemoryLength;

ISO14229_Service_t *Service;
ISO14229_SubFunction_t *SubFunction;
ISO14229_DID_t *DID;

void JumpToUserApp(void)
{
	void( * AppResetHandler)(void);
	u32 MSPValue = 0; // main stack pointer
    u32 ResetAddress = 0;

	// Get the MSP value of the user application
	MSPValue = *((volatile u32 *)(FlashStartAddress ) );

	// assign this value into MSP*/
	__asm volatile("MSR MSP,%0"::"r"(MSPValue));

	// Get the Reset Handler address of the user application
	ResetAddress = *((u32 *)(FlashStartAddress + 4)); // offset by 4 bytes
	AppResetHandler = (void *)ResetAddress;

	// Call the Reset Handler of the use application
	AppResetHandler();
}

void DiagnosticeService(void)
{
    GetRequest(); // Receive Data

	u8 Index = 0;
    for (Index = 0, Service = SupportedServices[Index]; Service != NULL; Service = SupportedServices[++Index])
    {
        if (Global_u8RequestBuffer[0] == Service->SID)
        {
            break;
        }
    }

    if (Service == NULL)
    {
        SendResponse(serviceNotSupported);
        return;
    }

    if ((Service->SecurityLevel != 0) && (Service->SecurityLevel != Global_u8CurrentSecurityLevel))
    {
        SendResponse(securityAccessDenied);
        return;
    }

    if (Service->ifSubFunction)
    {
        if (Global_u8RequestLength < 2)
        {
            SendResponse(subfunctionNotSupported);
            return;
        }

        for (Index = 0, SubFunction = Service->SubFunctions[Index]; SubFunction!= NULL; SubFunction = Service->SubFunctions[++Index])
        {
            if ((Global_u8RequestBuffer[1] & 0x7F) == SubFunction->ID)
            {
                break;
            }
        }
        if (SubFunction == NULL)
        {
            SendResponse(subfunctionNotSupported);
            return;
        }

        if ((SubFunction->SecurityLevel != 0) && (SubFunction->SecurityLevel != Global_u8CurrentSecurityLevel))
        {
            SendResponse(securityAccessDenied);
            return;
        }

        if (SubFunction->SubFunctionHandler == NULL)
        {
            SendResponse(subfunctionNotSupported);
            return;
        }

        SubFunction->SubFunctionHandler ();
    }
    else
    {
        if (Service->ServiceHandler == NULL)
        {
            SendResponse(serviceNotSupported);
            return;
        }

       Service->ServiceHandler();
    }
}

void defaultSession_Handler (void)
{
    if (Global_u8RequestLength != DiagnosticSessionRequestLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }

    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = SubFunction->ID; 

    Global_u8ResponseBuffer[2] = (defaultSessionP2 >> 8) & 0xFF;
    Global_u8ResponseBuffer[3] = (defaultSessionP2 >> 0) & 0xFF;

    Global_u8ResponseBuffer[4] = (defaultSessionP2s >> 8) & 0xFF;
    Global_u8ResponseBuffer[5] = (defaultSessionP2s >> 0) & 0xFF;

    Global_u8ResponseLength = DiagnosticSessionResponseLength; 

    // Change to Default Session
    Global_u8CurrentSession = InDefaultSession;

    // Reset Session Level and sequence
    Global_u8CurrentSecurityLevel = 0;
    Global_TransferDataSequence = 0;
    Global_SecurityAccessSequence = 0;

    SendResponse(0);

    // Jump to Application
    JumpToUserApp();
}

void ProgrammingSession_Handler (void)
{
    if (Global_u8RequestLength != DiagnosticSessionRequestLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }
    
    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = SubFunction->ID; 

    Global_u8ResponseBuffer[2] = (ProgrammingSessionP2 >> 8) & 0xFF;
    Global_u8ResponseBuffer[3] = (ProgrammingSessionP2 >> 0) & 0xFF;

    Global_u8ResponseBuffer[4] = (ProgrammingSessionP2s >> 8) & 0xFF;
    Global_u8ResponseBuffer[5] = (ProgrammingSessionP2s >> 0) & 0xFF;
    
   Global_u8ResponseLength = DiagnosticSessionResponseLength;

    // Change to Programming Session
    Global_u8CurrentSession = InProgrammingSession;

    // Reset Session Level and sequence
    Global_u8CurrentSecurityLevel = 0;
    Global_TransferDataSequence = 0;
    Global_SecurityAccessSequence = 0;

    SendResponse(0);
}

void hardReset_Handler (void)
{ 
    if (Global_u8RequestLength != HardResetRequestLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }
    
    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = SubFunction->ID; 
    Global_u8ResponseLength = HardResetResponseLength;

    SendResponse(0);

    // Reset Action
    SoftwareReset();
}

void requestSeedLevel01_Handler (void)
{
    if (Global_u8RequestLength != requestSeedRequestLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }

    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = SubFunction->ID; 
    Global_u8ResponseLength = requestSeedResponseLength;

    // Get a Random key
    u32 Seed = STK_u32GetRemainingTime ();
    if(Global_u8CurrentSecurityLevel == Level1) // if Already Having Access
        Seed = 0;

    Global_u8ResponseBuffer[2] = (Seed>>0) & 0xFF;
    Global_u8ResponseBuffer[3] = (Seed>>8) & 0xFF;

    if(Global_u8CurrentSecurityLevel != Level1) // if we don't Have Access
    {
        // Key Equation
        u8 SecurityConst = *((u8*)DID_FF22.Address)+1;
        Global_ExpectedKey[0] = Global_u8ResponseBuffer[2] + SecurityConst;
        Global_ExpectedKey[1] = Global_u8ResponseBuffer[3] + SecurityConst;

        Global_SecurityAccessSequence = 1;
        Global_sendKeyAttempts = sendKeyAttemps;
    }

    SendResponse(0);
}

void sendKeyLevel01_Handler (void)
{
    if (Global_SecurityAccessSequence == 0)
    {
        SendResponse(requestSequenceError);
        return;
    }

    if (Global_u8RequestLength != sendKeyRequestLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }
    
    if ((Global_ExpectedKey[0] != Global_u8RequestBuffer[2]) || (Global_ExpectedKey[1] != Global_u8RequestBuffer[3]))
    {
        Global_sendKeyAttempts--;
        if (Global_sendKeyAttempts == 0)
        {
            Global_SecurityAccessSequence = 0;
            SendResponse(exceededNumberOfAttempts);
            return;
        }
        SendResponse(invalidKey);
        return;
    }

    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = SubFunction->ID;
    Global_u8ResponseLength = sendKeyResponseLength;
    
    Global_SecurityAccessSequence = 0;

    // After Having Access change Session level to Level 1
    Global_u8CurrentSecurityLevel = Level1;

    SendResponse(0);
}

void zeroSubFunction_Handler (void)
{ 
    if (Global_u8RequestLength != zeroSubFunctionRequestLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }
    
    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = SubFunction->ID; 
    Global_u8ResponseLength = zeroSubFunctionResponseLength;

    SendResponse(0);
}

void ReadDataByIdentifier_Handler (void)
{
    if (Global_u8RequestLength != ReadDataByIdentifierRequestMinLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }

    u16 DIDnum = 0;
    DIDnum |= Global_u8RequestBuffer[1];
    DIDnum <<= 8;
    DIDnum |= Global_u8RequestBuffer[2];
    
    u8 Index = 0;
    for (Index = 0, DID = DID_List[Index]; DID != NULL; DID = DID_List[++Index])
    {
        if (DIDnum == DID->ID)
        {
            break;
        }
    }

    if ((DID == NULL) || (DID->ReadLength == 0))
    {
        SendResponse(requestOutOfRange);
        return;
    }

    if ((DID->ReadSecurityLevel != 0) && (DID->ReadSecurityLevel != Global_u8CurrentSecurityLevel))
    {
        SendResponse(securityAccessDenied);
        return;
    }

    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = (DID->ID >> 8) & 0xFF;
	Global_u8ResponseBuffer[2] = (DID->ID >> 0) & 0xFF;

    u8* Address = (u8*)DID->Address;
    for (Index = 0; Index != DID->ReadLength; Index++)
	{
        Global_u8ResponseBuffer[ReadDataByIdentifierRequestMinLength + Index] = Address[Index];
    }
	Global_u8ResponseLength = ReadDataByIdentifierRequestMinLength+DID->ReadLength;

    SendResponse(0);
}

void WriteDataByIdentifier_Handler (void)
{
    if (Global_u8RequestLength < WriteDataByIdentifierRequestMinLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }

    u16 DIDnum = 0;
    DIDnum |= Global_u8RequestBuffer[1];
    DIDnum <<= 8;
    DIDnum |= Global_u8RequestBuffer[2];
    
    u8 Index = 0;
    for (Index = 0, DID = DID_List[Index]; DID != NULL; DID = DID_List[++Index])
    {
        if (DIDnum == DID->ID)
            break;
    }

    if ((DID == NULL) || (DID->WriteLength == 0))
    {
        SendResponse(requestOutOfRange);
        return;
    }

    if ((DID->WriteSecurityLevel != 0) && (DID->WriteSecurityLevel != Global_u8CurrentSecurityLevel))
    {
        SendResponse(securityAccessDenied);
        return;
    }

    if ( (Global_u8RequestLength-3) != DID->WriteLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }

    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = (DID->ID >> 8) & 0xFF;
	Global_u8ResponseBuffer[2] = (DID->ID >> 0) & 0xFF;
    Global_u8ResponseLength = WriteDataByIdentifierResponseLength;

    FMI_WriteTypeDef FlashProgram;
	FlashProgram.Parallelism = FMI_PAR_BYTE;
    
    for (Index = 0; Index != DID->WriteLength; Index++)
	{
        /** Address[Index] = Global_u8RequestBuffer[3 + Index]; by Flash **/
        FlashProgram.Data = Global_u8RequestBuffer[WriteDataByIdentifierResponseLength + Index];
		FlashProgram.BaseAddress = DID->Address+Index;
        FMI_voidUnlock();
        u8 Error = FMI_u8FlashWrite(&FlashProgram);
        FMI_voidLock();

        if (Error != 0)
        {
            SendResponse(generalProgrammingFailure);
            return;
        }
    }

    SendResponse(0);
}

void RequestDownload_Handler (void)
{ 
    if (Global_u8RequestLength < RequestDownloadRequestMinLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }

    if ((Global_u8RequestBuffer[1] != dataFormatIdentifier) || (Global_u8RequestBuffer[2] != addressAndLengthFormatIdentifier)) 
    {
        SendResponse(requestOutOfRange);
        return;
    }

    if (Global_u8RequestLength != RequestDownloadRequestExactLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }

    if (Global_TransferDataSequence != 0)
    {
        SendResponse(conditionsNotCorrect);
        return;
    }
    
    Global_MemoryAddress = 0;
    Global_MemoryAddress |= Global_u8RequestBuffer[3];
    Global_MemoryAddress <<= 8;
    Global_MemoryAddress |= Global_u8RequestBuffer[4];
    Global_MemoryAddress <<= 8;
    Global_MemoryAddress |= Global_u8RequestBuffer[5];
    Global_MemoryAddress <<= 8;
    Global_MemoryAddress |= Global_u8RequestBuffer[6];

    Global_MemoryLength = 0;
    Global_MemoryLength |= Global_u8RequestBuffer[7];
    Global_MemoryLength <<= 8;
    Global_MemoryLength |= Global_u8RequestBuffer[8];
    Global_MemoryLength <<= 8;
    Global_MemoryLength |= Global_u8RequestBuffer[9];
    Global_MemoryLength <<= 8;
    Global_MemoryLength |= Global_u8RequestBuffer[10];

    u32 EndAddress = Global_MemoryAddress + Global_MemoryLength;

    if ((Global_MemoryAddress < FlashStartAddress) || (EndAddress > FlashEndAddress) || (Global_MemoryLength % MaxNumOfBlockLength != 0))
    {
        SendResponse(requestOutOfRange);
        return;
    }

    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = lengthFormatIdentifier;
    Global_u8ResponseBuffer[2] = MaxNumOfBlockLength;
    Global_u8ResponseLength = RequestDownloadResponseLength;

    Global_TransferDataSequence = 1;
    Global_TransferDataCounter = 1;

    SendResponse(0);
 }

void TransferData_Handler (void)
{
    if (Global_u8RequestLength < TransferDataRequestMinLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }

    if (Global_TransferDataSequence != 1)
    {
        SendResponse(requestSequenceError);
        return;
    }

    if (Global_u8RequestLength < (MaxNumOfBlockLength + 2)) // MaxNumOfBlockLength + Service + Counter 
    {
        SendResponse(requestOutOfRange);
        return;
    }

    if (Global_TransferDataCounter != Global_u8RequestBuffer[1]) 
    {
        SendResponse(wrongBlockSequenceCounter);
        return;
    }

    FMI_WriteTypeDef FlashProgram;
	FlashProgram.Parallelism = FMI_PAR_BYTE;
    
    u8 Index = 0;
    for (Index = 0; Index < MaxNumOfBlockLength; Index++)
	{
        FlashProgram.Data = Global_u8RequestBuffer[2 + Index];
		FlashProgram.BaseAddress = Global_MemoryAddress + Index;
        FMI_voidUnlock();
        u8 Error = FMI_u8FlashWrite(&FlashProgram);
        FMI_voidLock();

        if (Error != 0)
        {
            SendResponse(generalProgrammingFailure);
            Global_TransferDataSequence = 0;
            return;
        }
    }
    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseBuffer[1] = Global_TransferDataCounter;
    Global_u8ResponseLength = TransferDataResponseLength;

    Global_TransferDataCounter++;
    Global_MemoryAddress += MaxNumOfBlockLength;
    Global_MemoryLength -= MaxNumOfBlockLength;

    if (Global_MemoryLength == 0)
        Global_TransferDataSequence = 2;

    SendResponse(0);
}

void RequestTransferExit_Handler (void)
{
    if (Global_TransferDataSequence != 2)
    {
        SendResponse(requestSequenceError);
        return;
    }

    if (Global_u8RequestLength != TransferExitMinLength)
    {
        SendResponse(incorrectMessageLengthOrInvalidFormat);
        return;
    }
    
    Global_TransferDataSequence = 0;

    Global_u8ResponseBuffer[0] = PositiveResponse(Service->SID);
    Global_u8ResponseLength = TransferExitMinLength;

     SendResponse(0);
}

void GetRequest(void)
{   
    USART_voidReceiveArraySynch (USART1 , &Global_u8RequestLength , 1);
	USART_voidReceiveArraySynch (USART1 , &Global_u8RequestBuffer[0] , Global_u8RequestLength);
}

void SendResponse(u8 u8ErrorCode)
{
    if (u8ErrorCode == 0) // Positive Response
    {
        if (Service->ifSubFunction)
        {
            if ( GET_BIT(Global_u8RequestBuffer[1], SuspressedBit) == 1)
                return;
        }
    }
	else // NRC
	{
		Global_u8ResponseBuffer[0] = 0x7F;
		Global_u8ResponseBuffer[1] = Service->SID;
		Global_u8ResponseBuffer[2] = u8ErrorCode;
		Global_u8ResponseLength = NRCLength;
    }
    
    USART_voidTransmitArraySynch (ISO14229_USARTxNum , &Global_u8ResponseLength , 1);
	USART_voidTransmitArraySynch (ISO14229_USARTxNum , &Global_u8ResponseBuffer[0] , Global_u8ResponseLength);
}
