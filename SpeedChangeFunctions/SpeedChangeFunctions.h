/*
 * Author: Harrison Outram
 * Date: 5/09/2019
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
	static uint32_t noChange(uint32_t currSpeedInc, uint32_t speedIncChange);
	static uint32_t linearChange(uint32_t currSpeedInc, uint32_t speedIncChange);
	static uint32_t exponentialChange(uint32_t currSpeedInc, uint32_t speedIncChange);
};

#endif
