/**
 * @author Harrison Outram
 * Last Updated: 7/05/2020 (d/m/y, UTC+08:00)
 * @brief Simple functions for changing the bias of a machine learning AI
 * Project: Climbing Clock
 * Organisation: Curtin Robotics Club (CRoC)
 * Status: Untested
 */

#include "BiasChangeFunctions.h"

/**
 * Does not change bias
 * @param currBiasInc The current bias increment
 * @param biasIncChange useless, included for compatability
 * @return The current bias increment
 */
int noChange(int currBiasInc, int biasIncChange) { return currBiasInc; }

/**
 * Changes bias increment linearly
 * biasInc = initalBiasInc - numCalls * biasChangeInc
 * @param currBiasInc The current bias increment
 * @param biasIncChange The amount to decrease the bias increment by
 * @return The new current bias increment
 */
int linearChange(int currBiasInc, int biasIncChange) {
    return currBiasInc - biasIncChange;
}

/**
 * changes bias increment exponentially
 * biasInc = initialBiasInc * (1 / biasIncChange) ^ numCalls
 * @param currBiasInc The current bias increment
 * @param biasIncChange What to divide the bias increment by
 * @return The new bias increment
 */
int exponentialChange(int currBiasInc, int biasIncChange) {
    return currBiasInc / biasIncChange;
}
