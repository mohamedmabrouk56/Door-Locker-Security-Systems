/**
  * @file lcd_Cfg.h
  * @brief  Pre-Compile Configuration Header file for the Lcd module.
  *
  * This file contains the  Pre-Compile Configuration for the Lcd module
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

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/* used pins & ports*/

/**
  * @brief Used Port for RS Pin in LCD
  *
  * @details
  * - Type: define
  * - Range: 3U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define LCD_RS_PORT_ID PORTD_ID
/**
  * @brief Used Pin for Register Select in LCD
  *
  * @details
  * - Type: define
  * - Range: 2U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define LCD_RS_PIN_ID PIN2_ID
/**
  * @brief Used Port for Register Select Pin in LCD
  *
  * @details
  * - Type: define
  * - Range: 3U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define LCD_E_PORT_ID PORTD_ID
/**
  * @brief Used Pin for enable in LCD
  *
  * @details
  * - Type: define
  * - Range: 3U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define LCD_E_PIN_ID PIN3_ID
/**
  * @brief Choose the Data Mode
  *
  * @details
  * - Type: define
  * - Range: 4U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define LCD_DATA_MODE LCD_FOUR_BIT_DATA_MODE

#if (LCD_DATA_MODE==LCD_EIGHT_BIT_DATA_MODE)
/**
  * @brief Used Port of Data in LCD
  *
  * @details
  * - Type: define
  * - Range: 2U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define LCD_DATA_PORT_ID PORTB_ID

#elif (LCD_DATA_MODE == LCD_FOUR_BIT_DATA_MODE)
/**
  * @brief Used Pins of Data in LCD 4 bit mode
  *
  * @details
  * - Type: define
  * - Range: 0:7 U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define LCD_FOUR_BIT_PIN1 PIN4_ID
#define LCD_FOUR_BIT_PIN2 PIN5_ID
#define LCD_FOUR_BIT_PIN3 PIN6_ID
#define LCD_FOUR_BIT_PIN4 PIN7_ID

#define LCD_FOUR_BIT_DATA_PORT_ID PORTD_ID
#endif

#endif /* LCD_CFG_H_ */
