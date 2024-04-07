/**
  * @file uart.h
  * @brief Header file for the Uart module.
  *
  * This file contains the declarations and definitions for the Uart module
  *
  * @author [Mohamed Mabrouk]
  * @date [27 FEB 2024]
  *
  * @SWversion 1.0.0
  *
  * @remarks
  *    -Platform         : AVR
  *    -Peripherial      : Atmega32
  */
  /*==================================================================================================================================*/

#ifndef UART_H_
#define UART_H_
/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include "../../LIBRARY/Std_Types.h"
#include"uart_Cfg.h"
#include"uart_Regs.h"
/* ===================================================================================================
										Macro Definition
   ===================================================================================================*/
#define POLLING_MODE   0
#define INTERRUPT_MODE 1
/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/
/**
 * @brief Enumeration for Parity Type.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:3
 * - Resolution: 1U
 * - Unit: Bits
 */
typedef enum
{
	DISABLED,EVEN_PARITY = 3,ODD_PARITY
}UART_ParityType;

/**
 * @brief Enumeration for Parity Type.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:3
 * - Resolution: 1U
 * - Unit: Bits
 */

typedef enum
{
	BAUDRATE_2400=2400,BAUDRATE_4800=4800,BAUDRATE_9600=9600,BAUDRATE_14400=14400
}UART_BaudRate;

/**
 * @brief Enumeration for Data Bits Size.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:7
 * - Resolution: 1U
 * - Unit: Bits
 */
typedef enum
{
	DATA_SIZE_5,DATA_SIZE_6,DATA_SIZE_7,DATA_SIZE_8,DATA_SIZE_9 = 7
}UART_DataSize;

/**
 * @brief Enumeration for Clock Polarity.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:1
 * - Resolution: 1U
 * - Unit: Bits
 */
typedef enum
{
	RISING_XCK_EDGE,FALLING_XCK_EDGE
}UART_ClockPolarity;

/**
 * @brief Enumeration for Stop Bit size.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:1
 * - Resolution: 1U
 * - Unit: Bits
 */
typedef enum
{
	STOP_SIZE_1,STOP_SIZE_2
}UART_StopSize;

/**
 * @brief Enumeration for Speed Mode.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:1
 * - Resolution: 1U
 * - Unit: Bits
 */
typedef enum
{
	NORMANL_SPEED=1,DOUBLE_SPEED=2
}UART_SpeedMode;


typedef struct
{
	UART_BaudRate 	   BaudRate;
	UART_DataSize	   DataSizeType;
	UART_ParityType	   ParityType;
	UART_StopSize	   StopType;
	UART_ClockPolarity ClockPolarityType;
	UART_SpeedMode 	   SpeedMode;
}UART_ConfigType;


extern const UART_ConfigType UART_Configuration;
extern uint8 Recieved_Byte;
/* ===================================================================================================
									   Function Prototypes
   ===================================================================================================*/

/**
 *
 * This Function responsible for initialize the UART driver.
 *
 * @param[in]  Config_Ptr Type UART_ConfigType
 * @param[out] none
 * @return none
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/**
 *
 * This Function responsible For Sending a Byte.
 *
 * @param[in]  data Type uint8
 * @param[out] none
 * @return none
 */
void UART_sendByte(uint8 data);

#if (RECIEVER_MODE == POLLING_MODE)
/**
 *
 * This Function responsible For Receiving a Byte.
 *
 * @param[in]  none
 * @param[out] none
 * @return uint8
 */
uint8 UART_recieveByte(void);
#endif
/**
 *
 * This Function responsible For Sending a String.
 *
 * @param[in]  Str Type uint8
 * @param[out] none
 * @return none
 */
void UART_sendString(const uint8 *Str);

#if (RECIEVER_MODE == POLLING_MODE)
/**
 *
 * This Function responsible For Receiving a String.
 *
 * @param[in]  none
 * @param[out] Str Type Ptr to uint8
 * @return none
 */
void UART_recieveString(uint8 *Str);
#endif

/*ISR*/
#if (RECIEVER_MODE == INTERRUPT_MODE)
void __vector_13(void)    __attribute__((signal)); /* RX Complete ISR */
#endif

#if (TRANSMITTER_MODE == INTERRUPT_MODE)
void __vector_15(void)    __attribute__((signal)); /* TX Complete ISR */
#endif

#endif /* UART_H_ */
