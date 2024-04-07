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
/* HAL */
#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/lCD/lcd.h"

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
#define PASS_MATCHED		 	 1

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
 * - Range: 4
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define MAX_PASS_TRIES 		  4


/**
  * @brief Maximum number of digits for password
  *
  * @details
  * - Type: define
  * - Range: 6
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define MAX_NUM_OF_DIGITS 	  6


/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/
typedef enum
{
	NORMAL,MCU1_READYTOSEND=10,MCU1_READYTORECIEVE,MCU2_READYTOSEND,MCU2_READYTORECIEVE,CHECKPASS,CHANGEPASS,OPEN_DOOR,STATE_ERROR
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
void HMI_sysInit(void);

/**
  * This function allows the user to set a new password using the Human Machine Interface ECU
  *
  * @param None
  * @return None
  */
void HMI_setNewPassword(void);

/**
 * This function prompts the user to re-enter the password for verification using the Human Machine Interface ECU.
 *
 * @param None
 * @return None
 */
 void HMI_ReenterPassword(void);

/**
 * This function checks the password entered by the user using the Human Machine Interface ECU.
 * It sends the entered password to Control_ECU for verification.
 *
 * @param None
 * @return None
 */
 void HMI_checkPassword(void);

 /**
  * This function controls the opening of the door using the Human Machine Interface (HMI).
  * It increments the door opening state and sets the compare match value of Timer1 accordingly.
  * If the error state is STATE_ERROR, it handles the error state and resets the door control.
  *
  * @param None
  * @return None
  */
 void HMI_openDoor(void);
#endif /* APP_H_ */

