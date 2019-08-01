/*
 * Authors: Harrison O, Anton R
 * Date: 01/08/2019
 * Purpose: Code for the tortoise component of the clock
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include <SpeedCorrector.h>

#include <RTClib.h> // Real Time Clock library

const TimeSpan CORRECT_TIME = new TimeSpan(12*60*60); // Num of seconds in 12 hours
const uint16_t INITIAL_PWM = 300; // dummy value for bug testing. Get real value via testing robot.

uint16_t currentPwm, correctedPwm;
bool topMet = false;
DateTime prevTime;

SpeedCorrector speedCorrector(INITIAL_PWM, CORRECT_TIME);

RTC_DS1307 rtc;

void setup() {

  rtc.begin(); // start the real time clock

  DateTime startingTime = rtc.now(); // time at startup
  TimeSpan initalCorrectTime = new DateTime(previous12Hour(startingTime) - startingTime);

  do {
    topMet = checkIfAtTop();

    if ( (topMet) || (getTime() == initalCorrectTime) ) {
      prepareNextCycle();
    }
  } while (!topMet);
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
  uint16_t tempPwm = speedCorrector.getCorrectedPwm(getTime(), currentPwm, topMet);
  speedCorrector.addNewCorrectedPwm(tempPwm);
  currentPwm = speedCorrector.getMeanPwm();
  topMet = false;
  prevTime = getTime();
  delay(300); //prevents topMet from being reactivated
}

DateTime previous12Hour(DateTime time) {
  DateTime out = new Datetime(time.unixtime());

  if (time.hour() < 12) {
    out -= time.hour();
  }
  else if (time.hour() > 12) {
    out -= time.hour() - 12;
  }

  out -= time.minute() * 60 + time.second();

  return out;
}

//go back to the bottom of the rack/ladder
void resetPosition(void) {
  //definition pending
}
