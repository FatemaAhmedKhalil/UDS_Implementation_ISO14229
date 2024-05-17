#include "STD_Types.h"
#include "BitOperations.h"

#include "RCC_Interface.h"
#include "STK_Interface.h"
#include "ISO14229_Interface.h"
#include "GPIO_Interface.h"
#include "USART_Interface.h"
#include "NVIC_Interface.h"
#include "FMI_Interface.h"

USART_Initialization UART = {
		.BaudRate = 115200,
		.DataWidth = USART_MODE_8BIT,
		.Oversampling = USART_OVER_SAMPLING_16,
		.Parity_Enable = USART_DISABLE,
		.Parity_Selection = USART_EVEN_PARITY,
		.TransferDirection = USART_TX_RX,
		.StopBits = USART_STOP_BIT_1,
		.HardwareFlowControl = USART_DISABLE};

USART_ClockInitialization UARTCLOCK = { USART_DISABLE,
										USART_ClockPolarity_Outside_SteadyLow,
										USART_ClockPhase_FirstTransition,
										USART_LastBitClkPulse_LastDataNotOutput};

int main(void)
{
	/***** RCC Configurations *****/
	RCC_u8SystemClkInitialization();

	RCC_u8Enable(RCC_AHB1, RCC_GPIOA);		// Enable Port A
	RCC_u8Enable (RCC_APB2, RCC_USART1);	// Enable USART1

	/***** Systick Configurations *****/
	STK_voidInitialization ();
	STK_voidSetInterval_Periodic (0x00FFFFFF, NULL);

	/***** USART Configurations *****/
	GPIO_u8SetGPIOPinMode (GPIO_PORTA, GPIO_PIN9, GPIO_MODER_ALTERNATE);
	GPIO_u8SetGPIOPinMode (GPIO_PORTA, GPIO_PIN10, GPIO_MODER_ALTERNATE);
	GPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN9, AF7);
	GPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN10, AF7);

	USART_voidInitialization(&UART, &UARTCLOCK, USART1);
	USART_Enable(USART1);

	while(1)
	{
		DiagnosticeService();  
	}
}
