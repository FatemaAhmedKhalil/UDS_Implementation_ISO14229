/***********************************************************************************************/
/***********************************************************************************************/
/*********************************** Author: Fatema Ahmed **************************************/
/***************************************** Diagnostics *****************************************/
/**************************************** SWC: ISO14229 ****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef ISO14229_INTERFACE_H_
#define ISO14229_INTERFACE_H_

/************* Memory Addresses *************/
#define FlashStartAddress     0x08008000
#define FlashEndAddress       0x0807FFFF

/************* Request Transfer Response *************/
#define lengthFormatIdentifier      0x10
#define MaxNumOfBlockLength         4

/************* USART Number *************/
#define ISO14229_USARTxNum		USART1

/************* Current Session *************/
#define InDefaultSession       1
#define InProgrammingSession   2

typedef struct _ISO14229_SubFunction_t 
{
	u8 ID;
    u8 SecurityLevel;
    void  (*SubFunctionHandler)(void);
} const ISO14229_SubFunction_t;

typedef struct _ISO14229_Service_t
{
	u8 SID;
    u8 SecurityLevel;
    void  (*ServiceHandler)(void);
	u8 ifSubFunction;
    ISO14229_SubFunction_t *SubFunctions[];
} const ISO14229_Service_t;

typedef struct _ISO14229_DID_t
{
	u16 ID;
    u8 ReadSecurityLevel;
    u8 WriteSecurityLevel;
    u32 Address;
    u8 ReadLength;
    u8 WriteLength;
} const ISO14229_DID_t;

extern ISO14229_Service_t *SupportedServices[];
extern ISO14229_DID_t *DID_List[];

/******* Services' Sub Function *******/
#define DiagnosticSessionControl_SubFunction    1
#define ECUReset_SubFunction                    1
#define SecurityAccess_SubFunction              1
#define TesterPresent_SubFunction 				1
#define ReadDataByIdentifier_SubFunction 		0
#define WriteDataByIdentifier_SubFunction 		0
#define RequestDownload_SubFunction 			0
#define TransferData_SubFunction 			    0
#define RequestTransfer_SubFunction             0

/******* Positive Responses *******/
#define PositiveResponse(Service)				(Service | 0x40)

/******* Negative Responses *******/
#define serviceNotSupported 					0x11
#define subfunctionNotSupported 				0x12
#define incorrectMessageLengthOrInvalidFormat 	0x13
#define responseTooLong							0x14
#define conditionsNotCorrect					0x22
#define requestSequenceError 					0x24
#define requestOutOfRange						0x31
#define securityAccessDenied 					0x33
#define invalidKey								0x35
#define exceededNumberOfAttempts				0x36
#define requiredTimeDelayNotExpired 			0x37
#define uploadDownloadNotAccepted 				0x70
#define transferDataSuspended					0x71
#define generalProgrammingFailure				0x72
#define wrongBlockSequenceCounter 				0x73
#define voltageTooHigh							0x92
#define voltageTooLow							0x93

/********************************************************************************************************************
* @fn             : Application
* @brief          : Application Excute
* @param[in]      :
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void JumpToUserApp(void);

/********************************************************************************************************************
* @fn             : DiagnosticeService
* @brief          : The client choose to the Diagnostic service
* @param[in]      :
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void DiagnosticeService(void);

#endif
