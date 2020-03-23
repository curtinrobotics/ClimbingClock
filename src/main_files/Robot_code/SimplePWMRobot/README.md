# Simple PWM Robot

### Table of Contents

**[Project Details](#project-details)**<br>
**[Dependencies](#dependencies)**<br>
**[Limitations](#limitations)**<br>
**[How-To Guide](#how-to-guide)**<br>
**[External Material](#external-material)**<br>
**[Misc](#misc)**<br>

## Project Details

**Author:** Harrison Outram<br>
**Date:** 23/03/2020 (day/month/year, UTC+08:00)<br>
**Program:** SimpleRobot class<br>
**Language:** Arduino C++<br>
**Purpose:** Create Robot objects to keep track of robot's status and tell robot to do required tasks<br>
**Project:** Climbing Clock (2019-20)<br>
**README Version:** 1.0<br>
**Status:** In progress

## Dependencies

**Name:** `RTClib.h`<br>
**Purpose:** library for using real time clocks on Arduinos easily.<br>
**Availability:** Public, can install through Arduino IDE.

**Name:** `PwmCorrector.h`<br>
**Purpose:** Machine Learning AI that corrects robot's PWM over time.<br>
**Availability:** Private, see project Github repo.

## Limitations

1. Can only change speed of motor, not the direction
2. Only checks if at top or bottom or neither; cannot tell how far up
3. Does not disconnect motor when going down.

   * Will wear out motor faster

4. Robot goes down as fast as possible when commanded; it does not slow down to prevent damage
   
   * Assumes something at the bottom will soften the impact, e.g. pillows, bag of jelly

## How-To Guide

Use this section to learn how to use this library regardless of how it works.

To learn how this library works, read the source code.

### Steps

1. Ensure RTC is plugged in and working
2. Choose pin for controlling motor PWM
3. Determine correct position of robot given the time it will be turned on
4. Construct `PwmCorrector` and `RTC_DS1307` objects on the heap (either global variable or through `new` keyword)
5. Wait until next cycle starts (e.g. midday or when minutes = seconds = 0)
6. Run `start()` method to make the robot start moving
7. Constantly check if the robot has reached the top or run out of time via `cycleDone()` method
8. If at current cycle complete, command robot to go down via `goDown()`
9. If going down, constantly check if at the bottom via `atBottom()`
10. If at the bottom, call `goUp()` method
11. Repeat steps 7-10

Steps 4-6 should be done in the `setup()` function whereas steps 7-11 should be performed in the `loop()` function.

### Public Constants

**Name:** `BOTTOM\_RELEASE\_TIME`<br>
**Value:** 30<br>
**Purpose:** Seconds to ignore `atBottom()` trigger when starting to ascend from the bottom.<br>
**Note:** See `atBottom()` public method

**Name:** `DOWN\_PWM`<br>
**Value:** 0<br>
**Purpose:** Used for making robot go down ladder.<br>
**Note:** see `goDown()` public function

**Name:** `PWM\_CHANGE\_DELAY`<br>
**Value:** 1<br>
**Purpose:** Used for slowing down the change of PWM to prevent motor damage<br>
**Note 1:** Expressed in milliseconds.<br>
**Note 2:** Lower values result in faster speed changes but can wear out motor faster.<br>

### Typedefs

**Name:** `TriggerFunc`<br>
**Definition:** `bool (\*TriggerFunc)(void)`<br>
**Purpose:** Determining if the robot has reached the top or bottom.

### Constructors and Destructors

**Name:** Alternate 1<br>
**Parameters:** `pwmCorr (PwmCorrector&), inAtTopFuncPtr (TriggerFunc), inAtBottomFuncPtr (TriggerFunc), inSetPwmPin (uint8\_t), rtc (RTC\_DS1307&)`<br>
**Note 1:** Make sure the SpeedCorrector object is put on the heap, as the contructor does **not** create a copy for performance.<br>
**Note 2:** The PWM pin will be set to output mode via analogWrite(setPwmPin, OUTPUT).<br>
**Note 3:** Make sure the RTC object is put on the heap, as the contructor does **not** create a copy for performance.<br>
**Note 4:** RTC is **not** initialised in the constructor!

**Name:** Destructor<br>
**Parameters:** N/A

### Public Methods

**Name:** `start()`<br>
**Parameters:** void<br>
**Return:** void<br>
**Purpose:** Tell the robot to start moving up.<br>
**Note:** Only use for initial cycle! Do **not** use elsewhere!

**Name:** `cycleDone()`<br>
**Parameters:** void<br>
**Return:** (bool) Whether the cycle is done or not<br>
**Purpose:** Checks if the robot has completed the current cycle.

**Name:** `goDown()`<br>
**Parameters:** void<br>
**Return:** (bool) whether the robot is going down or not<br>
**Purpose:** Tells robot to go down.<br>
**Note:** Uses DOWN\_PWM constant (see above).

**Name:** `goUp()`<br>
**Parameters:** void<br>
**Return:** (bool) Whether the robot is going up or not.<br>
**Purpose:** Tells robot to go up.<br>
**Note:** will only go up if the current time is on or after the current cycle's end time.<br>

**Name:** `atBottom()`<br>
**Parameters:** N/A<br>
**Return:** bool<br>
**Purpose:** Checks if robot is at bottom of ladder.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Tutorial for learning [PWM](https://www.arduino.cc/en/Tutorial/PWM)

Tutorial for setting the motor's PWM: [Analog Write](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/)

## Misc

Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid classfields when constructing Robot objects.
