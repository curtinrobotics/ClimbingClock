/*
 * Author: Harrison Outram
 * Date: 12/12/2019 (d/m/y)
 * Version: 1.7
 * Purpose: Provide functionality for auto correcting motor speed
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Tested and works
 */

#include "SpeedCorrector.h"

/**
 * @param initialPwm The PWM the robot should start with
 * @param inCorrectTime The time it should take for the robot to complete each cycle
 * @param inSpeedChangeFunc The function which determines how the speedIncrement is changed
 */
SpeedCorrector::SpeedCorrector(uint8_t initialPwm, uint32_t inCorrectTime,
                    uint8_t (*inSpeedChangeFunc)(uint8_t currSpeedChange, uint8_t speedIncChange)) {
    pwmIndex = 0;
    maxPwmIndex = MAX_NUM_OF_PWMS - 1;
    correctedPwms = new uint8_t[MAX_NUM_OF_PWMS];
    correctedPwmsFull = false;
    correctedPwms[0] = initialPwm;
    correctTime = inCorrectTime;
    speedIncrement = SPEED_INCREMENT;
    minSpeedIncrement = MIN_SPEED_INCREMENT;
    speedChangeFunc = inSpeedChangeFunc;
    speedIncrementChange = SPEED_INCREMENT_CHANGE;
    currPwm = initialPwm;
}

/**
 * @param initialPwm The PWM the robot should start with
 * @param inCorrectTime The time it should take for the robot to complete each cycle
 * @param inMaxNumOfCorrectedPwms The max num of corrected PWMs the object should store
 * @param inSpeedIncrement The amount the PWM should be increased by if the robot fails to reach the top in time
 * @param inMinSpeedIncrement The minimum amount the PWM should be increased by if the robot fails to reach the top in time
 * @param inSpeedChangeFunc The function which determines how the speedIncrement is changed
 * @param inSpeedIncrementChange Dictates how much the speedIncrement is changed by inSpeedChangeFunc
 */
SpeedCorrector::SpeedCorrector(uint8_t initialPwm, uint32_t inCorrectTime,    uint8_t inMaxNumOfPwms, 
                    uint8_t inSpeedIncrement, uint8_t inMinSpeedIncrement,
                    uint8_t (*inSpeedChangeFunc)(uint8_t currSpeedChange, uint8_t speedIncChange),
                            uint8_t inSpeedIncrementChange) {
    pwmIndex = 0;
    maxPwmIndex = inMaxNumOfPwms - 1;
    correctedPwms = new uint8_t[inMaxNumOfPwms];
    correctedPwmsFull = false;
    correctedPwms[0] = initialPwm;
    correctTime = inCorrectTime;
    speedIncrement = inSpeedIncrement;
    minSpeedIncrement = inMinSpeedIncrement;
    speedChangeFunc = inSpeedChangeFunc;
    speedIncrementChange = inSpeedIncrementChange;
    currPwm = initialPwm;
}

SpeedCorrector::~SpeedCorrector() {
    delete correctedPwms;
}

    /* PUBLIC METHODS */

/**
 * calculates new PWM based on current PWM and error
 * @param actualTime The time in seconds for the robot to complete its current cycle
 * @param topRached Whether the robot reached the top or not
 * @return uint8_t
 */
uint8_t SpeedCorrector::getCorrectedPwm(uint32_t actualTime, bool topReached) {
    uint8_t correctedPwm;
    
    if (correctTime > actualTime)   // reached top too quickly
        correctedPwm = currPwm - getPwmOffset(correctTime - actualTime);
    else if (!topReached) {         // did not reach top in time
        correctedPwm = currPwm + speedIncrement;
        calcNewSpeedIncrement();
    } else {                        // speed just right
        correctedPwm = currPwm;
    }
    
    return correctedPwm;
}

/**
 * Adds new corrected PWM to object
 * Also updates current PWM
 * @param correctedPwm The PWM required to complete the last cycle correctly
 * @return void
 */
void SpeedCorrector::addNewCorrectedPwm(uint8_t correctedPwm) {
    if (pwmIndex == maxPwmIndex) {
        pwmIndex = 0; //reset index to replace oldest value
        correctedPwmsFull = true;
    } else {
        pwmIndex++;
    }
    correctedPwms[pwmIndex] = correctedPwm;
    currPwm = getMeanPwm();
}

uint8_t SpeedCorrector::getCurrentPwm(void) {
    return currPwm;
}

    /* PRIVATE METHODS */

uint8_t SpeedCorrector::getMeanPwm(void) {
    uint32_t meanPwm = 0;
    
    if (correctedPwmsFull) {
        for (uint8_t i = 0; i <= maxPwmIndex; i++)
            meanPwm += correctedPwms[i];
        
        meanPwm /= (maxPwmIndex + 1);
    } else {
        for (uint8_t i = 0; i <= pwmIndex; i++)
            meanPwm += correctedPwms[i];
        
        meanPwm /= (pwmIndex + 1);
    }
    
    return (uint8_t)meanPwm;
}

uint8_t SpeedCorrector::getPwmOffset(uint32_t timeErr) {
    //use dimensional analysis to confirm equation is correct
    return (uint8_t)( ((float)timeErr / (float)correctTime) * (float)currPwm );
}

//changes speedIncrement to new value, doesn't return it
void SpeedCorrector::calcNewSpeedIncrement(void) {
    speedIncrement = (*speedChangeFunc)(speedIncrement, speedIncrementChange);

    if (speedIncrement < minSpeedIncrement)
        speedIncrement = minSpeedIncrement;
}
