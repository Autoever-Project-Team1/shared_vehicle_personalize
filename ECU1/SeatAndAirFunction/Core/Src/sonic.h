// header : sonic.h
// note : Collection of ultrasonic wave related functions

#ifndef SONIC_H
#define SONIC_H

/* HEADER BEGIN */
#include "stm32f0xx_hal.h"
/* HEADER END */

/* MACRO BEGIN */
#define TRIG_PIN GPIO_PIN_13
#define TRIG_PORT GPIOB
/* MACRO END */

/* STRUCT & TYPE BEGIN */

/* STRUCT & TYPE END */

/* VARIABLES BEGIN */
extern uint32_t IC_Val1;
extern uint32_t IC_Val2;
extern uint32_t Difference;
extern uint8_t Is_First_Captured;
extern uint8_t Distance;

extern uint8_t DeadZone;
extern uint8_t SonicData;

extern TIM_HandleTypeDef htim15;
/* VARIABLES END */

/* FUNCTION BEGIN */
void delay (uint16_t time);
void Sonic_Read (void);
uint8_t CheckSonicClose();
void Sonic_Init(TIM_HandleTypeDef *htim, uint32_t Channel);
/* FUNCTION END */

#endif
