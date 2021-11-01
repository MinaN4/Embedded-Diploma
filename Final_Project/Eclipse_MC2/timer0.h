 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: timer0.h
 *
 * Description: Header file for the Timer0 AVR driver
 *
 * Author: Mina Nazieh
 *
 *******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_
#include "std_types.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define NUMBER_OF_COMPARE_MTACHES_PER_SECOND 4
#define NUMBER_OF_OVERFLOWS_PER_SECOND 123
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	normal,compare
}Timer0_Mode;

typedef enum{
	No_Clock,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,External_Fall,External_Rise
}Timer0_Prescale;

typedef struct{
	Timer0_Mode mode;
	uint16 init_value;
	uint16 compare_value;
	Timer0_Prescale prescale;
}Timer0_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Timer0_Init(const Timer0_ConfigType * Config_Ptr);
void Timer0_deInit(void);
void Timer_init_Normal_Mode(void);
void Timer0_Init_CTC_Mode(unsigned char tick);
void Timer0_setCallBack(void(*a_ptr)(void));

#endif /* TIMER0_H_ */
