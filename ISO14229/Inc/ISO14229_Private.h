/***********************************************************************************************/
/***********************************************************************************************/
/*********************************** Author: Fatema Ahmed **************************************/
/***************************************** Diagnostics *****************************************/
/**************************************** SWC: ISO14229 ****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef ISO14229_PRIVATE_H_
#define ISO14229_PRIVATE_H_

#include "ISO14229_Interface.h"

/******* Sessions Level *******/
#define Level1              1

/********** Attepms **********/
#define sendKeyAttemps      3

/******************* Length *******************/
#define DiagnosticSessionRequestLength              2
#define sessionParameterRecordLength                4
#define DiagnosticSessionResponseLength             6
#define HardResetRequestLength                      2
#define HardResetResponseLength                     2
#define requestSeedRequestLength                    2
#define requestSeedResponseLength                   4
#define sendKeyRequestLength                        4
#define sendKeyResponseLength                       2
#define zeroSubFunctionRequestLength                2
#define zeroSubFunctionResponseLength               2
#define ReadDataByIdentifierRequestMinLength        3
#define WriteDataByIdentifierRequestMinLength       4
#define WriteDataByIdentifierResponseLength         3
#define RequestDownloadRequestMinLength             5
#define RequestDownloadRequestExactLength           11
#define RequestDownloadResponseLength               3
#define TransferDataRequestMinLength                3
#define TransferDataResponseLength                  2
#define TransferExitMinLength                       1
#define NRCLength                                   3
#define SuspressedBit                               7

#define defaultSessionP2                    0x0032
#define defaultSessionP2s                   0x01F4
#define ProgrammingSessionP2                0x0019
#define ProgrammingSessionP2s               0x01F4
#define dataFormatIdentifier                0x00
#define addressAndLengthFormatIdentifier    0x44

extern ISO14229_SubFunction_t defaultSession;
extern ISO14229_SubFunction_t ProgrammingSession;
extern ISO14229_SubFunction_t hardReset;
extern ISO14229_SubFunction_t requestSeedLevel01;
extern ISO14229_SubFunction_t sendKeyLevel01;
extern ISO14229_SubFunction_t zeroSubFunction;
extern ISO14229_Service_t DiagnosticSessionControlServices;
extern ISO14229_Service_t ECUResetServices;
extern ISO14229_Service_t SecurityAccessServices;
extern ISO14229_Service_t TesterPresentServices;
extern ISO14229_Service_t ReadDataByIdentifierServices;
extern ISO14229_Service_t WriteDataByIdentifierServices;
extern ISO14229_Service_t RequestDownloadServices;
extern ISO14229_Service_t TransferDataServices;
extern ISO14229_Service_t RequestTransferExitServices;

void defaultSession_Handler (void);
void ProgrammingSession_Handler (void);
void hardReset_Handler (void);
void requestSeedLevel01_Handler (void);
void sendKeyLevel01_Handler (void);
void zeroSubFunction_Handler (void);
void ReadDataByIdentifier_Handler (void);
void WriteDataByIdentifier_Handler (void);
void RequestDownload_Handler (void);
void TransferData_Handler (void);
void RequestTransferExit_Handler (void);
void GetRequest(void);
void SendResponse(u8 u8ErrorCode);

#endif