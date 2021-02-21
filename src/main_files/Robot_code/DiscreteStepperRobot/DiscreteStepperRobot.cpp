/*
 * @author Harrison Outram
 * Last Updated: ??/??/2020 (d/m/y UTC+08:00)
 * @version 0.1.0
 * @brief Provide functionality for Robot class
 * Project: Climbing Clock
 * Organisation: Curtin Robotics Club (CRoC)
 * Status: in progress
 */

#include "DiscreteStepperRobot.h"

/**
 * @param stepCorr The step corrector AI used by Robot object
 * @param atTopFuncPtr A function pointer for determining if the robot is at the top
 * @param atBottomFuncPtr A function pointer for determining if the robot is at the bottom
 * @param stepPin The pin used to make the stepper motor rotate, must be a PWM pin
 * @param dirPin The pin for setting the direction of the motor
 * @param upDir The digital output setting for going up
 * @param rtc Real Time Clock (RTC) to keep track of time
 */
DiscreteStepperRobot::DiscreteStepperRobot(StepCorrector& stepCorr,
            TriggerFunc atTopFuncPtr, TriggerFunc atBottomFuncPtr,
            uint8_t stepPin, uint8_t dirPin, uint8_t upDir, RTC& rtc) {
    _currCycleEndDatePtr = NULL;
    _stepCorrPtr = &stepCorr;
    _atTopFuncPtr = atTopFuncPtr;
    _atBottomFuncPtr = atBottomFuncPtr;
    _rtcPtr = &rtc;
    _prevFinDatePtr = NULL;
    _stepPin = stepPin;
    _dirPin = dirPin;
    _upDir = upDir;
    _topMet = false;
    _waitingAtBottom = false;
    _goingUp = false;
    _goingDown = false;
    _oldPwm = 0;
}

DiscreteStepperRobot::~DiscreteStepperRobot() {
    if (_currCycleEndDatePtr != NULL)
        delete _currCycleEndDatePtr;

    if (_prevFinDatePtr != NULL)
        delete _prevFinDatePtr;
}

    /* PUBLIC METHODS */

/**
 * @brief Tells robot to start moving
 *          Should be used for initial cycle only!
 * @return void
 */
void DiscreteStepperRobot::start(void) {
    _prevFinDatePtr = new Date(rtcPtr->now());
    _currCycleEndDatePtr = new Date(_prevFinDatePtr->unixtime()
                                    + _stepCorrPtr->getCorrectTime());
    changePwm(_speedCorrPtr->getCurrentPwm());
}

/**
 * @brief Check how far the robot has climbed
 * @return 0 if at the bottom, TOP_POS if at the top, or -1 if unknown
 * @warning Will return -1 if not at the top nor the bottom
 */
int DiscreteStepperRobot::getPosition(void) {
    if (*_atTopFuncPtr)
        return TOP_POS;
    if (*_atBottomFuncPtr)
        return 0;
    
    return -1;
}

/**
 * @brief Checks which direction the robot is moving
 * @return An integer from the Direction enum
 */
int DiscreteStepperRobot::getDirection(void) {
    if (*_atTopFuncPtr)
        return AT_TOP;
    if (*_atBottomFuncPtr)
        return AT_BOTTOM;
    if (_goingUp)
        return UP;
    if (_goingDown)
        return DOWN;
    
    return STILL;
}

/**
 * @brief Checks if the robot has finished the current cycle
 * @return Whether the current cycle is done or not
 */
bool DiscreteStepperRobot::cycleDone(void) {
    bool result;

    _topMet = (*_atTopFuncPtr)();
    result = (_rtcPtr->now() >= *_currCycleEndDatePtr);
    result |= _topMet;

    return result;
}

/**
 * @brief Makes robot go down ladder
 * @warning Does **not** prevent robot from stopping at bottom!
 * @return Whether the robot is going down or not
 */
bool DiscreteStepperRobot::goDown(void) {

    return true;
}

/**
 * Will go up if enough time has passed
 * Won't go up if reached top too early and still waiting for cycle to end
 * @return bool representing if robot is going up
 */
bool DiscreteStepperRobot::goUp(void) {
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
bool DiscreteStepperRobot::atBottom(void) {
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
void DiscreteStepperRobot::changePwm(uint8_t newPwm) {
    uint8_t j;

    if (newPwm > _oldPwm) {
        for (uint8_t i = _oldPwm; i < newPwm; i++) {
            j = 0;
            while (i < newPwm && j < 10) {
                analogWrite(_setPwmPin, i);
                j++;
            }
            delay(_stepChangeDelay);
        }
    } else if (newPwm < _oldPwm) {
        for (uint8_t i = _oldPwm; i > newPwm; i--) {
            j = 0;
            while (i > newPwm && j < 10) {
                analogWrite(_setPwmPin, i);
                j++;
            }
            delay(_stepChangeDelay);
        }
    }

    _oldPwm = newPwm;
}

/**
 * Prepares object variables for next cycle
 * Does <b>not</b> tell robot to move!
 * @return void
 */
void DiscreteStepperRobot::prepareNextCycle(void) {
    uint8_t correctedPwm;
    
    delete _prevFinDatePtr;
    _prevFinDatePtr = new DateTime(_rtcPtr->now());
    correctedPwm = _speedCorrPtr->getCorrectedPwm(_prevFinDatePtr->unixtime(),
                                                  _topMet);
    _speedCorrPtr->addNewCorrectedPwm(correctedPwm);
    _topMet = false;
}

