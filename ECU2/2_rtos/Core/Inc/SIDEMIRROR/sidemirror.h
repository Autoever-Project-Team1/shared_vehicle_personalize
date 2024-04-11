#ifndef SIDEMIRROR_H_
#define SIDEMIRROR_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


// 사이드미러 모터 구조체 정의
typedef struct {
    uint16_t motorX_pwm; // 첫 번째 모터의 PWM 값
    uint16_t motorY_pwm; // 두 번째 모터의 PWM 값
} SideMirrorMotorPWM;

// 함수 프로토타입
void SideMirror_Init(void);
void AdjustSideMirrorByJoystick(void);
void SaveCurrentPWMSettings(void);
void LoadUserSettings(void);
void DisplayGuideline(void);
void I2C_LCD_GUIDELINE(uint8_t now_seq);

#ifdef __cplusplus
}
#endif

#endif /* SIDEMIRROR_H_ */
