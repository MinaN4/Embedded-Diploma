#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "DcMotor.h"
#include "PWM_Timer0.h"
#include <util/delay.h>
#include "gpio.h"
#include "std_types.h"
int main(void)
{
	uint8 temp;
	ADC_ConfigType *config;
	config->ref_volt=2.56;
	config->prescaler=8;
	ADC_init(config);
	LCD_init();
	LCD_moveCursor(0,3);
	LCD_displayString("Fan is ");
	LCD_sendCommand(0xC0);
	LCD_moveCursor(1,3);
	LCD_displayString("Temp =    C");
	DcMotor_Init();
    while(1)
    {
    	temp = LM35_getTemperature();
    	if(temp<30)
    	{
    		DcMotor_Rotate(STOP,0);
    		LCD_sendCommand(0x80);
    		LCD_moveCursor(0,10);
    		LCD_displayString("OFF");
    	}
    	else if(temp >=120)
    	{
    		DcMotor_Rotate(ACW,100);
    		LCD_sendCommand(0x80);
    		LCD_moveCursor(0,10);
    		LCD_displayString("ONN");
    	}
    	else if(temp >=90)
    	{
    		DcMotor_Rotate(ACW,75);
    		LCD_sendCommand(0x80);
    		LCD_moveCursor(0,10);
    		LCD_displayString("ONN");
    	}
    	else if(temp >=60)
    	{
    		DcMotor_Rotate(ACW,50);
    		LCD_sendCommand(0x80);
    		LCD_moveCursor(0,10);
    		LCD_displayString("ONN");
    	}
    	else if(temp >=30)
    	{
    		DcMotor_Rotate(ACW,25);
    		LCD_sendCommand(0x80);
    		LCD_moveCursor(0,10);
    		LCD_displayString("ONN");
    	}
    	if(temp >= 100)
    	{
    		LCD_sendCommand(0xC0);
    		LCD_moveCursor(1,10);
   			LCD_intgerToString(temp);
  		}
    	else
    	{
    		LCD_sendCommand(0xC0);
    		LCD_moveCursor(1,10);
    		LCD_intgerToString(temp);
    		/* In case the digital value is two or one digits print space in the next digit place */
    		LCD_displayCharacter(' ');
    	}

    }
}
