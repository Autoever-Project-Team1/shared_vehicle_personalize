#include "main.h"
#include "tim.h"
#include "IO/BUZZER/buzzer.h"
#include "usart.h" // Assuming USART is used for debugging

extern TIM_HandleTypeDef htim2; // Adjust the timer according to your configuration

uint8_t value = 0; // the value for the duty cycle

void buzzer_init(void) {
	MX_TIM2_Init();
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // Start PWM on the configured channel
}

void beep(uint32_t note, uint32_t duration) {
    if (note == NOTHING) {
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
    } else {
        // Calculate prescaler and period for each note frequency
        uint32_t clock_frequency = 16000000; // 16 MHz base clock
        uint32_t prescaler = (clock_frequency / note / 1000) - 1; // Prescaler for the timer
        uint32_t period = (clock_frequency / (prescaler + 1) / note) - 1; // Period for the timer

        __HAL_TIM_SET_PRESCALER(&htim2, prescaler);
        __HAL_TIM_SET_AUTORELOAD(&htim2, period);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, period / 2); // 50% duty cycle
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // Ensure PWM is started with new settings

    }
    HAL_Delay(duration);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0); // Stop the beep
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1); // Stop PWM
}


void welcomesound(void) {
    beep(SOL_SHARP_L, 150);
    beep(RA_L, 150);
    beep(MI_L, 200);
    beep(NOTHING, 200);
    beep(RE_SHARP, 150);
    beep(FA_SHARP, 150);
    beep(DO_SHARP_H, 200);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
}
