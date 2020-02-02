unsigned int a=0b00000001;
void setup()
{
DDRD = 0xFF;
DDRB = 0xFF;
}
void loop()
{
int d = analogRead (A0);
PORTD = a;
delay(d);
if (PINB == 0b00000001&&a! = 0b10000000)
a=a<<1;
if (PINB == 0b00000001&&a! = 0b00000001)
a =a >>1;
}
