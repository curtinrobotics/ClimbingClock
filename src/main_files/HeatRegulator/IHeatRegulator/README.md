# IHeatRegulator

### Table of Contents

**[Project Details](#project-details)**<br>
**[Dependencies](#dependencies)**<br>
**[Limitations](#limitations)**<br>
**[How-To Guide](#how-to-guide)**<br>
**[External Material](#external-material)**<br>
**[Misc](#misc)**<br>

## Project Details

**Author:** Harrison Outram<br>
**Date:** 31/03/2020 (day/month/year, UTC+08:00)<br>
**Program:** IHeatRegulator interface<br>
**Language:** Arduino C++<br>
**Purpose:** De-couple `Main_program.ino` from heat regulator classes.<br>
**Project:** Climbing Clock<br>
**README Version:** 1.2<br>
**Status:** In progress

## Dependencies

N/A

## Limitations

1. Interface does not know what mechanical nor electronic components the heat regulator classes uses.
2. Must be implemented by a heat regulator class that overloads every method.

## How-To Guide

### Steps

1. Decide on which cooling system to use.
2. Write heat regulator class to control the cooling system.
3. Ensure the heat regulator uses the methods in this interface.
4. Follow for steps of the heat regulator class.

### Public Class Constants

N/A

### Typedefs

N/A

### Methods

Note that, as this is an interface, all methods are pure virtual, not static, and public.

**Name:** `start()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the heat regulator initialised correctly or not.<br>
**Purpose:** Initialise the heat regulator's hardware.<br>
**Note:** If the heat regulator cannot detect if it initialised correcly, return `true`.

**Name:** `getTempt()`<br>
**Parameters:** `void`<br>
**Return:** (`int`) The temperature reading in celsuis.<br>
**Purpose:** Find the temperature.<br>
**Note:** Due to the environment, temperatures 0 degrees or less should be interpreted as the sensor malfunctioning.

**Name:** `faultDetected()`<br>
**Paramters:** `void`<br>
**Return:** (`int`) The status.<br>
**Purpose:** Determine if the temperature sensor is working.<br>
**NOte 1:** `0` should mean no fault is detected.<br>
**Note 2:** If it is not possible to detect if the sensor is working, always return `0`.<br>
**Note 3:** If the sensor(s) allow it, different non-zero integers could signify different faults as an enum.

**Name:** `setCooling()`<br>
**Parameters:** `uint8_t power`<br>
**Return:** (`bool`) Whether the cooling is being applied.<br>
**Purpose:** Tell the cooling system to start cooling at a specific power.<br>
**Note 1:** The parameter `power` can be any range of values to prevent unnecessary conversions.<br>
**Note 2:** Should return `false` if the cooling system is malfunctioning.<br>
**Note 3:** If there is no way for the system to detect if the cooling system has malfunctioned return `true`.

**Name:** `temptTopower()`<br>
**Parameters:** `int tempt`<br>
**Return:** `uint8_t power`<br>
**Purpose:** Return the recommended power given the temperature.<br>

**Name:** `stop()`<br>
**Parameters:** `void`<br>
**Return:** `void`<br>
**Purpose:** Emergency stop method in case a fault is detected.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Microsoft tutorial for creating a C++ interface: [__interface](https://docs.microsoft.com/en-us/cpp/cpp/interface?view=vs-2019)

## Misc

N/A
