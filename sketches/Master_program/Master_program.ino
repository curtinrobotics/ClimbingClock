/*
 * Authors: Harrison O, Anton R
 * Date: 08/12/2019 (DD/MM/YYY)
 * Purpose: Code for the tortoise component of the clock
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Compiles
 */

#include <SpeedChangeFunctions.h>
#include <SpeedCorrector.h>
#include <Robot.h>
#include <RTClib.h> // Real Time Clock (RTC) library
// LED library pending

#define TORTOISE_CORRECT_TIME (12 * 60 * 60)  // Num of seconds in 12 hours
#define HARE_CORRECT_TIME (60 * 60)           // Num of seconds in 1 hour
#define TORTOISE_PWM_PIN 5                    // dummy value
#define HARE_PWM_PIN 6                        // dummy value
#define SECONDS_PER_HOUR 3600

RTC_DS1307 rtc;
SpeedCorrector *tortoiseSpeedCorrPtr, *hareSpeedCorrPtr;
Robot *tortoisePtr, *harePtr;

void setup() {
  DateTime initialTortoiseEndDate, initialHareEndDate;
  
  rtc.begin(); // start the rtc
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // initialize the rtc
  
  initialTortoiseEndDate = getNextTwelveHour();
  initialHareEndDate = getNextHour();
  tortoiseSpeedCorrPtr = new SpeedCorrector(50, TORTOISE_CORRECT_TIME,
                                            &(SpeedChangeFunctions::linearChange));
  hareSpeedCorrPtr = new SpeedCorrector(150, HARE_CORRECT_TIME,
                                        &(SpeedChangeFunctions::linearChange));
  tortoisePtr = new Robot(initialTortoiseEndDate, tortoiseSpeedCorrPtr, &tortoiseAtTop,
                          &tortoiseAtBottom, TORTOISE_PWM_PIN, &rtc);
  harePtr = new Robot(initialHareEndDate, hareSpeedCorrPtr, &hareAtTop, &hareAtBottom,
                      HARE_PWM_PIN, &rtc);
  tortoisePtr->start();
  harePtr->start();
  
  // LED setup code pending
}

void loop() {
  if (tortoisePtr->atBottom()) {
    tortoisePtr->attemptToGoUp();
  } else if (tortoisePtr->cycleDone()) {
    tortoisePtr->prepareNextCycle();
    tortoisePtr->goDown();
  }

  if (harePtr->atBottom()) {
    harePtr->attemptToGoUp();
  } else if (harePtr->cycleDone()) {
    harePtr->prepareNextCycle();
    harePtr->goDown();
  }
  
  // LED loop code pending
}

bool tortoiseAtTop(void) {
  // definition pending

  return true; // for testing purposes
}

bool tortoiseAtBottom(void) {
  // definition pending

  return true; // for testing purposes
}

bool hareAtTop(void) {
  // definition pending

  return true; // for testing purposes
}

bool hareAtBottom(void) {
  // definition pending

  return true; // for testing purposes
}

DateTime getNextHour(void) {
    DateTime currTime = rtc.now();
    TimeSpan secTilNextHour = TimeSpan(SECONDS_PER_HOUR - 60 * currTime.minute() - currTime.second());
    
    return currTime + secTilNextHour;
}

DateTime getNextTwelveHour(void) {
    DateTime currHour = rtc.now();
    DateTime nextTwelveHour;

    currHour = currHour - TimeSpan(60 * currHour.minute() + currHour.second());
    
    if (currHour.hour() < 12) {
        nextTwelveHour = currHour + TimeSpan( (12 - currHour.hour()) * 60 * 60);
    } else if (currHour.hour() > 12) {
        nextTwelveHour = currHour + TimeSpan( (24 - currHour.hour()) * 60 * 60);
    } else {
        nextTwelveHour = currHour + TimeSpan(TORTOISE_CORRECT_TIME);
    }

    return nextTwelveHour;
}
