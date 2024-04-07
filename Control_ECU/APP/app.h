/**
 * @file 	app.h
 * @brief APP Header file.
 *
 * This file contains the declarations and definitions for the Application
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
#ifndef APP_H_
#define APP_H_

/* ===================================================================================================
										   Includes
   ===================================================================================================*/
/* LIBRARIRES */
#include"util/delay.h"
#include "../LIBRARY/common_macros.h"
/* MCAL */
#include "../MCAL/TIMER/timer.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/TWI/twi.h"
/* HAL */
#include "../HAL/DCMOTOR/DcMotor.h"
#include "../HAL/BUZZER/buzzer.h"
#include "../HAL/EXTERNAL_EEPROM/external_eeprom.h"

/* ===================================================================================================
                                        Macro Definition
   ===================================================================================================*/

/**
  * @brief Password is incorrect State
  *
  * @details
  * - Type: define
  * - Range: 0
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define PASS_INCORRECT 		  0

/**
  * @brief Password is correct State
  *
  * @details
  * - Type: define
  * - Range: 1
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define PASS_CORRECT    	  1
/**
 * @brief Password is unmatched State
 *
 * @details
 * - Type: define
 * - Range: 0
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define PASS_UNMATCHED 		  0

/**
 * @brief Both Password And Reentered Password are the same
 *
 * @details
 * - Type: define
 * - Range: 1
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define PASS_MATCHED 		  1

/**
 * @brief No State received Yet
 *
 * @details
 * - Type: define
 * - Range: 0
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define RECIEVED_NOTHING      0

/**
 * @brief Maximum number of password tries
 *
 * @details
 * - Type: define
 * - Range: 3
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define MAX_PASS_TRIES 		  3

/**
  * @brief Maximum number of digits for password
  *
  * @details
  * - Type: define
  * - Range: 5
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define MAX_NUM_OF_DIGITS 	  6


/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/
typedef enum
{
	NORMAL,MCU1_READYTOSEND = 10,MCU1_READYTORECIEVE,MCU2_READYTOSEND,MCU2_READYTORECIEVE,CHECKPASS,CHANGEPASS,OPEN_DOOR,STATE_ERROR
}States;

extern uint8 Error_state;
/* ===================================================================================================
                                             Function Prototypes
   ===================================================================================================*/

/**
 *
 * This function Initiallizes the System Modules
 *
 * @param[in]  none
 * @param[out]  none
 * @return none
 */
void CONTROL_sysInit(void);

/**
 * This function saves a new password received via UART.
 *
 * @param None
 * @return None
 */
void CONTROL_newPasswordSave(void);

 /**
  * This function checks if the entered password matches the saved password received via UART.
  *
  * @param None
  * @return uint8
  */
uint8 CONTROL_passwordCheck(void);

/**
 * This function controls the opening of the door based on the current error state.
 * If the error state is normal, it incrementally opens the door using a motor.
 * If the error state is STATE_ERROR, it handles the error state and resets the door control.
 *
 * @param None
 * @return None
 */
void CONTROL_openDoor(void);

/**
 * This function saves the password to the EEPROM memory.
 *
 * @param None
 * @return None
 */
void CONTROL_savePasswordMemory(void);

#endif /* APP_H_ */

