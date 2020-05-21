/**
 * Last Updated: 21/05/2020 (d/m/y, UTC+08:00)
 * @brief Auto corrects delay time time given feedback
 * Project: Climbing Clock (2019-20)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: untested
 */

#include "DelayCorrector.h"

/**
 * Calculates the next exponent of the next power of 2
 * @param startingNum The number to start finding the next power of 2
 * @return The exponent of the next power of 2
 * @attention If startingNum is already a power of 2 then log2(startingNum) is returned
 */
static uint8_t next2Exp(uint32_t startingNum) {
    uint8_t exp = 0;
    uint32_t next2Power = 1;

    while (startingNum > next2Power) {
        exp++;
        next2Power = next2Power << 1;
    }

    return exp;
}

/**
 * Alternate constructor 1
 * @param initialDelay The delay time the robot should start with
 * @param correctTime The time it should take for the robot to complete each cycle in seconds
 * @param delayChangeFunc The function which determines how the delayDecrement is changed
 */
DelayCorrector::DelayCorrector(uint32_t initialDelay, uint32_t correctTime,
                                BiasChangeFunc delayChangeFunc) {
    _delayIndex = 0;
    _numDelayLog2 = next2Exp((uint32_t)MAX_NUM_DELAYS);
    _correctedDelays = new uint32_t[1 << _numDelayLog2];
    _correctedDelaysFull = false;
    _correctedDelays[0] = initialDelay;
    _correctTime = correctTime;
    _delayDecrement = DELAY_DECREMENT;
    _minDelayDecrement = MIN_DELAY_DECREMENT;
    _delayChangeFunc = delayChangeFunc;
    _delayDecrementChange = DELAY_DECREMENT_CHANGE;
    _currDelay = initialDelay;
}

/**
 * Alternate constructor 2
 * @param initialDelay The delay time the robot should start with
 * @param correctTime The time it should take for the robot to complete each cycle in seconds
 * @param maxNumOfCorrectedDelays The max num of corrected delay times the object should store
 * @param delayDecrement The amount the delay time should be increased by if the robot fails to reach the top in time. Must be negative.
 * @param minDelayDecrement The minimum amount the delay time should be increased by if the robot fails to reach the top in time
 * @param delayChangeFunc The function which determines how the delayDecrement is changed
 * @param delayDecrementChange Dictates how much the delayDecrement is changed by delayChangeFunc. Must be negative.
 */
DelayCorrector::DelayCorrector(uint32_t initialDelay, uint32_t correctTime,
                    uint8_t maxNumOfDelays, int16_t delayDecrement,
                    int8_t minDelayDecrement, BiasChangeFunc delayChangeFunc,
                    int8_t delayDecrementChange) {
    _delayIndex = 0;
    _numDelayLog2 = next2Exp((uint32_t)maxNumOfDelays);
    _correctedDelays = new uint32_t[1 << _numDelayLog2];
    _correctedDelaysFull = false;
    _correctedDelays[0] = initialDelay;
    _correctTime = correctTime;
    _delayDecrement = delayDecrement;
    _minDelayDecrement = minDelayDecrement;
    _delayChangeFunc = delayChangeFunc;
    _delayDecrementChange = delayDecrementChange;
    _currDelay = initialDelay;
}

DelayCorrector::~DelayCorrector() {
    delete[] _correctedDelays;
}

    /* PUBLIC METHODS */

/**
 * calculates new delay time based on current delay time and error
 * @param actualTime The time in seconds for the robot to complete its current cycle
 * @param topRached Whether the robot reached the top or not
 * @return The corrected delay time
 */
uint32_t DelayCorrector::getCorrectedDelay(uint32_t actualTime, bool topReached) {
    uint32_t correctedDelay;
    uint32_t slope;
    
    if (_correctTime > actualTime) {                // reached top too quickly
        // completion time = (slope) * (delay time)
        slope = actualTime / _currDelay;
        correctedDelay = _correctTime / slope;
    } else if (!topReached) {                       // did not reach top in time
        correctedDelay = _currDelay + _delayDecrement;
        _delayDecrement = calcNewDelayDecrement();
    } else {                                        // delay just right
        correctedDelay = _currDelay;
    }
    
    return correctedDelay;
}

/**
 * Adds new corrected delay time to DelayCorrector object
 * Also updates current delay time
 * @param correctedDelay The delay time required to complete the last cycle correctly
 * @return void
 */
void DelayCorrector::addNewCorrectedDelay(uint32_t correctedDelay) {
    _delayIndex++;

    if (_delayIndex == (1 << _numDelayLog2)) {
        _delayIndex = 0; //reset index to replace oldest value
        _correctedDelaysFull = true;
    }

    _correctedDelays[_delayIndex] = correctedDelay;
    _currDelay = getMeanDelay();
}

    /* PROTECTED METHODS */

/**
 * Generates mean delay time from corrected delay times
 * @return The mean corrected delay
 */
uint32_t DelayCorrector::getMeanDelay(void) {
    uint32_t meanDelay = 0;
    
    if (_correctedDelaysFull) {
        for (uint8_t i = 0; i < (1 << _numDelayLog2); i++)
            meanDelay += _correctedDelays[i];
        
        meanDelay = meanDelay >> _numDelayLog2;
    } else {
        for (uint8_t i = 0; i <= _delayIndex; i++)
            meanDelay += _correctedDelays[i];
        
        meanDelay /= (_delayIndex + 1);
    }
    
    return meanDelay;
}

/**
 * Calculates new delay decrement using given delay change function
 * @return The new delay decrement
 */
uint16_t DelayCorrector::calcNewDelayDecrement(void) {
    uint16_t newDelayDec = (uint16_t)(*_delayChangeFunc)(_delayDecrement,
                                                        _delayDecrementChange);

    if (newDelayDec > _minDelayDecrement)
        newDelayDec = _minDelayDecrement;

    return newDelayDec;
}
