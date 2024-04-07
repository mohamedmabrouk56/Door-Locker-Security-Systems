/**
 * @file DcMotor.c
 * @brief DcMotor Source file.
 *
 * This file contains The Implementation of Functions of the DcMotor module
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

 /* ===================================================================================================
											  Includes
	===================================================================================================*/
#include"DcMotor.h"
#include "../../MCAL/TIMER/timer.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../LIBRARY/common_macros.h"

/* ===================================================================================================
										  Function Definition
   ===================================================================================================*/

/**
 *
 * This function Initiallize the DcMotor .
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void DcMotor_init(void)
{
	GPIO_setupPinDirection(MOTOR_L_PORT_ID, MOTOR_L_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_R_PORT_ID, MOTOR_R_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_E_PORT_ID, MOTOR_E_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(MOTOR_L_PORT_ID, MOTOR_L_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_R_PORT_ID, MOTOR_R_PIN_ID, LOGIC_LOW);
}

/**
 * This function rotates the DC motor according to the specified state and speed.
 *
 * @param[in]  state   Type DcMotor_State   The state of the DC motor (STOP, CLOCKWISE, or ANTICLOCKWISE)
 * @param[in]  speed   Type uint8           The speed of the DC motor (0 to 100)
 * @return None
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
    if (state == STOP) {
    	/* Stop the motor by setting PWM duty cycle to 0 */
        TIMER0_setPwmDutyCycle(0);
        /* Set up the motor pins to low */
        GPIO_writePin(MOTOR_L_PORT_ID, MOTOR_L_PIN_ID, LOGIC_LOW);
        GPIO_writePin(MOTOR_R_PORT_ID, MOTOR_R_PIN_ID, LOGIC_LOW);
    }
    else if (state == CLOCKWISE)
    {
    	/* Set the PWM duty cycle for clockwise rotation */
        TIMER0_setPwmDutyCycle(speed);
        GPIO_writePin(MOTOR_L_PORT_ID, MOTOR_L_PIN_ID, LOGIC_LOW); /* Set the left motor pin to low */
        GPIO_writePin(MOTOR_R_PORT_ID, MOTOR_R_PIN_ID, LOGIC_HIGH); /* Set the right motor pin to high */
    }
    else if (state == ANTICLOCKWISE)
    {
    	/* Set the PWM duty cycle for anticlockwise rotation */
        TIMER0_setPwmDutyCycle(speed);
        GPIO_writePin(MOTOR_L_PORT_ID, MOTOR_L_PIN_ID, LOGIC_HIGH); /* Set the left motor pin to high */
        GPIO_writePin(MOTOR_R_PORT_ID, MOTOR_R_PIN_ID, LOGIC_LOW); /* Set the right motor pin to low */
    }
}
