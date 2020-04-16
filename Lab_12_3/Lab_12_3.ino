#define EncoderA 2
#define EncoderB 3
#define MOTOR_D1 8
#define MOTOR_D2 7
#define MOTOR_PWM 6
#define SW1 5
#define SW2 4

unsigned long preMilli = 0;
unsigned long state = LOW;
int speedMotor = 100;

void setup(){
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(MOTOR_D1, OUTPUT);
  pinMode(MOTOR_D2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(SW1),
                  ChannelA,FALLING);
  attachInterrupt(digitalPinToInterrupt(SW2),
                  ChannelB,FALLING);
}
void loop(){
  unsigned long curMilli = millis();
  if(curMilli - preMilli >= 500){
    state = !state;
    digitalWrite(10, state);
    preMilli = curMilli;
  }
  setSpeed(speedMotor);
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
  if(i>0)
    moveForward(i);
  if(i<0){
    int j = i*(-1);
    moveBackward(j);
  }
}
void ChannelA() {
  digitalWrite(MOTOR_D1, LOW);
  digitalWrite(MOTOR_D2, LOW);
  speedMotor = 100;
  Serial.print("O");
}
void ChannelB() {
  digitalWrite(MOTOR_D1, LOW);
  digitalWrite(MOTOR_D2, LOW);
  speedMotor = -100;
  Serial.print("K");
}
