/**
  * @file DcMotor_Cfg.h
  * @brief  Pre-Compile Configuration Header file for the DcMotor module.
  *
  * This file contains the  Pre-Compile Configuration for the DcMotor module
  *
  * @author [Mohamed Mabrouk]
  * @date [25 JAN 2024]
  *
  * @SWversion 1.0.0
  *
  * @remarks
  *    -Platform         : AVR
  *    -Peripherial      : Atmega32
  */
  /*==================================================================================================================================*/

#ifndef DCMOTOR_CFG_H_
#define DCMOTOR_CFG_H_

/* ===================================================================================================
										   Macro Definition
   ===================================================================================================*/

/**
 * @brief Used port for the left motor pin
 *
 * @details
 * - Type: define
 * - Range: 1U
 * - Resolution: Fixed
 * - Unit: None
 */
#define MOTOR_L_PORT_ID PORTB_ID

/**
 * @brief Pin ID of the left motor
 *
 * @details
 * - Type: define
 * - Range: OU
 * - Resolution: Fixed
 * - Unit: None
 */
#define MOTOR_L_PIN_ID PIN0_ID

/**
 * @brief Used port for the right motor pin
 *
 * @details
 * - Type: define
 * - Range: 1U
 * - Resolution: Fixed
 * - Unit: None
 */
#define MOTOR_R_PORT_ID PORTB_ID

/**
 * @brief Pin ID of the right motor
 *
 * @details
 * - Type: define
 * - Range: 1U
 * - Resolution: Fixed
 * - Unit: None
 */
#define MOTOR_R_PIN_ID PIN1_ID

/**
 * @brief Used port for the enable pin of the motor
 *
 * @details
 * - Type: define
 * - Range: 1U
 * - Resolution: Fixed
 * - Unit: None
 */
#define MOTOR_E_PORT_ID PORTB_ID

/**
 * @brief Pin ID of the enable pin of the motor
 *
 * @details
 * - Type: define
 * - Range: 3U
 * - Resolution: Fixed
 * - Unit: None
 */
#define MOTOR_E_PIN_ID PIN3_ID


#endif /* DCMOTOR_CFG_H_ */
