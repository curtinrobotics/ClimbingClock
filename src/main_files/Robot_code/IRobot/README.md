# IRobot

### Table of Contents

**[Project Details](#project-details)**<br>
**[Dependencies](#dependencies)**<br>
**[Limitations](#limitations)**<br>
**[How-To Guide](#how-to-guide)**<br>
**[External Material](#external-material)**<br>
**[Misc](#misc)**<br>

## Project Details

**Author:** Harrison Outram<br>
**Date:** 26/03/2020 (day/month/year, UTC+08:00)<br>
**Program:** IRobot interface<br>
**Language:** Arduino C++<br>
**Purpose:** De-couple `Main_program.ino` from robot classes.<br>
**Project:** Climbing Clock<br>
**README Version:** 1.1<br>
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
**Return:** (`bool`) Whether the robot initialised correctly or not.<br>
**Purpose:** Initialise the robot's hardware.<br>
**Note:** If the robot cannot detect if it initialised correctly, return `true`.

**Name:** `goUp()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the robot is going up or not.<br>
**Purpose:** Tell the robot to go up.<br>
**Note 1:** `false` should be returned if the robot cannot or will not go up.<br>
**Note 2:** If the robot never decides to not go up and it cannot tell if it malfunctions, always return `true`.

**Name:** `goDown()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the robot is going down or not.<br>
**Purpose:** Tell the robot to go down.<br>
**Note 1:** `false` should be returned if the robot cannot or will not go down.<br>
**Note 2:** If the robot never decides to not go down and it cannot tell if it malfunctions, always return `true`.

**Name:** `getPosition()`<br>
**Parameters:** `void`<br>
**Return:** (`int`) How far up the robot has climbed.<br>
**Purpose:** To detect how far the robot has climbed up.<br>
**Note 1:** Each robot class implementing this interface should have a constant of the expected return value when the robot is at the top. E.g. `#define TOP_POS 100`.<br>
**Note 2:** This method should return `0` if the robot is at the bottom.<br>
**Note 3:** If the robot does not know its position, return a negative number. If the sensors allow it, different negative numbers could signify different malfunctions. E.g. `enum Positions {UNKNOWN = -1, ERRACTIC = -2, DEAD = -3};`.

**Name:** `cycleDone()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the current cycle is done or not.<br>
**Purpose:** Check if enough time has passed for the current cycle to end.<br>
**Note:** If the robot is too slow, `cycleDone()` should eventually start returning `true` before `atTop()` and vice versa.

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
