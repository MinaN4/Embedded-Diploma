/*
 * main.c
 *
 *  Created on: Aug 15, 2021
 *      Author: minanazieh
 */


#include <stdlib.h>
#include <stdio.h>

int vehicle_speed=0,_RoomTemperature=35,_EngineTemperature=90;
char *_engineState="OFF",*_AC="OFF",*_EngineTempController="OFF";

#define WITH_ENGINE_TEMP_CONTROLLER 1

void vehicle_state(void);
char SensorsSet(void);
void TrafficLight(void);
void RoomTemp(void);
void EngineTemp(void);

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char input1='b';
	while(input1!='c')
	{
		//Requirement 1
		printf("a. Turn on the vehicle engine\n");//1-a
		printf("b. Turn off the vehicle engine\n");//1-b
		printf("c. Quit the system\n");//1-c
		scanf(" %c",&input1);

		if(input1=='c')
		{
			printf("Quitting the system...\n");
			return 0;
		}
		else if(input1 =='a')
		{
			printf("Turning on the vehicle engine\n");
			_engineState="ON";
			while(_engineState=="ON")
			{
				//Requirement 5
				//sensors set menu
				char sensors_state=SensorsSet();
				//Requirement 7
				if(sensors_state=='a')
				{
					printf("Turning off the engine\n");
					_engineState="OFF";
					break;
				}
				else if(sensors_state=='b') //7-a
				{
					TrafficLight();
				}
				else if(sensors_state=='c')//7-b
				{
					//room temperature
					RoomTemp();

				}
#if WITH_ENGINE_TEMP_CONTROLLER
				else if(sensors_state=='d')//7-c
				{
					//engine temperature
					EngineTemp();

				}
#endif
				else{printf("!!! Please enter a valid input \n");}
				if(vehicle_speed==30)//7-d
				{
					if(_AC=="OFF")
					{_AC="ON";
					_RoomTemperature*=(5/4)+1;
					}
#if WITH_ENGINE_TEMP_CONTROLLER
					if(_EngineTempController=="OFF")
					{
						_EngineTempController="ON";
						_EngineTemperature*=(5/4)+1;
					}
#endif
				}
				vehicle_state();
			}

		}
		else if(input1=='b')
		{
			printf("Turning off the vehicle engine.....\n");
		}
		else{printf("!!! Please enter a valid input \n");}
	}
}

void vehicle_state(void)
{
	//7-e
	printf("***************************** \n");
	printf("current vehicle state \n");
	printf("............................. \n");
	printf("Engine state %s\n",_engineState);
	printf("AC %s\n",_AC);
	printf("vehicle speed %d km/hr\n",vehicle_speed);
	printf("Room Temperature %d C\n",_RoomTemperature);
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("Engine Temperature Controller State %s\n",_EngineTempController);
	printf("Engine Temperature %d C\n",_EngineTemperature);
#endif
	printf("***************************** \n");
}
char SensorsSet(void)
{
	char input2;
	printf("Sensors set menu\n");
	printf("a. Turn off the engine\n");//5-a
	printf("b. Set the traffic light color\n");//5-b
	printf("c. Set the room temperature\n");//5-c
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature\n");//5-d
#endif
	scanf(" %c",&input2);
	return input2;
}
void TrafficLight(void)
{
	printf("Setting the traffic light color\n");
	printf("Choose the traffic light state : G,O,R \n");
	char input3;
	scanf(" %c",&input3);
	if(input3=='G'||input3=='g')
	{
		vehicle_speed=100;
	}
	else if(input3=='O'||input3=='o')
	{
		vehicle_speed=30;
	}
	else if(input3=='R'||input3=='r')
	{
		vehicle_speed=0;
	}
}
void RoomTemp(void)
{
	printf("Setting the room temperature\n");
	printf("Enter the room temperature : \n");
	int input4;
	scanf(" %d",&input4);
	if(input4<10)
	{
		_AC="ON";
		_RoomTemperature=20;
	}
	else if(input4>30)
	{
		_AC="ON";
		_RoomTemperature=20;
	}
	else {
		_AC="OFF";
		_RoomTemperature=input4;
	}
}
void EngineTemp(void)
{
	printf("Setting the engine temperature\n");
	printf("Enter the engine temperature : \n");
	int input5;
	scanf(" %d",&input5);
	if(input5<100)
	{
		_EngineTempController="ON";
		_EngineTemperature=125;
	}
	else if(input5>150)
	{
		_EngineTempController="ON";
		_EngineTemperature=125;
	}
	else
	{
		_EngineTempController="OFF";
		_EngineTemperature=input5;
	}
}

