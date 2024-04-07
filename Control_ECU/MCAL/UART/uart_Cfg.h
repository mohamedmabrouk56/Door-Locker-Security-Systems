/**
 * @file 	uart_Cfg.h
 * @brief Uart Configratuions Header File.
 *
 * This file contains the Configratuions for the Uart module
 *
 * @author [Mohamed Mabrouk]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Platform         : AVR
 *    -Peripherial      : Atmega32
 */
 /*==================================================================================================================================*/

#ifndef UART_CFG_H_
#define UART_CFG_H_

#ifndef  F_CPU
#define  F_CPU 16000000UL					/*System Clock*/
#endif

#define TRANSMITTER_MODE	POLLING_MODE
#define RECIEVER_MODE 		POLLING_MODE

#endif /* UART_CFG_H_ */
