/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/***************************************** SWC: USART ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "USART_Config.h"
#include "USART_Private.h"
#include "USART_Interface.h"

u8 Global_u8String[20];

// Global Pointer to Function to Hold USART ISR Address
void (*USART_USART1Function)(void) = NULL;
void (*USART_USART2Function)(void) = NULL;
void (*USART_USART6Function)(void) = NULL;

void USART_voidInitialization(USART_Initialization *InitializatioStruct, USART_ClockInitialization *ClockInitializatioStruct, USART_MemoryMap *USARTx)
{

	// set the baud rate
	switch(InitializatioStruct->Oversampling)
	{
		case USART_OVER_SAMPLING_16 : USARTx->BRR = UART_BRR_SAMPLING16(USART_PCLK, InitializatioStruct->BaudRate); break;
		case USART_OVER_SAMPLING_8  : USARTx->BRR = UART_BRR_SAMPLING8(USART_PCLK, InitializatioStruct->BaudRate) ; break;
	}

	USARTx->CR1 = (InitializatioStruct->Oversampling << OVER8)     |
				  (InitializatioStruct->HardwareFlowControl << UE) |
				  (InitializatioStruct->DataWidth << M)            |
				  (InitializatioStruct->Parity_Enable << PCE)      |
				  (InitializatioStruct->Parity_Selection << PS);
	
	switch (InitializatioStruct->TransferDirection)
	{
		case USART_TX_ONLY: SET_BIT(USARTx->CR1, TE); CLR_BIT(USARTx->CR1, RE); break;
		case USART_RX_ONLY: SET_BIT(USARTx->CR1, RE); CLR_BIT(USARTx->CR1, TE); break;
		case USART_TX_RX:   SET_BIT(USARTx->CR1, TE); SET_BIT(USARTx->CR1, RE); break;
	}
	
	USARTx->CR2 = (InitializatioStruct->StopBits << STOP)			   |
				  (ClockInitializatioStruct->ClockEnable << CLKEN)     |
				  (ClockInitializatioStruct->ClockPhase << CPHA)       |
				  (ClockInitializatioStruct->ClockPolarity << CPOL)    |
				  (ClockInitializatioStruct->LastBitClockPulse << LBCL);

	USARTx->SR = 0;
}

void USART_Enable(USART_MemoryMap *USARTx)
{
	SET_BIT(USARTx->CR1, UE);
}

void USART_Disable(USART_MemoryMap *USARTx)
{
	CLR_BIT(USARTx->CR1, UE);
}

void USART_voidTransmitByte (USART_MemoryMap *USARTx, u8 u8Byte)
{
//	while ( GET_BIT(USARTx->SR, TXE) == 0 );
		
	USARTx->DR = u8Byte;
	
	while ( GET_BIT(USARTx->SR, TC) == 0);
	
	CLR_BIT(USARTx->SR, TC);
}

void USART_voidTransmitString (USART_MemoryMap *USARTx, u8 *ptru8String )
{
	u8 Iterator =0;
	
	while (ptru8String[Iterator] != '\0')
	{
		USART_voidTransmitByte(USARTx, ptru8String[Iterator]);
		Iterator++;
	}
}

void USART_voidTransmitArraySynch(USART_MemoryMap *USARTx, u8* ptru8DataArray, u32 u32Length)
{
	if ( ptru8DataArray != NULL )
	{
       for (u8 Counter = 0 ; Counter < u32Length; Counter++)
    	   USART_voidTransmitByte(USARTx, ptru8DataArray[Counter]);
	}
}

u8 USART_u8ReceiveByteSynchNonBlocking ( USART_MemoryMap *USARTx )
{
	u8 Data = 0;
	u32 TimeOut = 0;
	
	while ( ( GET_BIT(USARTx->SR, RXNE) == 0 ) && ( TimeOut < USART_TimeThreshold ) )
		TimeOut++;
	
	if (TimeOut == USART_TimeThreshold)
		Data = USART_TimeOut;
		
	else
		Data = USARTx->DR;
		
	return Data;
}

void USART_voidReceiveByteSynchBlocking (USART_MemoryMap *USARTx, u8 *ptru8Data)
{
	if ( ptru8Data!= NULL )
	{
		while ( ( GET_BIT(USARTx->SR, RXNE) == 0 ) );

		*ptru8Data = USARTx->DR;
	}
}

void USART_voidReceiveArraySynch  (USART_MemoryMap *USARTx , u8 *ptru8DataArray, u8 u8Size)
{
	if ( ptru8DataArray != NULL )
	{
       for (u8 Counter = 0; Counter < u8Size; Counter++)
    	   USART_voidReceiveByteSynchBlocking(USARTx, &ptru8DataArray[Counter]);
	}
}

u8 USART_u8CheckReceived (USART_MemoryMap *USARTx)
{

	if ( ( GET_BIT(USARTx->SR, RXNE) == 1 ) )
		return 1;
	else
		return 0;
}

void USART_voidRxInterruptStatus(USART_MemoryMap *USARTx, u8 u8Status)
{
	switch (u8Status)
	{
		case USART_ENABLE:  SET_BIT(USARTx->CR1, RXNEIE); break;
		case USART_DISABLE: CLR_BIT(USARTx->CR1, RXNEIE); break;
	}
}

void USART_voidClearFlags(USART_MemoryMap *USARTx)
{
	USARTx->SR = 0;
}

u8 USART_u8ReadDataRegister(USART_MemoryMap *USARTx)
{
	return USARTx->DR;
}

void USART1_voidSetCallBack( void (*pvvUSART1Function) (void) )
{
	USART_USART1Function = pvvUSART1Function;
}

void USART2_voidSetCallBack( void (*pvvUSART2Function) (void) )
{
	USART_USART2Function = pvvUSART2Function;
}

void USART6_voidSetCallBack( void (*pvvUSART6Function) (void) )
{
	USART_USART6Function = pvvUSART6Function;
}

/** ISR of USART1 **/
void USART1_IRQHandler(void)
{
	USART1->SR = 0 ;
	USART_USART1Function();
}

/** ISR of USART2 **/
void USART2_IRQHandler(void)
{
	USART2->SR = 0 ;
	USART_USART2Function();
}

/** ISR of USART6 **/
void USART6_IRQHandler(void)
{
	USART6->SR = 0 ;
	USART_USART6Function();
}
