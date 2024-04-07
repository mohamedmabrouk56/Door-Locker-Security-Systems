/**
 * @file uart_Cfg.c
 * @brief source file for the Uart module configuration.
 *
 * This file contains the declarations and definitions for the Uart module in accordance
 * with the AUTOSAR standard.
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
#include"uart.h"
#include"uart_Cfg.h"
/*====================================================================================*/

const UART_ConfigType UART_Configuration =
{
		BAUDRATE_9600,DATA_SIZE_8,EVEN_PARITY,STOP_SIZE_1,RISING_XCK_EDGE,DOUBLE_SPEED
};

