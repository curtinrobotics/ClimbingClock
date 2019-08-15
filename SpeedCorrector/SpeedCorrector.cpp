/*
 * Author: Harrison Outram
 * Date: 15/08/2019
 * Version: 1.2
 * Purpose: Provide functionality for auto correcting motor speed
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include "Arduino.h"
#include "SpeedCorrector.h"

const uint8_t SpeedCorrector::MAX_NUM_OF_PWMS = 10; //default value for alt constructor 1
const uint8_t SpeedCorrector::SPEED_INCREMENT = 10; //default value for alt constructor 1
const uint8_t SpeedCorrector::MIN_SPEED_INCREMENT = 5; //default value for alt constructor 1
const char SpeedCorrector::LINEAR_CHANGE_TYPE = 'l'; //value for setting linear change type
const char SpeedCorrector::EXP_CHANGE_TYPE = 'e'; //value for setting exponential change type
const char SpeedCorrector::NON_CHANGE_TYPE = 'n'; //value for setting non-change type
const uint8_t SpeedCorrector::SPEED_INCREMENT_CHANGE = 5; //default value for speedIncrementChange

SpeedCorrector::SpeedCorrector(uint16_t initialPwm, uint32_t inCorrectTime) {
	pwmIndex = 0;
	maxPwmIndex = MAX_NUM_OF_PWMS - 1;
	correctedPwms = new uint16_t[MAX_NUM_OF_PWMS];
	correctedPwmsFull = false;
	correctedPwms[0] = initialPwm;
	correctTime = inCorrectTime;
	speedIncrement = SPEED_INCREMENT;
	minSpeedIncrement = MIN_SPEED_INCREMENT;
	speedChangeType = LINEAR_CHANGE_TYPE;
	speedIncrementChange = SPEED_INCREMENT_CHANGE;
}

SpeedCorrector::SpeedCorrector(uint16_t initialPwm, uint32_t inCorrectTime,	uint8_t inMaxNumOfCorrectedPwms, 
								uint16_t inSpeedIncrement, uint8_t inMinSpeedIncrement, char inSpeedChangeType,
								uint8_t inSpeedIncrementChange) {
	pwmIndex = 0;
	maxPwmIndex = inMaxNumOfCorrectedPwms - 1;
	correctedPwms = new uint16_t[inMaxNumOfCorrectedPwms];
	correctedPwmsFull = false;
	correctedPwms[0] = initialPwm;
	correctTime = inCorrectTime;
	speedIncrement = inSpeedIncrement;
	minSpeedIncrement = inMinSpeedIncrement;
	speedChangeType = inSpeedChangeType;
	speedIncrementChange = inSpeedIncrementChange;
}

SpeedCorrector::~SpeedCorrector() {
	delete correctedPwms;
}

/*public methods*/

//calculates new PWM based on current PWM and error
uint16_t SpeedCorrector::getCorrectedPwm(uint32_t actualTime, uint16_t currentPwm, bool topReached) {
	uint16_t correctedPwm;
	
	if (correctTime > actualTime) { //reached top too quickly
		correctedPwm = currentPwm - getPwmOffset(correctTime - actualTime, currentPwm);
	} else if (!topReached) {
		correctedPwm = currentPwm + speedIncrement;
	} else {
		correctedPwm = currentPwm;
	}
	
	return correctedPwm;
}

void SpeedCorrector::addNewCorrectedPwm(uint16_t correctedPwm) {
	if (pwmIndex == maxPwmIndex) {
	pwmIndex = 0; //reset index to replace oldest value
	} else {
	pwmIndex++;
	}
	
	correctedPwms[pwmIndex] = correctedPwm;
}

uint16_t SpeedCorrector::getMeanPwm(void) {
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

/*private methods*/

uint16_t SpeedCorrector::getPwmOffset(uint32_t timeErr, uint16_t currentPwm) {
	//use dimensional analysis to confirm equation is correct
	return (uint16_t)( ((float)timeErr / (float)correctTime) * (float)currentPwm );
}

//change speedIncrement to new value
void SpeedCorrector::calcNewSpeedIncrement(void) {
	if (speedChangeType == LINEAR_CHANGE_TYPE) {
		speedIncrement = speedIncrement - speedIncrementChange;
	} else if (speedChangeType == EXP_CHANGE_TYPE) {
		speedIncrement /= speedIncrementChange;
	} else if (speedChangeType == NON_CHANGE_TYPE) {
		// do not change speedIncrement
    }

	if (speedIncrement < minSpeedIncrement) {
		speedIncrement = minSpeedIncrement;
	}
}
