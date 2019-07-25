/*
 * Author: Harrison Outram
 * Date: 25/07/2019
 * Version: 0.4 (incomplete: see comments)
 * Purpose: code for tortoise robot
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include <SpeedCorrector.h>

const uint32_t CORRECT_TIME = 12*60*60*1000; //Num of milliseconds in 12 hours
const uint16_t INITIAL_PWM = 300; //dummy value for bug testing. Get real value via testing robot.

uint16_t currentPwm, correctedPwm;
bool topMet = false;
uint64_t prevTime;

SpeedCorrector speedCorrector(INITIAL_PWM, CORRECT_TIME);

void setup() {
  uint32_t startingTime = 7*60*60*1000; //The num of milliseconds passed since the last 12PM/AM
  uint32_t initalCorrectTime = CORRECT_TIME - startingTime;
  //initialise time module pending
  
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

uint64_t getTime(void) {
  //definition pending
  //need further understanding

  return millis() - prevTime; //used for testing purposes
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
