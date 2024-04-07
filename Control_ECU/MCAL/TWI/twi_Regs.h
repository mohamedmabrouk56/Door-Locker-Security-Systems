/**
 * @file twi_Regs.h
 * @brief Header file for the Twi Registers.
 *
 * This file contains the Registers for the I2C module
 *
 * @author [Mohamed Mabrouk]
 * @date [17 MAR 2024]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Platform         : AVR
 *    -Peripherial      : Atmega32
 */
 /*==================================================================================================================================*/
#ifndef TWI_REGS_H_
#define TWI_REGS_H_
/* ===================================================================================================
											  Includes
   ===================================================================================================*/
#include "../../LIBRARY/Std_Types.h"
 /* ===================================================================================================
											I2C Registers
	===================================================================================================*/
#define TWCR  *((volatile uint8* const)(0x56))
#define TWDR  *((volatile uint8* const)(0x23))
#define TWAR  *((volatile uint8* const)(0x22))
#define TWSR  *((volatile uint8* const)(0x21))
#define TWBR  *((volatile uint8* const)(0x20))

 /* ===================================================================================================
												I2C Bits
	===================================================================================================*/
/*************************************************************************************************************/
/*TWCR*/
#define 		TWINT									7
#define 		TWEA									6
#define 		TWSTA									5
#define 		TWSTO									4
#define 		TWWC									3
#define 		TWEN									2
#define 		TWIE									0
/*************************************************************************************************************/
/*TWAR*/
#define 		TWA6									7
#define 		TWA5									6
#define 		TWA4									5
#define 		TWA3									4
#define 		TWA2									3
#define 		TWA1									2
#define 		TWA0									1
/*************************************************************************************************************/
/*TWSR*/
#define 		TWS7									7
#define 		TWS6									6
#define 		TWS5									5
#define 		TWS4									4
#define 		TWWC									3
#define 		TWPS1									1
#define 		TWPS0									0
/*************************************************************************************************************/












#endif /* TWI_REGS_H_ */
