// header : joystick.h

#ifndef JOYSTICK_H
#define JOYSTICK_H

/* HEADER BEGIN */
#include "stm32f0xx_hal.h"
/* HEADER END */

/* MACRO BEGIN */

/* MACRO END */

/* STRUCT & TYPE BEGIN */
typedef struct{
	uint8_t Upflag;
	uint8_t Downflag;
	uint8_t Rightflag;
	uint8_t Leftflag;
	uint8_t Centerflag;
}JoystickState;
/* STRUCT & TYPE END */

/* VARIABLES BEGIN */
extern JoystickState JoystickInfo;
extern uint32_t ADC_Val[2];
/* VARIABLES END */

/* FUNCTION BEGIN */
void CheckJoystick();
/* FUNCTION END */

#endif
