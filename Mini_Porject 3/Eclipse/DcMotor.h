/*
 * DcMotor.h
 *
 *  Created on: Oct 5, 2021
 *      Author: minanazieh
 */
#include "std_types.h"

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

typedef enum
{
	CW,ACW,STOP
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
