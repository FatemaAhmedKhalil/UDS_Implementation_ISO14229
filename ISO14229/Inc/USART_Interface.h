/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/***************************************** SWC: USART ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

typedef struct
{
	volatile u32 SR;	// Status register
	volatile u32 DR;	// Data register
	volatile u32 BRR;	// Baud rate register
	volatile u32 CR1;	// Control register 1
	volatile u32 CR2;	// Control register 2
	volatile u32 CR3;	// Control register 3
	volatile u32 GTPR;	// Guard time and PreScaler register
}USART_MemoryMap;

/****************************************************/
/* Define Which USART you will Use:					*/
/*          -> USART1								*/
/*          -> USART2								*/
/*          -> USART6								*/
/****************************************************/
#define	USART1		( ( USART_MemoryMap *)(0x40011000) )
#define	USART2		( ( USART_MemoryMap *)(0x40014400) )
#define	USART6		( ( USART_MemoryMap *)(0x40011400) )


/******* Error States *******/
#define USART_TimeOut	255

/********************* Initialize USART Configurations *********************/
typedef struct
{
	u32 BaudRate;
	u8 DataWidth;
	u8 StopBits;
	u8 Parity_Enable;
	u8 Parity_Selection;
	u8 TransferDirection; // Only Transmitter Or Only Receiver Or Both
	u8 HardwareFlowControl;
	u8 Oversampling;
}USART_Initialization;

/***************** Initialize USART Clock Configurations *****************/
typedef struct
{
	u8 ClockEnable;
	u8 ClockPolarity;
	u8 ClockPhase;
	u8 LastBitClockPulse;
}USART_ClockInitialization;

/************* Over Sampling *************/
#define USART_OVER_SAMPLING_16	0
#define USART_OVER_SAMPLING_8 	1

/********** Transfer Direction **********/
#define USART_TX_ONLY		0
#define USART_RX_ONLY		1
#define USART_TX_RX			2

/********** Parity Selection **********/
#define USART_EVEN_PARITY         0
#define USART_ODD_PARITY          1

/*********** Data Width ***********/
#define USART_MODE_8BIT			0
#define USART_MODE_9BIT			1

/************* Stop Bit *************/
#define USART_STOP_BIT_1		0
#define USART_STOP_BIT_0_5		1
#define USART_STOP_BIT_2		2
#define USART_STOP_BIT_1_5		3

/******************* Clock Polarity *******************/
#define USART_ClockPolarity_Outside_SteadyLow		0
#define USART_ClockPolarity_Outside_SteadyHigh		1

/******************* Clock Phase *******************/
#define USART_ClockPhase_FirstTransition	0
#define USART_ClockPhase_SecondTransition	1

/**************** Last Bit Clock Pulse ****************/
#define USART_LastBitClkPulse_LastDataNotOutput		0
#define USART_LastBitClkPulse_LastDataIsOutput		1

/************* Party or Clock En/Dis able *************/
#define USART_ENABLE		1
#define USART_DISABLE		0

 /********************************************************************************************************************
 * @fn             : USART_voidInitialization
 * @brief          : initialization of USART Configuration
 * @param[in]      : InitializatioStruct  --> Initialize USART Config Values from @USART_Initialization Struct
 * @param[in]      : ClockInitializatioStruct  --> Initialize Clock options from @USART_ClockInitialization Struct
 * @param[in]      : USARTx  --> get option from USART Registers Memory Map
 * @retval         :
 **********************************************************************************************************************
 * @attention
 *
 *
 **********************************************************************************************************************/
void USART_voidInitialization(USART_Initialization *InitializatioStruct,
								USART_ClockInitialization *ClockInitializatioStruct,
								USART_MemoryMap *USARTx);

/********************************************************************************************************************
* @fn             : USART_Enable
* @brief          : Enable USART Peripheral
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_Enable(USART_MemoryMap *USARTx);

/********************************************************************************************************************
* @fn             : USART_Disable
* @brief          : Disable USART Peripheral
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_Disable(USART_MemoryMap *USARTx);

/********************************************************************************************************************
* @fn             : USART_voidTransmitByte
* @brief          : Transmit one Byte
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @param[in]      : u8Byte  --> get the Byte to Transmit
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_voidTransmitByte (USART_MemoryMap *USARTx, u8 u8Byte);

/********************************************************************************************************************
* @fn             : USART_voidTransmitString
* @brief          : Transmit Strings and Text
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @param[in]      : u8Byte  --> get the String to Transmit
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_voidTransmitString (USART_MemoryMap *USARTx, u8 *ptru8String);

/********************************************************************************************************************
* @fn             : USART_u8TransmitArraySynch
* @brief          : Transmit an Array of Bytes
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @param[in]      : ptru8DataArray  --> get the Array Address to Transmit
* @param[in]      : u32Length  --> get the Length of the Array
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_voidTransmitArraySynch(USART_MemoryMap *USARTx, u8* ptru8DataArray, u32 u32Length);

/********************************************************************************************************************
* @fn             : USART_u8ReceiveByteSynchNonBlocking
* @brief          : Receive one Byte till Time out if there is issues
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @retval         : Receiving Data
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 USART_u8ReceiveByteSynchNonBlocking (USART_MemoryMap *USARTx);

/********************************************************************************************************************
* @fn             : USART_u8ReceiveByteSynchNonBlocking
* @brief          : Receive one Byte by Blocking the system till finish Receiving
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @param[in]      : ptru8Data  --> the Variable Address to Receive Data in
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_voidReceiveByteSynchBlocking (USART_MemoryMap *USARTx, u8 *ptru8Data);

/********************************************************************************************************************
* @fn             : USART_voidReceiveArraySynch
* @brief          : Receive an Array of Bytes
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @param[in]      : ptru8DataArray  --> the Array Address to Receive Data in
* @param[in]      : u8Size  --> the Size of the Received Array
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_voidReceiveArraySynch (USART_MemoryMap *USARTx , u8 *ptru8DataArray , u8 u8Size);

/********************************************************************************************************************
* @fn             : USART_u8CheckReceived
* @brief          : Check success of Receiving
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @retval         : 1 if success, 0 if not
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 USART_u8CheckReceived (USART_MemoryMap *USARTx);

/********************************************************************************************************************
* @fn             : USART_RxInterruptStatus
* @brief          : Interrupt Status
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @param[in]      : u8Status  --> get Enable or Disable Interrupt
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_voidRxInterruptStatus(USART_MemoryMap *USARTx, u8 u8Status);

/********************************************************************************************************************
* @fn             : USART_voidClearFlags
* @brief          : Clear Flags
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @retval         :
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
void USART_voidClearFlags(USART_MemoryMap *USARTx);

/********************************************************************************************************************
* @fn             : USART_u8ReadDataRegister
* @brief          : Read Data Register
* @param[in]      : USARTx  --> get option from USART Registers Memory Map
* @retval         : Receiving Data
**********************************************************************************************************************
* @attention
*
*
**********************************************************************************************************************/
u8 USART_u8ReadDataRegister(USART_MemoryMap *USARTx);

/** ********** Call Back Functions ********** **/
void USART1_voidSetCallBack( void (*pvvUSART1Function) (void) );
void USART2_voidSetCallBack( void (*pvvUSART2Function) (void) );
void USART6_voidSetCallBack( void (*pvvUSART6Function) (void) );


#endif
