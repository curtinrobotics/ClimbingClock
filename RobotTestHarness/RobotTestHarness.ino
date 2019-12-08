/*
 * Author: Harrison Outram
 * Date: 08/12/2019 (d/m/y)
 * Version: 0.1
 * Purpose: test script for Tortoise and Hare classes
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Compiles
 */

#include <SpeedCorrector.h>
#include <SpeedChangeFunctions.h>
#include <Robot.h>
#include <RTClib.h>

#define TEST_INITIAL_PWM 200
#define TEST_CORRECT_TIME 2 // 2 seconds
#define TEST_PWM_OUT1 5
#define TEST_PWM_OUT2 6
#define TEST_PWM_IN1 A0
#define TEST_PWM_IN2 A1

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
  robotTruePtr = new Robot(testInitialEndDate, speedCorr1Ptr,
                            &returnTrue, &returnTrue, TEST_PWM_OUT1, &rtc);
  robotFalsePtr = new Robot(testInitialEndDate, speedCorr2Ptr,
                            &returnFalse, &returnFalse, TEST_PWM_OUT2, &rtc);
}

bool returnTrue(void) { return true; }

bool returnFalse(void) { return false; }

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
    Serial.print("constructor test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("constructor test case 1 failed.\n");
    Serial.print("Expected initial input: "); Serial.print(expected);
    Serial.print(", actual input 1: "); Serial.print(actual1);
    Serial.print(", actual input 2: "); Serial.print(actual2);
    Serial.print("\n\n");
  }
  
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
  int expected = 802;
  int actual1, actual2;
  const uint8_t TOL = 3;
  bool result;

  robotTruePtr->start();
  robotTruePtr->start();
  actual1 = analogRead(TEST_PWM_IN1);
  actual2 = analogRead(TEST_PWM_IN2);

  result = (abs(actual1 - expected) < TOL && abs(actual2 - expected) < TOL);
  
  if (result) {
    Serial.print("start() test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("start() test case 1 failed.\n");
    Serial.print("Expected initial input: "); Serial.print(expected);
    Serial.print(", actual input 1: "); Serial.print(actual1);
    Serial.print(", actual input 2: "); Serial.print(actual2);
    Serial.print("\n\n");
  }

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

// When topMet is true
uint8_t cycleDone_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  actual = robotTruePtr->cycleDone();
  expected = true;
  
  if (actual == expected) {
    Serial.print("cycleDone() test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("cycleDone() test case 1 failed.\n");
    Serial.print("Expected cycleDone(): "); Serial.print(expected);
    Serial.print(", actual cycleDone(): "); Serial.print(actual);
    Serial.print("\n\n");
  }
  
  return testsPassed;
}

// When topMet is false and waitingAtBottom is true
uint8_t cycleDone_testCase2(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  robotFalsePtr->goDown();
  actual = robotFalsePtr->cycleDone();
  expected = true;
  
  if (actual == expected) {
    Serial.print("cycleDone() test case 2 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("cycleDone() test case 2 failed.\n");
    Serial.print("Expected cycleDone(): "); Serial.print(expected);
    Serial.print(", actual cycleDone(): "); Serial.print(actual);
    Serial.print("\n\n");
  }
  
  return testsPassed;
}

// When topMet is false, waitingAtBottom is false, and current time < nextCycleEndDate
uint8_t cycleDone_testCase3(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  actual = robotFalsePtr->cycleDone();
  expected = true;
  
  if (actual == expected) {
    Serial.print("cycleDone() test case 3 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("cycleDone() test case 3 failed.\n");
    Serial.print("Expected cycleDone(): "); Serial.print(expected);
    Serial.print(", actual cycleDone(): "); Serial.print(actual);
    Serial.print("\n\n");
  }
  
  return testsPassed;
}

// When topMet is false, waitingAtBottom is false, and current time >= nextCycleEndDate
uint8_t cycleDone_testCase4(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  robotFalsePtr->goDown();
  delay((TEST_CORRECT_TIME + 1) * 1000);
  actual = robotFalsePtr->cycleDone();
  expected = true;
  
  if (actual == expected) {
    Serial.print("cycleDone() test case 4 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("cycleDone() test case 4 failed.\n");
    Serial.print("Expected cycleDone(): "); Serial.print(expected);
    Serial.print(", actual cycleDone(): "); Serial.print(actual);
    Serial.print("\n\n");
  }
  
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
  int actual1, actual2;
  uint8_t testsPassed = 0;

  robotTruePtr->goDown();
  robotFalsePtr->goDown();
  actual1 = analogRead(TEST_PWM_OUT1);
  actual2 = analogRead(TEST_PWM_OUT2);
  
  if (expected == actual1 && expected == actual2) {
    Serial.print("start() test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("start() test case 1 failed.\n");
    Serial.print("Expected analog reading: "); Serial.print(expected);
    Serial.print(", actual analog reading 1: "); Serial.print(actual1);
    Serial.print(", actual analog reading 2: "); Serial.print(actual2);
    Serial.print("\n\n");
  }

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
  int expected1, expected2;
  int actual1, actual2;
  bool actualReturn1, actualReturn2, expectedReturn;
  uint8_t testsPassed = 0;

  expected1 = analogRead(TEST_PWM_OUT1);
  expected2 = analogRead(TEST_PWM_OUT2);
  expectedReturn = false;
  actualReturn1 = robotTruePtr->attemptToGoUp();
  actualReturn2 = robotFalsePtr->attemptToGoUp();
  actual1 = analogRead(TEST_PWM_OUT1);
  actual2 = analogRead(TEST_PWM_OUT2);
  
  if (expected1 == actual1 && expected2 == actual2 &&
      expectedReturn == actualReturn1 && expectedReturn == actualReturn2) {
    Serial.print("attemptToGoUp() test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("attemptToGoUp() test case 1 failed.\n");
    Serial.print("Expected analog reading 1: "); Serial.print(expected1);
    Serial.print(", actual analog reading 1: "); Serial.print(actual1);
    Serial.print("\n");
    Serial.print("Expected analog reading 2: "); Serial.print(expected2);
    Serial.print(", actual analog reading 2: "); Serial.print(actual2);
    Serial.print("\n");
    Serial.print("Expected return: "); Serial.print(expectedReturn);
    Serial.print(", actual return 1: "); Serial.print(actualReturn1);
    Serial.print(", actual return 2: "); Serial.print(actualReturn2);
    Serial.print("\n\n");
  }

  return testsPassed;
}

// current cycle has ended
uint8_t attemptToGoUp_testCase2(void) {
  int expected1, expected2;
  int actual1, actual2;
  bool actualReturn1, actualReturn2, expectedReturn;
  uint8_t testsPassed = 0;

  delay((TEST_CORRECT_TIME + 1) * 1000);
  robotTruePtr->prepareNextCycle();
  robotFalsePtr->prepareNextCycle();

  expected1 = (int)((float)speedCorr1Ptr->getCurrentPwm() / 255.0 * 1023);
  expected2 = (int)((float)speedCorr2Ptr->getCurrentPwm() / 255.0 * 1023);
  expectedReturn = true;
  actualReturn1 = robotTruePtr->attemptToGoUp();
  actualReturn2 = robotFalsePtr->attemptToGoUp();
  actual1 = analogRead(TEST_PWM_OUT1);
  actual2 = analogRead(TEST_PWM_OUT2);
  
  if (expected1 == actual1 && expected2 == actual2 &&
      expectedReturn == actualReturn1 && expectedReturn == actualReturn2) {
    Serial.print("attemptToGoUp() test case 2 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("attemptToGoUp() test case 2 failed.\n");
    Serial.print("Expected analog reading 1: "); Serial.print(expected1);
    Serial.print(", actual analog reading 1: "); Serial.print(actual1);
    Serial.print("\n");
    Serial.print("Expected analog reading 2: "); Serial.print(expected2);
    Serial.print(", actual analog reading 2: "); Serial.print(actual2);
    Serial.print("\n");
    Serial.print("Expected return: "); Serial.print(expectedReturn);
    Serial.print(", actual return 1: "); Serial.print(actualReturn1);
    Serial.print(", actual return 2: "); Serial.print(actualReturn2);
    Serial.print("\n\n");
  }

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

  robotTruePtr->goDown();
  robotFalsePtr->goDown();

  actual1 = robotTruePtr->atBottom();
  actual2 = robotFalsePtr->atBottom();
  expected1 = true;
  expected2 = true;
  
  if (expected1 == actual1 && expected2 == actual2) {
    Serial.print("atBottom() test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("atBottom() test case 1 failed.\n");
    Serial.print("Expected 1: "); Serial.print(expected1);
    Serial.print(", actual 1: "); Serial.print(actual1);
    Serial.print("\n");
    Serial.print("Expected 2: "); Serial.print(expected2);
    Serial.print(", actual 2: "); Serial.print(actual2);
    Serial.print("\n\n");
  }

  return testsPassed;
}

// Check trigger
uint8_t atBottom_testCase2(void) {
  bool expected1, expected2, actual1, actual2;
  uint8_t testsPassed = 0;

  delay(1000); // wait for current time to pass previous fin date
  actual1 = robotTruePtr->atBottom();
  actual2 = robotFalsePtr->atBottom();
  expected1 = true;
  expected2 = false;
  
  if (expected1 == actual1 && expected2 == actual2) {
    Serial.print("atBottom() test case 2 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("atBottom() test case 2 failed.\n");
    Serial.print("Expected 1: "); Serial.print(expected1);
    Serial.print(", actual 1: "); Serial.print(actual1);
    Serial.print("\n");
    Serial.print("Expected 2: "); Serial.print(expected2);
    Serial.print(", actual 2: "); Serial.print(actual2);
    Serial.print("\n\n");
  }

  return testsPassed;
}

// Ascending while trigger is still active
uint8_t atBottom_testCase3(void) {
  bool expected1, expected2, actual1, actual2;
  uint8_t testsPassed = 0;

  actual1 = robotTruePtr->atBottom();
  actual2 = robotFalsePtr->atBottom();
  expected1 = false;
  expected2 = false;
  
  if (expected1 == actual1 && expected2 == actual2) {
    Serial.print("atBottom() test case 3 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("atBottom() test case 3 failed.\n");
    Serial.print("Expected 1: "); Serial.print(expected1);
    Serial.print(", actual 1: "); Serial.print(actual1);
    Serial.print("\n");
    Serial.print("Expected 2: "); Serial.print(expected2);
    Serial.print(", actual 2: "); Serial.print(actual2);
    Serial.print("\n\n");
  }

  return testsPassed;
}

void outputOverallResult(uint8_t testsPassed) {
  uint8_t testsFailed = NUM_TESTS - testsPassed;

  Serial.print("=========================\n");
  Serial.print(NUM_TESTS); Serial.print(" tests performed\n");
  Serial.print("=========================\n");
  
  if (testsPassed == NUM_TESTS) {
    Serial.print("All tests passed!\n");
  } else {
    Serial.print(testsPassed); Serial.print(" tests passed.\n");
    Serial.print(testsFailed); Serial.print(" tests failed.\n");
  }
    
}

void loop() {
  //Should only run tests once
  //Hence, nothing should be here
}
