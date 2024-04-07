/*
 * @file timer_Cfg.c
 * @brief source file for the Timer module configuration.
 *
 * This file contains the declarations and definitions for the Timer module in accordance
 * with the AUTOSAR standard.
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
#include"timer.h"
#include"timer_Cfg.h"
/*====================================================================================*/

const TIMER_UnitConfig TIMER_Unit_Configuration [NUMBER_OF_USED_TIMERS] =
{

		{
				TIMER1,
				TIMER1_PRESCALER_1024,
				0,
				TIMER1_CTC_OCR,
				FAST_PWM_NON_INVERTING,
				OC_DISCONNECTED,
				58594

		},


};

const TIMER_ConfigType TIMER_Configuration =
{
		TIMER_Unit_Configuration
};
