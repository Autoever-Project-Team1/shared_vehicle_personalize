// header : button.h

#ifndef BUTTON_H
#define BUTTON_H

/* HEADER BEGIN */
#include "stm32f0xx_hal.h"
#include "joystick.h"
/* HEADER END */

/* MACRO BEGIN */

/* MACRO END */

/* STRUCT & TYPE BEGIN */
typedef struct{
	uint8_t cur;
	uint8_t bef;
	uint8_t Pushflag;
}ButtonState;

/* STRUCT & TYPE END */

/* VARIABLES BEGIN */
extern ButtonState JoyStick;
extern ButtonState SeatTurn;
extern ButtonState AirAuto;
/* VARIABLES END */

/* FUNCTION BEGIN */
void ReadButton();
/* FUNCTION END */

#endif
