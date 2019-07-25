#################################################################
AUTHOR: Harrison Outram
DATE: 25/07/2019 (day/month/year)
PROGRAM: SpeedCorrector library/class
LANGuaGE: C++ (Using the Arduino IDE)
PURPOSE: Provide functionality for a Machine Learning (ML) AI to
			auto-correct robot climbing speed
project: Climbing Clock (2019)
version: 1.1
#################################################################

				----------------------
				PUBLIC CLASS CONSTANTS
				----------------------
Name: MAX_NUM_OF_PWMS
Value: 10 (uint8_t)
Purpose: default size for correctedPwms array

Name: SPEED_INCREMENT
Value: 10 (uint8_t)
Purpose: default value for speedIncrement classfield

Name: MIN_SPEED_INCREMENT
Value: 5 (uint8_t)
Purpose: default minimum speed increment for adjusting motor speed

Name: LINEAR_CHANGE_TYPE
Value: 'l'
Purpose: value for setting the speedIncrement change method to a linear function
Note: See calcNewSpeedIncrement method

Name: EXP_CHANGE_TYPE
Value: 'e'
Purpose: value for setting the speedIncrement change method to an exponential function
Note: See calcNewSpeedIncrement method

Name: SPEED_INCREMENT_CHANGE
Value: 5 (uint8_t)
Purpose: default value for how exactly the speedIncrement classfield will change
Note: See calcNewSpeedIncrement method

				----------------------
				CLASSFIELDS/PROPERTIES
				----------------------
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

Name: speedIncrement
Datatype: int8_t
Mutable: Limited (see calcNewSpeedIncrement)
Purpose: Amount PWM is increased by if robot does not reach top in time.
Note 1: Small values will take longer to get to correct speed,
			but larger value are likely to overcorrect.
Note 2: Strongly recommended to keep this value small.

Name: minSpeedIncrement
Datatype: uint8_t
Mutable: No
Purpose: The minimum value for the speedIncrement classfield.

Name: speedChangeType
Datatype: char
Mutable: No
Purpose: Determines the equation to use for changing the speedIncrement classfied.

Name: speedIncrementChange
Datatype: uint8_t
Mutable: No
Purpose: value for how exactly the speedIncrement classfield will change
Note: See calcNewSpeedIncrement method

				---------------------------
				CONSTRUCTORS AND DESTRUCTOR
				---------------------------
Name: Alternate 1
Imports: initialPwm (uint16_t), inCorrectTime (uint32_t)
Note 1: assigns initialPwm as the 0th element in the correctedPwms array
Note 2: the max PWM index (and the array size by extension) is assigned the
			MAX_PWM_INDEX public class constant.
Note 3: the change type for the speedIncrement classfield is linear with a speedIncrementChange
			of SPEED_INCREMENT_CHANGE.

Name: Alternate 2
Imports: initialPwm (uint16_t), inCorrectTime (uint32_t), inMaxPwmIndex (uint8_t),
			inSpeedIncrement (int8_t), inMinSpeedIncrement (uint8_t), inSpeedChangeType (char),
			inSpeedIncrementChange (uint8_t)
Note 1: assigns initialPwm as the 0th element in the correctedPwms array
Note 2: Strongly recommended to keep inSpeedIncrement value small to avoid overcorrection.
Note 3: Despite signed integer datatype for inSpeedIncrement, do NOT assign a negative number.
			This signed integer datatype prevents a run-time error.
Note 4: Do NOT assign a value of 0 to inMinSpeedIncrement.
Note 5: inSpeedChangeType must be either LINEAR_CHANGE_TYPE or EXP_CHANGE_TYPE.
Note 6: It is strongly recommended that a small value (e.g. single digit) be chosed for inSpeedIncrementChange.

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
Note: Ignores elements that have not been assigned a correctedPwm.

				---------------
				PRIVATE METHODS
				---------------
Name: getPwmOffset
Imports: timeErr (uint32_t), currentPwm (uint16_t)
Export: pwmOffset (uint16_t)
Purpose: calculates how much the current PWM was off by via the timeError and the currentPwm.

Name: calcNewSpeedIncrement
Import: N/A
Export: N/A
Purpose: Reduces speedIncrement classfield based on speedChangeType and speedIncrementChange.
Note 1: If linear was chosen as the change type, then the equation
			newSpeedIncrement = speedIncrement - floor(time / correctTime) * speedIncrementChange
			is used.
Note 2: If exponential was chosen as the change type, then the equation
			newSpeedIncrement = speedIncrement * (1/speedIncrementChange) ^ floor(time / correctTime)
			is used.
Note 3: If the newSpeedIncrement is less than the minSpeedIncrement, then the newSpeedIncrement is
			assigned minSpeedIncrement.

				-----------------
				EXTERNAL MATERIAL
				-----------------
Tutorial used to create library/class: https://www.arduino.cc/en/Hacking/LibraryTutorial

				----
				MISC
				----
Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid classfields when constructing SpeedCorrector object.