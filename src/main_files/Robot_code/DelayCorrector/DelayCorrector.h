/**
 * Last Updated: 7/05/2020 (d/m/y, UTC+08:00)
 * @brief Header file for DelayCorrector
 * Project: Climbing Clock
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: untested
 */

#ifndef DelayCorrector_h
#define DelayCorrector_h

#include "Arduino.h"
#include "../BiasChangeFunctions/BiasChangeFunctions.h"

#define MAX_NUM_DELAYS 8
#define DELAY_DECREMENT -10
#define MIN_DELAY_DECREMENT -1
#define DELAY_DECREMENT_CHANGE -3

class DelayCorrector {
  public:
    /**
     * Alternate constructor 1
     * @param initialDelay The delay time the robot should start with
     * @param correctTime The time it should take for the robot to complete each cycle in seconds
     * @param delayChangeFunc The function which determines how the delayDecrement is changed
     */
    DelayCorrector(uint32_t initialDelay, uint32_t correctTime,
                  DelayChangeFunc delayChangeFunc);

    /**
     * Alternate constructor 2
     * @param initialDelay The delay time the robot should start with
     * @param correctTime The time it should take for the robot to complete each cycle in seconds
     * @param maxNumOfCorrectedDelays The max num of corrected delays the object should store
     * @param delayDecrement The amount the delay should be decreased by if the robot fails to reach the top in time
     * @param minDelayDecrement The minimum amount the delay should be decreased by if the robot fails to reach the top in time
     * @param delayChangeFunc The function which determines how the delayDecrement is changed
     * @param delayDecrementChange Dictates how much the delayDecrement is changed by biasChangeFunc. Should be negative.
     */
    DelayCorrector(uint32_t initialDelay, uint32_t correctTime,
                  uint8_t maxNumOfDelays, int16_t delayDecrement,
                  int8_t minDelayDecrement, BiasChangeFunc delayChangeFunc,
                  int8_t delayDecrementChange);
    ~DelayCorrector();
    
    uint32_t getCurrentDelay(void) { return _currDelay; }

    uint32_t getCorrectTime(void) { return _correctTime; }

    /**
     * calculates new delay based on current delay and error
     * @param actualTime The time in seconds for the robot to complete its current cycle
     * @param topRached Whether the robot reached the top or not
     * @return uint8_t
     */
    uint32_t getCorrectedDelay(uint32_t actualTime, bool topReached);

    /**
     * Adds new corrected delay to object
     * Also updates current delay
     * @param correctedDelay The delay required to complete the last cycle correctly
     * @return void
     */
    void addNewCorrectedDelay(uint32_t correctedDelay);
    
  protected:
    uint8_t _delayIndex;
    uint8_t _numDelayLog2;
    uint32_t* _correctedDelays;
    bool _correctedDelaysFull;
    uint32_t _correctTime;
    int16_t _delayDecrement;
    int8_t _minDelayDecrement;
    BiasChangeFunc _delayChangeFunc;
    int8_t _delayDecrementChange;
    uint32_t _currDelay;
    
    /**
     * Get the mean delay of all stored corrected delays
     * @return The mean corrected delay
     */
    uint32_t getMeanDelay(void);

    /**
     * Calculates the next exponent of the next power of 2
     * @param startingNum The number to start finding the next power of 2
     * @return The exponent of the next power of 2
     * @attention If startingNum is already a power of 2 then log2(startingNum) is returned
     */
    uint8_t next2Exp(uint32_t startingNum);

    /**
     * Get the difference between the correct delay and the current delay given the error in cycle completion time
     * @param timeErr the difference between the correct time and the completion time
     * @return The delay offset
     */
    uint8_t getDelayOffset(uint32_t timeErr);

    /**
     * Tells robot object to use bias change function to calculate new delay decrement
     * @return void
     */
    void calcNewDelayDecrement(void);
};

#endif
