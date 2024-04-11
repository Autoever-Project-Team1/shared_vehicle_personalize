#ifndef JOYSTICK_H_
#define JOYSTICK_H_

// STATE
#define ZERO 	0
#define LEFT	1
#define RIGHT	2
#define UP		3
#define DOWN	4


// Thresh value
// MIN < VALUE < MAX
#define ZERO_MIN	1900 - 300
#define ZERO_MAX	1900 + 300

#define LEFT_MIN	4095 - 300
#define LEFT_MAX	4095

#define RIGHT_MIN	0
#define RIGHT_MAX	300

#define UP_MIN		4095 - 300
#define UP_MAX		4095

#define DOWN_MIN	0
#define DOWN_MAX	300

// PWM value
#define PWM_ZERO			  	  0
#define PWM_INCREASE			  1
#define PWM_DECREASE			  1

#define PWM_MAX					125
#define PWM_MIN					20


#include "stm32f0xx_hal.h"

/*-----[ Prototypes For All Functions ]-----*/
uint8_t checkJoystickState(uint32_t *adc_value);
uint16_t updateJoystickPWM(uint8_t joystick_state, uint16_t current_pwm, uint8_t motor_id);
uint16_t mapValue(uint32_t input, uint32_t minInput, uint32_t maxInput, uint16_t minOutput, uint16_t maxOutput);

#endif /* JOYSTICK_H_ */
