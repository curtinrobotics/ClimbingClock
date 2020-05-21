# PWM Corrector

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
**Program:** PwmCorrector class<br>
**Language:** Arduino C++<br>
**Purpose:** Corrects robot PWM to ensure robot climbs at the correct speed<br>
**Project:** Climbing Clock<br>
**README Version:** 2.0<br>
**Status:** In progress

## Dependencies

N/A

## Limitations

1. Does not understand what sensors or actuators are used.
2. Requires additional code outside of this class to get sensor data.
3. Requires additional code outside of this class to command actuators.
4. Can not control PWM frequency.
5. PWMs must be 8 bit unsigned integers.

## How-To Guide

Use this section to learn how to use this library regardless of how it works.

To learn how this library works, read the source code.

### Steps

1. Decide on initial PWM (rough estimates of correct PWMs are fine).
2. Decide on how the PWM speedIncrement should be changed.
3. Construct PwmCorrector object.
4. Use PwmCorrector to construct Robot object.
5. To start the Robot, use the `getCurrentPwm()` method.
6. Whenever the Robot finished a cycle, call the `getCorrectedPwm()` method.
7. Insert the corrected PWM via `addNewCorrectedPwm()`.
8. When starting a new cycle, use `getCurrentPwm()` to set the Robot's PWM.
9. Repeat steps 6-8.

Steps 1-5 should be done in the `setup()` function. Steps 6-9 should be done in the `loop()` function.

### Public Class Constants

**Name:** `MAX_NUM_OF_PWMS`<br>
**Value:** `10 (uint8_t)`<br>
**Purpose:** Default size for correctedPwms array.
**Note:** Higher values can result in greater accuracy long-term but requires more dynamic memory and takes longer to correct PWM.

**Name:** `SPEED_INCREMENT`<br>
**Value:** `10 (uint8_t)`<br>
**Purpose:** Default value to increase speed by when robot is too slow.

**Name:** `MIN_SPEED_INCREMENT`<br>
**Value:** `1 (uint8_t)`<br>
**Purpose:** Default minimum speed increment.

**Name:** `SPEED_INCREMENT_CHANGE`<br>
**Value:** `3 (uint8_t)`<br>
**Purpose:** Default value for how exactly the speed increment will change.<br>
**Note:** Higher values makes the robot get to the correct PWM faster but can overshoot.

### Typedefs

**Name:** `SpeedChangeFunc`<br>
**Definition:** `uint8_t (*SpeedChangeFunc)(uint8_t, uint8_t)`<br>
**Purpose:** How to change the speed increment when the robot is too slow.<br>
**Note:** Should always return a new speed increment that is <= current speed increment

### Constructors and Destructor

**Name:** Alternate 1<br>
**Parameters:** `initialPwm (uint16_t), CorrectTime (uint32_t), speedChangeFunc (SpeedChangeFunc)`<br>
**Note 1:** assigns initialPwm as the 0th element in the storage of corrected PWMs.<br>
**Note 2:** the max PWM index (and the array size by extension) is assigned the `MAX_PWM_INDEX` public class constant.

**Name:** Alternate 2<br>
**Parameters:** `initialPwm (uint16_t), correctTime (uint32_t), maxPwmIndex (uint8_t), speedIncrement (int8_t), minSpeedIncrement (uint8_t), speedChangeFunc (SpeedChangeFunc), speedIncrementChange (uint8_t)`<br>
**Note 1:** assigns `initialPwm` as the 0th element in the storage of corrected PWMs.<br>
**Note 2:** Strongly recommended to keep `speedIncrement` value small to avoid overcorrection.<br>
**Note 3:** Despite signed integer datatype for `speedIncrement`, do **not** assign a negative number! This signed integer datatype prevents a run-time error.<br>
**Note 4:** Do **not** assign a value of 0 to `minSpeedIncrement`.<br>
**Note 5:** It is strongly recommended that a small value (e.g. single digit) be chosed for `speedIncrementChange`.

**Name:** Destructor<br>
**Parameters:** N/A

### Public Methods

**Name:** `getCorrectedPwm()`<br>
**Parameters:** `actualTime (uint32_t), topReached (bool)`<br>
**Return:** `correctedPwm (uint8_t)`<br>
**Purpose:** Calculate correct PWM based on current PWM, time taken and error.

**Name:** `addNewCorrectedPwm()`<br>
**Parameters:** `correctedPwm (uint8_t)`<br>
**Return:** N/A<br>
**Purpose:** Adds corrected PWM to internal storage.<br>
**Note:** Will replace oldest values when storage is full.

**Name:** `getCurrentPwm()`<br>
**Parameters:** N/A<br>
**Return:** `uint8_t`<br>
**Purpose:** Return current PWM.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Tutorial for learning [PWM](https://www.arduino.cc/en/Tutorial/PWM)

## Misc

Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid classfields when constructing Robot objects.

