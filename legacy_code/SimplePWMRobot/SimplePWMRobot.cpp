/*
 * @authors Harrison Outram and Anton R
 * Last Updated: 23/03/2020 (d/m/y UTC+08:00)
 * @version 1.2
 * @brief Provide functionality for Robot class
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Status: in progress
 */

#include "SimplePWMRobot.h"

/**
 * @param pwmCorr The PWM corrector AI used by Robot object
 * @param atTopFuncPtr A function pointer for determining if the robot is at the top
 * @param atBottomFuncPtr A function pointer for determining if the robot is at the bottom
 * @param setPwmPin The pin used to set the robot's PWM
 * @param rtcPtr Pointer to Real Time Clock (RTC) to keep track of time
 */
SimplePWMRobot::SimplePWMRobot(PwmCorrector& pwmCorr,
            TriggerFunc atTopFuncPtr, TriggerFunc atBottomFuncPtr,
            uint8_t setPwmPin, RTC_DS1307& rtc) {
    _currCycleEndDatePtr = NULL;
    _pwmCorrPtr = &pwmCorr;
    _atTopFuncPtr = atTopFuncPtr;
    _atBottomFuncPtr = atBottomFuncPtr;
    _rtcPtr = &rtc;
    _prevFinDatePtr = NULL;
    _setPwmPin = setPwmPin;
    _topMet = false;
    _waitingAtBottom = false;
    _oldPwm = 0;
    _pwmChangeDelay = PWM_CHANGE_DELAY;

    analogWrite(setPwmPin, OUTPUT);
}

SimplePWMRobot::~SimplePWMRobot() {
    if (_currCycleEndDatePtr != NULL)
        delete _currCycleEndDatePtr;

    if (_prevFinDatePtr != NULL)
        delete _prevFinDatePtr;
}

	/* PUBLIC METHODS */

/**
 * Tells robot to start moving
 * Should be used for initial cycle only!
 * @return void
 */
void SimplePWMRobot::start(void) {
    _prevFinDatePtr = new Date(rtcPtr->now());
    _currCycleEndDatePtr = new Date(_prevFinDatePtr->unixtime() + _pwmCorrPtr->getCorrectTime();
    changePwm(_speedCorrPtr->getCurrentPwm());
}

/**
 * Checks if the robot has finished the current cycle
 * @return bool
 */
bool SimplePWMRobot::cycleDone(void) {
    bool result;

    _topMet = (*_atTopFuncPtr)();
    result = (_rtcPtr->now() >= *_currCycleEndDatePtr);
    result |= _topMet;

	return result;
}

/**
 * Makes robot go down ladder
 * WARNING: Does **not** prevent robot from stopping at bottom!
 * @return Whether the robot is going down or not
 */
bool SimplePWMRobot::goDown(void) {
    changePwm(DOWN_PWM);
    _waitingAtBottom = true;
    return true;
}

/**
 * Will go up if enough time has passed
 * Won't go up if reached top too early and still waiting for cycle to end
 * @return bool representing if robot is going up
 */
bool SimplePWMRobot::goUp(void) {
    DateTime *oldCycleEndDatePtr;
    bool goUp = (_rtcPtr->now() >= *_currCycleEndDatePtr);
    
    if (goUp) {
        changePwm(_speedCorrPtr->getCurrentPwm());
        _waitingAtBottom = false;
        oldCycleEndDatePtr = _currCycleEndDatePtr;
        _currCycleEndDatePtr = new DateTime(_currCycleEndDatePtr->unixtime() + _rtcPtr->getCorrectTime());
        delete oldCycleEndDatePtr;
    }
    
    return goUp;
}

/**
 * Checks if robot thinks it's at the bottom of the ladder
 * If only just starting to go up, will ignore trigger
 * @return bool
 */
bool SimplePWMRobot::atBottom(void) {
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
void SimplePWMRobot::changePwm(uint8_t newPwm) {
    uint8_t j;

    if (newPwm > _oldPwm) {
        for (uint8_t i = _oldPwm; i < newPwm; i++) {
            j = 0;
            while (i < newPwm && j < 10) {
                analogWrite(_setPwmPin, i);
                j++;
            }
            delay(_pwmChangeDelay);
        }
    } else if (newPwm < _oldPwm) {
        for (uint8_t i = _oldPwm; i > newPwm; i--) {
            j = 0;
            while (i > newPwm && j < 10) {
                analogWrite(_setPwmPin, i);
                j++;
            }
            delay(_pwmChangeDelay);
        }
    }

    _oldPwm = newPwm;
}

/**
 * Prepares object variables for next cycle
 * Does <b>not</b> tell robot to move!
 * @return void
 */
void SimplePWMRobot::prepareNextCycle(void) {
    uint8_t correctedPwm;
    
    delete _prevFinDatePtr;
    _prevFinDatePtr = new DateTime(_rtcPtr->now());
    correctedPwm = _speedCorrPtr->getCorrectedPwm(_prevFinDatePtr->unixtime(),
                                                  _topMet);
    _speedCorrPtr->addNewCorrectedPwm(correctedPwm);
    _topMet = false;
}

