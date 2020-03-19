const byte ledPin = 8;
const byte interruptPin = 2;
volatile byte state = LOW;
int i=1;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop(){
  digitalWrite(ledPin, state);
  delay(i*1000);
  state = !state;
}

void blink(){
  i++;
  if(i>3)
    i = 1;
}
