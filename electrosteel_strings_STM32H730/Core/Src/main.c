/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "leaf.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define SAMPLE_RATE 48000
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

RNG_HandleTypeDef hrng;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi2_rx;

/* USER CODE BEGIN PV */
uint8_t SPI_TX[8]__ATTR_RAM_D2;
uint8_t SPI_RX[8]__ATTR_RAM_D2;

uint8_t SPI_PLUCK_TX[32]__ATTR_RAM_D2;
uint8_t SPI_PLUCK_RX[32]__ATTR_RAM_D2;

//uint8_t newFirmwareBuffer[65536]__ATTR_RAM_D1;
//uint32_t newFirmwareBufferPosition = 0;


uint8_t counter;
uint16_t ADC_values1[NUM_ADC_CHANNELS * ADC_BUFFER_SIZE]__ATTR_RAM_D2;
//uint16_t ADC_values2[NUM_ADC_CHANNELS * ADC_BUFFER_SIZE]__ATTR_RAM_D2;
#define FILTER_ORDER 2
#define ATODB_TABLE_SIZE 65536
#define ATODB_TABLE_SIZE_MINUS_ONE 65535


#define SMALL_MEM_SIZE 120000
char smallMemory[SMALL_MEM_SIZE];

LEAF leaf;


float atodbTable[ATODB_TABLE_SIZE] __ATTR_RAM_D1;
//tPluckDetectorInt myPluck[NUM_ADC_CHANNELS];
tHighpass opticalHighpass[NUM_STRINGS][FILTER_ORDER];
tVZFilter opticalLowpass[NUM_STRINGS][FILTER_ORDER];
tSlide fastSlide[NUM_STRINGS];
tSlide slowSlide[NUM_STRINGS];
tThreshold threshold[NUM_STRINGS];

//volatile uint_fast8_t gettingNewFirmware = 0;
volatile uint_fast8_t SPI_busy = 0;


uint16_t stringPositions[NUM_STRINGS];
uint16_t stringTouchRH[NUM_STRINGS];
int didPlucked[NUM_STRINGS];
int stringSounding[NUM_STRINGS];

int howManyFrames = 400;
int brokedIt = 0;
int didPlucked2[NUM_STRINGS];
int pluckDelay[NUM_STRINGS];
int pluckValues[NUM_STRINGS];
uint32_t stringStates[NUM_STRINGS];
uint32_t string_values[NUM_STRINGS];
volatile uint32_t changeHappened = 0;

uint32_t timeFrame;
uint32_t frameRate;
uint32_t frameRateStart;

int RHbits[2] = {0,0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_ADC1_Init(void);
static void MX_RNG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//void MPU_Conf(void);
float randomNumber(void);
void CycleCounterInit(void);
void MPU_Conf(void);
//void loadNewFirmware(uint32_t);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	MPU_Conf();
  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  CycleCounterInit();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_ADC1_Init();
  MX_RNG_Init();
  /* USER CODE BEGIN 2 */
  uint32_t tempFPURegisterVal = __get_FPSCR();
   tempFPURegisterVal |= (1<<24); // set the FTZ (flush-to-zero) bit in the FPU control register
   __set_FPSCR(tempFPURegisterVal);

   for (int i = 0; i < 4; i++)
   {
 	  SPI_TX[i] = counter++;
   }

   for (int i = 0; i < 32; i++)
   {
 	  SPI_PLUCK_TX[i] = 0;
 	  SPI_PLUCK_RX[i] = 0;
   }

   HAL_SPI_Receive_DMA(&hspi2, SPI_RX, 8);

   //wait for synth boards to load code from QSPI to SRAM
   HAL_Delay(10);
   //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
   HAL_Delay(10);

   LEAF_init(&leaf, SAMPLE_RATE, smallMemory, SMALL_MEM_SIZE, &randomNumber);

   for (int i = 0; i < NUM_STRINGS; i++)
   {
		tThreshold_init(&threshold[i],700.0f, 1300.0f, &leaf);
		tSlide_init(&fastSlide[i],1.0f,400.0f, &leaf); //1110
		tSlide_init(&slowSlide[i],1.0f,700.0f, &leaf); //1110

		for (int j = 0; j < FILTER_ORDER; j++)
		{
			tVZFilter_init(&opticalLowpass[i][j], Lowpass, 10000.0f, 0.8f, &leaf);//6000
			tHighpass_init(&opticalHighpass[i][j], 10.0f, &leaf);//100
		}
   }



   LEAF_generate_atodb(atodbTable, ATODB_TABLE_SIZE);



   HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_values1,NUM_ADC_CHANNELS * ADC_BUFFER_SIZE);
   //HAL_ADC_Start_DMA(&hadc2,(uint16_t*)&ADC_values2,NUM_ADC_CHANNELS * ADC_BUFFER_SIZE);
   //HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   while (1)
   {
		if (changeHappened)
		{
			if (!SPI_busy)// && (!gettingNewFirmware))
			{
				for (int j = 0; j < NUM_STRINGS; ++j)
				{
					SPI_PLUCK_TX[(j * 2) + 1] = (stringStates[j] >> 8);
					SPI_PLUCK_TX[(j * 2) + 2] = (stringStates[j] & 0xff);
				}
				SPI_PLUCK_TX[0] = 254;
				SPI_PLUCK_TX[31] = 253;

				SCB_CleanDCache_by_Addr((uint32_t*)(((uint32_t)SPI_PLUCK_TX) & ~(uint32_t)0x1F), 64);
				HAL_SPI_TransmitReceive_DMA(&hspi1, SPI_PLUCK_TX, SPI_PLUCK_RX, 32);
				changeHappened = 0;
				SPI_busy = 1;
			}
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
   }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 420;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_0;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOMEDIUM;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_16B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 10;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = ENABLE;
  hadc1.Init.Oversampling.Ratio = 2;
  hadc1.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_1;
  hadc1.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  hadc1.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_RESUMED_MODE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_16;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_32CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_17;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_18;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_19;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_9;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_10;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  hrng.Init.ClockErrorDetection = RNG_CED_ENABLE;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x0;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_SLAVE;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 0x0;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi2.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi2.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15|GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD15 PD0 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* USER CODE BEGIN 4 */
float randomNumber(void) {

	uint32_t rand;
	HAL_RNG_GenerateRandomNumber(&hrng, &rand);
	float num = (float)rand * INV_TWO_TO_32;
	return num;
}



void MPU_Conf(void)
{
	//code from Keshikan https://github.com/keshikan/STM32H7_DMA_sample
  //Thanks, Keshikan! This solves the issues with accessing the SRAM in the D2 area properly. -JS
	//should test the different possible settings to see what works best while avoiding needing to manually clear the cache -JS

	MPU_Region_InitTypeDef MPU_InitStruct;

	  HAL_MPU_Disable();

	  MPU_InitStruct.Enable = MPU_REGION_ENABLE;

	  //D2 Domain�SRAM1
	  MPU_InitStruct.BaseAddress = 0x30000000;
	  // Increased region size to 256k. In Keshikan's code, this was 512 bytes (that's all that application needed).
	  // Each audio buffer takes up the frame size * 8 (16 bits makes it *2 and stereo makes it *2 and double buffering makes it *2)
	  // So a buffer size for read/write of 4096 would take up 64k = 4096*8 * 2 (read and write).
	  // I increased that to 256k so that there would be room for the ADC knob inputs and other peripherals that might require DMA access.
	  // we have a total of 256k in SRAM1 (128k, 0x30000000-0x30020000) and SRAM2 (128k, 0x30020000-0x3004000) of D2 domain.
	  // There is an SRAM3 in D2 domain as well (32k, 0x30040000-0x3004800) that is currently not mapped by the MPU (memory protection unit) controller.

	  MPU_InitStruct.Size = MPU_REGION_SIZE_32KB;

	  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;

	  //AN4838
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;

	  //Shared Device
//	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
//	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
//	  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
//	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;


	  MPU_InitStruct.Number = MPU_REGION_NUMBER0;

	  MPU_InitStruct.SubRegionDisable = 0x00;


	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;


	  HAL_MPU_ConfigRegion(&MPU_InitStruct);


	  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

float Dsmoothed;
float Dsmoothed2;
float dbSmoothed2;
float dbSmoothedStorage;
int armed[NUM_STRINGS] = {0,0,0,0,0,0,0,0,0,0};
float prevdbSmoothed2[NUM_STRINGS];
int threshOut = 0;
int stringMaxes[NUM_STRINGS] = {0,0,0,0,0,0,0,0,0,0};
int downCounter[NUM_STRINGS];
int armedCounter[NUM_STRINGS];
float slopeStorage[NUM_STRINGS];
float integerVersions[NUM_STRINGS];
int attackDetectPeak2 (int whichString, int tempInt)
{
	float output = -1.0f;
	float tempSamp = (((float)tempInt - TWO_TO_15) * INV_TWO_TO_15);
	for (int k = 0; k < FILTER_ORDER; k++)
	{
		// a highpass filter, remove any slow moving signal (effectively centers the signal around zero and gets rid of the signal that isn't high frequency vibration) cutoff of 100Hz, // applied 8 times to get rid of a lot of low frequency bumbling around
		tempSamp = tHighpass_tick(&opticalHighpass[whichString][k], tempSamp);
		tempSamp = tVZFilter_tick(&opticalLowpass[whichString][k], tempSamp);
	}

	float tempAbs = fabsf(tempSamp);

	Dsmoothed = tSlide_tick(&fastSlide[whichString], tempAbs);
	Dsmoothed2 = tSlide_tick(&slowSlide[whichString], Dsmoothed);
	Dsmoothed2 = LEAF_clip(0.0f, Dsmoothed2, 1.0f);
	//dbSmoothed2 = atodb(Dsmoothed2);
	dbSmoothed2 = LEAF_clip(-39.0f, atodbTable[(uint32_t)(Dsmoothed2 * ATODB_TABLE_SIZE_MINUS_ONE)], 12.0f);//45
	if (whichString == 0)
	{
		dbSmoothedStorage = dbSmoothed2;
	}
	//dbSmoothed2 = LEAF_clip(-50.f, dbSmoothed2, 12.0f);
	//get the slope
	float slope = (dbSmoothed2 - prevdbSmoothed2[whichString]);
	slopeStorage[whichString] = slope;
	float integerVersion = Dsmoothed2 * (TWO_TO_16 - 1);
	integerVersions[whichString] = integerVersion;
	threshOut = tThreshold_tick(&threshold[whichString], integerVersion);

	if ((slope > .5f) && (threshOut > 0))//.3
	{
		armed[whichString] = 1;
	}

	if (armed[whichString] == 1)
	{
		if (integerVersion > stringMaxes[whichString])
		{
			stringMaxes[whichString] = integerVersion;
		}
		armedCounter[whichString]++;

		if (slope <= 0.0f)
		{
			downCounter[whichString]++;
		}
		if (downCounter[whichString] > 164)//was 256
		{
			//found a peak?
			output = stringMaxes[whichString] * 1.75f;
			output = LEAF_clip(0.0f, output, 65535.0f);
			armed[whichString] = 0;
			armedCounter[whichString] = 0;
			downCounter[whichString] = 0;
			stringMaxes[whichString] = 0;
		}
	}

	prevdbSmoothed2[whichString] = dbSmoothed2;
	return (int)output;
}


volatile float CPULoad = 0.0f;

void ADC_Frame(int offset)
{
	//HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_11);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
	uint32_t tempCountFrame = DWT->CYCCNT;
	frameRate = DWT->CYCCNT - frameRateStart;
	frameRateStart = DWT->CYCCNT;

	for (int i = offset; i < ADC_FRAME_SIZE + offset; i++)
	{
		//for (int j = 0; j < NUM_ADC_CHANNELS; j++)
		if (howManyFrames > 0)
		{
			howManyFrames--;
		}



		for (int k = 0; k < NUM_STRINGS; k++)
		{
			string_values[k] = ADC_values1[(i*NUM_ADC_CHANNELS) + k];
		}

		for (int j = 0; j < NUM_STRINGS; j++)
		{
			int tempInt = string_values[j];

			if (j < 8)
			{
				stringTouchRH[j] = (RHbits[0] >> j) & 1;
			}
			else
			{
				stringTouchRH[j] = (RHbits[1] >> (j-8)) & 1;
			}
			didPlucked[j] = attackDetectPeak2(j, tempInt);

			if (howManyFrames == 0)
			{
				if ((didPlucked[j] > 0) && (!stringSounding[j]))
				{
					stringStates[j] = (uint16_t)didPlucked[j];
					pluckValues[j] = didPlucked[j];
					changeHappened = 1;
					stringSounding[j] = 1;
				}

				if ((stringTouchRH[j]) && (stringSounding[j]))
				{

					stringStates[j] = 0;
					pluckValues[j] = 0;
					changeHappened = 1;
					stringSounding[j] = 0;
				}


			}
		}
	}
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);

	timeFrame = DWT->CYCCNT - tempCountFrame;
	CPULoad = (float)timeFrame / (float)frameRate;

}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	ADC_Frame(ADC_FRAME_SIZE);
}
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	ADC_Frame(0);
}
void HAL_ADC_Error(ADC_HandleTypeDef *hadc)
{
	;
}

//volatile uint32_t mySize  = 0;
//void loadNewFirmware(uint32_t size)
//{
//	mySize = size;
//}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	SPI_busy = 0;
}

volatile int numResets = 0;

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	if ((SPI_RX[6] == 254) && (SPI_RX[7] == 253))
	{
		for (int i = 0; i < 2; i++)
		{
			RHbits[i] = SPI_RX[i+4];
		}
	}
	else
	{
		HAL_SPI_Abort(&hspi2);
		__HAL_RCC_SPI2_FORCE_RESET();
		__HAL_RCC_SPI2_RELEASE_RESET();
		MX_SPI2_Init();
		__HAL_SPI_ENABLE(&hspi2);
		HAL_SPI_Receive_DMA(&hspi2, SPI_RX, 8);
		numResets++;
	}
}

void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	if ((SPI_RX[2] == 254) && (SPI_RX[3] == 253))
	{
		for (int i = 0; i < 2; i++)
		{
			RHbits[i] = SPI_RX[i];
		}
	}
	else
	{
		HAL_SPI_Abort(&hspi2);
		__HAL_RCC_SPI2_FORCE_RESET();
		__HAL_RCC_SPI2_RELEASE_RESET();
		MX_SPI2_Init();
		__HAL_SPI_ENABLE(&hspi2);
		HAL_SPI_Receive_DMA(&hspi2, SPI_RX, 8);
		numResets++;
	}
}

// helper function to initialize measuring unit (cycle counter) */
void CycleCounterInit( void )
{
  /* Enable TRC */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  /* Unlock DWT registers */
  if ((*(uint32_t*)0xE0001FB4) & 1)
    *(uint32_t*)0xE0001FB0 = 0xC5ACCE55;

  /* clear the cycle counter */
  DWT->CYCCNT = 0;

  /* start the cycle counter */
  DWT->CTRL = 0x40000001;

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
