/**
   * @file  buzzer.h
   * @brief Header file for the Buzzer module.
   *
   * This file contains the declarations and definitions for the Buzzer module
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

#ifndef BUZZER_H_
#define BUZZER_H_

/* ===================================================================================================
									   Includes
   ===================================================================================================*/
#include "../../LIBRARY/Std_Types.h"
#include"buzzer_Cfg.h"
 /* ===================================================================================================
											  Function Prototypes
    ===================================================================================================*/
/**
 *
 * This function Initiallize the Buzzer .
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void BUZZER_init(void);

/**
 * This function turns on the buzzer.
 *
 * @param None
 * @return None
 */
void BUZZER_on(void);

/**
 * This function turns off the buzzer.
 *
 * @param None
 * @return None
 */
void BUZZER_off(void);

#endif /* BUZZER_H_ */
