#include<SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
#define BUTTON_UP A0
#define BUTTON_DOWN A1
#define BUTTON_CD A2

int map7seg[10] = {
  0x3f, //0
  0x06, //1
  0x5b, //2
  0x4f, //3
  0x66, //4
  0x6d, //5
  0x7d, //6
  0x07, //7
  0x7f, //8
  0x6f, //9
};

void spi_write_1(unsigned char cData){
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST, cData);
  digitalWrite(SS_PIN_1,HIGH);
  digitalWrite(SS_PIN_1,LOW);

}
void spi_write_2(unsigned char cData){
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST, cData);
  digitalWrite(SS_PIN_2,HIGH);
  digitalWrite(SS_PIN_2,LOW);
}
void setup()
{
  Serial.begin(9600);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_CD, INPUT_PULLUP);
  
  spi_write_2(map7seg[0]);
  spi_write_1(map7seg[0]);
}

void loop()
{ 
  for(int i = 0 ; i < 100 ; i++){
    spi_write_1(map7seg[i/10]);
    spi_write_2(map7seg[i%10]);
    delay(300);
  }
}
