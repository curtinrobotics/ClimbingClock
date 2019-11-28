/*
 * Authors: Harrison O, Anton R
 * Date: 28/11/2019 (DD/MM/YYY)
 * Purpose: Code for the tortoise component of the clock
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include <SpeedCorrector.h>

#include <RTClib.h> // Real Time Clock (RTC) library

const TimeSpan CORRECT_TIME = TimeSpan(12*60*60); // Num of seconds in 12 hours
const uint16_t INITIAL_PWM = 300; // dummy value for bug testing. Get real value via testing robot.

uint16_t currentPwm;
bool topMet = false;
DateTime prevTime;

SpeedCorrector speedCorrector(INITIAL_PWM, CORRECT_TIME);

RTC_DS1307 rtc;

void setup() {
  rtc.begin(); // start the rtc
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // initialize the rtc

  DateTime startingTime = rtc.now(); // time at startup
  DateTime *prevTwelveHourPtr = getPreviousTwelveHour(startingTime);
  TimeSpan *initialCorrectTimePtr = new DateTime(*prevTwelveHourPtr - startingTime);

  do {
    topMet = checkIfAtTop();

    if ( (topMet) || (getTime() == *initialCorrectTimePtr) ) {
      prepareNextCycle();
    }
  } while (!topMet);
  
  delete prevTwelveHourPtr; delete initialCorrectTimePtr;
}

void loop() {
  topMet = checkIfAtTop();

  if ( (topMet) || (getTime() == CORRECT_TIME) ) {
    prepareNextCycle();
  }
}

bool checkIfAtTop(void) {
  //definition pending
  //need to make decision between photo interrupters, buttons, or magnetic sensors

  return true; //used for testing purposes
}

// returns time
DateTime getTime(void) {
  return rtc.now();
}

void prepareNextCycle() {
  resetPosition();
  uint16_t correctedPwm = speedCorrector.getCorrectedPwm(getTime(), currentPwm, topMet);
  speedCorrector.addNewCorrectedPwm(correctedPwm);
  currentPwm = speedCorrector.getMeanPwm();
  topMet = false;
  //line setting new PWM pending
  
  // if reached top too early wait until time is up
  while (getTime() - prevTime < CORRECT_TIME) { }
  
  prevTime = getTime();
  delay(300); //prevents topMet from being reactivated
}

// returns the last noon or midnight, whichever is closest
DateTime* getPreviousTwelveHour(DateTime time) {
  DateTime *prevTwelveHourPtr = new DateTime(time.unixtime());

  if (time.hour() < 12) {
    *prevTwelveHourPtr -= time.hour();
  }
  else if (time.hour() > 12) {
    *prevTwelveHourPtr -= time.hour() - 12;
  }

  *prevTwelveHourPtr -= time.minute() * 60 + time.second();

  return prevTwelveHourPtr;
}

//go back to the bottom of the rack/ladder
void resetPosition(void) {
  //definition pending
}
