/*
 * @author Harrison Outram and Anton R
 * Last Updated: 21/12/2019
 * @version 1.0
 * @brief Provide functionality for Robot class
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Compiles
 */

#include "Robot.h"

/**
 * @param initialEndDate The end date and time of the first cycle
 * @param speedCorr The speed corrector AI used by Robot object
 * @param atTopFuncPtr A function pointer for determining if the robot is at the top
 * @param atBottomFuncPtr A function pointer for determining if the robot is at the bottom
 * @param setPwmPin The pin used to set the robot's PWM
 * @param rtcPtr Pointer to Real Time Clock (RTC) to keep track of time
 */
Robot::Robot(DateTime& initialEndDate, SpeedCorrector* speedCorrPtr,
            TriggerFunc atTopFuncPtr, TriggerFunc atBottomFuncPtr,
            uint8_t setPwmPin, RTC_DS1307* rtcPtr) {
    _currCycleEndDatePtr = new DateTime(initialEndDate);
    _speedCorrPtr = speedCorrPtr;
    _atTopFuncPtr = atTopFuncPtr;
    _atBottomFuncPtr = atBottomFuncPtr;
    _rtcPtr = rtcPtr;
    _prevFinDatePtr = new DateTime(rtcPtr->now());
    _setPwmPin = setPwmPin;
    _topMet = false;
    _waitingAtBottom = false;
    _oldPwm = 0;

    analogWrite(setPwmPin, OUTPUT);
}

Robot::~Robot() {
    delete _currCycleEndDatePtr;
    delete _prevFinDatePtr;
}

	/* PUBLIC METHODS */

/**
 * Tells robot to start moving
 * Should be used for initial cycle only!
 * @return void
 */
void Robot::start(void) {
    changePwm(_speedCorrPtr->getCurrentPwm());
}

/**
 * Checks if the robot has finished the current cycle
 * @return bool
 */
bool Robot::cycleDone(void) {
    bool result;

    _topMet = (*_atTopFuncPtr)();
    result = (_rtcPtr->now() >= *_currCycleEndDatePtr);
    result |= _topMet;

	return result;
}

/**
 * Prepares object variables for next cycle
 * Does <b>not</b> tell robot to move!
 * @return void
 */
void Robot::prepareNextCycle(void) {
    uint8_t correctedPwm;
    
    delete _prevFinDatePtr;
    _prevFinDatePtr = new DateTime(_rtcPtr->now());
    correctedPwm = _speedCorrPtr->getCorrectedPwm(_prevFinDatePtr->unixtime(),
                                                  _topMet);
    _speedCorrPtr->addNewCorrectedPwm(correctedPwm);
    _topMet = false;
}

/**
 * Makes robot go down ladder
 * WARNING: Does **not** prevent robot from stopping at bottom!
 * Use stop() to command robot to stop!
 * @return void
 */
void Robot::goDown(void) {
    changePwm(DOWN_PWM);
    _waitingAtBottom = true;
}

/**
 * Will go up if enough time has passed
 * Won't go up if reached top too early and still waiting for cycle to end
 * @return bool representing if robot is going up
 */
bool Robot::attemptToGoUp(void) {
    DateTime *oldCycleEndDatePtr;
    DateTime newCycleEnd;
    bool goUp = (_rtcPtr->now() >= *_currCycleEndDatePtr);
    
    if (goUp) {
        changePwm(_speedCorrPtr->getCurrentPwm());
        _waitingAtBottom = false;
        oldCycleEndDatePtr = _currCycleEndDatePtr;
        newCycleEnd = *_currCycleEndDatePtr + *_correctTimePtr;
        _currCycleEndDatePtr = new DateTime(newCycleEnd);
        delete oldCycleEndDatePtr;
    }
    
    return goUp;
}

/**
 * Checks if robot thinks it's at the bottom of the ladder
 * If only just starting to go up, will ignore trigger
 * @return bool
 */
bool Robot::atBottom(void) {
    bool atBottom;
    TimeSpan timePassed;

    if (_waitingAtBottom) {
        atBottom = true;
    } else {
        //robot should only think it's at bottom if enough time has passed
        //since previous cycle trigger
        timePassed = _rtcPtr->now() - *_prevFinDatePtr;
        if (timePassed.totalseconds() > BOTTOM_RELEASE_TIME) {
            atBottom = (*_atBottomFuncPtr)();
        } else {
            atBottom = false;
        }
    }

    return atBottom;
}

/* PROTECTED METHODS */

/**
 * Gradually changes motor speed to prevent damage
 * Will also update oldPwm object variable
 * @param newPwm The new PWM to change the motor speed to
 * @return void
 */
void Robot::changePwm(uint8_t newPwm) {
    if (newPwm > _oldPwm) {
        for (uint8_t i = _oldPwm; i < newPwm; i++)
            analogWrite(_setPwmPin, i);
    } else if (newPwm < _oldPwm) {
        for (uint8_t i = _oldPwm; i > newPwm; i--) 
            analogWrite(_setPwmPin, i);
    }

    _oldPwm = newPwm;
}

