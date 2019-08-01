/*
 * Author: Anton R
 * Date: 01/08/2019
 * Purpose: Added Real Time Clock functionality
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include <SpeedCorrector.h>

#include <RTClib.h> // Real Time Clock library

const TimeSpan CORRECT_TIME = new TimeSpan(12*60*60); // Num of seconds in 12 hours
const uint16_t INITIAL_PWM = 300; //dummy value for bug testing. Get real value via testing robot.

uint16_t currentPwm, correctedPwm;
bool topMet = false;
DateTime prevTime;

SpeedCorrector speedCorrector(INITIAL_PWM, CORRECT_TIME);

RTC_DS1307 rtc;

void setup() {

  rtc.begin(); // start the real time clock

  DateTime startingTime = rtc.now(); // time at startup
  DateTime initalCorrectTime = new DateTime(CORRECT_TIME.unixtime() - startingTime.unixtime());

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

// returns current time
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

//go back to the bottom of the rack/ladder
void resetPosition(void) {
  //definition pending
}
