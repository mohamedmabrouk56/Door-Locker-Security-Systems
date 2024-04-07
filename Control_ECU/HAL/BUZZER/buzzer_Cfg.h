/**
  * @file buzzer_Cfg.h
  * @brief  Pre-Compile Configuration Header file for the Buzzer module.
  *
  * This file contains the  Pre-Compile Configuration for the Buzzer module
  *
  * @author [Mohamed Mabrouk]
  * @date [16 MAR 2024]
  *
  * @SWversion 1.0.0
  *
  * @remarks
  *    -Platform         : AVR
  *    -Peripherial      : Atmega32
  */
  /*==================================================================================================================================*/

#ifndef BUZZER_CFG_H_
#define BUZZER_CFG_H_

/* ===================================================================================================
										   Macro Definition
   ===================================================================================================*/

/**
 * @brief Used port for the Buzzer
 *
 * @details
 * - Type: define
 * - Range: 1U
 * - Resolution: Fixed
 * - Unit: None
 */
#define BUZZER_PORT_ID PORTC_ID

/**
 * @brief Pin ID of the Buzzer
 *
 * @details
 * - Type: define
 * - Range: OU
 * - Resolution: Fixed
 * - Unit: None
 */
#define BUZZER_PIN_ID PIN3_ID


#endif /* BUZZER_CFG_H_ */
