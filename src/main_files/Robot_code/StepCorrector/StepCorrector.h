/**
 * @brief Header file for StepCorrector
 * Project: Climbing Clock
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: In progress
 */

#ifndef StepCorrector_h
#define StepCorrector_h

#include "Arduino.h"

/** @brief Default size for correctedSteps array */
#define MAX_NUM_STEPS ((uint8_t)8)

class StepCorrector {
  public:
    /**
     * Alternate constructor 1: Only requires needed parameters
     * @param initialStep The step time the robot should start with
     * @param correctReading The reading the robot should be getting if at correct steps
     */
    StepCorrector(uint32_t initialStep, int32_t correctReading);

    /**
     * Alternate constructor 2: Full customisation of object properties
     * @param initialStep The step time the robot should start with
     * @param correctReading The reading the robot should be getting if at correct steps
     * @param maxNumCorrectedSteps The max num of corrected steps the object should store
     */
    StepCorrector(uint32_t initialStep, uint32_t correctReading,
                  uint8_t maxNumCorrectedSteps);
    ~StepCorrector();
    
    uint32_t getCurrentStep(void) { return _currStep; }

    uint32_t getCorrectReading(void) { return _correctReading; }

    /**
     * calculates new step based on current step and error
     * @param actualTime The time in seconds for the robot to complete its current cycle
     * @param topRached Whether the robot reached the top or not
     * @return The corrected step time
     */
    uint32_t getCorrectedStep(uint32_t actualTime, bool topReached);

    /**
     * Adds new corrected step to object
     * Also updates current step
     * @param correctedStep The step required to complete the last cycle correctly
     * @return void
     */
    void addNewCorrectedStep(uint32_t correctedStep);
    
  protected:
    uint8_t _stepIndex;
    uint8_t _numStepLog2;
    uint32_t* _correctedSteps;
    bool _correctedStepsFull;
    uint32_t _correctTime;
    int16_t _stepDecrement;
    int8_t _minStepDecrement;
    BiasChangeFunc _stepChangeFunc;
    int8_t _stepDecrementChange;
    uint32_t _currStep;
    
    /**
     * Get the mean step of all stored corrected steps
     * @return The mean corrected step
     */
    uint32_t getMeanStep(void);

    /**
     * Calculates new step increment using given step change function
     * @return The new step increment
     */
    uint16_t calcNewStepDecrement(void);
};

#endif
