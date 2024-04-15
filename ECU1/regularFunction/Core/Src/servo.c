// header : servo.h
// note : Collection of servo motor related functions

#include "servo.h"

/* VARIABLES BEGIN */

/* VARIABLES END */


void Servo_Init(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  //note : Check the parameters
  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  //note : Set the TIM channel state
  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  //note : Enable the Capture compare channel
  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {
    /* Enable the main output */
    __HAL_TIM_MOE_ENABLE(htim);
  }

  __HAL_TIM_ENABLE(htim);
}

void ServoAngleChange(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t angle)
{
	uint32_t ccr = ServoAngleToCCR(angle);

	if(Channel == TIM_CHANNEL_1)
	{
		htim->Instance->CCR1 = ccr;
	}
	else if(Channel == TIM_CHANNEL_2)
	{
		htim->Instance->CCR2 = ccr;
	}
	else if(Channel == TIM_CHANNEL_3)
	{
		htim->Instance->CCR3 = ccr;
	}
	else if(Channel == TIM_CHANNEL_4)
	{
		htim->Instance->CCR4 = ccr;
	}
	else;
}

uint32_t ServoAngleToCCR(uint8_t angle)
{
	//note : 0~180 angle -> 20~120 CCR, convert
	if(angle > 180)
	{
		angle = 180;
	}
	return (uint32_t)(DEG0TOCCR + (angle * DEGGAIN));
}
