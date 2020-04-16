#define EncoderB 3
#define EncoderA 2
#define MOTOR_D1 8
#define MOTOR_D2 7
#define MOTOR_PWM 6
#include <EEPROM.h>

int currentMotorState = 0;
int motorspeed = 0;
int typespeed = 0;
int enCount = 0;

int errorI = 0;
float Kp = 1.0;
float Ki = 0.3;

void setup(){
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(MOTOR_D1, OUTPUT);
  pinMode(MOTOR_D2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  Serial.begin(9600);

  timer1(300);
  
  attachInterrupt(digitalPinToInterrupt(EncoderA),
  ChannelA,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB),
  ChannelB,RISING);
}

void loop(){
  typespeed = 100;
  int error = typespeed - motorspeed;
  int pid = Kp*(float)(error) + Ki*(float)(errorI);
  errorI += error;
  setSpeed(pid);
  
  Serial.print(typespeed);
  Serial.print(" | ");
  Serial.println(motorspeed);
}
void serialEvent() {
  typespeed = Serial.parseInt();
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
  if(i > 100)
    i=100;
  if(i < -100)
    i=-100;
  if(i > 0){
    moveForward(i);
  }
  if(i < 0){
    int vv = i*(-1);
    moveBackward(i);
  }
}
void timer1(int period){
  noInterrupts(); 
  TCCR1A = 0;
  TCCR1B = 0; 
  TCNT1 = 0;
  OCR1A = (16000000.0/(256.0*100.0))*period - 1;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}

void ChannelA() {
  if(digitalRead(EncoderA) == 1 && digitalRead(EncoderB) == 0){
    enCount++;
  }
}
void ChannelB() {
  if(digitalRead(EncoderA) == 0 && digitalRead(EncoderB) == 1){
    enCount--;
  }
}
ISR(TIMER1_COMPA_vect){
  motorspeed = enCount;
  enCount = 0;
}
