int clk_pin = 13; //SHCP
int latch_pin = 10; //STCP
int data_pin = 11; //DS

void setup()
{
  pinMode(clk_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < 16 || i > 0; i = i)
  {
    digitalWrite(latch_pin, LOW);
    for (int c = 0; c < 16; c++)
    {
      if (c == i)
      {
        digitalWrite(data_pin, HIGH);
      }
      else
      {
        digitalWrite(data_pin, LOW);
      }
      digitalWrite(clk_pin, HIGH);
      digitalWrite(clk_pin, LOW);
    }
    Serial.println(analogRead(A1));
    if (analogRead(A0) == 0)
    {
      i--;
      if (i < 0) i = 15;
    }
    if (analogRead(A1) == 0)
    {
      i++;
      if (i > 15) i = 0;
    }
    delay(analogRead(A2));
    digitalWrite(latch_pin, HIGH);
  }
}
