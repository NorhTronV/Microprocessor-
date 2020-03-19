bool toggle = 1;
volatile int timer1;
const byte ledPin = 8;
const byte interruptPin = 2;

int i,j;

void setup(){
  noInterrupts(); 
  TCCR1A = 0;
  TCCR1B = 0; 
  TCNT1 = timer1;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
  
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
  Serial.begin(9600);
}

void loop(){
  
}

ISR(TIMER1_OVF_vect){
  TCNT1 = timer1;
  i -= 1;
  if(i < 1){
    digitalWrite(8, toggle);
  }
  else if(i == 5){
    digitalWrite(8, HIGH);
    i += 3;
  }
  else if(i ==7){
    digitalWrite(8, LOW);
  }
  toggle = !toggle;
}

void blink(){
   j++;
  if(j%3 == 0){
    timer1 = 31250;
    i = 1;
  }
  else if(j%3 == 1){
    timer1 = 0;
    i = 1;
  }
  else if(j%3 == 2)
  {
    timer1 = 16125;
    i = 6;
  }
}
