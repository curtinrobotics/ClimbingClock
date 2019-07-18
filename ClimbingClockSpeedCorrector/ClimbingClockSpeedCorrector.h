/*
 * Author: Harrison Outram
 * Date: 8/07/2019
 * Version: 0.3
 * Purpose: Header file for auto correcting motor speed
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#ifndef ClimbingClockSpeedCorrector_h
#define ClimbingClockSpeedCorrector_h

#include "Arduino.h"

class ClimbingClockSpeedCorrector {
  public:
  	//public class constants
    static const uint8_t MAX_NUM_OF_PWMS;
    static const uint8_t SPEED_INCREASE_INCREMENT;
    
    //constructors and destructor
    ClimbingClockSpeedCorrector(uint16_t initialPwm, uint32_t inCorrectTime);
    ClimbingClockSpeedCorrector(uint16_t initialPwm, uint32_t inCorrectTime, uint8_t inMaxNumOfPwms,
								uint16_t inSpeedIncreaseIncrement);
	~ClimbingClockSpeedCorrector();
    
    //public methods
    uint16_t getCorrectedPwm(uint32_t actualTime, uint16_t currentPwm, bool topReached);
    void addNewCorrectedPwm(uint16_t correctedPwm);
    uint16_t getMeanPwm(void);
  private:
  	//classfields
    uint8_t pwmIndex;
    uint8_t maxPwmIndex;
    uint16_t* correctedPwms;
    bool correctedPwmsFull;
    uint32_t correctTime;
    uint8_t speedIncreaseIncrement;
    
    //private methds
    uint16_t getPwmOffset(uint32_t timeErr, uint16_t currentPwm);
};

#endif
