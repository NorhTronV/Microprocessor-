#define DATA_PINa 11
#define CLOCK_PINa 13
#define LATCH_PINa 10
#define DATA_PINb 6
#define CLOCK_PINb 4
#define LATCH_PINb 5

int i=0;

void setup()
{
  pinMode(DATA_PINa,OUTPUT);
  pinMode(CLOCK_PINa,OUTPUT);
  pinMode(LATCH_PINa,OUTPUT);
  pinMode(DATA_PINb,OUTPUT);
  pinMode(CLOCK_PINb,OUTPUT);
  pinMode(LATCH_PINb,OUTPUT);
}

void loop()
{
   for (int i=0; i<8; i++) {
    shiftOut(DATA_PINa, CLOCK_PINa, MSBFIRST, B00000001 << i);
    digitalWrite(LATCH_PINa, HIGH);
    delay(125); 
    digitalWrite(LATCH_PINa, LOW);
  }
    shiftOut(DATA_PINa, CLOCK_PINa, MSBFIRST, B00000000);
    digitalWrite(LATCH_PINa, HIGH);
    delay(125); 
    digitalWrite(LATCH_PINa, LOW);
  
  for (int i=0; i<8; i++) {
    shiftOut(DATA_PINb, CLOCK_PINb, MSBFIRST, B00000001 << i);
    digitalWrite(LATCH_PINb, HIGH);
    delay(125); 
    digitalWrite(LATCH_PINb, LOW);
  }
  
  
  for (int i=0; i<8; i++) {
    shiftOut(DATA_PINb, CLOCK_PINb, MSBFIRST, B10000000 >> i);
    digitalWrite(LATCH_PINb, HIGH);
    delay(125);  
    digitalWrite(LATCH_PINb, LOW);
  }
    shiftOut(DATA_PINb, CLOCK_PINb, MSBFIRST, B00000000);
    digitalWrite(LATCH_PINb, HIGH);
    delay(125);  
    digitalWrite(LATCH_PINb, LOW);
  
   for (int i=0; i<8; i++) {
    shiftOut(DATA_PINa, CLOCK_PINa, MSBFIRST, B10000000 >> i);
    digitalWrite(LATCH_PINa, HIGH);
    delay(125);  
    digitalWrite(LATCH_PINa, LOW);
  }
} 
