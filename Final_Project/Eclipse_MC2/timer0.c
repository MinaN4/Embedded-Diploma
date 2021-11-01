/******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Source file for the Timer0 AVR driver
 *
 * Author: Mina Nazieh
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0.h"
#include "Buzzer.h"
/*Extern g_seconds from MC2.c file*/
extern uint8 g_seconds;
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/* global variable contain the ticks count of the comapare timer */
unsigned char g_tick_compare = 0;


/* global variable contain the ticks count of the normal timer */
unsigned char g_tick_normal=0;

/* Interrupt Service Routine for timer0 normal mode */
ISR(TIMER0_OVF_vect)
{
	g_tick_normal++;
	if(g_tick_normal == NUMBER_OF_OVERFLOWS_PER_SECOND)
	{
		g_tick_normal=0;
		g_seconds++;
	}
}
/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
	g_tick_compare++;
	if(g_tick_compare == NUMBER_OF_COMPARE_MTACHES_PER_SECOND)
	{
		g_tick_compare = 0;
		g_seconds++;
	}
}
void Timer0_Init(const Timer0_ConfigType * Config_Ptr)
{
	if(Config_Ptr->mode==normal)
	{
		TCNT0 =  Config_Ptr->init_value; // Set Timer initial value to 0
		TIMSK = (1 << TOIE0); // Enable Timer0 Overflow Interrupt
		/* configure the timer
		 * 1. Non PWM mode FOC0=1
		 * 2. Normal Mode WGM01=0 & WGM00=0
		 * 3. Normal Mode COM00=0 & COM01=0
		 * 4. clock = F_CPU/256 CS00=0 CS01=0 CS02=1
		 */
		TCCR0 = (1 << FOC0) | (Config_Ptr->prescale);
	}
	else if(Config_Ptr->mode==compare)
	{
		TCNT0 = Config_Ptr->init_value;    // Set Timer initial value to 0
		OCR0 = Config_Ptr->compare_value; // Set Compare Value
		TIMSK |= (1 << OCIE0); // Enable Timer0 Compare Interrupt
		/* Configure timer0 control register
		 * 1. Non PWM mode FOC0=1
		 * 2. CTC Mode WGM01=1 & WGM00=0
		 * 3. No need for OC0 in this example so COM00=0 & COM01=0
		 */
		TCCR0 = (1 << FOC0) | (1 << WGM01) | (Config_Ptr->prescale);
	}
}
void Timer0_deInit(void)
{
	TCCR0=0;//// Enable Timer0
	TIMSK=0;// Disable Timer0 Overflow Interrupt
}

