/*
 * Author: Harrison Outram
 * Date: 25/07/2019
 * Version: 0.4
 * Purpose: Provide functionality for auto correcting motor speed
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include "Arduino.h"
#include "ClimbingClockSpeedCorrector.h"

const uint8_t ClimbingClockSpeedCorrector::MAX_NUM_OF_PWMS = 9; //default value
const uint8_t ClimbingClockSpeedCorrector::SPEED_INCREASE_INCREMENT = 10; //default value
const char ClimbingClockSpeedCorrecter::LINEAR_CHANGE_TYPE = 'l';
const char ClimbingClockSpeedCorrecter::EXP_CHANGE_TYPE = 'e';
const int ClimbingClockSpeedCorrecter::MIN_SPEED_INCREMENT = 5;

ClimbingClockSpeedCorrector::ClimbingClockSpeedCorrector(uint16_t initialPwm, uint32_t inCorrectTime) {
  pwmIndex = 0;
  maxPwmIndex = MAX_NUM_OF_PWMS - 1;
  correctedPwms = new uint16_t[MAX_NUM_OF_PWMS];
  correctedPwmsFull = false;
  correctedPwms[0] = initialPwm;
  correctTime = inCorrectTime;
  speedIncreaseIncrement = SPEED_INCREASE_INCREMENT;
  speedChangeType = LINEAR_CHANGE_TYPE;
  
}

ClimbingClockSpeedCorrector::ClimbingClockSpeedCorrector(uint16_t initialPwm, uint32_t inCorrectTime,
																												 uint8_t inMaxNumOfCorrectedPwms, uint16_t inSpeedIncreaseIncrement,
																												 char inSpeedChangeType, ) {
  pwmIndex = 0;
  maxPwmIndex = inMaxNumOfCorrectedPwms - 1;
  correctedPwms = new uint16_t[inMaxNumOfCorrectedPwms];
  correctedPwmsFull = false;
  correctedPwms[0] = initialPwm;
  correctTime = inCorrectTime;
  speedIncreaseIncrement = inSpeedIncreaseIncrement;
}

ClimbingClockSpeedCorrector::~ClimbingClockSpeedCorrector() {
	delete correctedPwms;
}

//calculates new PWM based on current PWM and error
uint16_t ClimbingClockSpeedCorrector::getCorrectedPwm(uint32_t actualTime, uint16_t currentPwm, bool topReached) {
  uint16_t correctedPwm;
  
  if (correctTime > actualTime) { //reached top too quickly
    correctedPwm = currentPwm - getPwmOffset(correctTime - actualTime, currentPwm);
  } else if (!topReached) {
    correctedPwm = currentPwm + speedIncreaseIncrement;
  } else {
    correctedPwm = currentPwm;
  }
  
  return correctedPwm;
}

void ClimbingClockSpeedCorrector::addNewCorrectedPwm(uint16_t correctedPwm) {
  if (pwmIndex == maxPwmIndex) {
    pwmIndex = 0; //reset index to replace oldest value
  } else {
    pwmIndex++;
  }
  
  correctedPwms[pwmIndex] = correctedPwm;
}

uint16_t ClimbingClockSpeedCorrector::getMeanPwm(void) {
  uint32_t meanPwm = 0;
  
  if (correctedPwmsFull) {
  	for (uint8_t i = 0; i < maxPwmIndex; i++) {
      meanPwm += correctedPwms[i];
  	}
  	
  	meanPwm /= (maxPwmIndex + 1);
  } else {
  	for (uint8_t i = 0; i <= pwmIndex; i++) {
      meanPwm += correctedPwms[i];
    }
    
  	meanPwm /= (pwmIndex + 1);
  }
  
  return meanPwm;
}

//calculates how much the currentPwm is off by
uint16_t ClimbingClockSpeedCorrector::getPwmOffset(uint32_t timeErr, uint16_t currentPwm) {
  //use dimensional analysis to confirm equation is correct
  return (uint16_t)( ((float)timeErr / (float)correctTime) * (float)currentPwm );
}
