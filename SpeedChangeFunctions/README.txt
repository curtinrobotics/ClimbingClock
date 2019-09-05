#################################################################
AUTHOR: Harrison Outram
DATE: 5/09/2019 (day/month/year)
PROGRAM: SpeedChangeFunctions library
LANGuaGE: C++ (Using the Arduino IDE)
PURPOSE: Provide SpeedCorrector class with generic equations for
		changing speed increment
project: Climbing Clock (2019)
version: 1.1
#################################################################

				---------------------
				PUBLIC STATIC METHODS
				---------------------
Name: noChange
Imports: currSpeedInc (uint8_t), speedIncChange (uint8_t)
Export: newSpeedInc (uint8_t)
Equation: newSpeedInc = currSpeedInc

Name: linearChange
Imports: currSpeedInc (uint8_t), speedIncChange (uint8_t)
Export: newSpeedInc (uint8_t)
Equation: newSpeedInc = initialSpeedInc - floor(time / correctTime) * speedIncChange

Name: exponentialChange
Imports: currSpeedInc (uint8_t), speedIncChange (uint8_t)
Export: newSpeedInc (uint8_t)
Equation: speedInc = initialSpeedInc * (1 / speedIncChange) ^ floor(time / correctTime)

				-----------------
				EXTERNAL MATERIAL
				-----------------
Tutorial used to create library/class: https://www.arduino.cc/en/Hacking/LibraryTutorial

				----
				MISC
				----
Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for errors
