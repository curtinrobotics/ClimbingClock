/*
 * Author: Harrison Outram
 * Date: 5/09/2019
 * Version: 1.0
 * Purpose: Simple functions for changing speedCorrector
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include "Arduino.h"
#include "SpeedChangeFunctions.h"

//does not change speed increment
static uint32_t SpeedChangeFunctions::noChange(uint32_t currSpeedInc, uint32_t speedIncChange) {
	return currSpeedInc;
}

//changes speed increment linearly
// speedInc = initialSpeedInc - floor(time / correctTime) * speedIncChange
static uint32_t SpeedChangeFunctions::linearChange(uint32_t currSpeedInc, uint32_t speedIncChange) {
	return currSpeedInc -= speedIncChange;
}

//changes speed increment exponentially
// speedInc = initialSpeedInc * (1 / speedIncChange) ^ floor(time / correctTime)
static uint32_t SpeedChangeFunctions::exponentialChange(uint32_t currSpeedInc, uint32_t speedIncChange) {
	return currSpeedInc /= speedIncChange;
}
