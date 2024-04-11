#include "SIDEMIRROR/sidemirror.h"
#include "IO/LCD/I2C_LCD.h"
#include "IO/JOYSTICK/joystick.h"
#include "PROTOCOL/protocol.h"

#include "i2c.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"

uint32_t Adc_val[ADC_CHANNEL_NUMS] = {0};
uint32_t Joystick_val[2] = {0};
uint8_t joystick_state = 0;
SideMirrorMotorPWM SideMirrorPWM = {0, 0};

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
        	GuideLine_seq = IDLE;
        }
    }
    I2C_LCD_GUIDELINE(GuideLine_seq); // Display the current step on the LCD
}

void I2C_LCD_GUIDELINE(uint8_t now_seq)
{
    static uint8_t last_seq = 255; // 이전에 표시된 seq 값을 저장하는 변수, 임의의 초기값 설정

    // 현재 seq 값이 이전과 다른 경우에만 화면을 업데이트
    if (last_seq != now_seq)
    {
        last_seq = now_seq; // 현재 seq 값을 last_seq에 저장
        I2C_LCD_Clear(I2C_LCD_1); // LCD 화면 클리어

        // LED 제어 로직 추가
        // 상하 LED 2개
        if (now_seq == SEQ_2)
        {
            HAL_GPIO_WritePin(sideMirror_LED_U_GPIO_Port, sideMirror_LED_U_Pin, GPIO_PIN_SET); // LED_U 켜기
            HAL_GPIO_WritePin(sideMirror_LED_D_GPIO_Port, sideMirror_LED_D_Pin, GPIO_PIN_SET); // LED_D 켜기
            HAL_GPIO_WritePin(sideMirror_LED_R_GPIO_Port, sideMirror_LED_R_Pin, GPIO_PIN_RESET); // LED_R 끄기
            HAL_GPIO_WritePin(sideMirror_LED_L_GPIO_Port, sideMirror_LED_L_Pin, GPIO_PIN_RESET); // LED_L 끄기
        }
        // 좌우 LED 2개
        else if (now_seq == SEQ_3)
        {
            HAL_GPIO_WritePin(sideMirror_LED_U_GPIO_Port, sideMirror_LED_U_Pin, GPIO_PIN_RESET); // LED_U 끄기
            HAL_GPIO_WritePin(sideMirror_LED_D_GPIO_Port, sideMirror_LED_D_Pin, GPIO_PIN_RESET); // LED_D 끄기
            HAL_GPIO_WritePin(sideMirror_LED_R_GPIO_Port, sideMirror_LED_R_Pin, GPIO_PIN_SET); // LED_R 켜기
            HAL_GPIO_WritePin(sideMirror_LED_L_GPIO_Port, sideMirror_LED_L_Pin, GPIO_PIN_SET); // LED_L 켜기
        }
        else
        {
            // 나머지 상태에서는 모든 LED 끄기
            HAL_GPIO_WritePin(sideMirror_LED_U_GPIO_Port, sideMirror_LED_U_Pin, GPIO_PIN_RESET); // LED_U 끄기
            HAL_GPIO_WritePin(sideMirror_LED_D_GPIO_Port, sideMirror_LED_D_Pin, GPIO_PIN_RESET); // LED_D 끄기
            HAL_GPIO_WritePin(sideMirror_LED_R_GPIO_Port, sideMirror_LED_R_Pin, GPIO_PIN_RESET); // LED_R 켜기
            HAL_GPIO_WritePin(sideMirror_LED_L_GPIO_Port, sideMirror_LED_L_Pin, GPIO_PIN_RESET); // LED_L 켜기
        }

        // now_seq 값에 따른 메시지 표시
        switch (now_seq)
        {
			case SEQ_0:
				I2C_LCD_NoBacklight(I2C_LCD_1);
				I2C_LCD_NoDisplay(I2C_LCD_1);
				break;

            case SEQ_1:
            	I2C_LCD_Backlight(I2C_LCD_1);
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 0);
                I2C_LCD_WriteString(I2C_LCD_1, "SIDEMIRROR GUIDELINE ");
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 1);
                I2C_LCD_WriteString(I2C_LCD_1, "IF YOU READY ");
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 2);
                I2C_LCD_WriteString(I2C_LCD_1, "PUSH BUTTON");
                break;
            case SEQ_2:
            	I2C_LCD_Backlight(I2C_LCD_1);
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 0);
                I2C_LCD_WriteString(I2C_LCD_1, "SIDEMIRROR GUIDELINE ");
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 1);
                I2C_LCD_WriteString(I2C_LCD_1, "ALIGN UP AND DOWN ");
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 2);
                I2C_LCD_WriteString(I2C_LCD_1, "PLACE RED LED LINE");
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 3);
                I2C_LCD_WriteString(I2C_LCD_1, "AT HORIZON");
                break;
            case SEQ_3:
            	I2C_LCD_Backlight(I2C_LCD_1);
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 0);
                I2C_LCD_WriteString(I2C_LCD_1, "SIDEMIRROR GUIDELINE ");
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 1);
                I2C_LCD_WriteString(I2C_LCD_1, "ALIGN LEFT AND RIGHT ");
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 2);
                I2C_LCD_WriteString(I2C_LCD_1, "PLACE BLUE LED LINE");
                I2C_LCD_SetCursor(I2C_LCD_1, 0, 3);
                I2C_LCD_WriteString(I2C_LCD_1, "AT 1/4 CAR");
                break;
        }
    }
}


