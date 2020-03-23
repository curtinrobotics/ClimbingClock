/*
 * @author Harrison Outram
 * Last Updated: 23/03/2020 (d/m/y, UTC+08:00)
 * @version 2.0.0
 * @brief Simple functions for changing PwmCorrector speed increment
 * Project: Climbing Clock
 * Organisation: Curtin Robotics Club (CRoC)
 * Status: Untested
 */

#include "Arduino.h"
#include "SpeedChangeFunctions.h"

/**
 * does not change speed increment
 * @param currSpeedInc The current speed increment
 * @param speedIncChange The change of the speed increment (useless)
 * @return uint8_t
 */
uint8_t noChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc;
}

/**
 * Changes speed increment linearly
 * speedInc = initialSpeedInc - floor(time / correctTime) * speedIncChange
 * @param currSpeedInc The current speed increment
 * @param speedIncChange The amount to decrease the speed increment by
 * @return uint8_t
 */
uint8_t linearChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc - speedIncChange;
}

/**
 * changes speed increment exponentially
 * speedInc = initialSpeedInc * (1 / speedIncChange) ^ floor(time / correctTime)
 * @param currSpeedInc The current speed increment
 * @param speedIncChange What to divide the speed increment by
 * @return uint8_t
 */
uint8_t exponentialChange(uint8_t currSpeedInc, uint8_t speedIncChange) {
	return currSpeedInc / speedIncChange;
}
