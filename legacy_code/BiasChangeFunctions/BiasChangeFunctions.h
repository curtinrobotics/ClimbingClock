/**
 * @author Harrison Outram
 * Last Updated: 7/05/2020 (d/m/y, UTC+08:00)
 * @brief Header file for bias change functions
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Status: Untested
 */

#ifndef BiasChangeFunctions_h
#define BiasChangeFunctions_h

/** @typedef */
typedef int (*BiasChangeFunc)(int currBiasInc, int biasIncChange);

/**
 * does not change bias increment
 * @param currBiasInc The current bias increment
 * @param biasIncChange Useless, included for compatability
 * @return The current bias increment
 */
int noChange(int currBiasInc, int biasIncChange);

/**
 * Changes bias increment linearly
 * biasInc = initialBiasInc - numCalls * biasIncChange
 * @param currBiasInc The current bias increment
 * @param biasIncChange The amount to decrease the bias increment by
 * @return The next bias increment
 */
int linearChange(int currBiasInc, int biasIncChange);

/**
 * changes bias increment exponentially
 * biasInc = initialBiasInc * (1 / biasIncChange) ^ numCalls
 * @param currBiasInc The current bias increment
 * @param biasIncChange What to divide the bias increment by
 * @return The next bias increment
 */
int exponentialChange(int currBiasInc, int biasIncChange);

#endif
