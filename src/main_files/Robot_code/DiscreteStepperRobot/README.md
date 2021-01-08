# Discrete Stepper Robot

### Table of Contents

**[Project Details](#project-details)**<br>
**[Dependencies](#dependencies)**<br>
**[Limitations](#limitations)**<br>
**[How-To Guide](#how-to-guide)**<br>
**[External Material](#external-material)**<br>
**[Misc](#misc)**<br>

## Project Details

**Author:** Harrison Outram<br>
**Date:** 24/09/2020 (day/month/year, UTC+08:00)<br>
**Program:** DiscreteStepperRobot class<br>
**Language:** Arduino C++<br>
**Purpose:** Create Robot objects to keep track of robot's status and tell robot to do required tasks<br>
**Project:** Climbing Clock (2019-20)<br>
**README Version:** 1.0<br>
**Status:** In progress

## Dependencies

**Name:** `RTClib.h`<br>
**Purpose:** library for using real time clocks on Arduinos easily.<br>
**Availability:** Public, can install through Arduino IDE.

**Name:** `StepCorrector.h`<br>
**Purpose:** library for correcting the steps required per discrete movement.<br>
**Availability:** Private, see project Github repo.

## Limitations

1. Requires a stepper motor.
2. Must know the gearbox ratio.
3. Must know the steps per revolution of the stepper motor.
4. Requires worm gear to prevent robot falling down while ascending.
4. Does not disconnect motor when going down.

   * Will wear out motor faster

5. Will go down as fast as the stepper motor will allow.
   
   * Assumes something at the bottom will soften the impact, e.g. pillows, bag of jelly

## How-To Guide

Use this section to learn how to use this library regardless of how it works.

To learn how this library works, read the source code.

### Steps

1. Ensure RTC is plugged in and working
2. Choose pins for controlling stepper motor.
3. Construct `StepCorrector` and `RTC_DS1307` objects (either global variable or through `new` keyword)
4. Wait until next cycle starts (e.g. midday, midnight, or when minutes = seconds = 0)
5. Run `start()` method to turn the robot on.
6. Constantly run `goUp()` to get the robot to check if it needs to go up, and do so if necessary.
7. Constantly check if the robot has reached the top or run out of time via `cycleDone()` method.
8. If at current cycle complete, command robot to go down via `goDown()`.
9. If going down, constantly check if at the bottom via `atBottom()`.
10. If at the bottom, call `goUp()` method.
11. Repeat steps 6-10.

Steps 3-5 should be done in the `setup()` function whereas steps 6-10 should be performed in the `loop()` function.

### Public Constants

**Name:** `BOTTOM_RELEASE_TIME`<br>
**Value:** 30<br>
**Purpose:** Seconds to ignore `atBottom()` trigger when starting to ascend from the bottom.<br>
**Note:** See `atBottom()` public method

**Name:** `DOWN_PWM`<br>
**Value:** 0<br>
**Purpose:** Used for making robot go down ladder.<br>
**Note:** see `goDown()` public function

**Name:** `PWM_CHANGE_DELAY`<br>
**Value:** 1<br>
**Purpose:** Used for slowing down the change of PWM to prevent motor damage<br>
**Note 1:** Expressed in milliseconds.<br>
**Note 2:** Lower values result in faster speed changes but can wear out motor faster.<br>

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

## Misc

Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid data members when constructing Robot objects.
