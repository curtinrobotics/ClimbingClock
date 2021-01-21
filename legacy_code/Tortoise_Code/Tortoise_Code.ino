/*
 * Authors: Harrison O, Anton R
 * Date: 28/11/2019 (DD/MM/YYY)
 * Purpose: Code for the tortoise component of the clock
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include <SpeedCorrector.h>
#include <RTClib.h> // Real Time Clock (RTC) library

#define HOURS 12
const TimeSpan CORRECT_TIME = TimeSpan(HOURS * 60 * 60); // Num of seconds in 12 hours
const uint16_t INITIAL_PWM = 200; // dummy value for bug testing. Get real value via testing robot.

uint16_t currentPwm;
bool topMet = false;
DateTime currCycleCorrectTime;
SpeedCorrector speedCorrector(INITIAL_PWM, CORRECT_TIME.totalseconds());
RTC_DS1307 rtc;

void setup() {
  rtc.begin(); // start the rtc
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // initialize the rtc
  //line setting initial PWM pending

  DateTime currTime = rtc.now();
  DateTime& initialCorrectTimeRef = getNextTwelveHour(currTime);
  bool firstCycleDone = false;

  do {
    topMet = checkIfAtTop();
    
    if (topMet || rtc.now() >= initialCorrectTimeRef) {
      prepareNextCycle();
      firstCycleDone = true;
    }
  } while (!firstCycleDone);
  
  delete &initialCorrectTimeRef;
}

void loop() {
  topMet = checkIfAtTop();
  
  if (topMet || rtc.now() >= currCycleCorrectTime)
    prepareNextCycle(); //updates currCycleCorrectTime
}

bool checkIfAtTop(void) {
  //definition pending
  //need to make decision between photo interrupters, buttons, or magnetic sensors

  return true; //used for testing purposes
}

void prepareNextCycle() {
  resetPosition();
  DateTime currTime = rtc.now();
  DateTime& prevTwelveHourRef = getPrevTwelveHour(currTime);
  delete &prevTwelveHourRef;
  uint16_t correctedPwm = speedCorrector.getCorrectedPwm(currTime.unixtime(), currentPwm, topMet);
  speedCorrector.addNewCorrectedPwm(correctedPwm);
  currentPwm = speedCorrector.getMeanPwm();
  topMet = false;
  //line setting new PWM pending
  
  // if reached top too early wait until time is up
  while (rtc.now() <  currCycleCorrectTime) { }
  
  currCycleCorrectTime = DateTime(CORRECT_TIME.totalseconds() + prevTwelveHourRef.unixtime());
  delay(300); //prevents topMet from being reactivated
}

// returns the next noon or midnight DateTime
DateTime& getNextTwelveHour(DateTime& timeRef) {
  DateTime& nextTwelveHourRef = new DateTime(timeRef.unixtime());

  if (timeRef.hour() < HOURS) {
    nextTwelveHourRef = nextTwelveHourRef + TimeSpan(timeRef.hour());
  }
  else if (timeRef.hour() > HOURS) {
    nextTwelveHourRef = nextTwelveHourRef + TimeSpan(timeRef.hour() - HOURS);
  }

  nextTwelveHourRef = nextTwelveHourRef - TimeSpan(timeRef.minute() * 60 + timeRef.second());

  return nextTwelveHourRef;
}

// returns the last noon or midnight, whichever is closest
DateTime& getPrevTwelveHour(DateTime& timeRef) {
  DateTime& prevTwelveHourRef = new DateTime(timeRef.unixtime());

  if (timeRef.hour() < HOURS) {
    prevTwelveHourRef = prevTwelveHourRef + TimeSpan(timeRef.hour());
  }
  else if (timeRef.hour() > HOURS) {
    prevTwelveHourRef = prevTwelveHourRef + TimeSpan(timeRef.hour() - HOURS);
  }

  prevTwelveHourRef = prevTwelveHourRef - TimeSpan(timeRef.minute() * 60 + timeRef.second());

  return prevTwelveHourRef;
}

//go back to the bottom of the rack/ladder
void resetPosition(void) {
  //definition pending
}
