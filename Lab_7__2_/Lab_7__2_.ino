
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ThreeWire.h>
#include <RtcDS1302.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ThreeWire myWire(4, 5, 2);
RtcDS1302<ThreeWire> Rtc(myWire);
void printDateTime(const RtcDateTime& dt)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(dt.Year(), DEC);
  display.print('/');
  display.print(dt.Month(), DEC);
  display.print('/');
  display.print(dt.Day(), DEC);
  display.print(' ');
  display.print(dt.Hour(), DEC);
  display.print(':');
  display.print(dt.Minute(), DEC);
  display.print(':');
  display.print(dt.Second(), DEC);
  display.display();


}
void setup() {
  // put your setup code here, to run once:

  Rtc.Begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  display.clearDisplay(); // clears the screen and buffer
  RtcDateTime setting_time(2020,2,26,11,37,10);// year, month, dayOfMonth, hour, minute, second
  printDateTime(setting_time);
  Rtc.SetDateTime(setting_time);//Try to comment This line

}

void loop() {
  // put your main code here, to run repeatedly:
  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  delay(500);
}
