#pragma once
#include "stm32f1xx_hal.h"


class Hardware
{
public:
	static I2C_HandleTypeDef i2c;
	static UART_HandleTypeDef uart;
	static DMA_HandleTypeDef dma_i2c1_tx;
	static ADC_HandleTypeDef adc1;
	static DMA_HandleTypeDef dma_adc1;

	static void init();

	static void blink();

	static void ErroHandler(char * file, int line, char* msg);
};
