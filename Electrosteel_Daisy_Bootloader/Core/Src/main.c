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
#include "fatfs.h"
#include "i2c.h"
#include "quadspi.h"
#include "sdmmc.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define QSPI_START  0x90000000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Initialize(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */
static void FS_FileOperations(void);
void qspi_initialize(uint8_t mode);
__attribute__((noreturn)) static void boot_to(uint32_t addr);
void qspi_enable_memory_mapped();
void i2cError(void);
void checkForNewFirmwareFromMainSynthBoard(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
FILINFO fno;
DIR dir;

uint8_t tempBinaryBuffer[262144] __ATTR_SRAM;
UINT bytesRead = 0;
uint32_t binSize = 4000;
uint8_t flash_mem[262144] __ATTR_QSPI;
uint8_t volatile bootloaderFlag[32] __ATTR_USER_FLASH;
uint8_t bootloader_button_pressed = 0;

/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction JumpToApplication;



#define APPLICATION_ADDRESS (uint32_t)0x24000000
volatile uint8_t memory_already_mapped = 0;
uint8_t boardNumber = 255;

void FlushECC(void *ptr, int bytes)
{

	uint32_t addr = (uint32_t)ptr;
	/* Check if accessing AXI SRAM => 64-bit words*/
	if(addr >= 0x24000000 && addr < 0x24080000){
		volatile uint64_t temp;
		volatile uint64_t* flush_ptr = (uint64_t*) (addr & 0xFFFFFFF8);
		uint64_t *end_ptr = (uint64_t*) ((addr+bytes) & 0xFFFFFFF8);

		do{
			temp = *flush_ptr;
			*flush_ptr = temp;
			flush_ptr++;
		}while(flush_ptr != end_ptr);
	}
	/* Otherwise 32-bit words */
	else {
		volatile uint32_t temp;
		volatile uint32_t* flush_ptr = (uint32_t*) (addr & 0xFFFFFFFC);
		uint32_t *end_ptr = (uint32_t*) ((addr+bytes) & 0xFFFFFFFC);

		do{
			temp = *flush_ptr;
			*flush_ptr = temp;
			flush_ptr++;
		}while(flush_ptr != end_ptr);
	}
}


uint8_t BSP_SD_IsDetected(void)
{
  __IO uint8_t status = SD_PRESENT;

  //if (BSP_PlatformIsDetected() == 0x0)
  {
    //status = SD_NOT_PRESENT;
  }

  return status;
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	  /* Enable I-Cache---------------------------------------------------------*/
	  //SCB_EnableICache();

	  /* Enable D-Cache---------------------------------------------------------*/
	  //SCB_EnableDCache();

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_QUADSPI_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* Enable write access to Backup domain */
     PWR->CR1 |= PWR_CR1_DBP;
     while((PWR->CR1 & PWR_CR1_DBP) == RESET)
     {
  	   ;
     }
     /*Enable BKPRAM clock*/
     __HAL_RCC_BKPRAM_CLK_ENABLE();
     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
     HAL_Delay(100);
 	int bit0 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
 	int bit1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
 	int bit2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
 	boardNumber = ((bit0 << 1)+(bit1 << 2)+(bit2));
 	if (boardNumber == 0)
 	{
		  //set up the master send control pin to signal other daisies to listen to I2C bus
		  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

 		  GPIO_InitTypeDef GPIO_InitStruct = {0};
		  GPIO_InitStruct.Pin = GPIO_PIN_12;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

		  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
 		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);


 		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 0)
 		{
 			bootloader_button_pressed = 1;
 		}
 		else
 		{
 			bootloader_button_pressed = 0;
 		}
 	}
    //if (*(__IO uint32_t*)(0x38800000+36) != 12345678)

	qspi_initialize(INDIRECT_POLLING);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);


	if (bootloader_button_pressed == 1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // tell the other ICs

		MX_I2C1_Init();
		MX_SDMMC1_SD_Init();
		MX_FATFS_Init();

		int i = 6;
		while(i--)
		{
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
		  HAL_Delay(100);
		}

		FS_FileOperations();

		if (!memory_already_mapped)
		{
		  qspi_enable_memory_mapped();
		}

		//copy qspi flash code into SRAM location on every boot.
		for (int i = 0; i < 262140; i++)
		{
		  tempBinaryBuffer[i] = flash_mem[i];
		}

		//wait for manual bootloader button to go up (lets us test things by holding the device in this state)
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 0)
		{
		  ;
		}
		//bring signal pin down to tell the other chips we're ready to send firmware over I2C
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_Delay(100); //wait for them to receive and get ready

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_I2C_Master_Transmit(&hi2c1, 34<<1, tempBinaryBuffer, 65535,
			10000);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_I2C_Master_Transmit(&hi2c1, 34<<1, tempBinaryBuffer+65535, 65535,
			10000);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_I2C_Master_Transmit(&hi2c1, 34<<1, tempBinaryBuffer+131070, 65535,
			10000);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_I2C_Master_Transmit(&hi2c1, 34<<1, tempBinaryBuffer+196605, 65535,
			10000);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);


		HAL_Delay(6000);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_QSPI_MspDeInit(&hqspi);
		HAL_I2C_DeInit(&hi2c1);
		HAL_SD_MspDeInit(&hsd1);

		HAL_RCC_DeInit();
		HAL_DeInit();
		SysTick->CTRL = 0;
		SysTick->LOAD = 0;
		SysTick->VAL  = 0;

		HAL_NVIC_SystemReset();

	}

    else
    {
		int i = 6;
		HAL_Delay(10);
		while(i--)
		{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
			HAL_Delay(60);
		}
		checkForNewFirmwareFromMainSynthBoard();
		if (!memory_already_mapped)
		{
		 	qspi_enable_memory_mapped();

		}
		//copy qspi flash code into SRAM location on every boot.
		for (int i = 0; i < 262140; i++)
		{
			tempBinaryBuffer[i] = flash_mem[i];
		}


		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
		JumpToApplication = (pFunction) (*(__IO uint32_t*) (APPLICATION_ADDRESS+4));
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_Delay(1);
		if (((uint32_t)JumpToApplication > 0x30000000) ||  ((uint32_t)JumpToApplication < 0x24000000) )
		{
			//out of range, not a valid firmware
			while(1)
			{
				if (memory_already_mapped)
				{
					qspi_initialize(INDIRECT_POLLING);
				}
				HAL_Delay(1);
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
			}
		}
		//otherwise, boot it up!
		HAL_QSPI_MspDeInit(&hqspi);

		HAL_RCC_DeInit();
		HAL_DeInit();
		__disable_irq();

		NVIC->ICER[0] = 0xFFFFFFFF;
		NVIC->ICER[1] = 0xFFFFFFFF;
		NVIC->ICER[2] = 0xFFFFFFFF;
		NVIC->ICER[3] = 0xFFFFFFFF;
		NVIC->ICER[4] = 0xFFFFFFFF;
		NVIC->ICER[5] = 0xFFFFFFFF;
		NVIC->ICER[6] = 0xFFFFFFFF;
		NVIC->ICER[7] = 0xFFFFFFFF;

		NVIC->ICPR[0] = 0xFFFFFFFF;
		NVIC->ICPR[1] = 0xFFFFFFFF;
		NVIC->ICPR[2] = 0xFFFFFFFF;
		NVIC->ICPR[3] = 0xFFFFFFFF;
		NVIC->ICPR[4] = 0xFFFFFFFF;
		NVIC->ICPR[5] = 0xFFFFFFFF;
		NVIC->ICPR[6] = 0xFFFFFFFF;
		NVIC->ICPR[7] = 0xFFFFFFFF;

		SysTick->CTRL = 0;
		SysTick->LOAD = 0; // Needed?
		SysTick->VAL = 0;  // Needed?
		SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;

		SCB->SHCSR &= ~(SCB_SHCSR_USGFAULTENA_Msk | //
						SCB_SHCSR_BUSFAULTENA_Msk | //
						SCB_SHCSR_MEMFAULTENA_Msk);

		__set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
		__set_PSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
		SCB->VTOR = APPLICATION_ADDRESS;
		__set_CONTROL(0);


		SysTick->CTRL = 0;
		SysTick->LOAD = 0;
		SysTick->VAL  = 0;

		JumpToApplication();
	}








  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 6;
  RCC_OscInitStruct.PLL.PLLR = 8;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void i2cError(void)
{
	while(1)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_Delay(1000);
	}
}

void qspi_error(void)
{
	while(1)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_Delay(500);
	}

}

int AutopollingMemReady(int timeout)
{
	 int ok = 0;
	QSPI_CommandTypeDef     s_command;
	    QSPI_AutoPollingTypeDef s_config;

	    /* Configure automatic polling mode to wait for memory ready */
	    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	    s_command.Instruction       = READ_STATUS_REG_CMD;
	    s_command.AddressMode       = QSPI_ADDRESS_NONE;
	    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	    s_command.DataMode          = QSPI_DATA_1_LINE;
	    s_command.DummyCycles       = 0;
	    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	    s_config.Match         = 0;
	    s_config.MatchMode     = QSPI_MATCH_MODE_AND;
	    s_config.Interval      = 0x10;
	    s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
	    s_config.Mask          = IS25LP064A_SR_WIP;
	    //s_config.Mask            = 0;
	    s_config.StatusBytesSize = 1;

	    if(HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, timeout)
	       != HAL_OK)
	    {
	    	qspi_error();
	    }

	    ok= 1;
	    return ok;

}

int qspi_WriteEnable()
{
	 int ok = 0;
	QSPI_CommandTypeDef     s_command;
	    QSPI_AutoPollingTypeDef s_config;

	    /* Enable write operations */
	    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	    s_command.Instruction       = WRITE_ENABLE_CMD;
	    s_command.AddressMode       = QSPI_ADDRESS_NONE;
	    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	    s_command.DataMode          = QSPI_DATA_NONE;
	    s_command.DummyCycles       = 0;
	    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	    //RETURN_IF_ERR(CheckProgramMemory());

	    if(HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != HAL_OK)
	    {
	    	qspi_error();
	    }

	    /* Configure automatic polling mode to wait for write enabling */
	    //        s_config.Match           = IS25LP080D_SR_WREN | (IS25LP080D_SR_WREN << 8);
	    //        s_config.Mask            = IS25LP080D_SR_WREN | (IS25LP080D_SR_WREN << 8);
	    s_config.MatchMode       = QSPI_MATCH_MODE_AND;
	    s_config.Match           = IS25LP064A_SR_WREN;
	    s_config.Mask            = IS25LP064A_SR_WREN;
	    s_config.Interval        = 0x10;
	    s_config.StatusBytesSize = 1;
	    s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

	    s_command.Instruction = READ_STATUS_REG_CMD;
	    s_command.DataMode    = QSPI_DATA_1_LINE;

	    if(HAL_QSPI_AutoPolling(
	           &hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != HAL_OK)
	    {
	    	qspi_error();
	    }

	    ok= 1;
	    return ok;

}

void qspi_reset_memory(void)
{
	//reset memory
		QSPI_CommandTypeDef s_command;

		    /* Initialize the reset enable command */
		    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
		    s_command.Instruction       = RESET_ENABLE_CMD;
		    s_command.AddressMode       = QSPI_ADDRESS_NONE;
		    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
		    s_command.DataMode          = QSPI_DATA_NONE;
		    s_command.DummyCycles       = 0;
		    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
		    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
		    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

		    /* Send the command */
		    if(HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
		       != HAL_OK)
		    {
		    	qspi_error();
		    }

		    /* Send the reset memory command */
		    s_command.Instruction = RESET_MEMORY_CMD;
		    if(HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
		       != HAL_OK)
		    {
		    	qspi_error();
		    }


		    /* Configure automatic polling mode to wait the memory is ready */
		    if(AutopollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
		       != 1)
		    {
		    	qspi_error();
		    }

}

void qspi_dummy_cycles_config()
{
	 QSPI_CommandTypeDef s_command;
	    uint16_t            reg     = 0;
	    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	    s_command.AddressMode       = QSPI_ADDRESS_NONE;
	    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	    s_command.DataMode          = QSPI_DATA_1_LINE;
	    s_command.DummyCycles       = 0;
	    s_command.NbData            = 1;
	    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	    // Only volatile Read Params on 16MB chip.
	           // Explicitly set:
	           // Burst Length: 8 bytes (0, 0)
	           // Wrap Enable: 0
	           // Dummy Cycles: (Config 3, bits 1 0)
	           // Drive Strength (50%, bits 1 1 1)
	           // Byte to write: 0b11110000 (0xF0)
	           // TODO: Probably expand Burst to maximum if that works out.

	           reg = 0xF0;
	           /* Update volatile configuration register (with new dummy cycles) */
	             s_command.Instruction = WRITE_READ_PARAM_REG_CMD;
	             /* Configure the write volatile configuration register command */
	             if(HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	                != HAL_OK)
	             {
	            	 qspi_error();
	             }

	             /* Transmission of the data */
	             if(HAL_QSPI_Transmit(
	                    &hqspi, (uint8_t*)(&reg), HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	                != HAL_OK)
	             {
	            	 qspi_error();
	             }

	             /* Configure automatic polling mode to wait the memory is ready */
	             if(AutopollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	                != 1)
	             {
	            	 qspi_error();
	             }
}

void qspi_quad_enable()
{
	 QSPI_CommandTypeDef     s_command;
	    QSPI_AutoPollingTypeDef s_config;
	    uint8_t                 reg = 0;

	    /* Enable write operations */
	    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	    s_command.Instruction       = WRITE_STATUS_REG_CMD;
	    s_command.AddressMode       = QSPI_ADDRESS_NONE;
	    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	    s_command.DataMode          = QSPI_DATA_1_LINE;
	    s_command.DummyCycles       = 0;
	    s_command.NbData            = 1;
	    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	    /* Enable write operations */
	    if(qspi_WriteEnable() != 1)
	    {
	    	qspi_error();
	    }

	    if(HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != HAL_OK)
	    {
	    	qspi_error();
	    }


	    //    reg = 0;
	    //    MODIFY_REG(reg,
	    //        0xF0,
	    //        (IS25LP08D_SR_QE));
	    reg = IS25LP064A_SR_QE; // Set QE bit  to 1
	    /* Transmission of the data */
	    if(HAL_QSPI_Transmit(
	           &hqspi, (uint8_t*)(&reg), HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != HAL_OK)
	    {
	    	qspi_error();
	    }

	    /* Configure automatic polling mode to wait for write enabling */
	    //    s_config.Match           = IS25LP08D_SR_WREN | (IS25LP08D_SR_WREN << 8);
	    //    s_config.Mask            = IS25LP08D_SR_WREN | (IS25LP08D_SR_WREN << 8);
	    //    s_config.MatchMode       = QSPI_MATCH_MODE_AND;
	    //    s_config.StatusBytesSize = 2;
	    s_config.Match           = IS25LP064A_SR_QE;
	    s_config.Mask            = IS25LP064A_SR_QE;
	    s_config.MatchMode       = QSPI_MATCH_MODE_AND;
	    s_config.StatusBytesSize = 1;

	    s_config.Interval      = 0x10;
	    s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	    s_command.Instruction = READ_STATUS_REG_CMD;
	    s_command.DataMode    = QSPI_DATA_1_LINE;

	    if(HAL_QSPI_AutoPolling(
	           &hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != HAL_OK)
	    {
	    	qspi_error();
	    }

	    /* Configure automatic polling mode to wait the memory is ready */
	    if(AutopollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != 1)
	    {
	    	qspi_error();
	    }

}

void qspi_enable_memory_mapped()
{
	   QSPI_CommandTypeDef      s_command;
	    QSPI_MemoryMappedTypeDef s_mem_mapped_cfg;

	    /* Configure the command for the read instruction */
	    s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	    s_command.Instruction     = QUAD_INOUT_FAST_READ_CMD;
	    s_command.AddressMode     = QSPI_ADDRESS_4_LINES;
	    s_command.AddressSize     = QSPI_ADDRESS_24_BITS;
	    //    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	    //s_command.DummyCycles       = IS25LP080D_DUMMY_CYCLES_READ_QUAD;
	    s_command.AlternateByteMode  = QSPI_ALTERNATE_BYTES_4_LINES;
	    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	    s_command.AlternateBytes     = 0x000000A0;
	    s_command.DummyCycles        = 6;
	    s_command.DdrMode            = QSPI_DDR_MODE_DISABLE;
	    s_command.DdrHoldHalfCycle   = QSPI_DDR_HHC_ANALOG_DELAY;
	    //s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	    s_command.SIOOMode = QSPI_SIOO_INST_ONLY_FIRST_CMD;
	    s_command.DataMode = QSPI_DATA_4_LINES;

	    /* Configure the memory mapped mode */
	    s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
	    s_mem_mapped_cfg.TimeOutPeriod     = 0;
	    uint32_t qspiresult = HAL_QSPI_MemoryMapped(&hqspi, &s_command, &s_mem_mapped_cfg);
	    if(qspiresult
	       != HAL_OK)
	    {
	    	qspi_error();
	    }
	    memory_already_mapped = 1;
}

void qspi_initialize(uint8_t mode)
{
	HAL_QSPI_DeInit(&hqspi);
	HAL_QSPI_Init(&hqspi);

	qspi_reset_memory();
	qspi_dummy_cycles_config();
	qspi_quad_enable();
	if (mode == MEMORY_MAPPED)
	{
		qspi_enable_memory_mapped();
	}
	else
	{
		memory_already_mapped = 0;
	}
}

void qspi_SetMode(uint8_t mode)
{
	if (mode == INDIRECT_POLLING)
	{
		//qspi_initialize(INDIRECT_POLLING);
	}
	else if (mode == MEMORY_MAPPED)
	{
		qspi_enable_memory_mapped();
	}

}

int qpsi_EraseSector(uint32_t address)
{
    int ok = 0;
	uint8_t             use_qpi = 0;
    QSPI_CommandTypeDef s_command;
    if(use_qpi)
    {
        s_command.InstructionMode = QSPI_INSTRUCTION_4_LINES;
        s_command.Instruction     = SECTOR_ERASE_QPI_CMD;
        s_command.AddressMode     = QSPI_ADDRESS_4_LINES;
    }
    else
    {
        s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
        s_command.Instruction     = SECTOR_ERASE_CMD;
        s_command.AddressMode     = QSPI_ADDRESS_1_LINE;
    }
    s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    s_command.Address           = address;


    // Erasing takes a long time anyway, so not much point trying to
    // minimize reinitializations
    qspi_SetMode(INDIRECT_POLLING);

    if(qspi_WriteEnable() != 1)
    {
    	qspi_error();
    }
    if(HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
       != HAL_OK)
    {
    	qspi_error();
    }
    if(AutopollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
       != 1)
    {
    	qspi_error();
    }

    //qspi_SetMode(MEMORY_MAPPED);

    ok= 1;
    return ok;

}


void qspi_Erase(uint32_t start_addr, uint32_t end_addr)
{
    uint32_t block_addr;
    uint32_t block_size = IS25LP064A_SECTOR_SIZE; // 4kB blocks for now.
    // 64kB chunks for now.
    start_addr = start_addr - (start_addr % block_size);
    while(end_addr > start_addr)
    {
        block_addr = start_addr & 0x0FFFFFFF;
        if(qpsi_EraseSector(block_addr) != 1)
        {
        	qspi_error();
        }
        start_addr += block_size;
    }
}

int qspi_WritePage(uint32_t address, uint32_t size, uint8_t* buffer, uint8_t     reset_mode)
{
	  //RETURN_IF_ERR(CheckProgramMemory());
	int ok = 0;

	qspi_SetMode(INDIRECT_POLLING);

	    QSPI_CommandTypeDef s_command;
	    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	    s_command.Instruction       = PAGE_PROG_CMD;
	    s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
	    s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	    s_command.DataMode          = QSPI_DATA_1_LINE;
	    s_command.DummyCycles       = 0;
	    s_command.NbData            = size <= 256 ? size : 256;
	    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	    s_command.Address           = address;
	    if(qspi_WriteEnable() != 1)
	    {
	    	qspi_error();
	    }
	    if(HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != HAL_OK)
	    {
	    	qspi_error();
	    }
	    if(HAL_QSPI_Transmit(
	           &hqspi, (uint8_t*)buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != HAL_OK)
	    {
	    	qspi_error();
	    }
	    if(AutopollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
	       != 1)
	    {
	    	qspi_error();
	    }

	    if(reset_mode)
	    	qspi_SetMode(MEMORY_MAPPED);

	    ok= 1;
	    return ok;

}

void qspi_Write(uint32_t address, uint32_t size, uint8_t* buffer)
{
	 uint32_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	    uint32_t QSPI_DataNum    = 0;
	    uint32_t flash_page_size = IS25LP064A_PAGE_SIZE;
	    address                  = address & 0x0FFFFFFF;
	    Addr                     = address % flash_page_size;
	    count                    = flash_page_size - Addr;
	    NumOfPage                = size / flash_page_size;
	    NumOfSingle              = size % flash_page_size;

	    if(Addr == 0) /*!< Address is QSPI_PAGESIZE aligned  */
	    {
	        if(NumOfPage == 0) /*!< NumByteToWrite < QSPI_PAGESIZE */
	        {
	            QSPI_DataNum = size;
	            qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	        }
	        else /*!< Size > QSPI_PAGESIZE */
	        {
	            while(NumOfPage--)
	            {
	                QSPI_DataNum = flash_page_size;
	                qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	                address += flash_page_size;
	                buffer += flash_page_size;
	            }

	            QSPI_DataNum = NumOfSingle;
	            if(QSPI_DataNum > 0)
	            	qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	        }
	    }
	    else /*!< Address is not QSPI_PAGESIZE aligned  */
	    {
	        if(NumOfPage == 0) /*!< Size < QSPI_PAGESIZE */
	        {
	            if(NumOfSingle > count) /*!< (Size + Address) > QSPI_PAGESIZE */
	            {
	                temp         = NumOfSingle - count;
	                QSPI_DataNum = count;
	                qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	                address += count;
	                buffer += count;
	                QSPI_DataNum = temp;
	                qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	            }
	            else
	            {
	                QSPI_DataNum = size;
	                qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	            }
	        }
	        else /*!< Size > QSPI_PAGESIZE */
	        {
	            size -= count;
	            NumOfPage    = size / flash_page_size;
	            NumOfSingle  = size % flash_page_size;
	            QSPI_DataNum = count;
	            qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	            address += count;
	            buffer += count;

	            while(NumOfPage--)
	            {
	                QSPI_DataNum = flash_page_size;
	                qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	                address += flash_page_size;
	                buffer += flash_page_size;
	            }

	            if(NumOfSingle != 0)
	            {
	                QSPI_DataNum = NumOfSingle;
	                qspi_WritePage(address, QSPI_DataNum, buffer, 0);
	            }
	        }
	    }

	    qspi_SetMode(MEMORY_MAPPED);


}



static void FS_FileOperations(void)
{
	HAL_Delay(500);
	disk_initialize(0);
    disk_status(0);
    //if (statusH != RES_OK)
    //{
      //ShowDiskStatus(status);
    //}


	if(f_mount(&SDFatFS,  SDPath, 1) == FR_OK)
	{

		FRESULT res;


		//search for .bin firmware files
		res = f_findfirst(&dir, &fno, SDPath, "Electrosteel_Daisy_Audio.bin");

		/* Repeat while an item is found */
		if (fno.fname[0])
		{
		  if(res == FR_OK)
		  {
				if(f_open(&SDFile, fno.fname, FA_OPEN_ALWAYS | FA_READ) == FR_OK)
				{

					//write to local SRAM, then copy that to QSPI flash for more permanent storage
					f_read(&SDFile, &tempBinaryBuffer, f_size(&SDFile), &bytesRead);



					if (bytesRead < 262140)
					{
						qspi_Erase(QSPI_START, QSPI_START+262140);
						qspi_Write(QSPI_START, 262140,(uint8_t*)tempBinaryBuffer);
						//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
					}

					f_close(&SDFile);

				}
			}


		  }

		f_closedir(&dir);
		f_mount(0, "", 0); //unmount
	}


}

void checkForNewFirmwareFromMainSynthBoard(void)
{
	if (boardNumber != 0)
	{
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) ==  1)
		{
			HAL_StatusTypeDef returnVal = 0;

			MX_I2C1_Init();

			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) ==  1)
			{
				uint8_t fader = 0;
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
				HAL_Delay(63-fader);//wait for pin to go back low
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
				HAL_Delay(fader);//wait for pin to go back low
				fader = (fader+1) % 64;

			}
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
			returnVal = HAL_I2C_Slave_Receive(&hi2c1, tempBinaryBuffer, 65535,
					10000);
			if (returnVal != HAL_OK)
			{
				i2cError();
			}
			int i = 6;
			while(i--)
			{
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
				HAL_Delay(30);
			}
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
			returnVal = HAL_I2C_Slave_Receive(&hi2c1, tempBinaryBuffer+65535, 65535,
					10000);
			if (returnVal != HAL_OK)
			{
				i2cError();
			}
			i = 6;
			while(i--)
			{
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
				HAL_Delay(30);
			}

			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
			returnVal = HAL_I2C_Slave_Receive(&hi2c1, tempBinaryBuffer+131070, 65535,
					10000);
			if (returnVal != HAL_OK)
			{
				i2cError();
			}
			i = 6;
			while(i--)
			{
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
				HAL_Delay(30);
			}

			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
			returnVal = HAL_I2C_Slave_Receive(&hi2c1, tempBinaryBuffer+196605, 65535,
					10000);
			if (returnVal != HAL_OK)
			{
				i2cError();
			}
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
			i = 6;
			while(i--)
			{
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
				HAL_Delay(30);
			}

			qspi_Erase(QSPI_START, QSPI_START+262140);
			qspi_Write(QSPI_START, 262140,(uint8_t*)tempBinaryBuffer);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
			  if (!memory_already_mapped)
			  {
				  qspi_enable_memory_mapped();

			  }
			  i = 6;
				while(i--)
				{
					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
					HAL_Delay(30);
				}
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);

    	  HAL_I2C_DeInit(&hi2c1);
	 	  HAL_QSPI_MspDeInit(&hqspi);
		  HAL_RCC_DeInit();
		  HAL_DeInit();
  	 	  SysTick->CTRL = 0;
  	 	  SysTick->LOAD = 0;
  	 	  SysTick->VAL  = 0;
  	 	  HAL_NVIC_SystemReset();

		}
	}

}

// EXTI Line12 External Interrupt ISR Handler CallBackFun
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

}


__attribute__((noreturn)) static void boot_to(uint32_t addr)
{
    const uint32_t *vtor = (uint32_t *)addr;
    __disable_irq();
   // SCB_InvalidateDCache();
   // SCB_InvalidateICache();
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICER[1] = 0xFFFFFFFF;
    NVIC->ICER[2] = 0xFFFFFFFF;
    NVIC->ICER[3] = 0xFFFFFFFF;
    NVIC->ICER[4] = 0xFFFFFFFF;
    NVIC->ICER[5] = 0xFFFFFFFF;
    NVIC->ICER[6] = 0xFFFFFFFF;
    NVIC->ICER[7] = 0xFFFFFFFF;

    NVIC->ICPR[0] = 0xFFFFFFFF;
    NVIC->ICPR[1] = 0xFFFFFFFF;
    NVIC->ICPR[2] = 0xFFFFFFFF;
    NVIC->ICPR[3] = 0xFFFFFFFF;
    NVIC->ICPR[4] = 0xFFFFFFFF;
    NVIC->ICPR[5] = 0xFFFFFFFF;
    NVIC->ICPR[6] = 0xFFFFFFFF;
    NVIC->ICPR[7] = 0xFFFFFFFF;

    SysTick->CTRL = 0;
    SysTick->LOAD = 0; // Needed?
    SysTick->VAL = 0;  // Needed?
    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;

    SCB->SHCSR &= ~(SCB_SHCSR_USGFAULTENA_Msk | //
                    SCB_SHCSR_BUSFAULTENA_Msk | //
                    SCB_SHCSR_MEMFAULTENA_Msk);
    SCB->VTOR = addr;
    __set_MSP(vtor[0]);
    __set_PSP(vtor[0]);
    __set_CONTROL(0);
    void (*entry)(void) __attribute__((noreturn)) = (void *)vtor[1];
    entry();
    for (;;)
        ;
}
/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x90000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_8MB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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
