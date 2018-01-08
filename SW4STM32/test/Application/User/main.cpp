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


	printf("A\r\n");
	Adafruit_SSD1306 display(Hardware::i2c);
	printf("B\r\n");
	display.begin(SSD1306_SWITCHCAPVCC, 0x78);
	printf("C\r\n");

  int i = 0;
  while (1)
  {
	  ++i;
    Hardware::blink();
    display.dim((i % 2) == 0);
    testdrawline(display);
    display.clearDisplay();
//    display.drawLine(0, 5, display.width(), 5, WHITE);
    display.drawFastHLine(0, FIRST_LINE_BELOW_YELLOW - 1 , 128, WHITE);

    display.setTextColor(WHITE);
    display.setCursor(0, FIRST_LINE_BELOW_YELLOW);

    display.setTextSize(2);
    display.setTextWrap(true);
    display.println("NANANANA");
    display.display();


    HAL_Delay(3000);
   printf("AAAAA %d\r\n", i);
  }

}
