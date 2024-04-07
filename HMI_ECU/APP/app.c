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
uint8 opendoor_state = 0;
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
void HMI_sysInit(void)
{
	/* Initialize the LCD display module */
	LCD_init();

	/* Initialize the keypad */
	KEYPAD_init();

	UART_init(&UART_Configuration);

	/* Set up a callback function for Timer 1 As to HMI_openDoor */
	TIMER_setCallBack(TIMER1, HMI_openDoor);
}

/**
 * This function allows the user to set a new password using the Human Machine Interface ECU
 *
 * @param None
 * @return None
 */
void HMI_setNewPassword(void)
{
	/* Initialize an array to store the new password */
    uint8 Password[MAX_NUM_OF_DIGITS] = { 0 };
    uint8 Pass_digit;

    /* Clear the LCD screen */
    LCD_clearScreen();
    /* Display a message on the LCD to ask for Password */
    LCD_displayStringRowColumn(0, 0, "plz enter pass:");
    LCD_moveCursor(1, 0);

    for (Pass_digit = 0; Pass_digit < MAX_NUM_OF_DIGITS - 1; Pass_digit++)
    {
        /* Get the pressed key from the keypad */
        Password[Pass_digit] = KEYPAD_getPressedKey();

        /* Wait until a key is pressed */
        while (!(Password[Pass_digit]  <= 9 && Password[Pass_digit]  >= 0))
        {
            Password[Pass_digit] = KEYPAD_getPressedKey();
        }

        /* Wait until the key is released */
        while (Password[Pass_digit] == KEYPAD_getPressedKey());

        /* Send the pressed key via UART */
        UART_sendByte(Password[Pass_digit]);

        /* Display '*' on LCD to hide the entered digit */
        LCD_displayCharacter('*');
    }

    /* Null terminate the password array */
    Password[Pass_digit] = '\0';

    /* Wait until the '=' key is pressed to confirm the password */
    while (KEYPAD_getPressedKey() != '=');
}

/**
 * This function prompts the user to re-enter the password for verification using the Human Machine Interface ECU.
 *
 * @param None
 * @return None
 */
void HMI_ReenterPassword(void)
{
	/* Initialize an array to store the re-entered password */
    uint8 ReEnterPass[MAX_NUM_OF_DIGITS] = { 0 };
    uint8 Pass_digit;

    /* Clear the LCD screen */
    LCD_clearScreen();
    /* Display a message on the LCD to ask user to re-enter Password */
    LCD_displayStringRowColumn(0, 0, "plz re-enter the");
    LCD_displayStringRowColumn(1, 0, "same pass: ");

    for (Pass_digit = 0; Pass_digit < MAX_NUM_OF_DIGITS - 1; Pass_digit++)
    {
        /* Get the pressed key from the keypad */
        ReEnterPass[Pass_digit] = KEYPAD_getPressedKey();

        /* Wait until a key is pressed */
        while (!(ReEnterPass[Pass_digit]  <= 9 && ReEnterPass[Pass_digit]  >= 0))
        {
            ReEnterPass[Pass_digit] = KEYPAD_getPressedKey();
        }

        /* Send the pressed key via UART */
        UART_sendByte(ReEnterPass[Pass_digit]);

        /* Wait until the key is released */
        while (ReEnterPass[Pass_digit] == KEYPAD_getPressedKey());

        /* Display '*' on LCD to hide the entered digit */
        LCD_displayCharacter('*');
    }
    /* Null terminate the re-entered password array */
    ReEnterPass[Pass_digit] = '\0';

    /* Wait until the '=' key is pressed to confirm the re-entered password */
    while (KEYPAD_getPressedKey() != '=');
}

/**
 * This function checks the password entered by the user using the Human Machine Interface ECU.
 * It sends the entered password to Control_ECU for verification.
 *
 * @param None
 * @return None
 */
void HMI_checkPassword(void)
{
	/* Initialize an array to store the entered password */
    uint8 CheckPass[MAX_NUM_OF_DIGITS] = { 0 };
    uint8 Pass_digit;

    /* Send a ready-to-send signal to the Control_ECU */
    UART_sendByte(MCU1_READYTOSEND);
    /* Wait for a ready-to-receive signal from the Control_ECU */
    while(UART_recieveByte() != MCU2_READYTORECIEVE);
    /* Send a signal to indicate password check */
    UART_sendByte(CHECKPASS);

    LCD_clearScreen(); /* Clear the LCD screen */
    /* Display a message on the LCD to ask for Password */
    LCD_displayStringRowColumn(0, 0, "plz enter pass:");
    LCD_moveCursor(1, 0);

    for (Pass_digit = 0; Pass_digit < MAX_NUM_OF_DIGITS - 1; Pass_digit++)
    {
        /* Get the pressed key from the keypad */
        CheckPass[Pass_digit] = KEYPAD_getPressedKey();

        /* Wait until a key is pressed */
        while (!(CheckPass[Pass_digit]  <= 9 && CheckPass[Pass_digit]  >= 0))
        {
            CheckPass[Pass_digit] = KEYPAD_getPressedKey();
        }

        /* Send the pressed key via UART */
        UART_sendByte(CheckPass[Pass_digit]);

        /* Wait until the key is released */
        while (CheckPass[Pass_digit] == KEYPAD_getPressedKey());

        /* Display '*' on LCD to hide the entered digit */
        LCD_displayCharacter('*');
    }

    /* Null terminate the entered password array */
    CheckPass[Pass_digit] = '\0';

    /* Wait until the '=' key is pressed to confirm the entered password */
    while (KEYPAD_getPressedKey() != '=');
}

/**
 * This function controls the opening of the door using the Human Machine Interface (HMI).
 * It increments the door opening state and sets the compare match value of Timer1 accordingly.
 * If the error state is STATE_ERROR, it handles the error state and resets the door control.
 *
 * @param None
 * @return None
 */
void HMI_openDoor(void)
{
    if (Error_state == NORMAL)
    {
    	/* Increment the door open ticks counter as every tick timer counts 7.5 sec */
        opendoor_state++;

        if (opendoor_state == 2)
        {
        	/* Set the compare match value for timer 1 to count 3 sec */
            TIMER_setCompareMatch(TIMER1, 23437);
            LCD_clearScreen();
            /* Display "Door Will Lock soon" message on the LCD */
            LCD_displayStringRowColumn(0, 1,"Door Will Lock ");
            LCD_displayStringRowColumn(1, 6,"Soon");
        }
        else if (opendoor_state == 3)
        {
        	/* Set the compare match value for timer 1 to count 15 sec */
            TIMER_setCompareMatch(TIMER1, 58594);
            /* Clear the LCD screen */
            LCD_clearScreen();
            /* Display "Door is Locking" message on the LCD */
            LCD_displayStringRowColumn(0, 4,"Door is");
            LCD_displayStringRowColumn(1, 4,"Locking");
        }
        else if (opendoor_state == 4)
        {
        	/* Deinitialize timer 1 */
            TIMER_deInit(TIMER1);
            /* Reset the door opening state */
            opendoor_state = 0;
		    /* Clear the LCD screen */
		    LCD_clearScreen();
		    /* Display options on LCD */
		    LCD_displayStringRowColumn(0, 0, "+ : Open Door");
		    LCD_displayStringRowColumn(1, 0, "- : Change Pass");
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
    }
}
