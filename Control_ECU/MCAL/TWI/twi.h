/**
  * @file Twi.h
  * @brief Header file for the Twi module.
  *
  * This file contains the declarations and definitions for the Twi module
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
#ifndef TWI_H_
#define TWI_H_

/* ===================================================================================================
										   Includes
	===================================================================================================*/
#include "../../LIBRARY/Std_Types.h"
#include"twi_Cfg.h"
#include"twi_Regs.h"

 /* ===================================================================================================
								   	    Macro Definition
    ===================================================================================================*/
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/

typedef enum{
	TWI_PRESCALER_1,
	TWI_PRESCALER_4,
	TWI_PRESCALER_16,
	TWI_PRESCALER_64
}TWI_Prescaler;
/**
 * @brief Enumeration for Baud Rate.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:0xFF
 * - Resolution: 1U
 * - Unit: Bits
 */

typedef enum
{
	/* Assuming 8MHZ */
	TWI_NORMAL_MODE_100K = 0x20,
	TWI_FAST_MODE_400K = 0x02,
	/* Assuming 16MHZ */
#if(F_CPU == 16000000)
	TWI_FAST_MODE_PLUS_1M = 0x00,
#endif
/* cant operate on this Frequencies
	     HIGH_SPEED_MODE_3_4M 		*/

}TWI_BaudRate;


/**
 * @brief Enumeration for Slave Address.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:127
 * - Resolution: 1U
 * - Unit: Bits
 */
typedef enum
{
	TWI_SLAVE1_ADDRESS = 0b0001010
}TWI_Address;


typedef struct
{
	 TWI_Address   address;
	 TWI_BaudRate  bit_rate;
	 TWI_Prescaler prescaler;
}TWI_ConfigType;


extern const TWI_ConfigType TWI_Configuration;


/* ===================================================================================================
									   Function Prototypes
   ===================================================================================================*/
/**
 * @brief Initialize the TWI  module.
 *
 * @details
 * - This function initializes the TWI module with default settings.
 */
void TWI_init(const TWI_ConfigType *Config_Ptr);

/**
 * @brief Generate a start condition on the TWI bus.
 *
 * @details
 * - This function generates a start condition on the TWI bus to initiate communication.
 */
void TWI_start(void);

/**
 * @brief Generate a stop condition on the TWI bus.
 *
 * @details
 * - This function generates a stop condition on the TWI bus to terminate communication.
 */
void TWI_stop(void);

/**
 * @brief Write a byte of data to the TWI bus.
 *
 * @param[in] data The byte of data to be written.
 */
void TWI_writeByte(uint8 data);

/**
 * @brief Read a byte of data from the TWI bus with ACK (acknowledge).
 *
 * @return The byte of data read from the TWI bus with ACK.
 */
uint8 TWI_readByteWithACK(void);

/**
 * @brief Read a byte of data from the TWI bus with NACK (no acknowledge).
 *
 * @return The byte of data read from the TWI bus with NACK.
 */
uint8 TWI_readByteWithNACK(void);

/**
 * @brief Get the status of the TWI module.
 *
 * @details
 * - This function retrieves the current status of the TWI module.
 *
 * @return The status of the TWI module.
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
