#pragma once
#include "stm32f1xx_hal.h"


class Hardware
{
public:
	static I2C_HandleTypeDef i2c;
	static UART_HandleTypeDef uart;

	static void init();

	static void blink();
};
