/**
 * @file  buzzer.c
 * @brief Buzzer Source file.
 *
 * This file contains The Implementation of Functions of the Buzzer module
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

 /* ===================================================================================================
											  Includes
	===================================================================================================*/
#include "../../MCAL/GPIO/gpio.h"
#include "../../LIBRARY/common_macros.h"
#include"buzzer.h"

/* ===================================================================================================
										  Function Definition
   ===================================================================================================*/

/**
 *
 * This function Initiallize the Buzzer .
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/**
 * This function turns on the buzzer.
 *
 * @param None
 * @return None
 */
void BUZZER_on(void)
{
	/* Set the buzzer pin to high */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/**
 * This function turns off the buzzer.
 *
 * @param None
 * @return None
 */
void BUZZER_off(void)
{
	/* Set the buzzer pin to low */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
