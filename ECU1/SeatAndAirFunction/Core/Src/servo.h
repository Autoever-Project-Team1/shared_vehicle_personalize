// header : servo.h
// note : Collection of servo motor related functions
#ifndef SERVO_H
#define SERVO_H

/* HEADER BEGIN */
#include "stm32f0xx_hal.h"
/* HEADER END */

/* MACRO BEGIN */
#define DEG0TOCCR	20
#define DEGGAIN		0.56
/* MACRO END */

/* STRUCT & TYPE BEGIN */

/* STRUCT & TYPE END */

/* VARIABLES BEGIN */

/* VARIABLES END */

/* FUNCTION BEGIN */
void Servo_Init(TIM_HandleTypeDef *htim, uint32_t Channel);
void ServoAngleChange(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t angle);
uint32_t ServoAngleToCCR(uint8_t angle);
/* FUNCTION END */

#endif
