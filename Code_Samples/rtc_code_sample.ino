/*
 * File: rtc_code_sample.c
 * Date: 09/08/2019
 * Notes: This is an example of how to use the RTC library to get the time from
 *        the real-time clock
 */

#include <RTClib.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 16
#define BRIGHTNESS 50

#define HALF_DAY 43200UL


// make sure to initialize the rtc according to its model
// in this case, we're useing a DS1307
RTC_DS1307 rtc;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const uint32_t COL_RED = strip.Color(80,0,0);
const uint32_t COL_GRN = strip.Color(0,80,0);
const uint32_t COL_BLU = strip.Color(0,0,80);

void setup()
{
  // do this if you want output back to the computer
  Serial.begin(9600);

  // rtc.begin() starts the clock
  if (!rtc.begin())
  {
    Serial.println("Couldn't start the RTC");
  }

  // adjust the clock's time to correspond with the computer's time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));


  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);

}

void loop()
{
  
  DateTime currentTime = rtc.now();
  DateTime last12Hrs = previousTwelveHour(currentTime);

  // a bunch of example code below, uncomment to see how it works
  
/*
  Serial.print("The current time is: ");
  Serial.print(currentTime.hour());
  Serial.print(":");
  Serial.print(currentTime.minute());
  Serial.print(":");
  Serial.println(currentTime.second());

  Serial.print("Last 12th hour was: ");
  Serial.print(last12Hrs.hour());
  Serial.print(":");
  Serial.print(last12Hrs.minute());
  Serial.print(":");
  Serial.println(last12Hrs.second());
  Serial.println();

  delay(2000);

  Serial.print("red = ");
  Serial.println(COL_RED);
  Serial.print("green = ");
  Serial.println(COL_GRN);
  Serial.print("blue = ");
  Serial.println(COL_BLU);

*/
  //colorWipe(strip.Color(255,0,0), BRIGHTNESS);
  //colorWipe(strip.Color(128,0,128), BRIGHTNESS);
  drawTime(currentTime);
  //delay(500);
}

DateTime previousTwelveHour(DateTime time) {
  DateTime out(time.unixtime());

  if (time.hour() < 12) {
    out = out - TimeSpan((int) time.hour() * 60 * 60);
  }
  else if (time.hour() > 12) {
    out = out - TimeSpan((int) (time.hour() - 12) * 60 * 60);
  }

  out = out - TimeSpan((int) (time.minute() * 60) + (int) time.second());

  return out;
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void drawTime(DateTime currentTime) {
  // wipe pixels
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i,strip.Color(1,1,1));
  }
  
  int clockHour = currentTime.hour() % 12;
  int clockMinute = currentTime.minute();
  int clockSecond = currentTime.second();
  
  int hourLED = round((float)clockHour/12.0f * (float)LED_COUNT);
  hourLED %= LED_COUNT;
  int minuteLED = round((float)clockMinute/60.0f * (float)LED_COUNT);
  minuteLED %= LED_COUNT;
  int secondLED = round((float)clockSecond/60.0f * (float)LED_COUNT);
  secondLED %= LED_COUNT;

  //Serial.print("second = ");
  

  strip.setPixelColor(hourLED, COL_RED);
  strip.setPixelColor(minuteLED, strip.getPixelColor(minuteLED) + COL_GRN);
  strip.setPixelColor(secondLED, strip.getPixelColor(secondLED) + COL_BLU);

  strip.show();
}
