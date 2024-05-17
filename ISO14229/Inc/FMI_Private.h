/***********************************************************************************************/
/***********************************************************************************************/
/*********************************** Author: Fatema Ahmed **************************************/
/***************************************** Layer: MCAL *****************************************/
/********************************* SWC: Flash Memory Interface *********************************/
/**************************************** Version: 1.00 ****************************************/
/*************************************** Date: 5/02/2024 ***************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef FLASHMEMORYINTERFACE_PRIVATE_H_
#define FLASHMEMORYINTERFACE_PRIVATE_H_

#define FPECKEY1	0x45670123
#define FPECKEY2    0xCDEF89AB

#define OPTKEY1		0x08192A3B
#define OPTKEY2		0x4C5D6E7F

/** ACR Register Bits **/
#define LATENCY		0	// Latency 0:3 bits
#define PRFTEN		8	// Pre-fetch enable
#define ICEN		9	// Instruction cache enable
#define DCEN		10	// Data cache enable
#define ICRST		11	// Instruction cache reset
#define DCRST		12	// Data cache reset

/** SR Register Bits **/
#define EOP			0	// End of operation
#define OPERR		1	// Operation error
#define WRPERR		4	// Write protection error
#define PGAERR		5	// Programming alignment error
#define PGPERR		6	// Programming parallelism error
#define PGSERR		7	// Programming sequence error
#define RDERR		8	// Read Protection Error (pcrop)
#define BSY			16	// Busy

/** CR Register Bits **/
#define PG			0	// Programming
#define SER			1	// Sector Erase
#define MER			2	// Mass Erase
#define SNB			3	// Sector number 3:6 bits
#define PSIZE		8	// Program size 8:9 bits
#define STRT		16	// Start
#define EOPIE		24	// End of operation interrupt enable
#define ERRIE		25	// Error interrupt enable
#define LOCK		31	// Lock

/** OPTCR Register Bits **/
#define OPTLOCK		0	// Option lock
#define OPTSTRT		1	// Option start
#define BOR_LEV		2	// BOR reset Level 2:3 bits
#define USER		5	// User option bytes 5:7 bits
#define RDP			8	// Read protect 8:15 bits
#define nWRP1		16	// Not write protect 16:21 bits
#define nWRP2		22	// Not write protect
#define SPRMOD		31	// Selection of Protection Mode of nWPRi bits

#endif
