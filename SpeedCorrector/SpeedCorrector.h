/*
 * Author: Harrison Outram
 * Date: 08/12/2019 (d/m/y)
 * Version: 1.3
 * Purpose: Header file for auto correcting motor speed
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Compiles
 */

#ifndef SpeedCorrector_h
#define SpeedCorrector_h

#include "Arduino.h"

#define MAX_NUM_OF_PWMS 10
#define SPEED_INCREMENT 10
#define MIN_SPEED_INCREMENT 1
#define SPEED_INCREMENT_CHANGE 3
#define MAX_8BIT_INT 255

class SpeedCorrector {
  public:
    /**
     * @param initialPwm The PWM the robot should start with
     * @param inCorrectTime The time it should take for the robot to complete each cycle in seconds
     * @param inSpeedChangeFunc The function which determines how the speedIncrement is changed
     */
    SpeedCorrector(uint8_t initialPwm, uint32_t inCorrectTime,
                    uint8_t (*inSpeedChangeFunc)(uint8_t currSpeedChange, uint8_t speedIncChange));

    /**
     * @param initialPwm The PWM the robot should start with
     * @param inCorrectTime The time it should take for the robot to complete each cycle in seconds
     * @param inMaxNumOfCorrectedPwms The max num of corrected PWMs the object should store
     * @param inSpeedIncrement The amount the PWM should be increased by if the robot fails to reach the top in time
     * @param inMinSpeedIncrement The minimum amount the PWM should be increased by if the robot fails to reach the top in time
     * @param inSpeedChangeFunc The function which determines how the speedIncrement is changed
     * @param inSpeedIncrementChange Dictates how much the speedIncrement is changed by inSpeedChangeFunc
     */
    SpeedCorrector(uint8_t initialPwm, uint32_t inCorrectTime, uint8_t inMaxNumOfPwms,
                    uint8_t inSpeedIncrement, uint8_t inMinSpeedIncrement, uint8_t (*inSpeedChangeFunc)(uint8_t currSpeedChange, uint8_t speedIncChange),
                    uint8_t inSpeedIncrementChange);
    ~SpeedCorrector();
    
    /* PUBLIC METHODS */

    /**
     * calculates new PWM based on current PWM and error
     * @param actualTime The time in seconds for the robot to complete its current cycle
     * @param topRached Whether the robot reached the top or not
     * @return uint8_t
     */
    uint8_t getCorrectedPwm(uint32_t actualTime, bool topReached);

    /**
     * Adds new corrected PWM to object
     * Also updates current PWM
     * @param correctedPwm The PWM required to complete the last cycle correctly
     * @return void
     */
    void addNewCorrectedPwm(uint8_t correctedPwm);
    
    uint8_t getCurrentPwm(void);

  private:
    //object variables
    uint8_t pwmIndex;
    uint8_t maxPwmIndex;
    uint8_t* correctedPwms;
    bool correctedPwmsFull;
    uint32_t correctTime;
    int8_t speedIncrement;
    uint8_t minSpeedIncrement;
    uint8_t (*speedChangeFunc)(uint8_t currSpeedChange, uint8_t speedIncChange);
    uint8_t speedIncrementChange;
    uint8_t currPwm;
    
    //private methods
    uint8_t getMeanPwm(void);
    uint8_t getPwmOffset(uint32_t timeErr);
    void calcNewSpeedIncrement(void);
};

#endif
