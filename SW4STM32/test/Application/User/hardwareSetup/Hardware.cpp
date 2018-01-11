#include "Hardware.h"

void SystemClock_Config();
void MX_GPIO_Init();
void MX_USART1_UART_Init();
void MX_I2C1_Init();
void MX_DMA_Init();


I2C_HandleTypeDef Hardware::i2c;
UART_HandleTypeDef Hardware::uart;
DMA_HandleTypeDef Hardware::dma_i2c1_tx;

void Hardware::init()
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART1_UART_Init();
	MX_I2C1_Init();
}


extern "C"
{
//Retargets the C library printf function to the USART.
	int _write(int file, char* ptr, int len)
	{
		if(HAL_UART_Transmit(&Hardware::uart, (uint8_t*)ptr, len, 0xFFFF) != HAL_OK)
		{
			return -1;
		}
		return len;
	}
}


void Hardware::blink()
{
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
}


void _Error_Handler(char * file, int line)
{
	  while (1)
	  {
	    Hardware::blink();
	    HAL_UART_Transmit(&Hardware::uart, (uint8_t*)"ERR\r\n", 5, 0xFFFF);
	    HAL_Delay(600);
	  }
}
void Hardware::ErroHandler(char * file, int line, char* msg)
{
	printf("ERROR: %s, %d: %s\r\n", file, line, msg);
	  while (1)
	  {
	    Hardware::blink();
	    HAL_Delay(50);
	  }
}


#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
	printf("ASSERT: %s:%d\r\n", file, line);
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif



/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  Hardware::i2c.Instance = I2C1;
  Hardware::i2c.Init.ClockSpeed = 400000;
  Hardware::i2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
  Hardware::i2c.Init.OwnAddress1 = 0;
  Hardware::i2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  Hardware::i2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  Hardware::i2c.Init.OwnAddress2 = 0;
  Hardware::i2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  Hardware::i2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&Hardware::i2c) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

  Hardware::uart.Instance = USART1;
  Hardware::uart.Init.BaudRate = 115200;
  Hardware::uart.Init.WordLength = UART_WORDLENGTH_8B;
  Hardware::uart.Init.StopBits = UART_STOPBITS_1;
  Hardware::uart.Init.Parity = UART_PARITY_NONE;
  Hardware::uart.Init.Mode = UART_MODE_TX_RX;
  Hardware::uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  Hardware::uart.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&Hardware::uart) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

}

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED2_Pin */
  GPIO_InitStruct.Pin = LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);

}

