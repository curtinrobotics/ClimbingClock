/*
 * Author: Harrison Outram
 * Date: 19/09/2019
 * Version: 1.0
 * Purpose: Header file for speed change functions
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#ifndef SpeedChangeFunctions_h
#define SpeedChangeFunctions_h

#include "Arduino.h"

class SpeedChangeFunctions {
  public:
	static uint8_t noChange(uint8_t currSpeedInc, uint8_t speedIncChange);
	static uint8_t linearChange(uint8_t currSpeedInc, uint8_t speedIncChange);
	static uint8_t exponentialChange(uint8_t currSpeedInc, uint8_t speedIncChange);
};

#endif
