/*
 * Author: Harrison Outram and Anton R
 * Date: 08/12/2019
 * Version: 0.1
 * Purpose: Header file for Robot class
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Compiles
 */

#ifndef Robot_h
#define Robot_h

#include "Arduino.h"
#include "../SpeedCorrector/SpeedCorrector.h"
#include "../RTClib/RTClib.h"

#define DOWN_PWM 0
#define BOTTOM_RELEASE_TIME 30

class Robot {
  public:
    /**
     * @param initialEndDate The end date and time of the first cycle
     * @param inSpeedCorr The speed corrector AI used by Robot object
     * @param inAtTopFuncPtr A function pointer for determining if the robot is at the top
     * @param inAtBottomFuncPtr A function pointer for determining if the robot is at the bottom
     * @param inSetPwmPin The pin used to set the robot's PWM
     * @param inRtcPtr Pointer to Real Time Clock (RTC) to keep track of time
     */    
    Robot(DateTime& initialEndDate, SpeedCorrector* inSpeedCorrPtr,
            bool (*inAtTopFuncPtr)(void), bool (*inAtBottomFuncPtr)(void),
            uint8_t inSetPwmPin, RTC_DS1307* inRtcPtr);
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
    TimeSpan* correctTimePtr;
    DateTime* currCycleEndDatePtr;
    SpeedCorrector* speedCorrPtr;
    bool (*atTopFuncPtr)(void);
    bool (*atBottomFuncPtr)(void);
    RTC_DS1307* rtcPtr;
    DateTime* prevFinDatePtr;
    uint8_t setPwmPin;
    bool topMet;
    bool waitingAtBottom;
};

#endif