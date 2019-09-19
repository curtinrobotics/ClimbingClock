/*
 * Author: Harrison Outram
 * Date: 19/09/2019
 * Version: 1.2
 * Purpose: Header file for auto correcting motor speed
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#ifndef SpeedCorrector_h
#define SpeedCorrector_h

#include "Arduino.h"
#include "../SpeedChangeFunctions/SpeedChangeFunctions.h"

class SpeedCorrector {
  public:
	//public class constants
	static const uint8_t MAX_NUM_OF_PWMS;
	static const uint8_t SPEED_INCREMENT;
	static const uint8_t MIN_SPEED_INCREMENT;
	static const uint8_t SPEED_INCREMENT_CHANGE;
	
	//constructors and destructor
	SpeedCorrector(uint16_t initialPwm, uint32_t inCorrectTime);
	SpeedCorrector(uint16_t initialPwm, uint32_t inCorrectTime, uint8_t inMaxNumOfPwms,
					uint16_t inSpeedIncrement, uint8_t inMinSpeedIncrement, uint8_t (*inSpeedChangeFunc)(uint8_t currSpeedChange, uint8_t speedIncChange),
					uint8_t inSpeedIncrementChange);
	~SpeedCorrector();
	
	//public methods
	uint16_t getCorrectedPwm(uint32_t actualTime, uint16_t currentPwm, bool topReached);
	void addNewCorrectedPwm(uint16_t correctedPwm);
	uint16_t getMeanPwm(void);
  private:
	//object variables
	uint8_t pwmIndex;
	uint8_t maxPwmIndex;
	uint16_t* correctedPwms;
	bool correctedPwmsFull;
	uint32_t correctTime;
	int8_t speedIncrement;
	uint8_t minSpeedIncrement;
	uint8_t (*speedChangeFunc)(uint8_t currSpeedChange, uint8_t speedIncChange);
	uint8_t speedIncrementChange;
	
	//private methods
	uint16_t getPwmOffset(uint32_t timeErr, uint16_t currentPwm);
	void calcNewSpeedIncrement(void);
};

#endif
