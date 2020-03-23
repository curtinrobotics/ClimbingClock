/*
 * @author Harrison Outram
 * Last Updated: 23/03/2020 (d/m/y, UTC+08:00)
 * @version 2.0.0
 * @brief Header file for speed change functions
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Status: Untested
 */

#ifndef SpeedChangeFunctions_h
#define SpeedChangeFunctions_h

#include "Arduino.h"

/**
 * does not change speed increment
 * @param currSpeedInc The current speed increment
 * @param speedIncChange The change of the speed increment (useless)
 * @return uint8_t
 */
static uint8_t noChange(uint8_t currSpeedInc, uint8_t speedIncChange);

/**
 * Changes speed increment linearly
 * speedInc = initialSpeedInc - floor(time / correctTime) * speedIncChange
 * @param currSpeedInc The current speed increment
 * @param speedIncChange The amount to decrease the speed increment by
 * @return uint8_t
 */
static uint8_t linearChange(uint8_t currSpeedInc, uint8_t speedIncChange);

/**
 * changes speed increment exponentially
 * speedInc = initialSpeedInc * (1 / speedIncChange) ^ floor(time / correctTime)
 * @param currSpeedInc The current speed increment
 * @param speedIncChange What to divide the speed increment by
 * @return uint8_t
 */
static uint8_t exponentialChange(uint8_t currSpeedInc, uint8_t speedIncChange);

#endif
