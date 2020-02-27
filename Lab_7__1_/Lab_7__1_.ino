#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SWITCH_PIN1 4
#define SWITCH_PIN2 5

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool sw1 = 0;
bool sw2 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SWITCH_PIN1, INPUT_PULLUP);
  pinMode(SWITCH_PIN2, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
 
  
 
}

void loop() {
  // put your main code here, to run repeatedly:
//    
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("SW1");
    display.drawCircle(90, 8, 8, WHITE);
    display.println("SW2");
    display.drawCircle(90, 35, 8, WHITE);
    sw1 = digitalRead(SWITCH_PIN1);
    sw2 = digitalRead(SWITCH_PIN2);
    Serial.println(sw1);
//    Serial.println(digitalRead(SWITCH_PIN2));
    if(sw1 == LOW)
    {
      display.fillCircle(90, 8, 8, WHITE);
      
    }
    
    if(sw2 == LOW)
    {
      display.fillCircle(90, 35, 8, WHITE);
    }
    display.display();
    
}
