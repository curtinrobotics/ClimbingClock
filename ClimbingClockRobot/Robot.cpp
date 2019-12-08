/*
 * Author: Harrison Outram and Anton R
 * Date: 8/12/2019
 * Version: 0.1
 * Purpose: Provide functionality for Robot class
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Compiles
 */

#include "Robot.h"

/**
 * @param initialEndDate The end date and time of the first cycle
 * @param inSpeedCorrPtr The speed corrector AI used by Robot object
 * @param inAtTopFuncPtr A function pointer for determining if the robot is at the top
 * @param inAtBottomFuncPtr A function pointer for determining if the robot is at the bottom
 * @param inSetPwmPin The pin used to set the robot's PWM
 * @param inRtcPtr Pointer to Real Time Clock (RTC) to keep track of time
 */
Robot::Robot(DateTime& initialEndDate, SpeedCorrector* inSpeedCorrPtr,
            bool (*inAtTopFuncPtr)(void), bool (*inAtBottomFuncPtr)(void),
            uint8_t inSetPwmPin, RTC_DS1307* inRtcPtr) {
    currCycleEndDatePtr = new DateTime(initialEndDate);
    speedCorrPtr = inSpeedCorrPtr;
    atTopFuncPtr = inAtTopFuncPtr;
    atBottomFuncPtr = inAtBottomFuncPtr;
    rtcPtr = inRtcPtr;
    prevFinDatePtr = new DateTime(rtcPtr->now());
    setPwmPin = inSetPwmPin;
    topMet = false;
    waitingAtBottom = false;

    analogWrite(setPwmPin, OUTPUT);
}

Robot::~Robot() {
    delete currCycleEndDatePtr;
    delete prevFinDatePtr;
}

	/* PUBLIC METHODS */

/**
 * Tells robot to start moving
 * Should be used for initial cycle only!
 * @return void
 */
void Robot::start(void) {
    analogWrite(setPwmPin, speedCorrPtr->getCurrentPwm());
}

/**
 * Checks if the robot has finished the current cycle
 * @return bool
 */
bool Robot::cycleDone(void) {
    bool result;

    topMet = (*atTopFuncPtr)();
    result = (rtcPtr->now() >= *currCycleEndDatePtr && !waitingAtBottom);
    result |= topMet;

	return result;
}

/**
 * Prepares object variables for next cycle
 * Does **not** tell robot to move!
 * @return void
 */
void Robot::prepareNextCycle(void) {
    uint8_t correctedPwm;
    
    delete prevFinDatePtr;
    prevFinDatePtr = new DateTime(rtcPtr->now());
    correctedPwm = speedCorrPtr->getCorrectedPwm(prevFinDatePtr->unixtime(),
                                                topMet);
    speedCorrPtr->addNewCorrectedPwm(correctedPwm);
    topMet = false;
}

/**
 * Makes robot go down ladder
 * WARNING: Does **not** prevent robot from stopping at bottom!
 * Use stop() to command robot to stop!
 * @return void
 */
void Robot::goDown(void) {
    analogWrite(setPwmPin, DOWN_PWM);
    waitingAtBottom = true;
}

/**
 * Will go up if enough time has passed
 * Won't go up if reached top too early and still waiting for cycle to end
 * @return bool representing if robot is going up
 */
bool Robot::attemptToGoUp(void) {
    DateTime *oldCycleEndDatePtr;
    DateTime newCycleEnd;
    bool goUp = (rtcPtr->now() >= *currCycleEndDatePtr);
    
    if (goUp) {
        analogWrite(setPwmPin, speedCorrPtr->getCurrentPwm());
        waitingAtBottom = false;
        oldCycleEndDatePtr = currCycleEndDatePtr;
        newCycleEnd = *currCycleEndDatePtr + *correctTimePtr;
        currCycleEndDatePtr = new DateTime(newCycleEnd);
        delete oldCycleEndDatePtr;
    }
    
    return goUp;
}

/**
 * Checks if hare thinks it's at the bottom of the ladder
 * If only just starting to go up, will ignore trigger
 * @return bool
 */
bool Robot::atBottom(void) {
    bool atBottom;
    TimeSpan timePassed;

    if (waitingAtBottom) {
        atBottom = true;
    } else {
        //hare should only think it's at bottom if enough time has passed
        //since previous cycle trigger
        timePassed = rtcPtr->now() - *prevFinDatePtr;
        if (timePassed.totalseconds() > BOTTOM_RELEASE_TIME) {
            atBottom = (*atBottomFuncPtr)();
        } else {
            atBottom = false;
        }
    }

    return atBottom;
}

