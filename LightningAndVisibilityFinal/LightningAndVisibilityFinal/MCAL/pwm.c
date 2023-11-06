/******************************************************************************************************
File Name	: pwm.c
Author		: Mhoss
Description : source file for the PWM driver
*******************************************************************************************************/

#include <avr/io.h>
#include "pwm.h"
#include "gpio.h"

/*
 * Description :
 * Function responsible to calculate the ON_time of PWM with the duty cycle.
 * FAST PWM mode (WGM01 = 1, WGM00 = 1)
 * Non-Inverting  Clear OC0 On Compare ( COM01 = 1 )
 * Pre-scalar = 8 ( CS01 = 1 )
 */
void PWM_Timer2_Start(uint8 duty_cycle)
{
	GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
	uint8 ON_time = (uint8)((uint16)(PWM_MAX_VALUE * duty_cycle ) / 100);
	TCNT2 = 0;
	OCR2 = ON_time;
	TCCR2 = (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<CS21);		/* Non- Inverting Fast PWM ( Prescalar = 8 ) */
}
