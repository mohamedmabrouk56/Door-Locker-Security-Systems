/**
 * @file 	app.c
 * @brief APP Source file.
 *
 * This file contains The Application of Door Locker - security system
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
#include "app.h"

/* ===================================================================================================
                                              Global Variables
   ===================================================================================================*/

uint8 Password[MAX_NUM_OF_DIGITS] = { 0 };
uint8 ReEnterPass[MAX_NUM_OF_DIGITS] = { 0 };
uint8 opendoor_ticks = 0;
uint8 Error_state = NORMAL;
uint8 Error_state_ticks = 0;

/* ===================================================================================================
                                              Function Definition
   ===================================================================================================*/

/**
 *
 * This function Initiallizes the System Modules
 *
 * @param[in]  none
 * @param[out]  none
 * @return none
 */
void CONTROL_sysInit(void)
{

	UART_init(&UART_Configuration);

	DcMotor_init();

	TWI_init(&TWI_Configuration);

	/* Set up a callback function for Timer 1 As to CONTROL_openDoor */
	TIMER_setCallBack(TIMER1, CONTROL_openDoor);

	BUZZER_init();

}


/**
 * This function saves a new password received via UART.
 *
 * @param None
 * @return None
 */
void CONTROL_newPasswordSave(void)
{
    uint8 Pass_digit;

    /* Loop till get each digit of the password */
    for (Pass_digit = 0; Pass_digit < MAX_NUM_OF_DIGITS - 1; Pass_digit++)
    {
    	/* Receive send digit of the password via UART */
        Password[Pass_digit] = UART_recieveByte();
    }
}

/**
 * This function checks if the entered password matches the saved password received via UART.
 *
 * @param None
 * @return uint8
 */
uint8 CONTROL_passwordCheck(void)
{

    uint8 Pass_digitnum;
    uint8 Pass_digit = 0;
    /* Counter to track the number of correct digits of the Password */
    uint8 Correct_num = 0;

    /* Loop through each digit of the entered password */
    for (Pass_digitnum = 0; Pass_digitnum < MAX_NUM_OF_DIGITS - 1; Pass_digitnum++)
    {
    	/* Receive a byte (digit) of the password via UART */
    	ReEnterPass[Pass_digitnum] = UART_recieveByte();

    	/* Read the corresponding digit from EEPROM */
    	EEPROM_readByte(0x0100 + Pass_digitnum, &Pass_digit);
    	_delay_ms(10);

    	/* Check if the received digit matches the corresponding digit of the saved password in EEPROM */
    	if (ReEnterPass[Pass_digitnum] == Pass_digit)
    	{
    	    Correct_num++; /* Increment correct digit counter */
    	}
    }

    /* Check if all digits are correct */
    if (Correct_num == MAX_NUM_OF_DIGITS - 1)
    {
    	/* Return PASS_CORRECT if all digits are correct */
        return PASS_CORRECT;
    }
    else
    {
    	/* Return PASS_INCORRECT if any digit is incorrect */
        return PASS_INCORRECT;
    }
}

/**
 * This function controls the opening of the door based on the current error state.
 * If the error state is normal, it incrementally opens the door using a motor.
 * If the error state is STATE_ERROR, it handles the error state and resets the door control.
 *
 * @param None
 * @return None
 */
void CONTROL_openDoor(void)
{
    if (Error_state == NORMAL)
    {
    	/* Increment the door open ticks counter as every tick timer counts 7.5 sec */
        opendoor_ticks++;

        if (opendoor_ticks == 2)
        {
        	/* Set the compare match value for timer 1 to count 3 sec */
            TIMER_setCompareMatch(TIMER1, 23437);
            /* Stop the motor for 3 sec*/
            DcMotor_Rotate(STOP, 0);
        }
        else if (opendoor_ticks == 3)
        {
        	/* Set the compare match value for timer 1 to count 15 sec */
            TIMER_setCompareMatch(TIMER1, 58594);
            /* Rotate the motor anticlockwise for 15 sec */
            DcMotor_Rotate(ANTICLOCKWISE, 100);
        }
        else if (opendoor_ticks == 4)
        {
        	/* Stop the motor */
            DcMotor_Rotate(STOP, 0);
            /* Deinitialize timer 1 */
            TIMER_deInit(TIMER1);
            /* Reset the door open ticks counter */
            opendoor_ticks = 0;
        }
    }
    else if (Error_state_ticks < 8 && Error_state == STATE_ERROR)
    {
    	/* Increment the error state ticks counter as evrey tick it counts 7.5 sec*/
        Error_state_ticks++;
    }
    else if (Error_state_ticks >= 8 && Error_state == STATE_ERROR)
    {
    	/* When Timer 1 Reaches 1 Min Reset the error state to normal*/
        Error_state = NORMAL;
        /* Reset the error state ticks counter */
        Error_state_ticks = 0;
        /* Deinitialize timer 1 */
        TIMER_deInit(TIMER1);
        /* Turn off the buzzer */
        BUZZER_off();
    }
}

/**
 * This function saves the password to the EEPROM memory.
 *
 * @param None
 * @return None
 */
void CONTROL_savePasswordMemory(void)
{
    uint8 Pass_digitnum;

    /* Loop through each digit of the password */
    for (Pass_digitnum = 0; Pass_digitnum < MAX_NUM_OF_DIGITS - 1; Pass_digitnum++)
    {
    	/* Write the each password digit to EEPROM */
        EEPROM_writeByte(0x0100 + Pass_digitnum, Password[Pass_digitnum]);
        /* Delay for EEPROM write operation */
        _delay_ms(10);
    }
}
