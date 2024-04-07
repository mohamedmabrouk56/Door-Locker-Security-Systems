/**
   * @file DcMotor.h
   * @brief Header file for the DCMOTOR module.
   *
   * This file contains the declarations and definitions for the DCMOTOR module
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

#ifndef DCMOTOR_H_
#define DCMOTOR_H_
 /* ===================================================================================================
										   Includes
	===================================================================================================*/
#include "../../LIBRARY/Std_Types.h"
#include"DcMotor_Cfg.h"
/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/

typedef enum
{
 STOP,CLOCKWISE,ANTICLOCKWISE
}DcMotor_State;

 /* ===================================================================================================
											  Function Prototypes
    ===================================================================================================*/

/**
 *
 * This function Initiallize the DcMotor .
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void DcMotor_init(void);

/**
 * This function rotates the DC motor according to the specified state and speed.
 *
 * @param[in]  state   Type DcMotor_State   The state of the DC motor (STOP, CLOCKWISE, or ANTICLOCKWISE)
 * @param[in]  speed   Type uint8           The speed of the DC motor (0 to 100)
 * @return None
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
