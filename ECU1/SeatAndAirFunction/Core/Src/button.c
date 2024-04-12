// header : button.h

#include "button.h"

/* VARIABLES BEGIN */
ButtonState JoyStick;
ButtonState SeatTurn;
ButtonState AirAuto;
/* VARIABLES END */


void ReadButton()
{
	JoyStick.cur = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
	SeatTurn.cur = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
	AirAuto.cur = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);

	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0 && JoyStick.bef == 1)
	{
		JoyStick.Pushflag ^= 1;
	}
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 1 && SeatTurn.bef == 0)
	{
		SeatTurn.Pushflag = 1;
	}
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1 && AirAuto.bef == 0)
	{
		AirAuto.Pushflag ^= 1;
	}
	JoyStick.bef = JoyStick.cur;
	SeatTurn.bef = SeatTurn.cur;
	AirAuto.bef = AirAuto.cur;
}


