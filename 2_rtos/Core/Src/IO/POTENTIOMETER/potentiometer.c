#include "IO/POTENTIOMETER/POTENTIOMETER.h"
#include "math.h"

static uint32_t last_adc_value = 0;
static uint16_t last_pwm_value = PWM_MIN;

uint16_t PotmapValue(uint32_t input, uint32_t minInput, uint32_t maxInput, uint16_t minOutput, uint16_t maxOutput) {
    return (uint16_t)(((input - minInput) * (maxOutput - minOutput)) / (maxInput - minInput) + minOutput);
}

uint16_t updatePotPWM(uint32_t adc_value) {
    int32_t delta = (int32_t)adc_value - (int32_t)last_adc_value;

    if (abs((int)delta) > THRESHOLD_POSITIVE) {
        last_pwm_value = PotmapValue(adc_value, 0, 4095, PWM_MIN, PWM_MAX);
    }
    last_adc_value = adc_value;

    return last_pwm_value;
}
