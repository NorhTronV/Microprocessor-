int input1=0;
void setup()
{
  DDRD=0xFF;
  DDRC=0x00;
  PORTD=0x01;
}

void loop()
{
  if (!(PINC&0x01))
  {
    if (PORTD == 0x80)
    {
      PORTD=0x01;
    }
    else
    {
      PORTD=PORTD<<1;
    }
      delay(500);
    }
    if (!(PINC&0x02))
    {
      if (PORTD == 0x01)
      {
        PORTD=0x80;
      }
      else
      {
        PORTD=PORTD>>1;
      }
      delay(500);
    }
}
