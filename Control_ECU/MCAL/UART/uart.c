/**
 * @file 	uart.c
 * @brief UART Source file.
 *
 * This file contains The Implementation of Functions of the UART module
  *
  * @author [Mohamed Mabrouk]
  * @date [27 FEB 2024]
  *
  * @SWversion 1.0.0
  *
  * @remarks
  *    -Platform         : AVR
  *    -Peripherial      : Atmega32
  */
  /*==================================================================================================================================*/

/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include "uart.h"
#include "../../LIBRARY/common_macros.h"
/* ===================================================================================================
									   Global Variables
   ===================================================================================================*/
#if (RECIEVER_MODE == INTERRUPT_MODE)
volatile uint8 Recieved_Byte;
#endif
volatile uint8 Recieve_Flag = 0 ;
/* ===================================================================================================
									  Function Definition
   ===================================================================================================*/

/**
 *
 * This Function responsible for initialize the UART driver.
 *
 * @param[in]  Config_Ptr Type UART_ConfigType
 * @param[out] none
 * @return none
 */
void UART_init(const UART_ConfigType *Config_Ptr)
{

#if (TRANSMITTER_MODE == INTERRUPT_MODE)
	SET_BIT(UCSRB,TXCIE);
#endif

#if (RECIEVER_MODE == INTERRUPT_MODE)
	SET_BIT(UCSRB,RXCIE);
#endif

/* Setting the Speed Mode */
if (Config_Ptr->SpeedMode == DOUBLE_SPEED)
{
	SET_BIT(UCSRA,U2X);
}
else
{
	CLR_BIT(UCSRA,U2X);
}

/* Setting the Clock Polarity */
if (Config_Ptr->ClockPolarityType == FALLING_XCK_EDGE)
{
	SET_BIT(UCSRC,UCPOL);
}
else
{
	CLR_BIT(UCSRC,UCPOL);
}

/* Choosing the Write in UCSRC Register */
SET_BIT(UCSRC,URSEL);

/* Choosing the Data Bits Size */
UCSRC = (UCSRC & 0xF9) | ((Config_Ptr->DataSizeType)<<1);

/* Choosing the Stop Bit Size */
UCSRC = (UCSRC & 0xF7) | ((Config_Ptr->StopType)<<3);

/* Choosing the Parity Bit Mode */
UCSRC = (UCSRC & 0xCF) | ((Config_Ptr->ParityType)<<4);

/* Enabling the Receiver and Transmitter */
SET_BIT(UCSRB,RXEN);
SET_BIT(UCSRB,TXEN);

/* Setting the Baud Rate */
uint16 Rate = (uint16)((((F_CPU * (Config_Ptr->SpeedMode)) / ((Config_Ptr->BaudRate) * 16UL))) - 1);

CLR_BIT(UCSRC,URSEL);
UBRRH = Rate>>8;
UBRRL = Rate;
}

/**
 *
 * This Function responsible For Sending a Byte.
 *
 * @param[in]  data Type uint8
 * @param[out] none
 * @return none
 */
void UART_sendByte(uint8 data)
{
#if (TRANSMITTER_MODE == POLLING_MODE)
while(BIT_IS_CLEAR(UCSRA,UDRE));
#endif
UDR=data;
}

/**
 *
 * This Function responsible For Receiving a Byte.
 *
 * @param[in]  none
 * @param[out] none
 * @return uint8
 */
#if (RECIEVER_MODE == POLLING_MODE)
uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;
}
#endif

/**
 *
 * This Function responsible For Sending a String.
 *
 * @param[in]  Str Type uint8
 * @param[out] none
 * @return none
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i=0;
while(Str[i]!='\0')
{
	UART_sendByte(Str[i]);
	i++;
}
}

/**
 *
 * This Function responsible For Receiving a String.
 *
 * @param[in]  none
 * @param[out] Str Type Ptr to uint8
 * @return none
 */
#if (RECIEVER_MODE == POLLING_MODE)
void UART_recieveString(uint8 *Str)
{
	uint8 i = 0;
	/* Receive the whole string until the '#' */
do
{
	Str[i] = UART_recieveByte();
	i++;

}while(Str[i-1] != '#');
	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i-1] = '\0';
}
#endif


/*ISR*/
#if (RECIEVER_MODE == INTERRUPT_MODE)
/* RX Complete ISR */
void __vector_13(void)
{
	Recieved_Byte = UDR;
	Recieve_Flag = 1;
}
#endif

#if (TRANSMITTER_MODE == INTERRUPT_MODE)
/* TX Complete ISR */
void __vector_15(void)
{

}

#endif

