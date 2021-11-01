/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the Ultrasonic Sensor HC-SR04 driver
 *
 * Author: Mina Nazieh
 *
 *******************************************************************************/

#include "std_types.h"
#include <util/delay.h>
#include "gpio.h"
#include "icu.h"
#include "Ultrasonic.h"

extern uint16 g_timeHigh;


/*
 * Description : Function to initialize the Ultrasonic driver
 * 	1. Initialize the ICU driver.
 * 	2. Setup the ICU call back function.
 * 	3. Setup the direction for the trigger pin as output pin through the GPIO driver

 */
void Ultrasonic_init(void)
{
	/*Setup the direction for the trigger pin as output pin through the GPIO driver*/
	GPIO_setupPinDirection(ultraTrigger_PORT, ultraTrigger_PIN, PIN_OUTPUT);
	/* Create configuration structure for ICU driver */
	Icu_ConfigType Icu_Config = {F_CPU_CLOCK,RISING};
	/* Set the Call back function pointer in the ICU driver */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	/* Initialize the ICU driver */
	Icu_init(&Icu_Config);
}
/*
 * Description: Function to send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ultraTrigger_PORT, ultraTrigger_PIN, LOGIC_HIGH);
	_delay_ms(15);
	GPIO_writePin(ultraTrigger_PORT, ultraTrigger_PIN, LOGIC_LOW);
}

/*
 * Description: Function to send the Trigger pulse to the ultrasonic.
 * 1. Send the trigger pulse by using Ultrasonic_Trigger function.
 * 2. Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	return g_timeHigh/58.8;
}
