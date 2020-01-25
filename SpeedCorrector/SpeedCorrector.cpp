/*
 * @author Harrison Outram
 * Last Updated: 25/01/2020 (d/m/y, UTC+08:00)
 * @version 1.8.1
 * @brief Provide functionality for auto correcting motor speed
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: works
 */

#include "SpeedCorrector.h"

/**
 * @param initialPwm The PWM the robot should start with
 * @param correctTime The time it should take for the robot to complete each cycle in seconds
 * @param speedChangeFunc The function which determines how the speedIncrement is changed
 */
SpeedCorrector::SpeedCorrector(uint8_t initialPwm, uint32_t correctTime,
                                SpeedChangeFunc speedChangeFunc) {
    _pwmIndex = 0;
    _maxPwmIndex = MAX_NUM_OF_PWMS - 1;
    _correctedPwms = new uint8_t[MAX_NUM_OF_PWMS];
    _correctedPwmsFull = false;
    _correctedPwms[0] = initialPwm;
    _correctTime = correctTime;
    _speedIncrement = SPEED_INCREMENT;
    _minSpeedIncrement = MIN_SPEED_INCREMENT;
    _speedChangeFunc = speedChangeFunc;
    _speedIncrementChange = SPEED_INCREMENT_CHANGE;
    _currPwm = initialPwm;
}

/**
 * @param initialPwm The PWM the robot should start with
 * @param correctTime The time it should take for the robot to complete each cycle in seconds
 * @param maxNumOfCorrectedPwms The max num of corrected PWMs the object should store
 * @param speedIncrement The amount the PWM should be increased by if the robot fails to reach the top in time
 * @param minSpeedIncrement The minimum amount the PWM should be increased by if the robot fails to reach the top in time
 * @param speedChangeFunc The function which determines how the speedIncrement is changed
 * @param speedIncrementChange Dictates how much the speedIncrement is changed by inSpeedChangeFunc
 */
SpeedCorrector::SpeedCorrector(uint8_t initialPwm, uint32_t correctTime,    uint8_t maxNumOfPwms, 
                    uint8_t speedIncrement, uint8_t minSpeedIncrement,
                    SpeedChangeFunc speedChangeFunc,
                    uint8_t speedIncrementChange) {
    _pwmIndex = 0;
    _maxPwmIndex = maxNumOfPwms - 1;
    _correctedPwms = new uint8_t[maxNumOfPwms];
    _correctedPwmsFull = false;
    _correctedPwms[0] = initialPwm;
    _correctTime = correctTime;
    _speedIncrement = speedIncrement;
    _minSpeedIncrement = minSpeedIncrement;
    _speedChangeFunc = speedChangeFunc;
    _speedIncrementChange = speedIncrementChange;
    _currPwm = initialPwm;
}

SpeedCorrector::~SpeedCorrector() {
    delete[] _correctedPwms;
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
    
    if (_correctTime > actualTime) {                 // reached top too quickly
        correctedPwm = _currPwm - getPwmOffset(_correctTime - actualTime);
    } else if (!topReached) {                       // did not reach top in time
        if (_currPwm + _speedIncrement > MAX_PWM) {   // prevents overflow error
            correctedPwm = MAX_PWM;
        } else {
            correctedPwm = _currPwm + _speedIncrement;
        }
        calcNewSpeedIncrement();
    } else {                                        // speed just right
        correctedPwm = _currPwm;
    }
    
    return correctedPwm;
}

/**
 * Adds new corrected PWM to SpeedCorrector object
 * Also updates current PWM
 * @param correctedPwm The PWM required to complete the last cycle correctly
 * @return void
 */
void SpeedCorrector::addNewCorrectedPwm(uint8_t correctedPwm) {
    if (_pwmIndex == _maxPwmIndex) {
        _pwmIndex = 0; //reset index to replace oldest value
        _correctedPwmsFull = true;
    } else {
        _pwmIndex++;
    }
    _correctedPwms[_pwmIndex] = correctedPwm;
    _currPwm = getMeanPwm();
}

/**
 * currPwm getter
 * @return uint8_t
 */
uint8_t SpeedCorrector::getCurrentPwm(void) {
    return _currPwm;
}

    /* PRIVATE METHODS */

/**
 * Generates mean PWM from corrected PWMs
 * @return uint8_t
 */
uint8_t SpeedCorrector::getMeanPwm(void) {
    uint32_t meanPwm = 0;
    
    if (_correctedPwmsFull) {
        for (uint8_t i = 0; i <= _maxPwmIndex; i++)
            meanPwm += _correctedPwms[i];
        
        meanPwm /= (_maxPwmIndex + 1);
    } else {
        for (uint8_t i = 0; i <= _pwmIndex; i++)
            meanPwm += _correctedPwms[i];
        
        meanPwm /= (_pwmIndex + 1);
    }
    
    return (uint8_t)meanPwm;
}

/**
 * Calculates how much the PWM was off
 * @param timeErr The difference between the actual time and the correct time
 * @return uint8_t
 */
uint8_t SpeedCorrector::getPwmOffset(uint32_t timeErr) {
    //use dimensional analysis to confirm equation is correct
    // Assumes PWM input and output scale linearly
    return (uint8_t)( ((float)timeErr / (float)_correctTime) * (float)_currPwm );
}

/**
 * Changes speedIncrement to new value
 * @return void
 */
void SpeedCorrector::calcNewSpeedIncrement(void) {
    _speedIncrement = (*_speedChangeFunc)(_speedIncrement,
                                         _speedIncrementChange);

    if (_speedIncrement < _minSpeedIncrement)
        _speedIncrement = _minSpeedIncrement;
}
