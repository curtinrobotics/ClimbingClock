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
**Date:** 25/03/2020 (day/month/year, UTC+08:00)<br>
**Program:** PwmCorrector class<br>
**Language:** Arduino C++<br>
**Purpose:** De-couple `Main_program.ino` from robot classes.<br>
**Project:** Climbing Clock<br>
**README Version:** 1.0<br>
**Status:** In progress

## Dependencies

N/A

## Limitations

1. Interface does not know what mechanical nor electronic components the robot classes use.
2. Must be implemented by a robot class that overloads every method.
3. No private, protected, nor static methods.
4. No data members.

## How-To Guide

### Steps

1. Decide on Robot class to use.
2. Ensure the Robot class has a method for each pure virtual method in this interface.
3. Ensure the Robot class inherits this interface.
4. Follow for steps of the Robot class.

### Public Class Constants

N/A

### Typedefs

N/A

### Methods

Note that, as this is an interface, all methods are pure virtual and public.

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

Microsoft tutorial for creating a C++ interface: [__interface](https://docs.microsoft.com/en-us/cpp/cpp/interface?view=vs-2019)

## Misc

Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid classfields when constructing Robot objects.

