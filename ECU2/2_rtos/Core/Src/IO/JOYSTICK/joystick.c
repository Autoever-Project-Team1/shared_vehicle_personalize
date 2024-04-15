#include "IO/JOYSTICK/JOYSTICK.H"
#include "math.h"

uint16_t mapValue(uint32_t input, uint32_t minInput, uint32_t maxInput, uint16_t minOutput, uint16_t maxOutput) {
    return (uint16_t)(((input - minInput) * (maxOutput - minOutput)) / (maxInput - minInput) + minOutput);
}

uint8_t checkJoystickState(uint32_t *adc_value)
{
	// zero
	if (adc_value[0] > ZERO_MIN && adc_value[0] < ZERO_MAX
			&& adc_value[1] > ZERO_MIN && adc_value[1] < ZERO_MAX) {
		return ZERO;
	}

	// x axis
	else if (adc_value[1] >= LEFT_MIN && adc_value[1] <= LEFT_MAX) {
		return LEFT;
	}
	else if (adc_value[1] >= RIGHT_MIN && adc_value[1] <= RIGHT_MAX) {
		return RIGHT;
	}
	// y axis
	if (adc_value[0] >= UP_MIN && adc_value[0] <= UP_MAX) {
		return DOWN;
	}
	else if (adc_value[0] >= DOWN_MIN && adc_value[0] <= DOWN_MAX) {
		return UP;
	}
	else {
		return ZERO;
	}
}


uint16_t updateJoystickPWM(uint8_t joystick_state, uint16_t current_pwm, uint8_t motor_id)
{
    uint16_t reference_pwm = current_pwm; // 현재 PWM 값으로 초기화

    // motor_id에 따라 서로 다른 방향 처리
    if (motor_id == 1) { // 첫 번째 서보 모터 (UP-DOWN 제어)
        switch (joystick_state) {
        case UP:
            if (current_pwm < PWM_MAX) reference_pwm += PWM_INCREASE;
            break;
        case DOWN:
            if (current_pwm > PWM_MIN) reference_pwm -= PWM_DECREASE;
            break;
        }
    } else if (motor_id == 2) { // 두 번째 서보 모터 (RIGHT-LEFT 제어)
        switch (joystick_state) {
        case RIGHT:
            if (current_pwm < PWM_MAX) reference_pwm += PWM_INCREASE;
            break;
        case LEFT:
            if (current_pwm > PWM_MIN) reference_pwm -= PWM_DECREASE;
            break;
        }
    }

    // 업데이트된 PWM 값을 반환
    return reference_pwm;
}

