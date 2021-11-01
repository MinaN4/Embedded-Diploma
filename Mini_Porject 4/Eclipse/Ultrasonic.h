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

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"
#include "gpio.h"

#define ultraTrigger_PIN 	PIN5_ID
#define ultraTrigger_PORT	PORTB_ID
#define ultraEcho_PIN		PIN6_ID
#define ultraEcho_PORT		PORTD_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
