/**
 * @file twi_Cfg.c
 * @brief source file for the Twi module configuration.
 *
 *
 * @author [Mohamed Mabrouk]
 * @date [17 MAR 2024]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Platform         : AVR
 *    -Peripherial      : Atmega32
 */
/*==================================================================================================================================*/
#include"twi.h"
/*====================================================================================*/

const TWI_ConfigType TWI_Configuration =
{
		TWI_SLAVE1_ADDRESS,TWI_FAST_MODE_400K,TWI_PRESCALER_1
};

