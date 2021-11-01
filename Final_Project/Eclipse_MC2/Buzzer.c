 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Mina Nazieh
 *
 *******************************************************************************/
#include "gpio.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Initialize the Buzzer
 */
void Buzzer_init(void)
{
	/*BUZZER*/
	GPIO_setupPinDirection(PORTC_ID, PIN6_ID, PIN_OUTPUT); /* All PORTD pins are o/p pins */
}
/*
 * Description :
 * Turn on the buzzer
 */
void Buzzer_on(void)
{
	GPIO_writePin(PORTC_ID,PIN6_ID,1);
}
/*
 * Description :
 * Turn off the buzzer
 */
void Buzzer_off(void)
{
	GPIO_writePin(PORTC_ID,PIN6_ID,0);
}
