// CONNECTIONS:
// DS1302 CLK/SCLK --> 5
// DS1302 DAT/IO --> 4
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v -5v
// DS1302 GND --> GND
1.
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#define ledPin 13
ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
void printDateTime(const RtcDateTime& dt)
{
  
  Serial.print(dt.Year(), DEC);
  Serial.print('/');
  Serial.print(dt.Month(), DEC);
  Serial.print('/');
  Serial.print(dt.Day(), DEC);
  Serial.print(' ');
  Serial.print(dt.Hour(), DEC);
  Serial.print(':');
  Serial.print(dt.Minute(), DEC);
  Serial.print(':');
  Serial.print(dt.Second(), DEC);
  Serial.println();
  Serial.print("Total Seconds since 1/1/2000 : ");
  Serial.print(dt.TotalSeconds());
  Serial.println();
  
}
void setup() 
{

  Serial.begin(57600);
  pinMode(ledPin, OUTPUT);
  Rtc.Begin();
  RtcDateTime setting_time(2020,2,19,10,24,10);// year, month, dayOfMonth, hour, minute, second
  printDateTime(setting_time);
  Rtc.SetDateTime(setting_time);//Try to comment This line
}
void loop() 
{
  int timeDiff, lastRead = 0;
  RtcDateTime now = Rtc.GetDateTime();
  Serial.println("START");
  printDateTime(now);

  if(now.TotalSeconds()%2){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
  delay(120000);
  Serial.print("STOP");
}
