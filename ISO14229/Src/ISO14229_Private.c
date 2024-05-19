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

extern u8 Global_u8CurrentSession;
const char Programmer[] = "Fatema STM32F401CCU6";  // Serial Number

ISO14229_DID_t DID_F186 = { // ISO14229 standard for detecting current session
                            .ID = 0xF186,
                            .ReadSecurityLevel = 0,
                            .WriteSecurityLevel = 0,
                            .Address = (u32)&Global_u8CurrentSession,
                            .ReadLength = 1,
                            .WriteLength = 0
};

ISO14229_DID_t DID_FA12 = { // example for display Serial number
                            .ID = 0xFA12,
                            .ReadSecurityLevel = 1,
                            .WriteSecurityLevel = 0,
                            .Address = (u32)&Programmer[0],
                            .ReadLength = 20,
                            .WriteLength = 0
};

ISO14229_DID_t DID_FF22 = {  // Security Constant = Value in Flash @Address  + 1
                            .ID = 0xFF22,
                            .ReadSecurityLevel = 0,
                            .WriteSecurityLevel = 1,
                            .Address = 0x8004000,
                            .ReadLength = 0,
                            .WriteLength = 1
};
