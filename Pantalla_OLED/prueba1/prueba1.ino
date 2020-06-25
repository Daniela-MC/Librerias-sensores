#include <SPI.h>
//#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  48
#define OLED_CLK   53
#define OLED_DC    51
#define OLED_CS    50
#define OLED_RESET 52
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC); // Show initial display buffer contents on the screen --  // the library initializes this with an Adafruit splash screen.
                                        
  display.display();
  delay(1000);
  // Clear the buffer
  display.clearDisplay();
  display.display();

   testscrolltext(); // Draw scrolling text

}

void loop() {
  
}
void testscrolltext(void) {
  
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(12, 32);
  display.println(F("MATALLANA"));
  display.display();      // Show initial text
  delay(100);
  
  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
 // display.startscrollleft(0x00, 0x0F);
 // delay(2000);
 // display.stopscroll();
 // delay(1000);
  //display.startscrolldiagright(0x00, 0x07);
  //delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  //delay(2000);
  //display.stopscroll();
  //delay(1000);
}
