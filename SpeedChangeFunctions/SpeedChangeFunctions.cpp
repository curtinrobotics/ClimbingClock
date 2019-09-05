/*
 * Author: Harrison Outram
 * Date: 5/09/2019
 * Version: 1.1
 * Purpose: Simple functions for changing speedCorrector
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include "Arduino.h"
#include "SpeedChangeFunctions.h"

//does not change speed increment
static uint8_t SpeedChangeFunctions::noChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc;
}

//changes speed increment linearly
// speedInc = initialSpeedInc - floor(time / correctTime) * speedIncChange
static uint8_t SpeedChangeFunctions::linearChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc -= speedIncChange;
}

//changes speed increment exponentially
// speedInc = initialSpeedInc * (1 / speedIncChange) ^ floor(time / correctTime)
static uint8_t SpeedChangeFunctions::exponentialChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc /= speedIncChange;
}
