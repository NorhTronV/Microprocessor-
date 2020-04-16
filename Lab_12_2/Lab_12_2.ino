#define EncoderA 2
#define EncoderB 3
#define MOTOR_D1 8
#define MOTOR_D2 7
#define MOTOR_PWM 6

int currentState = 0;
int motorspeed = 0;
int typespeed = 0;
int enCount = 0;
int timer1_counter = 3200;
String buff;

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

  timer1_interrupt(5000);
  
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
  Serial.print(motorspeed);
  Serial.print(" | ");
  Serial.println(pid);
}

void SerialEvent(){
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if(inByte == 's' && currentState == 0){
      currentState = 1;
      buff = " ";
      }
    if(inByte == '-'&& currentState == 1){
      buff += inByte;
      } 
    if(('0'<= inByte) && (inByte <= '9') && (currentState == 1)){
      buff += inByte;
      }
    if((inByte == 'n') && (currentState == 1)){
      typespeed = buff.toInt();
      currentState = 0;
      }  
  }
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

void timer1_interrupt(int period){
  noInterrupts(); 
  TCCR1A = 0;
  TCCR1B = 0; 
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  OCR1A = (16000000.0/(256.0*100.0))*period - 1;
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
ISR(TIMER1_OVF_vect){
  TCNT1 = timer1_counter;
  motorspeed = 60.0*(enCount/200.0)/0.1;
  enCount = 0;
}
