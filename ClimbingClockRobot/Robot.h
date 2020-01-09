/*
 * @author Harrison Outram and Anton R
 * Last Updated: 21/12/2019
 * @version 1.0
 * @brief Header file for Robot class
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Works
 */

#ifndef Robot_h
#define Robot_h

#include "Arduino.h"
#include "../SpeedCorrector/SpeedCorrector.h"
#include "../RTClib/RTClib.h"

#define DOWN_PWM 0
#define BOTTOM_RELEASE_TIME 5

typedef bool (*TriggerFunc)(void);

class Robot {
  public:
    /**
     * @param initialEndDate The end date and time of the first cycle
     * @param speedCorr The speed corrector AI used by Robot object
     * @param atTopFuncPtr A function pointer for determining if the robot is at the top
     * @param atBottomFuncPtr A function pointer for determining if the robot is at the bottom
     * @param setPwmPin The pin used to set the robot's PWM
     * @param rtcPtr Pointer to Real Time Clock (RTC) to keep track of time
     */
    Robot(DateTime& initialEndDate, SpeedCorrector* speedCorrPtr,
            TriggerFunc atTopFuncPtr, TriggerFunc atBottomFuncPtr,
            uint8_t setPwmPin, RTC_DS1307* rtcPtr);
    ~Robot();

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
     * Prepares object variables for next cycle
     * Does **not** tell robot to move!
     * @return void
     */
    void prepareNextCycle(void);

    /**
     * Makes robot go down ladder
     * WARNING: Does **not** prevent robot from stopping at bottom!
     * Use stop() to command robot to stop!
     * @return void
     */
    void goDown(void);

    /**
     * Will go up if enough time has passed
     * @return bool representing if robot is going up
     */
    bool attemptToGoUp(void);

    /**
     * Check if at bottom of ladder
     * @return bool
     */
    bool atBottom(void);

  protected:
    //object variables
    TimeSpan* _correctTimePtr;
    DateTime* _currCycleEndDatePtr;
    SpeedCorrector* _speedCorrPtr;
    TriggerFunc _atTopFuncPtr;
    TriggerFunc _atBottomFuncPtr;
    RTC_DS1307* _rtcPtr;
    DateTime* _prevFinDatePtr;
    uint8_t _setPwmPin;
    bool _topMet;
    bool _waitingAtBottom;
    uint8_t _oldPwm;

    void changePwm(uint8_t i);
};

#endif
