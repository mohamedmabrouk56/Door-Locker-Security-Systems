/**
  * @file keypad_Cfg.h
  * @brief  Pre-Compile Configuration Header file for the Keypad module.
  *
  * This file contains the  Pre-Compile Configuration for the Keypad module
  *
  * @author [Mohamed Mabrouk]
  * @date [11 FEB 2024]
  *
  * @SWversion 1.0.0
  *
  * @remarks
  *    -Platform         : AVR
  *    -Peripherial      : Atmega32
  */
  /*==================================================================================================================================*/


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

/* ===================================================================================================
										Macro Definition
   ===================================================================================================*/

/**
 * @brief Number of columns in the keypad matrix
 *
 * @details
 * - Type: define
 * - Range: 4U
 * - Resolution: Fixed
 * - Unit: None
 */
#define KEYPAD_COL_NUM 4

/**
 * @brief Number of rows in the keypad matrix
 *
 * @details
 * - Type: define
 * - Range: 4U
 * - Resolution: Fixed
 * - Unit: None
 */
#define KEYPAD_ROW_NUM 4

/**
 * @brief Used port for keypad row pins
 *
 * @details
 * - Type: define
 * - Range: 0U
 * - Resolution: Fixed
 * - Unit: None
 */
#define KEYPAD_ROW_PORT_ID PORTA_ID

/**
 * @brief First row pin ID of the keypad
 *
 * @details
 * - Type: define
 * - Range: 0U
 * - Resolution: Fixed
 * - Unit: None
 */
#define KEYPAD_FIRST_ROW_PIN_ID PIN0_ID

/**
 * @brief Used port for keypad column pins
 *
 * @details
 * - Type: define
 * - Range: 0U
 * - Resolution: Fixed
 * - Unit: None
 */
#define KEYPAD_COL_PORT_ID PORTA_ID

/**
 * @brief First column pin ID of the keypad
 *
 * @details
 * - Type: define
 * - Range: 4U
 * - Resolution: Fixed
 * - Unit: None
 */
#define KEYPAD_FIRST_COL_PIN_ID PIN4_ID

/**
 * @brief Logic level indicating a button press on the keypad
 *
 * @details
 * - Type: define
 * - Range: 0U
 * - Resolution: Fixed
 * - Unit: None
 */
#define KEYPAD_BUTTON_PRESSED LOGIC_LOW

/**
 * @brief Logic level indicating a button release on the keypad
 *
 * @details
 * - Type: define
 * - Range: 1U
 * - Resolution: Fixed
 * - Unit: None
 */
#define KEYPAD_BUTTON_RELEASED LOGIC_HIGH


#endif /* KEYPAD_CFG_H_ */
