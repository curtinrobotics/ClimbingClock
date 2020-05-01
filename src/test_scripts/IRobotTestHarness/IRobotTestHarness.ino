/*!
 * @author Harrison Outram
 * Last Updated: 30/04/2020 (d/m/y UTC+08:00)
 * @version 1.0
 * @brief test script for IRobot interface
 * Project: Climbing Clock (2019-20)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: ?/8 test cases pass
 * @attention Hardware Dependancies: Arduino
 */

// Inclued code to be tested
#include <IRobot.h>

// total number of tests
#define NUM_TESTS 8

class MockRobot : public IRobot {
  public:
    MockRobot() { }

    bool start(void) { return true; }
    void stop(void) { }
    bool goUp(void) { return true; }
    bool goDown(void) { return true; }
    int getPosition(void) { return 0; }
    int getDirection(void) { return 1; }
    int faultDetected(void) { return 2; }
    bool cycleDone(void) { return false; }

    ~MockRobot() { Serial.println(F("MockRobot destroyed")); }
};

//global variables needed
MockRobot *mockRobot;

void setup(void) {
  while (!Serial) { } // wait for Serial monitor to be ready
  Serial.begin(9600);
  
  uint8_t testsPassed = 0;
  
  testsPassed += testSuite_start();
  testsPassed += testSuite_stop();
  testsPassed += testSuite_goUp();
  testsPassed += testSuite_goDown();
  testsPassed += testSuite_getPosition();
  testsPassed += testSuite_getDirection();
  testsPassed += testSuite_faultDetected();
  testsPassed += testSuite_cycleDone();
  
  outputOverallResult(testsPassed);
}

// used to set up global variables for next test case
void setUp(void) {
  mockRobot = new MockRobot();
}

// deletes global variables after test case done
void tearDown(void) {
  delete mockRobot;
}

// test initialise hardware devices here
uint8_t testSuite_start(void) {
  uint8_t testsPassed = 0;

  setUp();
  testsPassed += start_testCase1();
  tearDown();
  
  return testsPassed;
}

uint8_t start_testCase1(void) {
  uint8_t testsPassed = 0;
  bool expected = true;
  bool actual;
  bool result;
  
  // test devices have started up correctly
  actual = mockRobot->start();
  result = (actual == expected);

  if (result) {
    Serial.println(F("start() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("start() test case 1 failed."));
    Serial.print(F("Expected return: ")); Serial.println(expected);
    Serial.print(F("Actual return: ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t testSuite_stop(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += stop_testCase1();
  tearDown();

  return testsPassed;
}

uint8_t stop_testCase1(void) {
  uint8_t testsPassed = 0;

  // make sure calling method does not cause run-time error
  mockRobot->stop();
  
  Serial.println(F("stop() test case 1 passed."));
  testsPassed++;
  Serial.println(F(""));
  
  return testsPassed;
}

// test method 2 here
uint8_t testSuite_goUp(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += goUp_testCase1();
  tearDown();
  
  return testsPassed;
}

uint8_t goUp_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected = true;

  // test actual and expected here
  actual = mockRobot->goUp();
  
  if (actual == expected) {
    Serial.println(F("goUp() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("goUp() test case 1 failed."));
    Serial.print(F("Expected return: ")); Serial.println(expected);
    Serial.print(F("Actual return: ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
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
  uint8_t testsPassed = 0;
  bool actual, expected = true;

  // test actual and expected here
  actual = mockRobot->goDown();
  
  if (actual == expected) {
    Serial.println(F("goDown() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("goDown() test case 1 failed."));
    Serial.print(F("Expected return(): ")); Serial.println(expected);
    Serial.print(F("Actual return(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t testSuite_getPosition(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += getPosition_testCase1();
  tearDown();

  return testsPassed;
}

uint8_t getPosition_testCase1(void) {
  uint8_t testsPassed = 0;
  int actual, expected = 0;

  // test actual and expected here
  actual = mockRobot->getPosition();
  
  if (actual == expected) {
    Serial.println(F("getPosition() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("getPosition() test case 1 failed."));
    Serial.print(F("Expected return(): ")); Serial.println(expected);
    Serial.print(F("Actual return(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t testSuite_getDirection(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += getDirection_testCase1();
  tearDown();

  return testsPassed;
}

uint8_t getDirection_testCase1(void) {
  uint8_t testsPassed = 0;
  int actual, expected = 1;

  // test actual and expected here
  actual = mockRobot->getDirection();
  
  if (actual == expected) {
    Serial.println(F("getDirection() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("getDirection() test case 1 failed."));
    Serial.print(F("Expected return(): ")); Serial.println(expected);
    Serial.print(F("Actual return(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t testSuite_faultDetected(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += faultDetected_testCase1();
  tearDown();

  return testsPassed;
}

uint8_t faultDetected_testCase1(void) {
  uint8_t testsPassed = 0;
  int actual, expected = 2;

  // test actual and expected here
  actual = mockRobot->faultDetected();
  
  if (actual == expected) {
    Serial.println(F("faultDetected() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("faultDetected() test case 1 failed."));
    Serial.print(F("Expected return(): ")); Serial.println(expected);
    Serial.print(F("Actual return(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t testSuite_cycleDone(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += cycleDone_testCase1();
  tearDown();

  return testsPassed;
}

uint8_t cycleDone_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected = false;

  // test actual and expected here
  actual = mockRobot->cycleDone();
  
  if (actual == expected) {
    Serial.println(F("cycleDone() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("cycleDone() test case 1 failed."));
    Serial.print(F("Expected return(): ")); Serial.println(expected);
    Serial.print(F("Actual return(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// final output of program
void outputOverallResult(uint8_t testsPassed) {
  uint8_t testsFailed = NUM_TESTS - testsPassed;

  Serial.println(F("============================="));
  Serial.print(NUM_TESTS); Serial.println(F(" tests performed"));
  Serial.println(F("============================="));
  Serial.println(F(""));
  
  if (testsPassed == NUM_TESTS) {
    Serial.println(F("All tests passed!"));
  } else {
    Serial.print(testsPassed); Serial.println(F(" tests passed."));
    Serial.print(testsFailed); Serial.println(F(" tests failed."));
    Serial.print(F("Success rate: ")); Serial.print( (float)(NUM_TESTS - testsFailed) / (float)NUM_TESTS * 100.0); Serial.println(F("%"));
  }
  
  Serial.println(F("WARNING: did not test if interface was destroyed!!"));
  Serial.println(F("Check Serial monitor for \"IRobot destroyed\" text"));
}

void loop() {
  //Should only run tests once
  //Hence, nothing should be here
}
