#define MOTOR_D1 7
#define MOTOR_D2 8
#define MOTOR_PWM 6

void setVelocity(int velo) {
  if(velo > 0 && velo < 256){
    digitalWrite(MOTOR_D1,HIGH);
    digitalWrite(MOTOR_D2,LOW);
    analogWrite(MOTOR_PWM,velo);
    delay(1000);
  }
  if(velo < 0 && velo > -256){
    velo = velo*(-1);
    digitalWrite(MOTOR_D1,LOW);
    digitalWrite(MOTOR_D2,HIGH);
    analogWrite(MOTOR_PWM,velo);
    delay(1000);
  }
  else{
    digitalWrite(MOTOR_D1,LOW);
    digitalWrite(MOTOR_D2,LOW);
  }
}

void setup() {
  pinMode(MOTOR_D1,OUTPUT);
  pinMode(MOTOR_D2,OUTPUT);
  pinMode(MOTOR_PWM,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  setVelocity(255);
  setVelocity(-255);
  setVelocity(0);
}
