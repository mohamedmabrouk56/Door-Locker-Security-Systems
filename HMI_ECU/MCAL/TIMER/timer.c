/**
 * @file 	timer.c
 * @brief TIMER Source file.
 *
 * This file contains The Implementation of Functions of the TIMER module
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
#include"timer.h"
#include "../GPIO/gpio.h"
#include"timer_Regs.h"
#include "../../LIBRARY/common_macros.h"
	/* ===================================================================================================
											  Global Variables
	   ===================================================================================================*/

/*Global Pointer to function*/
static volatile void (*TIMER0_PtrCallBack)(void) = NULL_PTR;
static volatile void (*TIMER1_PtrCallBack)(void) = NULL_PTR;
static volatile void (*TIMER2_PtrCallBack)(void) = NULL_PTR;

uint8 Timer1_Mode;

/* ===================================================================================================
										  Function Definition
   ===================================================================================================*/

/**
 *
 * This Function responsible for initialize the TIMER driver.
 *
 * @param[in]  Config_Ptr Type TIMER_ConfigType
 * @param[out] none
 * @return none
 */
void TIMER_init(const TIMER_ConfigType *Config_Ptr)
{
	int i;
	for(i=0;i<NUMBER_OF_USED_TIMERS;i++)
	{
	switch(Config_Ptr->Units[i].TimerNum)
	{
	case TIMER0:
	TCCR0 |= Config_Ptr->Units[i].Prescaler;
	switch(Config_Ptr->Units[i].Mode)
	{
	case TIMER0_OVF:
	/* Choose the Normal Mode  */
	CLR_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);

	TCNT0 = Config_Ptr->Units[i].Initial_value;

	/* Enabling the Overflow Interrupt Enable */
	TIMSK = (TIMSK & 0xFC) | (1 << TOIE0);
	/* Enabling the FOCO As i Choose Non Pwm Mode */
	SET_BIT(TCCR0, FOC0);
	break;

	case  TIMER0_CTC:
	/* Choose the Compare Match Mode */
	CLR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

	TCNT0 = Config_Ptr->Units[i].Initial_value;
	OCR0  = Config_Ptr->Units[i].Compare_value;

	/* Choose the OCO State in CTC */
	TCCR0 = (TCCR0 & 0xCF) | ((Config_Ptr->Units[i].CtcMode)<<COM00) ;

	/* Enabling the CTC Interrupt Enable */
	TIMSK = (TIMSK & 0xFC) | (1 << OCIE0);
	/* Enabling the FOCO As To Choose Non Pwm Mode */
	SET_BIT(TCCR0, FOC0);
	break;

	case  TIMER0_FAST_PWM:
	/* Choose the FAST PWM */
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

	/* Choose the Fast Pwm Working Mode */
	TCCR0 = (TCCR0 & 0xCF) | ((Config_Ptr->Units[i].PwmMode)<<COM00) ;

	/* Disabling the CTC , Overflow Interrupt Enable */
	TIMSK = (TIMSK & 0xFC);

	/* Disabling the FOCO As To Choose a Pwm Mode */
	CLR_BIT(TCCR0, FOC0);

	/* Defining OC0 Pin As an Output */
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	break;

	case TIMER0_PHASE_PWM:
	/* Choose the PHASE PWM Mode */
	SET_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);

	/* Defining OC0 Pin As an Output */
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_OUTPUT);
	break;

	default :
		/* Wrong Input */
	break;

	}

	break;
	case TIMER1:

		TCCR1B |= Config_Ptr->Units[i].Prescaler;
		Timer1_Mode = Config_Ptr->Units[i].Mode;

		switch(Config_Ptr->Units[i].Mode)
		{
		case TIMER1_OVF:
		/* Choose the Mode */
		CLR_BIT(TCCR1A, WGM10);
		CLR_BIT(TCCR1A, WGM11);
		CLR_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		TCNT1 = Config_Ptr->Units[i].Initial_value;

		/* Enabling the FOC1A & FOC1B To Choose Non Pwm Mode */
		SET_BIT(TCCR1A, FOC1A);
		SET_BIT(TCCR1A, FOC1B);

		/* Enabling the Overflow Interrupt Enable */
		TIMSK = (TIMSK & 0xE3)  | (1 << TOIE1);

		break;
		case  TIMER1_CTC_OCR:
		/* Choose the CTC Mode With OCR */
		CLR_BIT(TCCR1A, WGM10);
		CLR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		TCNT1 = Config_Ptr->Units[i].Initial_value;
		OCR1A = Config_Ptr->Units[i].Compare_value;

		/* Enabling the FOC1A & FOC1B To Choose Non Pwm Mode */
		SET_BIT(TCCR1A, FOC1A);
		SET_BIT(TCCR1A, FOC1B);

		/* Enabling the Overflow Interrupt Enable */
		TIMSK = (TIMSK & 0xE3)  | (1 << OCIE1A);

		/* Choose the OC1A , OC1B State in CTC */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].CtcMode)<<COM1B0) | ((Config_Ptr->Units[i].CtcMode)<<COM1A0);
		break;

		case   TIMER1_FAST_PWM_8BIT :
		/* Choose the Fast Pwm With 8bit Range */
		SET_BIT(TCCR1A, WGM10);
		CLR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining OC1A / OC1B Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		break;

		case    TIMER1_FAST_PWM_9BIT :
		/* Choose the Fast Pwm With 9bit Range */
		CLR_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining OC1A / OC1B Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		break;

		case    TIMER1_FAST_PWM_10BIT :
		/* Choose the Fast Pwm With 10bit Range */
		SET_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLR_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining OC1A / OC1B Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		break;

		case    TIMER1_CTC_ICR :
		/* Choose the CTC Mode With ICR */
		CLR_BIT(TCCR1A, WGM10);
		CLR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);

		TCNT1 = Config_Ptr->Units[i].Initial_value;
		ICR1 = Config_Ptr->Units[i].Compare_value;

		/* Enabling the FOC1A & FOC1B To Choose Non Pwm Mode */
		SET_BIT(TCCR1A, FOC1A);
		SET_BIT(TCCR1A, FOC1B);

		/* Enabling the Overflow Interrupt Enable */
		TIMSK = (TIMSK & 0xE3)  | (1 << OCIE1A);

		/* Choose the OC1A , OC1B State in CTC */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].CtcMode)<<COM1B0) | ((Config_Ptr->Units[i].CtcMode)<<COM1A0);
		break;

		case    TIMER1_FAST_PWM_ICR	 :
		/* Choose the Fast Pwm With ICR REG */
		CLR_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining ICR Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_OUTPUT);
		break;

		case	 TIMER1_FAST_PWM_OCR :
		/* Choose the Fast Pwm With 0CR REG */
		SET_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);

		/* Choose the PWM Working Mode */
		TCCR1A = (TCCR0 & 0x0F) | ((Config_Ptr->Units[i].PwmMode)<<COM1B0) | ((Config_Ptr->Units[i].PwmMode)<<COM1A0);

		/* Defining OC1A / OC1B Pin As an Output */
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		break;

		default :
			/* Wrong Input */
			break;
		}
		break;

		/*Timer2 initiaillitation*/
	case TIMER2:
		TCCR2 |= Config_Ptr->Units[i].Prescaler;
		switch(Config_Ptr->Units[i].Mode)
			{
			case TIMER2_OVF:
			/* Choose the Normal Mode  */
			CLR_BIT(TCCR2, WGM20);
			CLR_BIT(TCCR2, WGM21);

			/* Enabling the Overflow Interrupt Enable */
			TIMSK = (TIMSK & 0x3F) | (1 << TOIE2);
			/* Enabling the FOC2 As To Choose Non Pwm Mode */
			SET_BIT(TCCR2, FOC2);
			break;

			case TIMER2_CTC:
			/* Choose the Compare Match Mode */
			CLR_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);

			/* Enabling the Overflow Interrupt Enable */
			TIMSK = (TIMSK & 0x3F) | (1 << OCIE2);
			/* Enabling the FOC2 As To Choose Non Pwm Mode */
			SET_BIT(TCCR2, FOC2);
			break;

			case TIMER2_FAST_PWM :
			/* Choose the FAST PWM */
			SET_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);

			/* Choose the Fast Pwm Working Mode */
			TCCR2 = (TCCR2 & 0xCF) | ((Config_Ptr->Units[i].PwmMode)<<COM20) ;

			/* Disabling the CTC , Overflow Interrupt Enable */
			TIMSK = (TIMSK & 0x3F);

			/* Disabling the FOCO As i Choose a Pwm Mode */
			CLR_BIT(TCCR2, FOC2);

			/* Defining OC2 Pin As an Output */
			GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
			break;

		    case TIMER2_PHASE_PWM :
		    /* Choose the Phase PWM */
			SET_BIT(TCCR2, WGM20);
			CLR_BIT(TCCR2, WGM21);

			/* Defining OC2 Pin As an Output */
			GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
			break;

		    default :
		    	/* Wrong Input */
		    break;
			}
		break;

		 default :
				 /* Wrong Timer Num */
		 break;
	}
	}
}

/**
 * This function reads the current count value of the specified timer.
 *
 * @param[in]  Timer_num     Type Timer_ID     Range TIMER0, TIMER1, TIMER2
 * @return     Type uint8    The current count value of the specified timer
 */
uint8 TIMER_read(Timer_ID Timer_num)
{
	/* Read the current count value of the specified timer */
	switch(Timer_num)
	{
		case TIMER0:
			return TCNT0; /* Return the current count value of TIMER0 */
			break;

		case TIMER1:
			return TCNT1; /* Return the current count value of TIMER1 */
			break;

		case TIMER2:
			return TCNT2; /* Return the current count value of TIMER2 */
			break;

		default:
			/* Wrong Timer Num: Invalid timer number specified */
			return 0;
			break;
	}
}

/**
 * This function sets the preload value for the specified timer.
 *
 * @param[in]  Timer_num     Type Timer_ID     Range TIMER0, TIMER1, TIMER2
 * @param[in]  Preload       Type uint16       Range 0 to 65535
 * @return None
 */
void TIMER_setPreloadValue(Timer_ID Timer_num, uint16 Preload)
{
	/* Set the preload value for the specified timer */
	switch(Timer_num)
	{
		case TIMER0:
			TCNT0 = Preload; /* Set the preload value for TIMER0 */
			break;

		case TIMER1:
			TCNT1 = Preload; /* Set the preload value for TIMER1 */
			break;

		case TIMER2:
			TCNT2 = Preload; /* Set the preload value for TIMER2 */
			break;

		default:
			/* Wrong Timer Num: Invalid timer number specified */
			break;
	}
}

/**
 * This function sets the compare match value for the specified timer.
 *
 * @param[in]  Timer_num     Type Timer_ID     Range TIMER0, TIMER1, TIMER2
 * @param[in]  Value         Type uint16       Range 0 to 65535
 * @return None
 */
void TIMER_setCompareMatch(Timer_ID Timer_num, uint16 Value)
{
	/* Set the compare match value for the specified timer */
	switch(Timer_num)
	{
		case TIMER0:
			OCR0 = Value; /* Set the compare match value for TIMER0 */
			break;

		case TIMER1:
			/* Check the mode of TIMER1 and set the compare match value accordingly */
			if (Timer1_Mode == TIMER1_CTC_OCR)
			{
				OCR1A = Value; /* Set the compare match value for TIMER1 in CTC mode with OCR1A */
			}
			else if (Timer1_Mode == TIMER1_CTC_ICR)
			{
				ICR1 = Value; /* Set the compare match value for TIMER1 in CTC mode with ICR1 Reg*/
			}
			break;

		case TIMER2:
			OCR2 = Value; /* Set the compare match value for TIMER2 */
			break;

		default:
			/* Wrong Timer Num: Invalid timer number specified */
			break;
	}
}
/**
 * This function sets a callback function for the specified timer.
 *
 * @param[in]  Timer_num     Type Timer_ID     Range TIMER0, TIMER1, TIMER2
 * @param[in]  copy_ptr      Type pointer to function   Range Any function pointer
 * @return None
 */
void TIMER_setCallBack(Timer_ID Timer_num , void (*copy_ptr)(void))
{
	/* Set the callback function for the specified timer */
	switch(Timer_num)
	{
		case TIMER0:
			TIMER0_PtrCallBack = copy_ptr; /* Set the callback function for TIMER0 */
			break;
		case TIMER1:
			TIMER1_PtrCallBack = copy_ptr; /* Set the callback function for TIMER1 */
			break;
		case TIMER2:
			TIMER2_PtrCallBack = copy_ptr; /* Set the callback function for TIMER2 */
			break;
		default :
	  		/* Wrong Timer Num: Invalid timer number specified */
			break;
	}
}

/**
 * This function deinitializes the specified timer.
 *
 * @param[in]  Timer_num     Type Timer_ID     Range TIMER0, TIMER1, TIMER2
 * @return None
 */
void TIMER_deInit(Timer_ID Timer_num)
{
	/* Deinitialize the specified timer */
	switch(Timer_num)
	{
		case TIMER0:
			TCCR0 = 0;     /* Reset TIMER0 control register */
			TIMSK &= 0xFC; /* Disable TIMER0 interrupts */
			break;

		case TIMER1:
			TCCR1A = 0;    /* Reset TIMER1 control register A */
			TCCR1B = 0;    /* Reset TIMER1 control register B */
			TIMSK &= 0xC3; /* Disable TIMER1 interrupts */
			break;

		case TIMER2:
			TCCR2 = 0;     /* Reset TIMER2 control register */
			TIMSK &= 0x3F; /* Disable TIMER2 interrupts */
			break;

		default:
			/* Wrong Timer Num: Invalid timer number specified */
			break;
	}
}
/* ===================================================================================================
									   	   	  Timer 0
   ===================================================================================================*/

/**
 * This function sets the PWM duty cycle for TIMER0.
 *
 * @param[in]  DutyCycle   Type uint8     Range 0 to 100
 * @return None
 */
void TIMER0_setPwmDutyCycle(uint8 DutyCycle)
{
	/* Calculate and set the PWM duty cycle for TIMER0 */
	OCR0 = (float32)((float32)DutyCycle / 100) * 255;
}

/* ===================================================================================================
									   	   	  Timer 1
   ===================================================================================================*/

/**
 * This function sets the PWM duty cycle for TIMER1.
 *
 * @param[in]  DutyCycle   Type uint8     Range 0 to 100
 * @param[in]  Circuit     Type uint8     Range OCRA or OCRB
 * @return None
 */
void TIMER1_setPwmDutyCycle(uint8 DutyCycle, uint8 Circuit)
{
	/* Set the PWM duty cycle for TIMER1 based on the selected mode and circuit */
	if (Timer1_Mode == TIMER1_FAST_PWM_8BIT)
	{
		/* Set the PWM duty cycle for TIMER1 in 8-bit fast PWM mode */
		switch(Circuit)
		{
			case 1:
				OCR1A = (float32)((float32)DutyCycle / 100) * 255;
				break;
			case 2:
				OCR1B = (float32)((float32)DutyCycle / 100) * 255;
				break;
			default:
				/* Wrong Input: Invalid circuit specified */
				break;
		}
	}
	else if (Timer1_Mode == TIMER1_FAST_PWM_9BIT)
	{
		/* Set the PWM duty cycle for TIMER1 in 9-bit fast PWM mode */
		switch(Circuit)
		{
			case 1:
				OCR1A = (float32)((float32)DutyCycle / 100) * 511;
				break;
			case 2:
				OCR1B = (float32)((float32)DutyCycle / 100) * 511;
				break;
			default:
				/* Wrong Input: Invalid circuit specified */
				break;
		}
	}
	else if (Timer1_Mode == TIMER1_FAST_PWM_10BIT)
	{
		/* Set the PWM duty cycle for TIMER1 in 10-bit fast PWM mode */
		switch(Circuit)
		{
			case 1:
				OCR1A = (float32)((float32)DutyCycle / 100) * 1023;
				break;
			case 2:
				OCR1B = (float32)((float32)DutyCycle / 100) * 1023;
				break;
			default:
				/* Wrong Input: Invalid circuit specified */
				break;
		}
	}
	else if (Timer1_Mode == TIMER1_FAST_PWM_ICR)
	{
		/* Set the PWM duty cycle for TIMER1 in fast PWM mode with ICR as top value */
		ICR1 = 2499; /* Assuming 2500 as TOP value for ICR1 */
		OCR1A = DutyCycle; /* Set OCR1A with the provided duty cycle */
	}
	else if (Timer1_Mode == TIMER1_FAST_PWM_OCR)
	{
		/* Set the PWM duty cycle for TIMER1 in fast PWM mode with OCR1 as top value */
		OCR1A = 65535; /* Setting the maximum value for OCR1A */
		OCR1B = (float32)((float32)DutyCycle / 100) * 65535; /* Set OCR1B with the provided duty cycle */
	}
}
/* ===================================================================================================
									   	   	  Timer 2
   ===================================================================================================*/

/**
 * This function sets the PWM duty cycle for TIMER2.
 *
 * @param[in]  DutyCycle   Type uint8     Range 0 to 100
 * @return None
 */
void TIMER2_setPwmDutyCycle(uint8 DutyCycle)
{
	/* Calculate and set the PWM duty cycle for TIMER2 */
	OCR2 = (float32)((float32)DutyCycle / 100) * 255;
}
/* ===================================================================================================
									   	   	   ISR
   ===================================================================================================*/

/*TIMER2 COMP ISR*/
void __vector_4(void)
{

	if (TIMER2_PtrCallBack != NULL_PTR)
			{
			TIMER2_PtrCallBack();
			}
	else
			{
			/* Do Nothing */
			}
}
/*TIMER2 OVF ISR*/
void __vector_5(void)
{
		if (TIMER2_PtrCallBack != NULL_PTR)
		{
			TIMER2_PtrCallBack();
		}
		else
		{
			/* Do Nothing */
		}

}

/* TIMER1 COMPA ISR */
void __vector_7(void)
{
if (TIMER1_PtrCallBack != NULL_PTR)
			{
	TIMER1_PtrCallBack();
			}
			else
			{
			/* Do Nothing */
			}

}

/* TIMER1 COMPB ISR */
void __vector_8(void)
{
	TIMER1_PtrCallBack();
}

/*TIMER1 OVF ISR*/
void __vector_9(void)
{
	TIMER1_PtrCallBack();
}

/*TIMER0 COMP ISR*/
void __vector_10(void)
{
	if (TIMER0_PtrCallBack != NULL_PTR)
			{
	TIMER0_PtrCallBack();
			}
	else
			{
			/* Do Nothing */
			}
}

/* TIMER0 OVF ISR */
void __vector_11(void)
{

		if (TIMER0_PtrCallBack != NULL_PTR)
		{
			TIMER0_PtrCallBack();
		}
		else
		{
			/* Do Nothing */
		}
}

