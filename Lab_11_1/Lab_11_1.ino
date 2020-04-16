#include <SPI.h> 
#define Data_pin 11
#define Clock_pin 13
#define SS_pin1 10
#define SS_pin2 9
#define EncoderB 3
#define EncoderA 2
#define MOTOR_D1 8
#define MOTOR_D2 7
#define MOTOR_PWM 6
#define LED 4

volatile int enCount = 0;
volatile int enDir;
int j = 0;

int map7seg[10] = {
  0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
  0x07, //7
    0x7F, //8
    0x6F  //9
};

void setup(){
  pinMode(Data_pin, OUTPUT);
  pinMode(Clock_pin, OUTPUT);
  pinMode(SS_pin1, OUTPUT);
  pinMode(SS_pin2, OUTPUT);
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(MOTOR_D1, OUTPUT);
  pinMode(MOTOR_D2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(EncoderA),
                  ChannelA, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB),
                  ChannelB, RISING);
}

void loop(){
  int control_value = 100;
  //int control_value = -100;
  setSpeed(control_value);
  Serial.print(control_value);
  Serial.print(" , ");
  Serial.print(enCount);
  Serial.print(" , ");
  Serial.println(enDir);
}

void moveForward(int velo){
  digitalWrite(MOTOR_D1, LOW);
  digitalWrite(MOTOR_D2, HIGH);
  analogWrite(MOTOR_PWM, velo);
}

void moveBackward(int velo){
  digitalWrite(MOTOR_D1, HIGH);
  digitalWrite(MOTOR_D2, LOW);
  analogWrite(MOTOR_PWM, velo);
}

void setSpeed(int i){
  if(i > 0 && i < 255){
    moveForward(i);
  }
  if(i < 0 && i > -255){
    int vv = i*(-1);
    moveBackward(i);
  }
  digitalWrite(LED, enDir);
  int j = enCount/100;
  write7segment(j);
}

void spi_write1(unsigned char cData){
  shiftOut(Data_pin, Clock_pin, MSBFIRST, cData);
    digitalWrite(SS_pin1, HIGH);
    digitalWrite(SS_pin1, LOW);
}
void spi_write2(unsigned char cData){
  shiftOut(Data_pin, Clock_pin, MSBFIRST, cData);
    digitalWrite(SS_pin2, HIGH);
    digitalWrite(SS_pin2, LOW);
}
void write7segment(int num){
  int luk10 = num/10;
  int luk1  = num%10;
  spi_write1(map7seg[luk10]);
  spi_write2(map7seg[luk1]);
}
void ChannelA() {
  if (digitalRead(EncoderA) == 1 
      && digitalRead(EncoderB) == 0) {
    enCount--;
    enDir = 0;
  }
}
void ChannelB() {
  if (digitalRead(EncoderA) == 0 
      && digitalRead(EncoderB) == 1){
    enCount++;
    enDir = 1;
  }
}
