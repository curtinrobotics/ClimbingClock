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

Note that, as this is an interface, all methods are pure virtual, not static, and public.

**Name:** `start()`<br>
**Parameters:** `void`<br>
**Return:** `void`<br>
**Purpose:** Initialise the robot's hardware.

**Name:** `goUp()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the robot is going up or not.<br>
**Purpose:** Tell the robot to go up.<br>
**Note:** `false` should be returned based on the Robot class' documentation.

**Name:** `goDown()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the robot is going down or not.<br>
**Purpose:** Tell the robot to go down.<br>
**Note:** `false` should be returned based on the Robot class' documentation.

**Name:** `atTop()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the robot is at the top or not.<br>
**Purpose:** Check if the robot is at the top or not.
**Note:** If the robot climbs too fast, meaning it should be waiting at the bottom for the current cycle to end, this should return `false`.

**Name:** `atBottom()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the robot is at the bottom or not.<br>
**Purpose:** Check if the robot is at the bottom or not.

**Name:** `cycleDone()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the current cycle is done or not.<br>
**Purpose:** Check if enough time has passed for the current cycle to end.<br>
**Note:** If the robot is too slow, `cycleDone()` will eventually start returning `true` before `atTop()`.

**Name:** `stop()`<br>
**Parameters:** `void`<br>
**Return:** `void`<br>
**Purpose:** Emergency stop method to tell robot to go down to the bottom and do nothing.<br>
**Note:** Should be used if a fault is detected and someone needs to manually investigate.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Microsoft tutorial for creating a C++ interface: [__interface](https://docs.microsoft.com/en-us/cpp/cpp/interface?view=vs-2019)

## Misc

N/A
