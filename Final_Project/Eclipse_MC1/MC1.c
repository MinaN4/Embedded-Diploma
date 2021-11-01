/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mina Nazieh
 Description : Main fuction for the first microcontroller
 Date        : 25/10/2021
 ================================================================================================
 */

#include "keypad.h"
#include "uart.h"
#include <util/delay.h> /* For the delay functions */
#include "std_types.h"
#include "string.h"
#include "lcd.h"
#include <stdio.h>
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

void enter_password(uint8 *Str, uint8 *Str2);
void get_password(uint8 *Str);


int main(void) {
	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_ConfigType uart_config={_8Bit,Disabled,_1bit,9600};
	UART_init(&uart_config);
	LCD_init();
	uint8 state = 1;

	while (1) {
		if (state == 1) //enter new password
				{
			uint8 a_pass[7];
			uint8 a_pass2[7];
			uint8 a_pass3[7];
			uint8 a_rec;
			enter_password(a_pass, "Enter new pass");
			LCD_clearScreen();
			enter_password(a_pass2, "Re-enter pass");
			LCD_clearScreen();
			if (strcmp(a_pass, a_pass2) == 0) //Match
					{
				UART_sendByte(add_pass); //anounnce state to mc2
				strcpy(a_pass3, a_pass);
				LCD_displayString("Match");
				UART_sendString(a_pass3);
				_delay_ms(10);
				a_rec = UART_recieveByte();
				LCD_displayString("s");
				if (a_rec == rec_pass)
				{
					LCD_clearScreen();
					LCD_displayString("Saved");
					_delay_ms(500);
					LCD_clearScreen();
					state = 2;
				}
			} else //Not match
			{
				LCD_displayString("Not-Match");
				_delay_ms(500);
				LCD_clearScreen();
				state = 1; //repeat state 0
			}
		}
		else if(state==2)// choose to open door or change pass
		{
			uint8 count_false=1;
			uint8 pass_state=0;//0->not-match 1->match
			uint8 a_pass[7];
			uint8 a_pass2[7];
			uint8 a_key_num2=0;
			/*
			 * while the choice not equal to '+' or '-'
			 * wait in the menu display for the
			 * right user input
			*/
			while((a_key_num2!='+') && (a_key_num2!='-'))
			{
				LCD_clearScreen();
				LCD_displayString("+ : open door");
				LCD_moveCursor(1, 0);
				LCD_displayString("- : change pass");
				LCD_moveCursor(0, 0);
				a_key_num2 = KEYPAD_getPressedKey();
				_delay_ms(400);
			}
			get_password(a_pass);
			enter_password(a_pass2, "Enter pass");
			_delay_ms(400);
			while(!pass_state){
				if (strcmp(a_pass, a_pass2) == 0) {
					pass_state=1;
					if (a_key_num2 == '+') {
						state = 3;
					} else if (a_key_num2 == '-') {
						LCD_clearScreen();
						LCD_displayString("Changing password");
						state = 1;
					}
				} else {
					count_false++;
					LCD_clearScreen();
					enter_password(a_pass2, "Enter pass again");
					_delay_ms(400);
				}
				if (count_false == 3) {/*trigger buzzer*/
					uint8 buzzer_byte=0;
					LCD_clearScreen();
					LCD_displayString("Error->Buzzer");
					UART_sendByte(trigger_buzzer);
					while(buzzer_byte!=stop_buzzer){
						buzzer_byte=UART_recieveByte();
					}
					count_false=0;
				}
			}
		}
		else if (state == 3) //Opening door
		{
			UART_sendByte(motor_start);
			uint8 door_byte=0;
			while(1){
				door_byte=UART_recieveByte();
				if(door_byte==motor_cw)
				{
					door_byte=0;
					LCD_clearScreen();
					LCD_displayString("Unlocking Door");
				}
				else if(door_byte==motor_stop)
				{
					door_byte=0;
					LCD_clearScreen();
					LCD_displayString("Holding Door");
				}
				else if(door_byte==motor_acw)
				{
					door_byte=0;
					LCD_clearScreen();
					LCD_displayString("Locking Door");
				}
				else if(door_byte==motor_finish)
				{
					LCD_clearScreen();
					LCD_displayString("Door closed");
					door_byte=0;
					state=2;//return to menu
					_delay_ms(500);
					break;
				}

			}
		}
	}
}
/*
 * Description :
 * 1.Display command on LCD
 * 2.Retrieve password entered from the user
 */
void enter_password(uint8 *Str, uint8 *Str2) {
	LCD_clearScreen();
	LCD_displayString(Str2);
	uint8 i = 0;
	uint8 a_key_num;
	LCD_moveCursor(1, 0);
	a_key_num = KEYPAD_getPressedKey();
	_delay_ms(400);
	while (a_key_num != 61) {
		Str[i] = a_key_num;
		i++;
		LCD_intgerToString(a_key_num);
		a_key_num = KEYPAD_getPressedKey();
		_delay_ms(400);
	}
	Str[i] = '#';
	LCD_moveCursor(0, 0);
}
/*
 * Description :
 * 1.Get the password saved in eeprom from mc2
 */
void get_password(uint8 *Str){
	UART_sendByte(get_pass); //anounnce state to mc2
	UART_receiveString(Str);
	uint8 i = 0;
	while (Str[i] != '\0') {
		i++;
	}
	Str[i]='#';
}

