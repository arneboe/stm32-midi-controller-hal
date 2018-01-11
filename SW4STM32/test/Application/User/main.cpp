#include "display/Adafruit_SSD1306.h"
#include "main.h"
#include "hardwareSetup/Hardware.h"



#define FIRST_LINE_BELOW_YELLOW 16

int main(void)
{
	Hardware::init();

	Adafruit_SSD1306 display(Hardware::i2c);
	display.begin(SSD1306_SWITCHCAPVCC, 0x78);

	uint8_t i = 0;
	uint32_t t = 0;

	printf("ALIVE!\n");

	while (1)
	{
//		printf("ALIVE!\n");
		++i;
//		Hardware::blink();
//		display.dim((i % 2) == 0);
//		testdrawline(display);
		display.clearDisplay();


		//TODO damit das zeichnen schnell wird, muss man ein partial update machen können irgendwie.
		//     println ist mega teuer, STAGE STROBO dauert 2ms zum printen. Nur printen wenn es sich ändert.
		//     Vorher nur die Flöche wo sich was ändert schwärzen.

		//    display.drawLine(0, 5, display.width(), 5, WHITE);
		display.drawFastHLine(0, FIRST_LINE_BELOW_YELLOW - 1 , 128, WHITE);

		display.setTextColor(WHITE);
		display.setCursor(0, FIRST_LINE_BELOW_YELLOW);



		display.setTextSize(3);
		display.setTextWrap(true);
		display.println("STAGE");
		display.println("STROBO");


		display.setTextSize(2);
		display.setCursor(0, 0);
		display.print(t);
		display.print(" ");
		display.print(i);
		display.println("   LOG");
		const uint32_t start = HAL_GetTick();
		//FIXME display muss mit dma laufen, sonst dauert das 25ms. In der zeit darf ich nicht blockieren sonst laggt midi
//		printf("BEFORE\n");
		display.display();
//		printf("after display\n");
		t = HAL_GetTick() - start;

//		printf("AA\n");
		//wait for dma to finish
		  while (HAL_I2C_GetState(&Hardware::i2c) != HAL_I2C_STATE_READY)
		  {
//			  switch(HAL_I2C_GetState(&Hardware::i2c))
//			  {
//			  case HAL_I2C_STATE_RESET:
//				  printf("reset\n");
//				  break;
//			  case HAL_I2C_STATE_BUSY:
//				  printf("busy\n");
//				  break;
//			  case HAL_I2C_STATE_BUSY_TX:
//				  printf("busy tx\”");
//				  break;
//			  case HAL_I2C_STATE_BUSY_RX:
//				  printf("busy rx\n");
//				  break;
//			  case HAL_I2C_STATE_ERROR:
//				  printf("error\n");
//				  break;
//			  default:
//				  printf("default\n");
//
//			  }

		  }

//	  printf("BB\n");



//		HAL_Delay(3000);
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

