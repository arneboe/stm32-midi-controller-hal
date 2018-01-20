#include "display/Adafruit_SSD1306.h"
#include "main.h"
#include "hardwareSetup/Hardware.h"



//NOTE this is later casted to uint32* but the dma is configured to write only half-words
volatile uint16_t adcValues[8] = {0};

#define FIRST_LINE_BELOW_YELLOW 16

void tcaselect(uint8_t i) {
	if (i > 7) return;

	uint8_t data[1] = {1 << i};

	if(HAL_I2C_Master_Transmit(&Hardware::i2c, 0xe0, data, 1, 10000) != HAL_OK)
	{
		printf("Failed to set addr %d\n", i);
	}
	else
	{
		printf("Set multiplexer target to %d\n", i);
	}
}

int main(void)
{
	Hardware::init();
	printf("ALIVE!\n");

	for(int i = 0; i <= 7; ++i)
	{
		tcaselect(i);
	}
	tcaselect(0);

	Adafruit_SSD1306 display(Hardware::i2c);
	display.begin(SSD1306_SWITCHCAPVCC, 0x78);
	display.fillScreen(WHITE);
	display.display();

	display.waitForReady();

	tcaselect(1);
	display.begin(SSD1306_SWITCHCAPVCC, 0x78);
	display.fillScreen(WHITE);
	display.display();

	while(1)  {}



	uint8_t i = 0;
	uint32_t t = 0;

	uint32_t tt = 0;




//	  while (HAL_I2C_GetState(&Hardware::i2c) != HAL_I2C_STATE_READY)
//	  {}

	while(1){

		for(int i = 0; i < 8; ++i)
		{
			printf("%d\t", adcValues[i]);
		}
		printf("\n");

//		++i;
//		display.clearDisplay();
//		display.drawFastHLine(0, FIRST_LINE_BELOW_YELLOW - 1 , 128, WHITE);
//
//		display.setTextSize(2);
//		display.setTextColor(WHITE);
//		display.setCursor(0, 0);
//		display.print(t);
//		display.print(" ");
//		display.print(i);
//		display.println("   LOG");
//
//		display.displayHeader();
//		const uint32_t start = HAL_GetTick();
//		while (HAL_I2C_GetState(&Hardware::i2c) != HAL_I2C_STATE_READY)
//			  {}
//		t = HAL_GetTick() - start;
	}



}



void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
  /* Toggle LED2: Transfer in reception process is correct */
  printf("hal callback comple\n");
}


/**
  * @brief  I2C error callbacks.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
	printf("hal callback error\n");
}

