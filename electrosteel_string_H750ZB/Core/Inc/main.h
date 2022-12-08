/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define __ATTR_RAM_D1	__attribute__ ((section(".RAM_D1"))) __attribute__ ((aligned (32)))
#define __ATTR_RAM_D2	__attribute__ ((section(".RAM_D2"))) __attribute__ ((aligned (32)))
#define __ATTR_RAM_D3	__attribute__ ((section(".RAM_D3"))) __attribute__ ((aligned (32)))
#define __ATTR_SDRAM	__attribute__ ((section(".SDRAM"))) __attribute__ ((aligned (32)))

#define NUM_ADC_CHANNELS 10
#define NUM_STRINGS NUM_ADC_CHANNELS
#define LHMUTE_COUNTLIM 100
#define RHMUTE_COUNTLIM 1

#define AUDIO_FRAME_SIZE 512
#define AUDIO_BUFFER_SIZE AUDIO_FRAME_SIZE * 4
#define ADC_FRAME_SIZE 4
#define ADC_BUFFER_SIZE ADC_FRAME_SIZE * 2
#define LARGE_MEM_SIZE 33554432 //32 MBytes - size of SDRAM IC
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
