// header : scheduling.h

#ifndef SCHEDULING_H
#define SCHEDULING_H

/* HEADER BEGIN */
#include "stm32f0xx_hal.h"

#include "protocol.h"
#include "servo.h"
#include "sonic.h"
#include "fnd.h"
#include "scheduling.h"
#include "button.h"
#include "joystick.h"

#include <stdio.h>
#include <string.h>
/* HEADER END */

/* MACRO BEGIN */
#define AIRDIR			90
#define AIRSPEED		90
#define SEATUPDOWN		0
#define SEATRIGHTLEFT	90
#define SEATROTATE		10

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim15;
/* MACRO END */

/* STRUCT & TYPE BEGIN */
typedef struct
{
    uint8_t ms1Flag;
    uint8_t ms10Flag;
    uint8_t ms100Flag;
    uint8_t ms150Flag;
    uint8_t ms1000Flag;
}SchedulingFlag;
/* STRUCT & TYPE END */

/* VARIABLES BEGIN */
extern SchedulingFlag SchedulInfo;
extern uint32_t cnt1ms;
/* VARIABLES END */

/* FUNCTION BEGIN */
void Scheduling_Init(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

void TaskScheduling();
void Task1ms();
void Task10ms();
void Task100ms();
void Task150ms();
void Task1000ms();
/* FUNCTION END */

#endif
