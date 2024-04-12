// header : scheduling.h

#include "scheduling.h"

/* VARIABLES BEGIN */
SchedulingFlag SchedulInfo;
uint32_t cnt1ms = 0;
int32_t airAutoDir = 1;
/* VARIABLES END */

void Scheduling_Init(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Start_IT(htim);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM3) /* 1s */
  {
	  cnt1ms++;

	  if((cnt1ms % 1) == 0)
	  {
		  SchedulInfo.ms1Flag = 1;
	  }
	  if((cnt1ms % 10) == 0)
	  {
		  SchedulInfo.ms10Flag = 1;
	  }
	  if((cnt1ms % 100) == 0)
	  {
		  SchedulInfo.ms100Flag = 1;
	  }
	  if((cnt1ms % 150) == 0)
	  {
		  SchedulInfo.ms150Flag = 1;
	  }
	  if((cnt1ms % 1000) == 0)
	  {
		  SchedulInfo.ms1000Flag = 1;
	  }
  }
}

void TaskScheduling()
{
	if(SchedulInfo.ms1Flag)
	{
		Task1ms();
		SchedulInfo.ms1Flag = 0;
	}
	if(SchedulInfo.ms10Flag)
	{
		Task10ms();
		SchedulInfo.ms10Flag = 0;
	}
	if(SchedulInfo.ms100Flag)
	{
		Task100ms();
		SchedulInfo.ms100Flag = 0;
	}
	if(SchedulInfo.ms150Flag)
	{
		Task150ms();
		SchedulInfo.ms150Flag = 0;
	}
	if(SchedulInfo.ms1000Flag)
	{
		Task1000ms();
		SchedulInfo.ms1000Flag = 0;
	}
}

void Task1ms()
{
	if(FlagInfo.Key_On_Flag == 1)
	{
		if(FlagInfo.Air_Dir_Flag && FlagInfo.Air_Speed_Flag && FlagInfo.Seat_RightLeft_Flag && FlagInfo.Seat_UpDown_Flag)
		{
			if(DataInfo.Air_Speed_Data == 0 && DataInfo.Air_Dir_Data == 0 && DataInfo.Seat_UpDown_Data == 0 && DataInfo.Seat_RightLeft_Data == 0)
			{
				DataInfo.Air_Dir_Data 			= AIRDIR;
				DataInfo.Air_Speed_Data			= AIRSPEED;
				DataInfo.Seat_UpDown_Data		= SEATUPDOWN;
				DataInfo.Seat_RightLeft_Data	= SEATRIGHTLEFT;
				DataInfo.Seat_Rotate_Data 		= SEATROTATE;
			}
			DataInfo.Seat_Rotate_Data = 45;
			ServoAngleChange(&htim2, TIM_CHANNEL_1, DataInfo.Air_Speed_Data);
			ServoAngleChange(&htim1, TIM_CHANNEL_4, DataInfo.Air_Dir_Data);
			ServoAngleChange(&htim1, TIM_CHANNEL_1, DataInfo.Seat_UpDown_Data);
			ServoAngleChange(&htim1, TIM_CHANNEL_3, DataInfo.Seat_RightLeft_Data);
			ServoAngleChange(&htim1, TIM_CHANNEL_2, DataInfo.Seat_Rotate_Data); // seat rotate

			//clear flag
			FlagInfo.Air_Dir_Flag = 0;
			FlagInfo.Air_Speed_Flag = 0;
			FlagInfo.Seat_RightLeft_Flag = 0;
			FlagInfo.Seat_UpDown_Flag = 0;


			FlagInfo.SeatWatting_Flag = 1;
			FlagInfo.Key_On_Flag = 0;
		}
	}

	if(FlagInfo.Key_Off_Flag == 1)
	{
		if(FlagInfo.Run_Flag == 1)
		{
			Comm_UartWrite('A', 'H', DataInfo.Air_Dir_Data);
			HAL_Delay(100);
			Comm_UartWrite('A', 'L', DataInfo.Air_Speed_Data);
			HAL_Delay(100);
			Comm_UartWrite('C', 'H', DataInfo.Seat_UpDown_Data);
			HAL_Delay(100);
			Comm_UartWrite('C', 'L', DataInfo.Seat_RightLeft_Data);
		}

		OffFND();

		DataInfo.Air_Dir_Data 			= AIRDIR;
		DataInfo.Air_Speed_Data			= AIRSPEED;
		DataInfo.Seat_UpDown_Data		= SEATUPDOWN;
		DataInfo.Seat_RightLeft_Data	= SEATRIGHTLEFT;
		DataInfo.Seat_Rotate_Data 		= SEATROTATE;

		ServoAngleChange(&htim2, TIM_CHANNEL_1, DataInfo.Air_Speed_Data);
		ServoAngleChange(&htim1, TIM_CHANNEL_4, DataInfo.Air_Dir_Data);
		ServoAngleChange(&htim1, TIM_CHANNEL_1, DataInfo.Seat_UpDown_Data);
		ServoAngleChange(&htim1, TIM_CHANNEL_3, DataInfo.Seat_RightLeft_Data);
		ServoAngleChange(&htim1, TIM_CHANNEL_2, DataInfo.Seat_Rotate_Data);

		FlagInfo.Key_Off_Flag = 0;
		FlagInfo.SeatWatting_Flag = 0;
		FlagInfo.Run_Flag = 0;

		SeatTurn.Pushflag = 0;
		JoyStick.Pushflag = 0;
		AirAuto.Pushflag  = 0;
	}

}

void Task10ms()
{
	if(FlagInfo.Run_Flag == 1)
	{
		ReadButton();
	}

	if(FlagInfo.SeatWatting_Flag == 1)
	{
		Sonic_Read();
		SonicData += CheckSonicClose();
	}

	if((JoystickInfo.Upflag == 1 || JoystickInfo.Downflag == 1) && JoyStick.Pushflag == 1)
	{
		AirAuto.Pushflag = 0;
	}
}

void Task100ms()
{
	//TestProtocol();

	if(FlagInfo.Run_Flag == 1)
	{
		ADC_read(ADC_Val, 2);
		CheckJoystick();
	}

	if(FlagInfo.Run_Flag == 1)
	{
		if(AirAuto.Pushflag == 1)
		{
			if(DataInfo.Air_Dir_Data <= 40)
			{
				airAutoDir = +1;
			}
			else if(DataInfo.Air_Dir_Data >= 140)
			{
				airAutoDir = -1;
			}

			DataInfo.Air_Dir_Data += 10 * airAutoDir;
			ServoAngleChange(&htim1, TIM_CHANNEL_4, DataInfo.Air_Dir_Data);
		}
	}

}

void Task150ms()
{
	if(FlagInfo.Run_Flag == 1)
	{
		if(JoyStick.Pushflag == 0) //note : 0 is seat control mode
		{
			if(JoystickInfo.Upflag)
			{
				if(DataInfo.Seat_UpDown_Data >= 180);
				else
				{
					DataInfo.Seat_UpDown_Data		+= 10;
				}
			}
			else if(JoystickInfo.Downflag)
			{
				if(DataInfo.Seat_UpDown_Data <= 0);
				else
				{
					DataInfo.Seat_UpDown_Data		-= 10;
				}
			}
			else if(JoystickInfo.Rightflag)
			{
				if(DataInfo.Seat_RightLeft_Data <= 30);
				else
				{
					DataInfo.Seat_RightLeft_Data	-= 10;
				}
			}
			else if(JoystickInfo.Leftflag)
			{
				if(DataInfo.Seat_RightLeft_Data >= 100);
				else
				{
					DataInfo.Seat_RightLeft_Data	+= 10;
				}
			}
			else;
		}
		else if(JoyStick.Pushflag == 1)
		{
			if(JoystickInfo.Downflag)
			{
				if(DataInfo.Air_Dir_Data <= 40);
				else
				{
					DataInfo.Air_Dir_Data		-= 10;
				}
			}
			else if(JoystickInfo.Upflag)
			{
				if(DataInfo.Air_Dir_Data >= 140);
				else
				{
					DataInfo.Air_Dir_Data		+= 10;
				}
			}
			else if(JoystickInfo.Leftflag)
			{
				if(DataInfo.Air_Speed_Data <= 10);
				else
				{
					DataInfo.Air_Speed_Data	-= 10;
				}
			}
			else if(JoystickInfo.Rightflag)
			{
				if(DataInfo.Air_Speed_Data >= 90);
				else
				{
					DataInfo.Air_Speed_Data	+= 10;
				}
			}
			else;
		}

		//set motor
		ServoAngleChange(&htim2, TIM_CHANNEL_1, DataInfo.Air_Speed_Data);
		ServoAngleChange(&htim1, TIM_CHANNEL_4, DataInfo.Air_Dir_Data);
		ServoAngleChange(&htim1, TIM_CHANNEL_1, DataInfo.Seat_UpDown_Data);
		ServoAngleChange(&htim1, TIM_CHANNEL_3, DataInfo.Seat_RightLeft_Data);
	}

}

void Task1000ms()
{
	if(FlagInfo.SeatWatting_Flag == 1)
	{
		if(SonicData > 80)
		{
			FlagInfo.SeatWatting_Flag = 0;
			FlagInfo.Run_Flag = 1;

			DataInfo.Seat_Rotate_Data = SEATROTATE;
			ServoAngleChange(&htim1, TIM_CHANNEL_2, DataInfo.Seat_Rotate_Data); // seat rotate
		}
		SonicData = 0;
	}

	if(SeatTurn.Pushflag == 1)
	{
		if(DataInfo.Seat_Rotate_Data == 180)
		{
			DataInfo.Seat_Rotate_Data 		= SEATROTATE;
			ServoAngleChange(&htim1, TIM_CHANNEL_2, DataInfo.Seat_Rotate_Data);
		}
		else
		{
			DataInfo.Seat_Rotate_Data 		= 180;
			ServoAngleChange(&htim1, TIM_CHANNEL_2, DataInfo.Seat_Rotate_Data);
		}

		SeatTurn.Pushflag = 0;
	}



	//uint8_t buffer[256];
	//sprintf((char *)buffer, "%d		%d	     \n", ADC_Val[0], ADC_Val[1]);
	//HAL_UART_Transmit(&huart1, buffer, strlen((char *)buffer), 100);
}
