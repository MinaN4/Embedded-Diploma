/*
 ================================================================================================
 Name        : MC2.c
 Author      : Mina Nazieh
 Description : Main fuction for the second microcontroller
 Date        : 25/10/2021
 ================================================================================================
 */

#include "uart.h"
#include "twi.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "Buzzer.h"
#include "std_types.h"
#include "gpio.h"
#include "util/delay.h"
#include "timer0.h"
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define add_pass 55
#define rec_pass 66
#define get_pass 77
#define trigger_buzzer 88
#define stop_buzzer 89
#define motor_start 95
#define motor_cw 96
#define motor_acw 97
#define motor_stop 98
#define motor_finish 99
uint8 g_seconds;

int main(void)
{
	uint8 i=0;
	uint8 a_rec;
	uint8 a_readByte=0;
	uint8 a_pass[7];
	uint8 a_passCheck[7];

	/* Initialize the UART driver */
	UART_ConfigType uart_config = { _8Bit, Disabled, _1bit, 9600 };
	UART_init(&uart_config);
	/* Initialize the I2C driver */
	TWI_ConfigType twi_config = { 0x01, T_CPU_1 };
	TWI_init(&twi_config);
	/* Initialize Timer Configurations */
	Timer0_ConfigType timer_config = { normal,0, 255,F_CPU_256 };
	/* Initialize the Dc Motor driver */
	DcMotor_Init();
	/* Initialize the Buzzer driver */
	Buzzer_init();
	/*Enable global interrupts in MC.*/
	SREG  |= (1<<7);
	while(1)
    {
		a_rec=UART_recieveByte();
		if(a_rec==add_pass)//check request state
		{
			UART_receiveString(a_passCheck);
			i=0;
			while(a_passCheck[i] != '\0')
			{
				if(a_passCheck[i]>=0 && a_passCheck[i]<=9)
				{
					EEPROM_writeByte(0x0311 + i, a_passCheck[i]);
				}
				i++;
				_delay_ms(20);
			}
				UART_sendByte(rec_pass);//66=success
				_delay_ms(20);
				a_rec=0;
		}
		else if(a_rec==get_pass)//Retrieve pass
		{
			i = 0;
			while (a_passCheck[i] != '\0')
			{
				EEPROM_readByte(0x0311 + i, &a_readByte);
				_delay_ms(20);
				if (a_readByte >= 0 && a_readByte <= 9) {
					a_pass[i] = a_readByte;
				}
				i++;
			}
			a_pass[i]='#';
			UART_sendString(a_pass);
			_delay_ms(20);
			a_rec=0;
		}
		else if(a_rec==trigger_buzzer)
		{
			g_seconds=0;
			Buzzer_on();
			Timer0_setCallBack(Timer0_deInit);
			Timer0_Init(&timer_config);
			while(g_seconds!=60){}
			g_seconds=0;
			Buzzer_off();
			UART_sendByte(stop_buzzer);
		}
		else if (a_rec == motor_start) {
			Timer0_setCallBack(Timer0_deInit);
			DcMotor_Rotate(DC_MOTOR_CW);//unlocking
			UART_sendByte(motor_cw);
			Timer0_Init(&timer_config);
			while (g_seconds != 15) {}
			g_seconds = 0;

			DcMotor_Rotate(DC_MOTOR_STOP);//hold
			UART_sendByte(motor_stop);
			Timer0_Init(&timer_config);
			while (g_seconds != 3) {}
			g_seconds = 0;

			DcMotor_Rotate(DC_MOTOR_ACW);//locking
			UART_sendByte(motor_acw);
			Timer0_Init(&timer_config);
			while (g_seconds != 15) {}
			g_seconds = 0;

			DcMotor_Rotate(DC_MOTOR_STOP);
			UART_sendByte(motor_finish);//finish
			a_rec=0;
		}
    }
}


