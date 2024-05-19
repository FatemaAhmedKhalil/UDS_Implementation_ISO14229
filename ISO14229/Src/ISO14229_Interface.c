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

#include "ISO14229_Private.h"
#include "ISO14229_Interface.h"

extern u8 Global_u8CurrentSession;
extern const char Programmer[];

/******* Diagnostic Session Control Sub Functions *******/
ISO14229_SubFunction_t defaultSession = {
    .ID = 0x01,
    .SecurityLevel = 0,
    .SubFunctionHandler = defaultSession_Handler
};
ISO14229_SubFunction_t ProgrammingSession = {
    .ID = 0x02,
    .SecurityLevel = 0,
    .SubFunctionHandler = ProgrammingSession_Handler
};

/******* ECU Reset Sub Functions *******/
ISO14229_SubFunction_t hardReset = {
    .ID = 0x01,
    .SecurityLevel = 0,
    .SubFunctionHandler = hardReset_Handler
};

/******* Security Access Sub Functions *******/
ISO14229_SubFunction_t requestSeedLevel01 = {
    .ID = 0x01,
    .SecurityLevel = 0,
    .SubFunctionHandler = requestSeedLevel01_Handler
};
ISO14229_SubFunction_t sendKeyLevel01 = {
    .ID = 0x02,
    .SecurityLevel = 0,
    .SubFunctionHandler = sendKeyLevel01_Handler
};

/******* Tester Present Sub Functions *******/
ISO14229_SubFunction_t zeroSubFunction = {
    .ID = 0x00,
    .SecurityLevel = 0,
    .SubFunctionHandler = zeroSubFunction_Handler
};

/******* Services *******/
ISO14229_Service_t DiagnosticSessionControlServices = {
    .SID = 0x10,
    .SecurityLevel = 0,
    .ServiceHandler = NULL,
    .ifSubFunction = DiagnosticSessionControl_SubFunction,
    .SubFunctions = {&defaultSession, &ProgrammingSession, NULL}
};

ISO14229_Service_t ECUResetServices = {
    .SID = 0x11,
    .SecurityLevel = 0, 
    .ServiceHandler = NULL,
    .ifSubFunction = ECUReset_SubFunction,
    .SubFunctions = {&hardReset, NULL}
};

ISO14229_Service_t SecurityAccessServices = {
    .SID = 0x27,
    .SecurityLevel = 0,
    .ServiceHandler = NULL,
    .ifSubFunction = SecurityAccess_SubFunction,
    .SubFunctions = {&requestSeedLevel01, &sendKeyLevel01, NULL}
};

ISO14229_Service_t TesterPresentServices = {
    .SID = 0x3E,
    .SecurityLevel = 0,
    .ServiceHandler = NULL,
    .ifSubFunction = TesterPresent_SubFunction,
    .SubFunctions = {&zeroSubFunction, NULL}
};

ISO14229_Service_t ReadDataByIdentifierServices = {
    .SID = 0x22,
    .SecurityLevel = 0,
    .ServiceHandler = ReadDataByIdentifier_Handler,
    .ifSubFunction = ReadDataByIdentifier_SubFunction,
    .SubFunctions = {NULL}
};

ISO14229_Service_t WriteDataByIdentifierServices = {
    .SID = 0x2E,
    .SecurityLevel = 0,
    .ServiceHandler = WriteDataByIdentifier_Handler,
    .ifSubFunction = WriteDataByIdentifier_SubFunction,
    .SubFunctions = {NULL}
};

ISO14229_Service_t RequestDownloadServices = {
    .SID = 0x34,
    .SecurityLevel = 1,
    .ServiceHandler = RequestDownload_Handler,
    .ifSubFunction = RequestDownload_SubFunction,
    .SubFunctions = {NULL}
};

ISO14229_Service_t TransferDataServices = {
    .SID = 0x36,
    .SecurityLevel = 1,
    .ServiceHandler = TransferData_Handler,
    .ifSubFunction = TransferData_SubFunction,
    .SubFunctions = {NULL}
};

ISO14229_Service_t RequestTransferExitServices = {
    .SID = 0x37,
    .SecurityLevel = 1,
    .ServiceHandler = RequestTransferExit_Handler,
    .ifSubFunction = RequestTransfer_SubFunction,
    .SubFunctions = {NULL}
};

ISO14229_Service_t *SupportedServices[] = {
                                            &DiagnosticSessionControlServices,
                                            &ECUResetServices,
                                            &SecurityAccessServices,
                                            &TesterPresentServices,
                                            &ReadDataByIdentifierServices,
                                            &WriteDataByIdentifierServices,
                                            &RequestDownloadServices,
                                            &TransferDataServices,
                                            &RequestTransferExitServices,
                                            NULL
};

/*************** DIDs List ***************/
extern ISO14229_DID_t DID_F186; // ISO14229 standard for detecting current session
extern ISO14229_DID_t DID_FA12; // example for display Serial number
extern ISO14229_DID_t DID_FF22; // example for take Security Constant = Value in Flash @Address  + 1

ISO14229_DID_t DID_EBCD = { // example for reading from and writing into flash
                            .ID = 0xEBCD,
                            .ReadSecurityLevel = 0,
                            .WriteSecurityLevel = 0,
                            .Address = 0x8004000,
                            .ReadLength = 4,
                            .WriteLength = 4
};

ISO14229_DID_t *DID_List[] = { 
                                &DID_F186,
                                &DID_FA12,
                                &DID_FF22,
                                &DID_EBCD,
                                NULL
};
