#################################################################
AUTHOR: Harrison Outram
DATE: 8/12/2019 (day/month/year)
PROGRAM: Robot class
LANGUAGE: C++ (Using the Arduino IDE)
PURPOSE: Create Robot objects to keep track of robot's status and
            tell robot to do required tasks
PROJECT: Climbing Clock (2019)
VERSION: 0.1
WORKING STATUS: Compiles
#################################################################

				------------
				DEPENDENCIES
				------------
Name: RTClib.h
Purpose: library for using real time clocks on Arduinos easily
Availability: Public, can install through Arduino IDE

Name: SpeedCorrector.h
Purpose: Machine Learning AI that corrects robot's PWM over time
Availability: Private, see project Github repo

				----------------------
				PUBLIC CLASS CONSTANTS
				----------------------
Name: BOTTOM_RELEASE_TIME
Value: 30
Purpose: Seconds to ignore atBottom() trigger when ascending
Note: See atBottom() public method

Name: DOWN_PWM
Value: 0
Purpose: Used for making robot go down ladder
Note: see goDown() public function

				----------------------
				CLASSFIELDS/PROPERTIES
				----------------------
Name: correctTimePtr
Datatype: TimeSpan*
Mutable: No
Accessable: No
Purpose: Tracks amount of time, in seconds, that robot should complete one cycle

Name: currCycleEndDatePtr
Datatype: DateTime*
Mutable: Limited (see attemptToGoUp())
Accessable: No
Purpose: Keep track of date and time that robot should reach top of current cycle

Name: speedCorrPtr
Datatype: SpeedCorrector*
Mutable: No
Accessable: No
Purpose: Link to SpeedCorrector AI

Name: atTopFuncPtr
Datatype: bool (*)(void)
Mutable: No
Accessable: No
Purpose: Callback function used to determine if robot has reached the top

Name: atBottomFuncPtr
Datatype: bool (*)(void)
Mutable: No
Accessable: No
Purpose: Callback function used to determine if robot has reached the bottom

Name: rtcPtr
Datatype: RTC_DS1307*
Mutable: No
Accessable: No
Purpose: Used to keep track of time

Name: prevFinDatePtr
Datatype: DateTime*
Mutable: Limited (see atBottom() and prepareNextCycle())
Accessable: No
Purpose: Keeps track of what the finish date and time for the previous cycle was

Name: setPwmPin
Datatype: uint8_t
Mutable: No
Accessable: No
Purpose: The pin for setting the robot's PWM.

Name: topMet
Datatype: bool
Mutable: Limited (see cycleDone() and prepareNextCycle())
Accessable: No
Purpose: Tracks whether the robot reached the top in the current cycle.

Name: waitingAtBottom
Datatype: bool
Mutable: Limited (see goDown() and attemptToGoUp())
Accessable: No
Purpose: Tracks whether the robot is waiting at the bottom for the current
            cycle to end.

				---------------------------
				CONSTRUCTORS AND DESTRUCTOR
				---------------------------
Name: Alternate 1
Imports: initialEndDate (DateTime&), inSpeedCorrPtr (SpeedCorrector*),
            inAtTopFuncPtr (bool (*)(void)), inAtBottomFuncPtr (bool (*)(void)),
            inSetPwmPin (uint8_t), inRtcPtr (RTC_DS1307*)
Note 1: Make sure the SpeedCorrector object is put on the heap, as the contructor
            does **not** create a copy.
Note 2: The PWM pin will be set to output mode via analogWrite(setPwmPin, OUTPUT).
Note 3: Make sure the RTC object is put on the heap, as the contructor
            does **not** create a copy.
Note 4: RTC is **not** initialised in the constructor!

Name: Destructor
Imports: N/A

				--------------
				PUBLIC METHODS
				--------------
Name: start
Imports: N/A
Export: N/A
Purpose: Tell the robot to start moving up
Note: Only use for initial cycle! Do **not** use elsewhere!
                
Name: cycleDone
Imports: N/A
Export: bool
Purpose: Checks if the robot has completed the current cycle

Name: prepareNextCycle
Import: N/A
Export: N/A
Purpose: Updates object variables for next cycle
Note: Does **not** tell robot to move!

Name: goDown
Import: N/A
Export: N/A
Purpose: Tells robot to go down.
Note: Uses DOWN_PWM constant (see above).

Name: attemptToGoUp
Imports: N/A
Export: bool
Purpose: Tells robot to go up.
Note 1: will only go up if the current time is on or after the current cycle's
        end time.
Note 2: Return value tells caller if robot is going up or not.

Name: atBottom
Imports: N/A
Export: bool
Purpose: Checks if robot is at bottom of ladder.

				-----------------
				EXTERNAL MATERIAL
				-----------------
Tutorial used to create library/class: https://www.arduino.cc/en/Hacking/LibraryTutorial
Tutorial for learning PWM: https://www.arduino.cc/en/Tutorial/PWM
Tutorial for setting PWM: https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/

				----
				MISC
				----
Due to lacking screen and control panel on robots, exception handling has not been implemented.
Ergo, code must be visually inspected for valid classfields when constructing Robot objects.