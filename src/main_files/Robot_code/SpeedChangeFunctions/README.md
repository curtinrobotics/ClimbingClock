# Speed Change Functions

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
**Purpose:** Provide functions for changing PwmCorrector speed increment.<br>
**Project:** Climbing Clock<br>
**README Version:** 2.0<br>
**Status:** Done

## Dependencies

N/A

## Limitations

1. Does **not** store any data long term.
2. Only tells what next speed increment should be given current speed increment.
3. Functions do **not** allow for minimum speed increments to be returned.

## How-To Guide

### Steps

1. Choose a function based on desired rate of change of speed increment.
2. Decide on a speed increment change.
3. Every time a new speed increment is required, call function.

### Functions

**Name:** `noChange()`<br>
**Parameters:** `currSpeedInc (uint8_t), speedIncChange (uint8_t)`<br>
**Return:** `newSpeedInc (uint8_t)`<br>
**Equation:** newSpeedInc = currSpeedInc

**Name:** `linearChange()`<br>
**Parameters:** `currSpeedInc (uint8_t), speedIncChange (uint8_t)`<br>
**Return:** `newSpeedInc (uint8_t)`<br>
**Equation:** newSpeedInc = initialSpeedInc - floor(time / correctTime) * speedIncChange

**Name:** `exponentialChange()`<br>
**Parameters:** `currSpeedInc (uint8_t), speedIncChange (uint8_t)`<br>
**Return:** `newSpeedInc (uint8_t)`<br>
**Equation:** speedInc = initialSpeedInc * (1 / speedIncChange) ^ floor(time / correctTime)

## External Material

Tutorial used to create library: https://www.arduino.cc/en/Hacking/LibraryTutorial

## Misc

Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for errors
