#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void Buttons_Init(void);
void Interrupts_Init(void);
void _7segments_Init(void);
void Timer1_Init(void);
unsigned char _flag=0; //0=run/resume,1=pause,2=reset

#define r_sec1 0
#define r_sec2 1
#define r_min1 2
#define r_min2 3
#define r_hr1 4
#define r_hr2 5
struct student
{
    unsigned char sec1; //PA0
	unsigned char sec2; //PA1
	unsigned char min1; //PA2
	unsigned char min2; //PA3
	unsigned char hr1;  //PA4
	unsigned char hr2;  //PA5
}_clock;

ISR(INT0_vect)
{
	_flag=2;//reset
}
ISR(INT1_vect)
{
	_flag=1;//pause
}
ISR(INT2_vect)
{
	_flag=0;//resume
}
ISR(TIMER1_COMPA_vect)
{
	if(_flag != 1)
	{
		_flag=0;
		_clock.sec1 ++;
	}
}
void clock_update(void)
{
	_delay_ms(3);
	PORTA =(1<<r_sec1);
	PORTC=(PORTC&0xF0)|(_clock.sec1 &0x0F);
	_delay_ms(3);
	PORTA =(1<<r_sec2);
	PORTC=(PORTC&0xF0)|(_clock.sec2 &0x0F);
	_delay_ms(3);
	PORTA =(1<<r_min1);
	PORTC=(PORTC&0xF0)|(_clock.min1 &0x0F);
	_delay_ms(3);
	PORTA =(1<<r_min2);
	PORTC=(PORTC&0xF0)|(_clock.min2 &0x0F);
	_delay_ms(3);
	PORTA =(1<<r_hr1);
	PORTC=(PORTC&0xF0)|(_clock.hr1 &0x0F);
	_delay_ms(3);
	PORTA =(1<<r_hr2);
	PORTC=(PORTC&0xF0)|(_clock.hr2 &0x0F);
	_delay_ms(3);
}
void clock_counter(void)
{
	if(_clock.sec1==9)
	{
		_clock.sec2++;
		_clock.sec1=0;

	}
	if((_clock.sec2==6) && (_clock.sec1==0))
		{
			_clock.min1++;
			_clock.sec1=0,_clock.sec2=0;
		}
	if(_clock.min1==9)
			{
				_clock.min2++;
				_clock.min1=0;
			}
	if((_clock.min2==6) && (_clock.min1==0))
			{
				_clock.hr1++;
				_clock.min1=0,_clock.min2=0;
			}
	if(_clock.hr1==9)
				{
					_clock.hr2++;
					_clock.hr1=0;

				}
	if((_clock.hr2==2) &&(_clock.hr1==4))
	{
		_flag=1;
	}
}
int main(void)
{
	Buttons_Init();
	Timer1_Init();
	_7segments_Init();
	Interrupts_Init();
	_clock.sec1=0,_clock.sec2=0,_clock.min1=0,_clock.min2=0,_clock.hr1=0,_clock.hr2=0;
	while(1)
	{
		if(_flag==0) //run/resume
		{
			clock_counter();
			clock_update();
		}
		else if(_flag==1) //pause
		{

			clock_update();
		}
		else if(_flag==2) //reset
		{
			_clock.sec1=0,_clock.sec2=0,_clock.min1=0,_clock.min2=0,_clock.hr1=0,_clock.hr2=0;
			clock_update();
		}
	}
	return 0;
}

void Buttons_Init(void)
{
	//D2-reset-internal pull up-INT0-falling edge
	DDRD &=~(1<<2); //input pin-D
	PORTD |=(1<<2);//activate internal pull up
	//D3-Pause-external pull down-INT1-raising edge
	DDRD &=~(1<<3); //input pin-D
	//B2-Resume-INT2-internal pull up-falling edge
	DDRB &=~(1<<2); //input pin-D
	PORTB |=(1<<2);//activate internal pull up
}

void Interrupts_Init(void)
{

	MCUCR |=(1<<ISC01)|(1<<ISC11)|(1<<ISC10); //falling edge INT0 - rasing edge INT1
	MCUCSR &=~(1<<ISC2); //falling edge INT2
	GICR |=(1<<INT0)|(1<<INT1)|(1<<INT2); //enable interrupts modules
	SREG |=(1<<7);//enable I-bit
}

void _7segments_Init(void)
{
	DDRC |=0x0F; //PC0-PC1-PC2-PC3 => output pins to set value to display
	PORTC &= 0xF0;
	DDRA |=0x3F; //PA0-PA1-PA2-PA3-PA4-PA5 => enable/disable 7-segments from 1 to 6
}

void Timer1_Init(void)
{
	TCNT1 = 0;		// Set timer1 initial count to zero
	OCR1A = 1000;    // Set the Compare value
	TIMSK |= (1<<OCIE1A); // Enable Timer1 Compare A Interrupt
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12) | (1<<CS10)|(1<<CS12);
}
