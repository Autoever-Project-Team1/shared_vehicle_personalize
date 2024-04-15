/*
 * headlights_control.h
 *
 *  Created on: Apr 8, 2024
 *      Author: user
 */

#ifndef INC_HEADLIGHTS_CONTROL_H_
#define INC_HEADLIGHTS_CONTROL_H_

#include "IO/IMU/bno055.h"

#define MODE0			0
#define MODE1			1
#define MODE2			2
#define MODE3			3

#define MODE0_ANGLE		8
#define MODE1_ANGLE		20
#define MODE2_ANGLE		40
#define MODE3_ANGLE		60

void HeadLights_initialize();
double HeadLights_readPitch();
void HeadLights_control(void);
void HeadLights_adjustPitch(int pitch_angle);
void HeadLights_setmotorAngle(int angle);
void HeadLights_LEDoff();
void InitCarSetting_H(void);

#endif /* INC_HEADLIGHTS_CONTROL_H_ */
