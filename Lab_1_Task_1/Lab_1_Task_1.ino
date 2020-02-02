void setup() {
 DDRD = 0xFF;
 DDRB = 0xFF;
}

void loop() 
{
for (int i = 0; i<10; i++)
{
  PORTB =1 <<i;
  PORTD =1 << i;

  delay(100);
}
}
