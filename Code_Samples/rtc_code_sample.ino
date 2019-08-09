#include <RTClib.h>

RTC_DS1307 rtc;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  if (!rtc.begin())
  {
    Serial.println("Couldn't start the RTC");
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  DateTime currentTime = rtc.now();

  Serial.print("The current time is: ");
  Serial.print(currentTime.hour());
  Serial.print(":");
  Serial.print(currentTime.minute());
  Serial.print(":");
  Serial.println(currentTime.second());

  delay(2000);
}
