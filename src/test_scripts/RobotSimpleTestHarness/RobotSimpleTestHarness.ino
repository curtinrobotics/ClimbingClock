/*
 * @author Harrison Outram
 * Last Updated: 25/01/2020 (d/m/y UTC+08:00)
 * @version 1.0
 * @brief test script for Tortoise and Hare classes
 * Project: Climbing Clock (2019-20)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: 13/13 test cases pass
 * !!!! Hardware Dependancies: RTC !!!!
 */

#include <SpeedCorrector.h>
#include <SpeedChangeFunctions.h>
#include <RobotSimple.h>
#include <RTClib.h>

#define TEST_INITIAL_PWM 200
#define TEST_CORRECT_TIME 1 // 1 second
#define PWM_CHANGE_WAIT 200 // 0.2 seconds
#define TEST_PWM_OUT1 5
#define TEST_PWM_OUT2 6
#define TEST_PWM_IN1 A1
#define TEST_PWM_IN2 A0
#define PWM_TOL 35          // see excel spreadsheet
#define PWM_SAMPLE_SIZE 100
#define EXPECTED_BOTTOM_RELEASE_TIME 5

#define NUM_TESTS 13

SpeedCorrector *speedCorr1Ptr, *speedCorr2Ptr;
Robot *robotTruePtr, *robotFalsePtr;
RTC_DS1307 rtc;

void setup(void) {
  Serial.begin(9600);
  uint8_t testsPassed = 0;
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // initialize the rtc

  testsPassed += testSuite_constructor();
  testsPassed += testSuite_start();
  testsPassed += testSuite_cycleDone();
  testsPassed += testSuite_prepareNextCycle();
  testsPassed += testSuite_goDown();
  testsPassed += testSuite_attemptToGoUp();
  testsPassed += testSuite_atBottom();
  
  outputOverallResult(testsPassed);
}

void setUp(void) {
  DateTime testInitialEndDate = rtc.now() + TimeSpan(TEST_CORRECT_TIME);
  speedCorr1Ptr = new SpeedCorrector(TEST_INITIAL_PWM, TEST_CORRECT_TIME,
                                     &(SpeedChangeFunctions::linearChange));
  speedCorr2Ptr = new SpeedCorrector(TEST_INITIAL_PWM, TEST_CORRECT_TIME,
                                     &(SpeedChangeFunctions::linearChange));
  robotTruePtr = new RobotSimple(testInitialEndDate, speedCorr1Ptr,
                            &returnTrue, &returnTrue, TEST_PWM_OUT1, &rtc);
  robotFalsePtr = new RobotSimple(testInitialEndDate, speedCorr2Ptr,
                            &returnFalse, &returnFalse, TEST_PWM_OUT2, &rtc);
}

bool returnTrue(void) { return true; }

bool returnFalse(void) { return false; }

// see excel spreadsheet for equation
uint16_t calcAnalogInEstimate(uint8_t outPwm) {
  uint16_t analogInEstimate;

  analogInEstimate = (uint16_t)( 3.9913 * (float)outPwm + 4.4663 );

  return analogInEstimate;
}

void tearDown(void) {
  delete robotTruePtr;
  delete robotFalsePtr;
  delete speedCorr1Ptr;
  delete speedCorr2Ptr;
}

uint8_t testSuite_constructor(void) {
  uint8_t testsPassed = 0;

  setUp();
  testsPassed += constructor_testCase1();
  tearDown();
  
  return testsPassed;
}

uint8_t constructor_testCase1(void) {
  uint8_t testsPassed = 0;
  int expected = 0;
  int actual1, actual2;

  actual1 = analogRead(TEST_PWM_IN1);
  actual2 = analogRead(TEST_PWM_IN2);

  if (expected == actual1 && expected == actual2) {
    Serial.println("constructor test case 1 passed.");
    testsPassed++;
  } else {
    Serial.println("constructor test case 1 failed.");
    Serial.print("Expected initial input: "); Serial.println(expected);
    Serial.print("Actual input 1: "); Serial.println(actual1);
    Serial.print("Actual input 2: "); Serial.println(actual2);
  }
  Serial.print("\n");
  
  return testsPassed;
}

uint8_t testSuite_start(void) {
  uint8_t testsPassed = 0;

  setUp();
  testsPassed += start_testCase1();
  tearDown();
  
  return testsPassed;
}

uint8_t start_testCase1(void) {
  uint8_t testsPassed = 0;
  uint16_t expected = calcAnalogInEstimate(TEST_INITIAL_PWM);
  uint32_t actual1 = 0, actual2 = 0;
  bool result;
  
  robotTruePtr->start();
  robotFalsePtr->start();

  for (uint8_t i = 0; i < PWM_SAMPLE_SIZE; i++) {
   actual1 += analogRead(TEST_PWM_IN1);
   actual2 += analogRead(TEST_PWM_IN2);
  }

  actual1 /= PWM_SAMPLE_SIZE;
  actual2 /= PWM_SAMPLE_SIZE;

  result = (expected > actual1 - PWM_TOL) || (expected < actual1 + PWM_TOL);
  result &= (expected > actual2 - PWM_TOL) || (expected < actual2 + PWM_TOL);
  
  if (result) {
    Serial.println("start() test case 1 passed.");
    testsPassed++;
  } else {
    Serial.println("start() test case 1 failed.");
    Serial.print("Expected initial input: "); Serial.println(expected);
    Serial.print("Actual input 1: "); Serial.println(actual1);
    Serial.print("Actual input 2: "); Serial.println(actual2);  
  }
  Serial.print("\n");
  
  return testsPassed;
}

uint8_t testSuite_cycleDone(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  // When topMet is true
  testsPassed += cycleDone_testCase1();
  tearDown();
  
  // When topMet is false and waitingAtBottom is true
  setUp();
  testsPassed += cycleDone_testCase2();
  tearDown();
  
  // When topMet is false, waitingAtBottom is false, and current time < nextCycleEndDate
  setUp();
  testsPassed += cycleDone_testCase3();
  tearDown();

  // When topMet is false, waitingAtBottom is false, and current time >= nextCycleEndDate
  setUp();
  testsPassed += cycleDone_testCase4();
  tearDown();

  return testsPassed;
}

// When topMet is true and current time < current cycle end time
uint8_t cycleDone_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  actual = robotTruePtr->cycleDone();
  expected = true;
  
  if (actual == expected) {
    Serial.println("cycleDone() test case 1 passed.");
    testsPassed++;
  } else {
    Serial.println("cycleDone() test case 1 failed.");
    Serial.print("Expected cycleDone(): "); Serial.println(expected);
    Serial.print("Actual cycleDone(): "); Serial.println(actual);
  }
  Serial.print("\n");
  
  return testsPassed;
}

// When topMet is false and current time < current cycle end time
uint8_t cycleDone_testCase2(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  actual = robotFalsePtr->cycleDone();
  expected = false;
  
  if (actual == expected) {
    Serial.println("cycleDone() test case 2 passed.");
    testsPassed++;
  } else {
    Serial.println("cycleDone() test case 2 failed.");
    Serial.print("Expected cycleDone(): "); Serial.println(expected);
    Serial.print("Actual cycleDone(): "); Serial.println(actual);
  }
  Serial.print("\n");
  
  return testsPassed;
}

// When topMet is false and current time >= nextCycleEndDate
uint8_t cycleDone_testCase3(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  delay((TEST_CORRECT_TIME) * 1000); // wait for current cycle to expire
  actual = robotFalsePtr->cycleDone();
  expected = true;
  
  if (actual == expected) {
    Serial.println("cycleDone() test case 3 passed.");
    testsPassed++;
  } else {
    Serial.println("cycleDone() test case 3 failed.");
    Serial.print("Expected cycleDone(): "); Serial.println(expected);
    Serial.print("Actual cycleDone(): "); Serial.println(actual);
  }
  Serial.print("\n");
  
  return testsPassed;
}

// When topMet is true and current time >= nextCycleEndDate
uint8_t cycleDone_testCase4(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  robotFalsePtr->goDown();
  delay(TEST_CORRECT_TIME * 1000);
  actual = robotTruePtr->cycleDone();
  expected = true;
  
  if (actual == expected) {
    Serial.println("cycleDone() test case 4 passed.");
    testsPassed++;
  } else {
    Serial.println("cycleDone() test case 4 failed.");
    Serial.print("Expected cycleDone(): "); Serial.println(expected);
    Serial.print("Actual cycleDone(): "); Serial.println(actual);
  }
  Serial.print("\n");
  
  return testsPassed;
}

uint8_t testSuite_prepareNextCycle(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += prepareNextCycle_testCase1();
  tearDown();

  return testsPassed;
}

// WARNING: Only tests that method does not crash!
uint8_t prepareNextCycle_testCase1(void) {
  uint8_t testsPassed = 1;
  
  robotFalsePtr->prepareNextCycle();
  robotTruePtr->prepareNextCycle();

  return testsPassed;
}

uint8_t testSuite_goDown(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += goDown_testCase1();
  tearDown();

  return testsPassed;
}

uint8_t goDown_testCase1(void) {
  int expected = 0;
  int actual1 = 0, actual2 = 0;
  uint8_t testsPassed = 0;
  bool result;

  robotTruePtr->goDown();
  robotFalsePtr->goDown();
  
  for (uint8_t i = 0; i < PWM_SAMPLE_SIZE; i++) {
   actual1 += analogRead(TEST_PWM_IN1);
   actual2 += analogRead(TEST_PWM_IN2);
  }

  actual1 /= PWM_SAMPLE_SIZE;
  actual2 /= PWM_SAMPLE_SIZE;

  result = (expected > actual1 - PWM_TOL) || (expected < actual1 + PWM_TOL);
  result &= (expected > actual2 - PWM_TOL) || (expected < actual2 + PWM_TOL);
  
  if (result) {
    Serial.println("goDown() test case 1 passed.");
    testsPassed++;
  } else {
    Serial.println("goDown() test case 1 failed.");
    Serial.print("Expected analog reading: "); Serial.println(expected);
    Serial.print("Actual analog reading 1: "); Serial.println(actual1);
    Serial.print("Actual analog reading 2: "); Serial.println(actual2);
  }
  Serial.print("\n");
  
  return testsPassed;
}

uint8_t testSuite_attemptToGoUp(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += attemptToGoUp_testCase1();
  tearDown();

  setUp();
  testsPassed += attemptToGoUp_testCase2();
  tearDown();

  return testsPassed;
}

// current cycle has not ended
uint8_t attemptToGoUp_testCase1(void) {
  uint32_t expected1 = 0, expected2 = 0;
  uint32_t actual1 = 0, actual2 = 0;
  bool actualReturn1, actualReturn2, expectedReturn, pwmResult;
  uint8_t testsPassed = 0;

  robotTruePtr->start();
  robotFalsePtr->start();

  for (uint8_t i = 0; i < PWM_SAMPLE_SIZE; i++) {
   expected1 += analogRead(TEST_PWM_IN1);
   expected2 += analogRead(TEST_PWM_IN2);
  }
  expected1 /= PWM_SAMPLE_SIZE;
  expected2 /= PWM_SAMPLE_SIZE;

  actualReturn1 = robotTruePtr->attemptToGoUp();
  actualReturn2 = robotFalsePtr->attemptToGoUp();

  for (uint8_t i = 0; i < PWM_SAMPLE_SIZE; i++) {
   actual1 += analogRead(TEST_PWM_IN1);
   actual2 += analogRead(TEST_PWM_IN2);
  }
  actual1 /= PWM_SAMPLE_SIZE;
  actual1 /= PWM_SAMPLE_SIZE;
  expectedReturn = false;

  for (uint8_t i = 0; i < PWM_SAMPLE_SIZE; i++) {
   actual1 += analogRead(TEST_PWM_IN1);
   actual2 += analogRead(TEST_PWM_IN2);
  }

  actual1 /= PWM_SAMPLE_SIZE;
  actual2 /= PWM_SAMPLE_SIZE;

  pwmResult = (expected1 > actual1 - PWM_TOL) || (expected1 < actual1 + PWM_TOL);
  pwmResult &= (expected2 > actual2 - PWM_TOL) || (expected2 < actual2 + PWM_TOL);
  
  if (pwmResult && expectedReturn == actualReturn1 && expectedReturn == actualReturn2) {
    Serial.println("attemptToGoUp() test case 1 passed.");
    testsPassed++;
  } else {
    Serial.println("attemptToGoUp() test case 1 failed.");
    Serial.print("Expected analog reading 1: "); Serial.println(expected1);
    Serial.print("Actual analog reading 1: "); Serial.println(actual1);
    Serial.print("Expected analog reading 2: "); Serial.println(expected2);
    Serial.print("Actual analog reading 2: "); Serial.println(actual2);
    Serial.print("Expected return: "); Serial.println(expectedReturn);
    Serial.print("Actual return 1: "); Serial.println(actualReturn1);
    Serial.print("Actual return 2: "); Serial.println(actualReturn2);
  }
  Serial.print("\n");

  return testsPassed;
}

// current cycle has ended
uint8_t attemptToGoUp_testCase2(void) {
  uint16_t expected;
  uint32_t actual1 = 0, actual2 = 0;
  bool actualReturn1, actualReturn2, expectedReturn, pwmResult;
  uint8_t testsPassed = 0;

  robotTruePtr->start();
  robotFalsePtr->start();

  expected = calcAnalogInEstimate(TEST_INITIAL_PWM);
  expectedReturn = true;
  
  delay((TEST_CORRECT_TIME + 1) * 1000); // wait for current cycle to end
  actualReturn1 = robotTruePtr->attemptToGoUp();
  actualReturn2 = robotFalsePtr->attemptToGoUp();

  for (uint8_t i = 0; i < PWM_SAMPLE_SIZE; i++) {
   actual1 += analogRead(TEST_PWM_IN1);
   actual2 += analogRead(TEST_PWM_IN2);
  }

  actual1 /= PWM_SAMPLE_SIZE;
  actual2 /= PWM_SAMPLE_SIZE;
  
  pwmResult = (expected > actual1 - PWM_TOL) || (expected < actual1 + PWM_TOL);
  pwmResult &= (expected > actual2 - PWM_TOL) || (expected < actual2 + PWM_TOL);
  
  if (pwmResult && expectedReturn == actualReturn1 && expectedReturn == actualReturn2) {
    Serial.println("attemptToGoUp() test case 2 passed.");
    testsPassed++;
  } else {
    Serial.println("attemptToGoUp() test case 2 failed.");
    Serial.print("Expected analog reading 1: "); Serial.println(expected);
    Serial.print("Actual analog reading 1: "); Serial.println(actual1);
    Serial.print("Expected analog reading 2: "); Serial.print(expected);
    Serial.print("Actual analog reading 2: "); Serial.println(actual2);
    Serial.print("Expected return: "); Serial.println(expectedReturn);
    Serial.print("Actual return 1: "); Serial.println(actualReturn1);
    Serial.print("Actual return 2: "); Serial.println(actualReturn2);
  }
  Serial.print("\n");
  
  return testsPassed;
}

uint8_t testSuite_atBottom(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += atBottom_testCase1();
  tearDown();

  setUp();
  testsPassed += atBottom_testCase2();
  tearDown();

  setUp();
  testsPassed += atBottom_testCase3();
  tearDown();

  return testsPassed;
}

// Currently waiting at bottom
uint8_t atBottom_testCase1(void) {
  bool expected1, expected2, actual1, actual2;
  uint8_t testsPassed = 0;

  robotTruePtr->start(); robotFalsePtr->start();
  robotTruePtr->goDown();
  robotFalsePtr->goDown();

  actual1 = robotTruePtr->atBottom();
  actual2 = robotFalsePtr->atBottom();
  expected1 = true;
  expected2 = true;
  
  if (expected1 == actual1 && expected2 == actual2) {
    Serial.println("atBottom() test case 1 passed.");
    testsPassed++;
  } else {
    Serial.println("atBottom() test case 1 failed.");
    Serial.print("Expected 1: "); Serial.println(expected1);
    Serial.print("Actual 1: "); Serial.println(actual1);
    Serial.print("Expected 2: "); Serial.println(expected2);
    Serial.print("Actual 2: "); Serial.println(actual2);
  }
  Serial.print("\n");

  return testsPassed;
}

// Check trigger
uint8_t atBottom_testCase2(void) {
  bool expected1, expected2, actual1, actual2;
  uint8_t testsPassed = 0;

  robotTruePtr->start(); robotFalsePtr->start();
  delay((EXPECTED_BOTTOM_RELEASE_TIME + 1) * 1000); // wait for current time to pass previous fin date
  actual1 = robotTruePtr->atBottom();
  actual2 = robotFalsePtr->atBottom();
  expected1 = true;
  expected2 = false;
  
  if (expected1 == actual1 && expected2 == actual2) {
    Serial.println("atBottom() test case 2 passed.");
    testsPassed++;
  } else {
    Serial.println("atBottom() test case 2 failed.");
    Serial.print("Expected 1: "); Serial.println(expected1);
    Serial.print("Actual 1: "); Serial.println(actual1);
    Serial.print("Expected 2: "); Serial.println(expected2);
    Serial.print("Actual 2: "); Serial.println(actual2);
  }
  Serial.print("\n");

  return testsPassed;
}

// Ascending while trigger is still active
uint8_t atBottom_testCase3(void) {
  bool expected1, expected2, actual1, actual2;
  uint8_t testsPassed = 0;

  robotTruePtr->start(); robotFalsePtr->start();
  actual1 = robotTruePtr->atBottom();
  actual2 = robotFalsePtr->atBottom();
  expected1 = false;
  expected2 = false;
  
  if (expected1 == actual1 && expected2 == actual2) {
    Serial.println("atBottom() test case 3 passed.");
    testsPassed++;
  } else {
    Serial.println("atBottom() test case 3 failed.");
    Serial.print("Expected 1: "); Serial.println(expected1);
    Serial.print("Actual 1: "); Serial.println(actual1);
    Serial.print("Expected 2: "); Serial.println(expected2);
    Serial.print("Actual 2: "); Serial.println(actual2);
  }
  Serial.print('\n');

  return testsPassed;
}

void outputOverallResult(uint8_t testsPassed) {
  uint8_t testsFailed = NUM_TESTS - testsPassed;

  Serial.println("=============================");
  Serial.print(NUM_TESTS); Serial.println(" tests performed");
  Serial.println("=============================");
  
  if (testsPassed == NUM_TESTS) {
    Serial.println("All tests passed!");
  } else {
    Serial.print(testsPassed); Serial.println(" tests passed.");
    Serial.print(testsFailed); Serial.println(" tests failed.");
    Serial.print("Success rate: "); Serial.print( (float)(NUM_TESTS - testsFailed) / (float)NUM_TESTS * 100.0); Serial.println("%");
    Serial.println("Make sure the RTC is connected and working!");
  }
}

void loop() {
  //Should only run tests once
  //Hence, nothing should be here
}
