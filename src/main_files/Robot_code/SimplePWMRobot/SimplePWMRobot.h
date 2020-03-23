/*
 * @authors Harrison Outram and Anton R
 * Last Updated: 23/03/2020
 * @version 1.2
 * @brief Header file for SimplePWMRobot class
 * <p>The SimplePWMRobot class requires the robot to use sensors that can tell if the
 * robot is at the bottom or top.</p>
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Status: in progress
 */

#ifndef SimplePWMRobot_h
#define SimplePWMRobot_h

#include "Arduino.h"
#include "../IRobot/IRobot.h"
#include "../SpeedCorrector/SpeedCorrector.h"
#include "../RTClib/RTClib.h"

#define DOWN_PWM 0
#define BOTTOM_RELEASE_TIME 5
#define PWM_CHANGE_DELAY 1

/** Used for detecting if robot has reached top or bottom */
typedef bool (*TriggerFunc)(void);

class SimplePWMRobot : public IRobot {
  public:
    /**
     * @param pwmCorr The speed corrector AI used by Robot object
     * @param atTopFuncPtr A function pointer for determining if the robot is at the top
     * @param atBottomFuncPtr A function pointer for determining if the robot is at the bottom
     * @param setPwmPin The pin used to set the robot's PWM
     * @param rtc Real Time Clock (RTC) to keep track of time
     */
    SimplePWMRobot(PwmCorrector& pwmCorr,
            TriggerFunc atTopFuncPtr, TriggerFunc atBottomFuncPtr,
            uint8_t setPwmPin, RTC_DS1307& rtc);
    ~SimplePWMRobot();

    /**
     * Tells robot to start moving
     * Should be used for initial cycle only!
     * @return void
     */
    void start(void);

    /**
     * Checks if the robot has finished the current cycle
     * @return bool
     */
    bool cycleDone(void);

    /**
     * Makes robot go down ladder
     * WARNING: Does <b>not</b> prevent robot from stopping at bottom!
     * @return Whether the robot has started going down or not
     */
    bool goDown(void);

    /**
     * Will go up if enough time has passed
     * @return bool representing if robot is going up
     */
    bool goUp(void);

    /**
     * Check if at bottom of ladder
     * @return bool
     */
    bool atBottom(void);

  protected:
    //object variables
    DateTime* _currCycleEndDatePtr;
    PwmCorrector* _pwmCorrPtr;
    TriggerFunc _atTopFuncPtr;
    TriggerFunc _atBottomFuncPtr;
    RTC_DS1307* _rtcPtr;
    DateTime* _prevFinDatePtr;
    uint8_t _setPwmPin;
    bool _topMet;
    bool _waitingAtBottom;
    uint8_t _oldPwm;
    uint8_t _pwmChangeDelay;

    void changePwm(uint8_t i);

    /**
     * Prepares object variables for next cycle
     * Does <b>not</b> tell robot to move!
     * @return void
     */
    void prepareNextCycle(void);
};

#endif
