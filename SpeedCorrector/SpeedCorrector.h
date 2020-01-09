/*
 * @author Harrison Outram
 * Last Updated: 21/12/2019 (d/m/y)
 * @version 1.4
 * @brief Header file for auto correcting motor speed
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: works
 */

#ifndef SpeedCorrector_h
#define SpeedCorrector_h

#include "Arduino.h"

#define MAX_NUM_OF_PWMS 10
#define SPEED_INCREMENT 10
#define MIN_SPEED_INCREMENT 1
#define SPEED_INCREMENT_CHANGE 3
#define MAX_PWM 255                 // Max PWM Arduino will accept

typedef uint8_t (*SpeedChangeFunc)(uint8_t currSpeedChange,
                                    uint8_t speedIncChange);

class SpeedCorrector {
  public:
    /**
     * @param initialPwm The PWM the robot should start with
     * @param correctTime The time it should take for the robot to complete each cycle in seconds
     * @param speedChangeFunc The function which determines how the speedIncrement is changed
     */
    SpeedCorrector(uint8_t initialPwm, uint32_t correctTime,
                    SpeedChangeFunc speedChangeFunc);

    /**
     * @param initialPwm The PWM the robot should start with
     * @param correctTime The time it should take for the robot to complete each cycle in seconds
     * @param maxNumOfCorrectedPwms The max num of corrected PWMs the object should store
     * @param speedIncrement The amount the PWM should be increased by if the robot fails to reach the top in time
     * @param minSpeedIncrement The minimum amount the PWM should be increased by if the robot fails to reach the top in time
     * @param speedChangeFunc The function which determines how the speedIncrement is changed
     * @param speedIncrementChange Dictates how much the speedIncrement is changed by inSpeedChangeFunc
     */
    SpeedCorrector(uint8_t initialPwm, uint32_t correctTime, uint8_t maxNumOfPwms,
                    uint8_t speedIncrement, uint8_t minSpeedIncrement,
                    SpeedChangeFunc speedChangeFunc,
                    uint8_t speedIncrementChange);
    ~SpeedCorrector();
    
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
    uint8_t _pwmIndex;
    uint8_t _maxPwmIndex;
    uint8_t* _correctedPwms;
    bool _correctedPwmsFull;
    uint32_t _correctTime;
    int8_t _speedIncrement;
    uint8_t _minSpeedIncrement;
    SpeedChangeFunc _speedChangeFunc;
    uint8_t _speedIncrementChange;
    uint8_t _currPwm;
    
    uint8_t getMeanPwm(void);
    uint8_t getPwmOffset(uint32_t timeErr);
    void calcNewSpeedIncrement(void);
};

#endif
