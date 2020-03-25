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
**Date:** 25/03/2020 (day/month/year, UTC+08:00)<br>
**Program:** IHeatRegulator interface<br>
**Language:** Arduino C++<br>
**Purpose:** De-couple `Main_program.ino` from heat regulator classes.<br>
**Project:** Climbing Clock<br>
**README Version:** 1.0<br>
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
**Return:** `void`<br>
**Purpose:** Initialise the heat regulator's hardware.

**Name:** `getTempt()`<br>
**Parameters:** `void`<br>
**Return:** (`int`) The temperature reading in celsuis.<br>
**Purpose:** Find the temperature.<br>
**Note:** Due to the environment, temperatures 0 degrees or less should be interpreted as the sensor malfunctioning.

**Name:** `setCooling()`<br>
**Parameters:** `uint8_t power`<br>
**Return:** (`bool`) Whether the cooling is being applied.<br>
**Purpose:** Tell the cooling system to start cooling at a specific power.<br>
**Note 1:** The parameter `power` is a percentage from 0% to 100%, hence the datatype. Values above 100 will be interpreted as 100%.<br>
**Note 2:** Should return `false` if the cooling system is malfunctioning.<br>
**Note 3:** If there is no way for the system to detect if the cooling system has malfunctioned return `true`.

**Name:** `temp2power()`<br>
**Parameters:** `int tempt`<br>
**Return:** `uint8_t power`<br>
**Purpose:** Return the recommended power given the temperature.<br>
**Note:** While not necessary, it is recommended that the heat regulator dictate what power to output.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Microsoft tutorial for creating a C++ interface: [__interface](https://docs.microsoft.com/en-us/cpp/cpp/interface?view=vs-2019)

## Misc

N/A
