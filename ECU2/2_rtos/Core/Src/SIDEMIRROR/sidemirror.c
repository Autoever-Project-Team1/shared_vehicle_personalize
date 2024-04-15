#include <IO/LCD/lcd.h>
#include "SIDEMIRROR/sidemirror.h"
#include "IO/JOYSTICK/joystick.h"
#include "PROTOCOL/protocol.h"

#include "i2c.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"

uint32_t Adc_val[ADC_CHANNEL_NUMS] = {0};
uint32_t Joystick_val[2] = {0};
uint8_t joystick_state = 0;
SideMirrorMotorPWM SideMirrorPWM = {70, 72};

uint8_t GuideLine_seq = 0;

// 사이드미러 초기화
void SideMirror_Init(void) {
    // 사이드미러 모터와 관련된 하드웨어 초기화 로직
	MX_ADC_Init();
	MX_TIM1_Init();
    MX_GPIO_Init();
    MX_I2C2_Init();
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    I2C_LCD_Init(I2C_LCD_1);
}

// 조이스틱을 이용한 사이드미러 조정
void AdjustSideMirrorByJoystick(void) {
    // 조이스틱 입력을 받아 사이드미러 모터의 PWM을 조정하는 로직
	ADC_read(Adc_val, ADC_CHANNEL_NUMS);
	Joystick_val[0] = Adc_val[0];
	Joystick_val[1] = Adc_val[1];
	joystick_state = checkJoystickState(Joystick_val);

	SideMirrorPWM.motorX_pwm = updateJoystickPWM(joystick_state, SideMirrorPWM.motorX_pwm, 1);
	SideMirrorPWM.motorY_pwm = updateJoystickPWM(joystick_state, SideMirrorPWM.motorY_pwm, 2);
	*(&TIM1->CCR1) = SideMirrorPWM.motorX_pwm;
	*(&TIM1->CCR2) = SideMirrorPWM.motorY_pwm;
}

// 현재 PWM 설정 저장
void SaveCurrentPWMSettings(void) {
    // 현재 사이드미러 모터의 PWM 설정을 저장하는 로직
	// usart protocol기반으로 SideMirrorPWM 값 보내주기
	uint8_t ud_pwm = SideMirrorPWM.motorX_pwm;
	uint8_t rl_pwm = SideMirrorPWM.motorY_pwm;
	Send_sideMirror(ud_pwm, rl_pwm);
}

// 사용자 설정 로드
void LoadUserSettings(void) {
    // 사용자 정보가 있을 경우 해당 정보를 로드하여 PWM 설정을 적용하는 로직
	// usart protocol기반으로 SideMirrorPWM 값 불러오기
	SideMirrorPWM.motorX_pwm = Receieve_UDsideMirror();
	SideMirrorPWM.motorY_pwm = Receieve_RLsideMirror();
	*(&TIM1->CCR1) = SideMirrorPWM.motorX_pwm;
	*(&TIM1->CCR2) = SideMirrorPWM.motorY_pwm;
}

// LCD 가이드라인 표시
void DisplayGuideline(void) {
    // LCD를 사용하여 사이드미러 조정 가이드라인을 표시하는 로직
    if (Switch_GetState1() == 1) {
        I2C_LCD_Display(I2C_LCD_1);
        GuideLine_seq++;
        if (GuideLine_seq > SEQ_3) {
        	GuideLine_seq = 0;
        }
    }
    I2C_LCD_GUIDELINE(GuideLine_seq); // Display the current step on the LCD
}

void InitCarSetting(void)
{
	SideMirrorPWM.motorX_pwm = 70;
	SideMirrorPWM.motorY_pwm = 72;
	*(&TIM1->CCR1) = SideMirrorPWM.motorX_pwm;
	*(&TIM1->CCR2) = SideMirrorPWM.motorY_pwm;
}



