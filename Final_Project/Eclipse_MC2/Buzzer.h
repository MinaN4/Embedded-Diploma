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

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Buzzer_PinNumber PIN6_ID
#define Buzzer_PortNumber PORTC_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Buzzer
 */
void Buzzer_init(void);
/*
 * Description :
 * Turn on the buzzer
 */
void Buzzer_on(void);
/*
 * Description :
 * Turn off the buzzer
 */
void Buzzer_off(void);
#endif /* BUZZER_H_ */
