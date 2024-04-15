/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "PROTOCOL/protocol.h"
#include "SIDEMIRROR/sidemirror.h"
#include "HEADLIGHT/headlight.h"
#include "timers.h"
#include "IO/BUZZER/buzzer.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
TimerHandle_t xTimerBlinkLED;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

uint8_t aaaa = 0;
static int loadSettingValue = 0;
static int saveSettingValue = 0;
static int farSettingValue = 0;
uint8_t sw1 = 0;
uint8_t sw2 = 0;
uint8_t buttonState = 0;



/* USER CODE END Variables */
/* Definitions for sideMirrorTask */
osThreadId_t sideMirrorTaskHandle;
const osThreadAttr_t sideMirrorTask_attributes = {
  .name = "sideMirrorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for headLightTask */
osThreadId_t headLightTaskHandle;
const osThreadAttr_t headLightTask_attributes = {
  .name = "headLightTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for checkPacketTask */
osThreadId_t checkPacketTaskHandle;
const osThreadAttr_t checkPacketTask_attributes = {
  .name = "checkPacketTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void vTimerBlinkLEDCallback(TimerHandle_t xTimer);
/* USER CODE END FunctionPrototypes */

void FsideMirrorTask(void *argument);
void FheadLightTask(void *argument);
void FcheckPacketTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  xTimerBlinkLED = xTimerCreate("TimerBlinkLED", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, vTimerBlinkLEDCallback);
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of sideMirrorTask */
  sideMirrorTaskHandle = osThreadNew(FsideMirrorTask, NULL, &sideMirrorTask_attributes);

  /* creation of headLightTask */
  headLightTaskHandle = osThreadNew(FheadLightTask, NULL, &headLightTask_attributes);

  /* creation of checkPacketTask */
  checkPacketTaskHandle = osThreadNew(FcheckPacketTask, NULL, &checkPacketTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_FsideMirrorTask */
/**
  * @brief  Function implementing the sideMirrorTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_FsideMirrorTask */
void FsideMirrorTask(void *argument)
{
  /* USER CODE BEGIN FsideMirrorTask */
  /* Infinite loop */
	SideMirror_Init();

  for(;;)
  {
	  AdjustSideMirrorByJoystick();
	  DisplayGuideline();
    osDelay(10);
  }
  /* USER CODE END FsideMirrorTask */
}

/* USER CODE BEGIN Header_FheadLightTask */
/**
* @brief Function implementing the headLightTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FheadLightTask */
void FheadLightTask(void *argument)
{
  /* USER CODE BEGIN FheadLightTask */
  /* Infinite loop */
	HeadLights_initialize();
	InitCarSetting_H();
	for(;;)
	{
		if (Switch_GetState2() == 1)
		{
			HeadLights_control();
			HAL_GPIO_WritePin(headLight_Laser_GPIO_Port, headLight_Laser_Pin, SET);
			HAL_GPIO_WritePin(headLight_LED_GPIO_Port, headLight_LED_Pin, SET);
		}
		else if (Check_KeyState() == KEYON)
		{
			HAL_GPIO_WritePin(headLight_Laser_GPIO_Port, headLight_Laser_Pin, SET);
			HAL_GPIO_WritePin(headLight_LED_GPIO_Port, headLight_LED_Pin, SET);
		}
		osDelay(10);

	}
  /* USER CODE END FheadLightTask */
}

/* USER CODE BEGIN Header_FcheckPacketTask */
/**
* @brief Function implementing the checkPacketTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FcheckPacketTask */
void FcheckPacketTask(void *argument)
{
  /* USER CODE BEGIN FcheckPacketTask */
  /* Infinite loop */
	Uart_Init();
	buzzer_init();
  for(;;)
  {
      if (Check_CloseState() == CLOSE)
      {	  // WELCOME LIGHT ON -> UNSYNC
          if (xTimerIsTimerActive(xTimerBlinkLED) == pdFALSE)
          {
              xTimerStart(xTimerBlinkLED, 0);
              farSettingValue = 0;
          }
          aaaa = CLOSE;
      }
      else if (Check_CloseState() == FAR && farSettingValue == 0)
      {	  // WELCOME LIGHT OFF
          xTimerStop(xTimerBlinkLED, 0);
          HeadLights_LEDoff();
          farSettingValue = 1;
          aaaa = FAR;
      }

	  if (Check_KeyState() == KEYON && loadSettingValue == 0)
	  {
		  // WELCOME LIGHT OFF
		  xTimerStop(xTimerBlinkLED, 0);
		  HeadLights_LEDoff();
		  aaaa=KEYON;

		  welcomesound();

		  // LOAD USER INFO
		  LoadUserSettings();
		  loadSettingValue = 1;
		  saveSettingValue = 0;
	  }
	  if (Check_KeyState() == KEYOFF && saveSettingValue == 0)
	  {
		  SaveCurrentPWMSettings();
		  InitCarSetting();
		  InitCarSetting_H();
		  aaaa=KEYOFF;
		  loadSettingValue = 0;
		  saveSettingValue = 1;

	  }
	  osDelay(10);
  }
  /* USER CODE END FcheckPacketTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vTimerBlinkLEDCallback(TimerHandle_t xTimer) {
    static BaseType_t xLEDState = pdFALSE;

    xLEDState = !xLEDState;
    HAL_GPIO_WritePin(headLight_LED_GPIO_Port, headLight_LED_Pin, xLEDState);
    HAL_GPIO_WritePin(headLight_Laser_GPIO_Port, headLight_Laser_Pin, xLEDState);

    HAL_GPIO_WritePin(sideMirror_LED_U_GPIO_Port, sideMirror_LED_U_Pin, xLEDState);
    HAL_GPIO_WritePin(sideMirror_LED_D_GPIO_Port, sideMirror_LED_D_Pin, xLEDState);
    HAL_GPIO_WritePin(sideMirror_LED_R_GPIO_Port, sideMirror_LED_R_Pin, xLEDState);
    HAL_GPIO_WritePin(sideMirror_LED_L_GPIO_Port, sideMirror_LED_L_Pin, xLEDState);
}
/* USER CODE END Application */

