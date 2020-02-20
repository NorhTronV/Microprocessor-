void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  Serial.println("START!!");
}

void loop() {
  int counter;
  for(counter = 0; counter <=120 ; counter++){
  Serial.println(counter);
    if(counter == 0 || counter<=120){
       digitalWrite(13,counter%2);
       delay(1000);
    }
    if(counter == 121){
      digitalWrite(13,0);
      Serial.println("STOP!!");
    }
  }
}
