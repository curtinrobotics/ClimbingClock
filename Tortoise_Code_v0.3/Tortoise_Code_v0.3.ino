/*
 * Author: Harrison Outram
 * Date: 8/07/2019
 * Version: 0.3 (incomplete: see comments)
 * Purpose: code for tortoise robot
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include <ClimbingClockSpeedCorrector.h>

const uint8_t MAX_HOURS = 12; //12 hour clock
const uint32_t CORRECT_TIME = MAX_HOURS*60*60*1000; //Num of milliseconds in 12 hours
const uint16_t INITIAL_PWM = 300; //obtained via testing
const uint8_t MAX_NUM_OF_PWMS = ClimbingClockSpeedCorrector::MAX_NUM_OF_PWMS;
const uint8_t SPEED_INCREASE_INCREMENT = ClimbingClockSpeedCorrector::SPEED_INCREASE_INCREMENT;

uint16_t currentPwm;
uint16_t correctedPwm;
bool photoInterruptMet = false;

ClimbingClockSpeedCorrector speedCorrector(INITIAL_PWM, CORRECT_TIME, MAX_NUM_OF_PWMS, SPEED_INCREASE_INCREMENT);

void setup() {
  uint32_t startingTime = 0; //The num of milliseconds passed since the last 12PM/AM
  uint32_t initalCorrectTime = CORRECT_TIME - startingTime;
  //initialise milliseconds counter

  do {
    photoInterruptMet = checkIfAtTop();
    
    if ( (photoInterruptMet) || (millis() == initalCorrectTime) ) {
      prepareNextCycle();
    }
  } while (!photoInterruptMet);
}

void loop() {
  photoInterruptMet = checkIfAtTop();
  
  if ( (photoInterruptMet) || (millis() == CORRECT_TIME) ) {
    prepareNextCycle();
  }
}

bool checkIfAtTop(void) {
  //definition pending
  //need further understanding of photo interrupts

  return true; //used for testing purposes
}

void prepareNextCycle() {
  resetPosition();
  uint16_t tempPwm = speedCorrector.getCorrectedPwm(millis(), currentPwm, photoInterruptMet);
  speedCorrector.addNewCorrectedPwm(tempPwm);
  currentPwm = speedCorrector.getMeanPwm();
  photoInterruptMet = false;
  //reset milliseconds counter line pending
  delay(50); //prevents photoInterrupt from being turned true while laser is still in view
}

//go back to the bottom of the rack/ladder
void resetPosition(void) {
  //definition pending
}
