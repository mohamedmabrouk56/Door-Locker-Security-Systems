/**
 * @file uart_Regs.h
 * @brief Header file for the Uart Registers.
 *
 * This file contains the Registers for the Uart module
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
#ifndef UART_REGS_H_
#define UART_REGS_H_

/* ===================================================================================================
											  Includes
   ===================================================================================================*/
#include "../../LIBRARY/Std_Types.h"
/* ===================================================================================================
		   								   Uart Registers
   ===================================================================================================*/

/* Baud Rate Register*/
#define UBRRH      *((volatile uint8* const)(0x40))
#define UBRRL      *((volatile uint8* const)(0x29))

/* Data Register*/
#define UDR        *((volatile uint8* const)(0x2C))

/* Control Registers */
#define UCSRA      *((volatile uint8* const)(0x2B))
#define UCSRB      *((volatile uint8* const)(0x2A))
#define UCSRC      *((volatile uint8* const)(0x40))

/*************************************************************************************************************/
/*UCSRA*/
#define 		RXC	     								7
#define 		TXC 									6
#define 		UDRE									5
#define 		FE  									4
#define 		DOR 									3
#define 		PE  									2
#define 		U2X 									1
#define 		MPCM 									0
/*************************************************************************************************************/
/*UCSRB*/
#define 		RXCIE									7
#define 		TXCIE									6
#define 		UDRIE									5
#define 		RXEN									4
#define 		TXEN									3
#define 		UCSZ2									2
#define 		RXB8									1
#define 		TXB8									0
/*************************************************************************************************************/
/*UCSRC*/
#define 		URSEL									7
#define 		UMSEL									6
#define 		UPM1 									5
#define 		UPM0 									4
#define 		USBS									3
#define 		UCSZ1									2
#define 		UCSZ0									1
#define 		UCPOL									0
/*************************************************************************************************************/

#endif /* UART_REGS_H_ */
