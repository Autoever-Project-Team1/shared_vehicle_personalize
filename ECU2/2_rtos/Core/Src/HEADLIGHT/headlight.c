/*
 * headlights_control.c
 *
 *  Created on: Apr 8, 2024
 *      Author: user
 */

#include "HEADLIGHT/headlight.h"
#include "i2c.h"
#include "IO/SERVO/servo.h"
extern TIM_HandleTypeDef htim1;
static int headlight_mode = 0;
static int pitch_angle = 0;
uint8_t headLightPWM = 0;
bno055_vector_t v = {0};


void HeadLights_initialize()
{
	  MX_I2C1_Init();
	  Servo_Init(&htim1,TIM_CHANNEL_3);
	  bno055_assignI2C(&hi2c1);
	  bno055_setup();
	  bno055_setOperationModeNDOF();
	  MX_GPIO_Init();
}

void HeadLights_control(void) {
    v = bno055_getVectorEuler(); // BNO055 센서로부터 Pitch 각도 읽기
    double my_y = v.y;

    HeadLights_adjustPitch((int)my_y); // 계산된 각도를 전조등 조절 장치에 적용
}

void HeadLights_adjustPitch(int new_pitch_angle) {
    pitch_angle = new_pitch_angle;

    if (pitch_angle >= 0 && pitch_angle <= 5)
    {
        headlight_mode = MODE0;
    }
    else if (pitch_angle > 5 && pitch_angle <= 10)
    {
        headlight_mode = MODE1;
    }
    else if (pitch_angle > 10 && pitch_angle <= 15)
    {
        headlight_mode = MODE2;
    }
    else if (pitch_angle > 15 && pitch_angle <= 20)
    {
        headlight_mode = MODE3;
    }
    else
    {
        return;
    }

    HeadLights_setmotorAngle(headlight_mode);
}

void HeadLights_setmotorAngle(int headlight_mode) {
    // headlight_mode에 따라 서보 모터 각도 설정
    uint8_t angle;


    switch (headlight_mode) {
        case 1:
            angle = MODE1_ANGLE;
            break;
        case 2:
            angle = MODE2_ANGLE;
            break;
        case 3:
            angle = MODE3_ANGLE;
            break;
        default:
            angle = MODE0_ANGLE;
            break;
    }
    headLightPWM = angle;
    ServoAngleChange(&htim1,TIM_CHANNEL_3,angle);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, ServoAngleToCCR(angle));
//    *(&TIM1->CCR3) = headLightPWM;
}

void HeadLights_LEDoff()
{
	//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, xLEDState); // test led
	    HAL_GPIO_WritePin(headLight_LED_GPIO_Port, headLight_LED_Pin, RESET);
	    HAL_GPIO_WritePin(headLight_Laser_GPIO_Port, headLight_Laser_Pin, RESET);

	    HAL_GPIO_WritePin(sideMirror_LED_U_GPIO_Port, sideMirror_LED_U_Pin, RESET);
	    HAL_GPIO_WritePin(sideMirror_LED_D_GPIO_Port, sideMirror_LED_D_Pin, RESET);
	    HAL_GPIO_WritePin(sideMirror_LED_R_GPIO_Port, sideMirror_LED_R_Pin, RESET);
	    HAL_GPIO_WritePin(sideMirror_LED_L_GPIO_Port, sideMirror_LED_L_Pin, RESET);
}

void InitCarSetting_H(void)
{
	uint8_t angle;
	angle = MODE0_ANGLE;
    ServoAngleChange(&htim1,TIM_CHANNEL_3,angle);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, ServoAngleToCCR(angle));
}
