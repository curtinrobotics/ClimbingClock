#################################################################
AUTHOR: Harrison Outram
DATE: 8/07/2019 (day/month/year)
PROGRAM: ClimbingClockSpeedCorrector library/class
LANGuaGE: C++ (Using the Arduino IDE)
PURPOSE: Provide functionality for a Machine Learning (ML) AI to
			auto-correct robot climbing speed
project: Climbing Clock (2019)
version: 0.3
#################################################################

				----------------------
				PUBLIC CLASS CONSTANTS
				----------------------
Name: MAX_PWM_INDEX
Value: 10 (uint8_t)
Purpose: default index for the last element of the correctedPwms array

Name: SPEED_INCREASE_INCREMENT
Value: 10 (uint8_t)
Purpose: default value for speedIncreaseIncrement classfield

				-----------
				CLASSFIELDS
				-----------
Name: pwmIndex
Datatype: uint8_t
Mutable: No
Purpose: keeps track of the index of the last corrected PWM added

Name: maxPwmIndex
Datatype: uint8_t
Mutable: No
Purpose: the index of the last element of the correctedPwms array

Name: correctedPwms
Datatype: uint16_t[] pointer
Mutable: Limited (see addNewCorrectedPwm method below)
Purpose: records the latest corrected PWMs
Note: Defined as a pointer to allow for array size to be specified upon object construction

Name: correctedPwmsFull
Datatype: boolean
Mutable: No
Purpose: keeps track of whether the correctedPwms array is full or not

Name: correctTime
Datatype: uint32_t
Mutable: No
Purpose: keeps track of the correct time it should take for the robot
			to reach the top.
Note: can use any unit of time desired, as long as it's a positive integer

Name: speedIncreaseIncrement
Datatype: uint8_t
Mutable: No
Purpose: Amount PWM is increased by if robot does not reach top in time.
Note 1: Small values will take longer to get to correct speed,
			but larger value are likely to overcorrect.
Note 2: Strongly recommended to keep this value small.

				---------------------------
				CONSTRUCTORS AND DESTRUCTOR
				---------------------------
Name: Alternate 1
Imports: initialPwm (uint16_t), inCorrectTime (uint32_t)
Note 1: assigns initialPwm as the 0th element in the correctedPwms array
Note 2: the max PWM index (and the array size by extension) is assigned the
			MAX_PWM_INDEX public class constant.

Name: Alternate 2
Imports: initialPwm (uint16_t), inCorrectTime (uint32_t), inMaxPwmIndex (uint8_t),
			inSpeedIncreaseIncrement (uint8_t)
Note 1: assigns initialPwm as the 0th element in the correctedPwms array
Note 2: Strongly recommended to keep inSpeedIncreaseIncrement value small to avoid overcorrection.

Name: Destructor
Imports: N/A

				--------------
				PUBLIC METHODS
				--------------
Name: getCorrectedPwm
Imports: actualTime (uint32_t), currentPwm (uint16_t), topReached (bool)
Export: correctedPwm (uint16_t)
Purpose: calculate correct PWM based on current PWM, time taken and error

Name: addNewCorrectedPwm
Import: correctedPwm (uint16_t)
Export: N/A
Purpose: Adds import to correctedPwms array.
Note: If the correctedPwms array is full, oldest value is replaced first.

Name: getMeanPwm
Import: N/A
Export: meanPwm
Purpose: Calculates and returns the mean PWMs within the correctedPwms array.
Note: Ignores elements that have not been assigned a correctedPwm

				-----------------
				EXTERNAL MATERIAL
				-----------------
Tutorial used to create library/class: https://www.arduino.cc/en/Hacking/LibraryTutorial

				----
				MISC
				----
Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid classfields when constructing ClimbingClockSpeedCorrector object.