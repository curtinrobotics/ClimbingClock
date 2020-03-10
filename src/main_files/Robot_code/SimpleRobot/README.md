# Simple Robot README

## Project Details

**Author:** Harrison Outram
**Date:** 25/01/2020 (day/month/year, UTC+08:00)
**Program:** SimpleRobot class
**Language:** Arduino C++
**Purpose:** Create Robot objects to keep track of robot's status and
            tell robot to do required tasks
**Project:** Climbing Clock (2019-20)
**README Version:** 0.3
**Status:** In progress

## Dependencies

Name: RTClib.h
Purpose: library for using real time clocks on Arduinos easily
Availability: Public, can install through Arduino IDE

Name: SpeedCorrector.h
Purpose: Machine Learning AI that corrects robot's PWM over time
Availability: Private, see project Github repo

## Limitations

1. Can only change speed of motor, not the direction
2. Only checks if at top or bottom or neither; cannot tell how far up
3. Robot goes down as fast as possible when commanded; it does not slow down to prevent damage
   
   * Assumes something at the bottom will soften the impact, e.g. pillow

## How-To Guide

Use this section to learn how to use this library regardless of how it works.

To learn how this library works, read the source code.

### Steps

1. Ensure RTC is plugged in and working
2. Choose pin for controlling motor PWM
3. Determine correct position of robot given the time it will be turned on
4. Construct `SpeedCorrector` and `RTC_DS1307` objects on the heap (either global variable or through `new` keyword)
5. Determine the end date/time of the first cycle and store it in a DateTime object
6. Run `start()` method to make the robot start moving
7. Constantly check if the robot has reached the top or run out of time via `cycleDone()` method
8. If at current cycle complete, prepare object variables via `prepareNextCycle()` method *first* then command robot to go down via `goDown()`
9. If going down, constantly check if at the bottom via `atBottom()`
10. If at the bottom, call `attemptToGoUp()` method
11. Repeat steps 6-10

### Public Constants

Name: BOTTOM\_RELEASE\_TIME
Value: 30
Purpose: Seconds to ignore `atBottom()` trigger when ascending
Note: See `atBottom()` public method

Name: DOWN\_PWM
Value: 0
Purpose: Used for making robot go down ladder
Note: see `goDown()` public function

### Constructors and Destructors

Name: Alternate 1

Parameters: initialEndDate (DateTime&), inSpeedCorrPtr (SpeedCorrector\*), inAtTopFuncPtr (bool (\*)(void)), inAtBottomFuncPtr (bool (\*)(void)), inSetPwmPin (uint8\_t), inRtcPtr (RTC\_DS1307\*)

Note 1: Make sure the SpeedCorrector object is put on the heap, as the contructor does **not** create a copy for performance.

Note 2: The PWM pin will be set to output mode via analogWrite(setPwmPin, OUTPUT).

Note 3: Make sure the RTC object is put on the heap, as the contructor does **not** create a copy for performance.

Note 4: RTC is **not** initialised in the constructor!



Name: Destructor

Parameters: N/A

				--------------
				PUBLIC METHODS
				--------------
Name: `start()`

Parameters: N/A

Return: N/A

Purpose: Tell the robot to start moving up

Note: Only use for initial cycle! Do **not** use elsewhere!
                

Name: `cycleDone()`

Parameters: N/A

Return: bool

Purpose: Checks if the robot has completed the current cycle


Name: `prepareNextCycle()`

Parameters: N/A

Return: N/A

Purpose: Updates object variables for next cycle

Note: Does **not** tell robot to move!


Name: `goDown()`

Parameters: N/A

Return: N/A

Purpose: Tells robot to go down.

Note: Uses DOWN\_PWM constant (see above).


Name: `attemptToGoUp()`

Parameters: N/A

Return: bool

Purpose: Tells robot to go up.

Note 1: will only go up if the current time is on or after the current cycle's
        end time.
Note 2: Return value tells caller if robot is going up or not.

Name: `atBottom()`

Parameters: N/A

Return: bool

Purpose: Checks if robot is at bottom of ladder.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Tutorial for learning PWM: [PWM](https://www.arduino.cc/en/Tutorial/PWM)

Tutorial for setting PWM: [Analog Write](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/)


## Misc

Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid classfields when constructing Robot objects.
