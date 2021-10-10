/*
 * DcMotor.c
 *
 *  Created on: Oct 5, 2021
 *      Author: minanazieh
 */
#include <util/delay.h> /* For the delay functions */
#include "DcMotor.h"
#include "PWM_Timer0.h"
#include "gpio.h"
#include "std_types.h"

/*
 * Description :
 * Initialize the DC Motor:
 * 1. Setup the IN1 and IN2 directions by use the GPIO driver.
 * 2. Setup the motor in stop state
 */
void DcMotor_Init(void)
{
	/* configure pin PB0 and PB1 as output pins */
	GPIO_setupPinDirection(PORTB_ID, PIN0_ID, 1);
	GPIO_setupPinDirection(PORTB_ID, PIN1_ID, 1);
	/* Motor is stop at the beginning */
	GPIO_writePin(PORTB_ID, PIN0_ID, 0);
	GPIO_writePin(PORTB_ID, PIN1_ID, 0);

}
/*
 * Description :
 * Set the direction of rotation of the DC Motor:
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(speed<=100 || speed>=0)
	{
		PWM_Timer0_Start(speed);
	}
	// Rotate the motor --> clock wise
	if(state==1)
	{
		GPIO_writePin(PORTB_ID, PIN0_ID, 0);
		GPIO_writePin(PORTB_ID, PIN1_ID, 1);
	}
	// Rotate the motor --> anti-clock wise
	else if(state==2)
	{
		GPIO_writePin(PORTB_ID, PIN0_ID, 1);
		GPIO_writePin(PORTB_ID, PIN1_ID, 0);
	}
	// Stop the motor
	else //stop
	{
		GPIO_writePin(PORTB_ID, PIN0_ID, 0);
		GPIO_writePin(PORTB_ID, PIN1_ID, 0);
	}
}
