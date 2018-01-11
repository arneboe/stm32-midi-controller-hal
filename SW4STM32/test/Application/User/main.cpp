#include "display/Adafruit_SSD1306.h"
#include "main.h"
#include "hardwareSetup/Hardware.h"

void testdrawline(Adafruit_SSD1306& display) {
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);

  }
  display.display();

  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);

  }
  display.display();

  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);

  }
  display.display();
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);

  }
  display.display();

  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);

  }
  display.display();
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);

  }
  display.display();

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);

  }
  display.display();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE);

  }
  display.display();
}

void testscrolltext(Adafruit_SSD1306& display) {

}

#define FIRST_LINE_BELOW_YELLOW 16

int main(void)
{
	Hardware::init();

	Adafruit_SSD1306 display(Hardware::i2c);
	display.begin(SSD1306_SWITCHCAPVCC, 0x78);

	uint8_t i = 0;
	uint32_t t = 0;
	while (1)
	{
		const uint32_t start = HAL_GetTick();
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

		t = HAL_GetTick() - start;

		display.setTextSize(3);
		display.setTextWrap(true);
		display.println("STAGE");
		display.println("STROBO");


		display.setTextSize(2);
		display.setCursor(0, 0);
		display.print(t);
		display.println("   LOG");

		//FIXME display muss mit dma laufen, sonst dauert das 25ms. In der zeit darf ich nicht blockieren sonst laggt midi
		display.display();


//		HAL_Delay(3000);
	}

}
