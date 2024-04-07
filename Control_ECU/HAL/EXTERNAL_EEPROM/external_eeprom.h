/**
  * @file external_eeprom.h
  * @brief Header file for the External_EEPROM module.
  *
  * This file contains the declarations and definitions for the External_EEPROM  module
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

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include "../../LIBRARY/Std_Types.h"

 /* ===================================================================================================
								   	    Macro Definition
    ===================================================================================================*/
#define ERROR 0
#define SUCCESS 1

/* ===================================================================================================
									   Function Prototypes
   ===================================================================================================*/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
 
#endif /* EXTERNAL_EEPROM_H_ */
