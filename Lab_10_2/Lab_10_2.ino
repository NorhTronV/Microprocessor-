#define ENA 2
#define ENB 3

//Exercise 2
int count = 0;

void setup(){
  pinMode(ENA, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("TestEncoder");
  
  attachInterrupt(digitalPinToInterrupt(ENA),
                  ISR_Ext, RISING);
}

void loop(){
  Serial.println(count);
}

void ISR_Ext(){
   count++;
}
