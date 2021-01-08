# Step Corrector

### Table of Contents

**[Project Details](#project-details)**<br>
**[Dependencies](#dependencies)**<br>
**[Limitations](#limitations)**<br>
**[How-To Guide](#how-to-guide)**<br>
**[External Material](#external-material)**<br>
**[Misc](#misc)**<br>

## Project Details

**Author:** Harrison Outram<br>
**Program:** StepCorrector class<br>
**Language:** Arduino C++<br>
**Purpose:** Corrects stepper motor's delay between steps to ensure robot climbs at the correct speed<br>
**Project:** Climbing Clock<br>
**README Version:** 2.0<br>
**Status:** Tested and working

## Dependencies

N/A

## Limitations

1. Does not understand what sensors or actuators are used.
2. Requires additional code outside of this class to get sensor data.
3. Requires additional code outside of this class to command actuators.
4. Can not control delay directly; only keeps track of correct delay.
5. Step time must be uint32_t.

## How-To Guide

Use this section to learn how to use this library regardless of how it works.

To learn how this library works, read the source code.

### Steps

1. Decide on initial delay (use analytical calculations of gearbox ratio and distance travelled).
2. Decide on how the delay increment should be changed.
3. Construct StepCorrector object.
4. Use StepCorrector to construct Robot object.
5. To start the Robot, use the `getCurrentStep()` method.
6. Whenever the Robot finishes a cycle, call the `getCorrectedStep()` method.
7. Insert the corrected delay via `addNewCorrectedStep()`.
8. When starting a new cycle, use `getCurrentStep()` to set the stepper motor's delay.
9. Repeat steps 6-8.

Steps 1-5 should be done in the `setup()` function. Steps 6-9 should be done in the `loop()` function.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

## Misc

Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid data members when constructing Robot objects.

