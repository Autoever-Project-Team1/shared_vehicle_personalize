// header : joystick.h

#include "joystick.h"

/* VARIABLES BEGIN */
JoystickState JoystickInfo;
uint32_t ADC_Val[2] = {0,};
/* VARIABLES END */


void CheckJoystick()
{
	if((ADC_Val[1] == 0) && (ADC_Val[0] > 0))
	{
		JoystickInfo.Leftflag =  1;
		JoystickInfo.Rightflag = 0;
		JoystickInfo.Upflag = 	 0;
		JoystickInfo.Downflag =  0;
		JoystickInfo.Centerflag =0;
	}
	else if((ADC_Val[0] == 0) && (ADC_Val[1] > 0))
	{
		JoystickInfo.Leftflag =  0;
		JoystickInfo.Rightflag = 0;
		JoystickInfo.Upflag = 	 0;
		JoystickInfo.Downflag =  1;
		JoystickInfo.Centerflag =0;
	}
	else if((ADC_Val[0] > 1000) && (ADC_Val[1] > 4090))
	{
		JoystickInfo.Leftflag =  0;
		JoystickInfo.Rightflag = 1;
		JoystickInfo.Upflag = 	 0;
		JoystickInfo.Downflag =  0;
		JoystickInfo.Centerflag =0;
	}
	else if((ADC_Val[0] > 4090) && (ADC_Val[1] > 1000))
	{
		JoystickInfo.Leftflag =  0;
		JoystickInfo.Rightflag = 0;
		JoystickInfo.Upflag = 	 1;
		JoystickInfo.Downflag =  0;
		JoystickInfo.Centerflag =0;
	}
	else
	{
		JoystickInfo.Leftflag =  0;
		JoystickInfo.Rightflag = 0;
		JoystickInfo.Upflag = 	 0;
		JoystickInfo.Downflag =  0;
		JoystickInfo.Centerflag =  1;
	}
}


