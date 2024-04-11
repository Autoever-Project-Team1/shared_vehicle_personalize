/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define test_SW_Pin GPIO_PIN_13
#define test_SW_GPIO_Port GPIOC
#define sideMirror_Joystick_UD_Pin GPIO_PIN_0
#define sideMirror_Joystick_UD_GPIO_Port GPIOA
#define sideMirror_Joystick_RL_Pin GPIO_PIN_1
#define sideMirror_Joystick_RL_GPIO_Port GPIOA
#define sideMirror_Joystick_Switch_Pin GPIO_PIN_2
#define sideMirror_Joystick_Switch_GPIO_Port GPIOA
#define sideMirror_LED_U_Pin GPIO_PIN_4
#define sideMirror_LED_U_GPIO_Port GPIOA
#define sideMirror_LED_D_Pin GPIO_PIN_5
#define sideMirror_LED_D_GPIO_Port GPIOA
#define sideMirror_LED_R_Pin GPIO_PIN_6
#define sideMirror_LED_R_GPIO_Port GPIOA
#define sideMirror_LED_L_Pin GPIO_PIN_7
#define sideMirror_LED_L_GPIO_Port GPIOA
#define Ras_Stm_usart3_TX_Pin GPIO_PIN_4
#define Ras_Stm_usart3_TX_GPIO_Port GPIOC
#define Ras_Stm_usart3_RX_Pin GPIO_PIN_5
#define Ras_Stm_usart3_RX_GPIO_Port GPIOC
#define sideMirror_LCD_SCL_Pin GPIO_PIN_10
#define sideMirror_LCD_SCL_GPIO_Port GPIOB
#define sideMirror_LCD_SDA_Pin GPIO_PIN_11
#define sideMirror_LCD_SDA_GPIO_Port GPIOB
#define headLight_Laser_Pin GPIO_PIN_6
#define headLight_Laser_GPIO_Port GPIOC
#define headLight_LED_Pin GPIO_PIN_7
#define headLight_LED_GPIO_Port GPIOC
#define headLight_SW_start_Pin GPIO_PIN_8
#define headLight_SW_start_GPIO_Port GPIOC
#define sideMirror_motor_UD_Pin GPIO_PIN_8
#define sideMirror_motor_UD_GPIO_Port GPIOA
#define sideMirror_motor_RL_Pin GPIO_PIN_9
#define sideMirror_motor_RL_GPIO_Port GPIOA
#define headLight_motor_UD_Pin GPIO_PIN_10
#define headLight_motor_UD_GPIO_Port GPIOA
#define headLight_IMU_SCL_Pin GPIO_PIN_6
#define headLight_IMU_SCL_GPIO_Port GPIOB
#define headLight_IMU_SDA_Pin GPIO_PIN_7
#define headLight_IMU_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
