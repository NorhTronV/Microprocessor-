#define EncoderB 3
#define EncoderA 2
#define MOTOR_D1 8
#define MOTOR_D2 7
#define MOTOR_PWM 6

volatile int enCount = 0;
volatile int enDir;
int setpoint;

void setup(){
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(MOTOR_D1, OUTPUT);
  pinMode(MOTOR_D2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(EncoderA),
                  ChannelA, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB),
                  ChannelB, RISING);
}

void loop(){
  int val = analogRead(A0);
  setpoint = map (val,0,1023,0,360);
  int error = setpoint - enCount;
  int control_value= 3.5*(float)(error);
  setSpeed(control_value);
  Serial.print(control_value);
  Serial.print(" , ");
  Serial.println(enCount);
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
  if(i > 255)
    i=255;
  if(i < -255)
    i=-225;
  if(i > 0){
    moveForward(i);
  }
  if(i < 0){
    int vv = i*(-1);
    moveBackward(i);
  }
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
