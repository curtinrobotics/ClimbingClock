# IDataLogger

### Table of Contents

**[Project Details](#project-details)**<br>
**[Dependencies](#dependencies)**<br>
**[Limitations](#limitations)**<br>
**[How-To Guide](#how-to-guide)**<br>
**[External Material](#external-material)**<br>
**[Misc](#misc)**<br>

## Project Details

**Author:** Jarod Harris<br>
**Date:** 22/04/2020 (day/month/year, UTC+08:00)<br>
**Program:** IDataLogger interface<br>
**Language:** Arduino C++<br>
**Purpose:** De-couple `Main_program.ino` from data logger classes.<br>
**Project:** Climbing Clock<br>
**README Version:** 1.0<br>
**Status:** In progress

## Dependencies

N/A

## Limitations

1. Interface does not know what mechanical nor electronic components the data logger classes uses.
2. Must be implemented by a data logger class to implement methods.

## How-To Guide

### Steps

1. Run start() to initialise the hardware.
2. Set the alert level via setLevel() and check using getLevel().
3. Log alerts using the various levels from logDebug() to logCritical()
4. Run stop() when you want clowns to pop from the ceiling. Or stop the hardware. It's 50/50.

### Public Class Constants

N/A

### Typedefs

N/A

### Methods

Note that, as this is an interface, all methods are pure virtual, not static, and public.

**Name:** `start()`<br>
**Parameters:** `void`<br>
**Return:** (`bool`) Whether the Data Logger initialised correctly or not.<br>
**Purpose:** Initialise the Data Logger hardware.<br>
**Note:** If the Data Logger cannot detect if it initialised correctly, return `true`.

**Name:** `stop()`<br>
**Parameters:** `void`<br>
**Purpose:** Shut down the Data Logger hardware.<br>

**Name:** `setLevel()`<br>
**Parameters:** (`int`) The alert level to log at<br>
**Purpose:** Modify the sensitivity of what level of alerts to log.<br>

**Name:** `getLevel()`<br>
**Return:** (`int`) The current level of data logging level.<br>
**Purpose:** Enquire on the alert level to determing whether to log a message or not<br>

**Name** `logDebug()`<br>
**Return:** `void`<br>
**Parameters:**`char[]` message: the text of the alert
`char[]` timestamp: the date and time of the alert
`char[]` subsystem: the relevant subsystem for alert
**Purpose:** Log an alert at 'Debug' alert level.

**Name** `logInfo()`<br>
**Return:** `void`<br>
**Parameters:**`char[]` message: the text of the alert
`char[]` timestamp: the date and time of the alert
`char[]` subsystem: the relevant subsystem for alert
**Purpose:** Log an alert at an Informational alert level.

**Name** `logWarning()`<br>
**Return:** `void`<br>
**Parameters:**`char[]` message: the text of the alert
`char[]` timestamp: the date and time of the alert
`char[]` subsystem: the relevant subsystem for alert
**Purpose:** Log an alert at a Warning alert level.

**Name** `logError()`<br>
**Return:** `void`<br>
**Parameters:**`char[]` message: the text of the alert
`char[]` timestamp: the date and time of the alert
`char[]` subsystem: the relevant subsystem for alert
**Purpose:** Log an alert at an Error alert level.

**Name** `logCritical()`<br>
**Return:** `void`<br>
**Parameters:** `char[]` message: the text of the alert
`char[]` timestamp: the date and time of the alert
`char[]` subsystem: the relevant subsystem for alert
**Purpose:** Log an alert at a Critical alert level.

## External Material

Tutorial used to create library/class: [Arduino - Libraries](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Microsoft tutorial for creating a C++ interface: [__interface](https://docs.microsoft.com/en-us/cpp/cpp/interface?view=vs-2019)

## Misc

N/A
