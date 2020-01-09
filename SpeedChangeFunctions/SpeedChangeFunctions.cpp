/*
 * @author Harrison Outram
 * Last Updated: 06/12/2019
 * @version 1.2
 * @brief Simple functions for changing speedCorrector
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include "Arduino.h"
#include "SpeedChangeFunctions.h"

/**
 * does not change speed increment
 * @param currSpeedInc The current speed increment
 * @param speedIncChange The change of the speed increment (useless)
 * @return uint8_t
 */
uint8_t SpeedChangeFunctions::noChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc;
}

/**
 * Changes speed increment linearly
 * speedInc = initialSpeedInc - floor(time / correctTime) * speedIncChange
 * @param currSpeedInc The current speed increment
 * @param speedIncChange The amount to decrease the speed increment by
 * @return uint8_t
 */
uint8_t SpeedChangeFunctions::linearChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc - speedIncChange;
}

/**
 * changes speed increment exponentially
 * speedInc = initialSpeedInc * (1 / speedIncChange) ^ floor(time / correctTime)
 * @param currSpeedInc The current speed increment
 * @param speedIncChange What to divide the speed increment by
 * @return uint8_t
 */
uint8_t SpeedChangeFunctions::exponentialChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc / speedIncChange;
}
