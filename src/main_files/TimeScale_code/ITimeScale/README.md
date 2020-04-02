# ITimeScale

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
**Program:** ITimeScale interface<br>
**Language:** Arduino C++<br>
**Purpose:** De-couple `Main_program.ino` from time scale classes.<br>
**Project:** Climbing Clock<br>
**README Version:** 1.1<br>
**Status:** In progress

## Dependencies

N/A

## Limitations

1. Interface does not know what mechanical nor electronic components the time scale classes use.
2. Must be implemented by a time scale class that overloads every method.

## How-To Guide

### Steps

1. Decide on Time Scale design.
2. Write a TimeScale class to control the time scale subsystem.
3. Ensure the TimeScale class implements this interface.
4. Follow for steps of the TimeScale class.

### Public Class Constants

N/A

### Typedefs

N/A

### Methods

Note that, as this is an interface, all methods are pure virtual, not static, and public.

**Name:** `start()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the time scale initialised correctly or not.<br>
**Purpose:** Initialise the time scale's hardware.<br>
**Note:** If the time scale cannot detect if it initialised correctly, always return `true`.

**Name:** `setTime()`<br>
**Parameters:** `uint8_t hours, uint8_t minutes, uint8_t seconds`<br>
**Return:** (`bool`) Whether the time was set successfully or not.<br>
**Purpose:** Set the time on the time scale.<br>
**Note 1:** `false` should be returned if the time scale malfunctions.<br>
**Note 2:** If the time scale cannot detect if a malfunction has occured then always return `true`.

**Name:** `faultDetected()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether a fault was detected or not.<br>
**Purpose:** Detect if a fault has occured.<br>
**Note:** If the time scale cannot detect if a fault has occured, always return `false`.

**Name:** `stop()`<br>
**Parameters:** `void`<br>
**Return:** `void`<br>
**Purpose:** Emergency stop method to tell time scale to turn off all electronics.<br>
**Note:** Should be used if a fault is detected and someone needs to manually investigate.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Microsoft tutorial for creating a C++ interface: [__interface](https://docs.microsoft.com/en-us/cpp/cpp/interface?view=vs-2019)

## Misc

N/A
