/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/***************************************** SWC: USART ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

/**********************************************/
/*     ST Baud Rate Generator Macros          */
/**********************************************/

#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            ((u32)((((u64)(_PCLK_))*25U)/(4U*((u64)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U) + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            ((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

#define UART_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((u32)((((u64)(_PCLK_))*25U)/(2U*((u64)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (UART_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         ((((UART_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U) + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + ((UART DIVFRAQ & 0xF8) << 1) + (UART DIVFRAQ & 0x07U) */
#define UART_BRR_SAMPLING8(_PCLK_, _BAUD_)             ((UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U) + \
                                                        (UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))

/***********************************************************************************************************************************************************************************/

/** SR Register Bits **/
#define PE		0	// Parity error
#define FE		1	// Framing error
#define NE		2	// Noise error flag
#define ORE		3	// Overrun error
#define IDLE	4	// IDLE line detected
#define RXNE	5	// Read data register not empty
#define TC		6	// Transmission complete
#define TXE		7	// Transmit data register empty
#define LBD		8	// LIN break detection flag
#define CTS		9	// CTS flag	


/** CR1 Register Bits **/
#define SBK		0	// Send break	bit
#define RWU		1	// Receiver Wake up	bit
#define RE		2	// Receiver Enable bit
#define TE		3	// Transmitter Enable bit
#define IDLEIE		4	// IDLE interrupt enable bit
#define RXNEIE		5	// RXNEIE interrupt enable bit
#define TCIE		6	// Transmission complete interrupt enable bit
#define TXEIE		7	// TXE interrupt enable bit
#define PEIE		8	// PE interrupt enable bit
#define PS			9	// Parity selection bit
#define PCE			10	// Parity control enable bit
#define WAKE		11	// Wake up method bit
#define M			12	// Word length bit
#define UE			13	// USART enable bit
#define OVER8	    15	// USART Over sampling bit

/** CR2 Register Bits **/
// Address of the USART node bits
#define ADD0		0
#define ADD1		1
#define ADD2		2
#define ADD3		3
	    
#define LBDL		5	// LIN break detection length bit
#define LBDIE		6	// LIN break detection interrupt enable bit
#define LBCL		8	// Last bit clock pulse bit
#define CPHA		9	// Clock phase bit
#define CPOL		10	// Clock polarity bit
#define CLKEN		11	// Clock enable bit
#define STOP		12	// STOP bit start

// STOP bits
#define STOP0	12
#define STOP1	13

#define LINEN	14	// LIN mode enable bit



/** CR3 Register Bits **/
#define CTSIE		10	// CTS interrupt enable bit
#define CTSE		9	// CTS enable bit
#define RTSE		8	// RTS enable bit
#define DMAT		7	// DMA enable transmitter bit
#define DMAR		6	// DMA enable receiver bit
#define SCEN		5	// Smart card mode enable bit
#define NACK		4	// Smart card NACK enable bit
#define HDSEL		3	// Half-duplex selection bit
#define IRLP		2	// IrDA low-power bit
#define IREN		1	// IrDA mode enable bit
#define EIE			0	// Error interrupt enable bit

#endif
