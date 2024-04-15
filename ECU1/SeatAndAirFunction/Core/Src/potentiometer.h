#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

#define THRESHOLD_POSITIVE  20

// PWM THRESHOLD
#define PWM_MAX             125
#define PWM_MIN             20

#include "stm32f0xx_hal.h"

/*-----[ Prototypes For All Functions ]-----*/
uint16_t updatePotPWM(uint32_t adc_value);
uint16_t PotmapValue(uint32_t input, uint32_t minInput, uint32_t maxInput, uint16_t minOutput, uint16_t maxOutput);
#endif /* POTENTIOMETER_H_ */
