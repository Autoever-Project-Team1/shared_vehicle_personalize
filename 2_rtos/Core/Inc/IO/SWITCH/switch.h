#ifndef SWITCH_H_
#define SWITCH_H_

#include "main.h" // Ensure this includes or references your STM32 HAL GPIO definitions
#include "gpio.h"
#include "stm32f0xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function prototypes
void Switch_Init(void); // Optional, if additional initialization is needed
uint8_t Switch_GetState1(void); // Returns 1 if pressed, 0 if not
uint8_t Switch_GetState2(void); // Returns 1 if pressed, 0 if not

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H_ */
