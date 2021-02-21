/*
 * @authors Harrison Outram
 * Last Updated: ??/??/2020
 * @brief Header file for DiscreteStepperRobot class
 * <p>The DiscreteStepperRobot class requires the robot to use sensors that can tell if the
 * robot is at the bottom or top.</p>
 * Project: Climbing Clock (2019-20)
 * Organisation: Curtin Robotics Club (CRoC)
 * Status: in progress
 */

#ifndef DiscreteStepperRobot_h
#define DiscreteStepperRobot_h

#include "Arduino.h"
#include "../IRobot/IRobot.h"
#include "../RTClib/RTClib.h"
#include "../StepCorrector/StepCorrector.h"

#define BOTTOM_RELEASE_TIME 5
#define TOP_POS 1

enum Direction {UP, DOWN, AT_TOP, AT_BOTTOM, STILL};

/** Used for detecting if robot has reached top or bottom */
typedef bool (*TriggerFunc)(void);

template<class RTC>
class DiscreteStepperRobot : public IRobot {
  public:
    /**
     * @param stepCorr The step corrector AI used by Robot object
     * @param atTopFuncPtr A function pointer for determining if the robot is at the top
     * @param atBottomFuncPtr A function pointer for determining if the robot is at the bottom
     * @param stepPin The pin used to make the stepper motor rotate, must be a PWM pin
     * @param dirPin The pin for setting the direction of the motor
     * @param upDir The digital output setting for going up
     * @param rtc Real Time Clock (RTC) to keep track of time
     */
    DiscreteStepperRobot(StepCorrector& stepCorr,
            TriggerFunc atTopFuncPtr, TriggerFunc atBottomFuncPtr,
            uint8_t stepPin, uint8_t dirPin, uint8_t upDir, RTC& rtc);
    
    ~DiscreteStepperRobot();

    /**
     * @brief Initialises robot's hardware
     *      Should be used for initial cycle only!
     * @return void
     */
    void start(void);

    /**
     * @brief Check how far the robot has climbed
     * @return 0 if at the bottom, TOP_POS if at the top, or -1 if unknown
     * @warning Will return -1 if not at the top nor the bottom
     */
    int getPosition(void);

    /**
     * @brief Checks which direction the robot is moving
     * @return An integer from the Direction enum
     */
    int getDirection(void);

    /**
     * @brief Checks if the robot has finished the current cycle
     *        Checks both if at top and if enough time has passed
     * @return bool
     */
    bool cycleDone(void);

    /**
     * @brief Makes robot go down ladder
     * @warning Does <b>not</b> prevent robot from stopping at bottom!
     * @return Whether the robot has started going down or not
     */
    bool goDown(void);

    /**
     * @brief Will go up if enough time has passed
     * @return bool representing if robot is going up
     */
    bool goUp(void);

    /**
     * @brief checks if enough time has passed to start going up
     *      Does not tell robot to go up even if enough time has passed
     * @see goUp()
     * @return Whether the robot should go up
     */
    bool mustGoUp(void);

    /**
     * Check if at bottom of ladder
     * @return bool
     */
    bool atBottom(void);

    /**
     * @brief Checks if a fault has occured
     * @return An int from the Faults enum
     */
    int faultDetected(void);

  protected:
    //object variables
    DateTime* _currCycleEndDatePtr;
    StepCorrector* _stepCorrPtr;
    TriggerFunc _atTopFuncPtr;
    TriggerFunc _atBottomFuncPtr;
    RTC* _rtcPtr;
    DateTime* _prevFinDatePtr;
    uint8_t _stepPin, _dirPin, _upDir;
    bool _topMet;
    bool _waitingAtBottom;
    bool _goingUp, _goingDown;
    uint8_t _oldStep;
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
