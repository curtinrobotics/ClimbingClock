/*
 * @author Harrison Outram
 * Last Updated: 30/04/2020 (d/m/y UTC+08:00)
 * @version 1.0
 * @brief test script for ITimeScale interface
 * Project: Climbing Clock (2019-20)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: ?/4 test cases pass
 * @attention Hardware Dependancies: Arduino
 */

// Inclued code to be tested
#include <ITimeScale.h>

// total number of tests
#define NUM_TESTS 4

class MockTimeScale : public ITimeScale {
  public:
    MockTimeScale() { }

    bool start(void) { return true; }
    void stop(void) { }
    bool faultDetected(void) { return true; }
    bool setTime(uint8_t hours, uint8_t minutes, uint8_t seconds) { return false; }

    ~MockTimeScale() { Serial.println(F("MockTimeScale destroyed")); }
};

//global variables needed
MockTimeScale *mockTimeScale;

void setup(void) {
  while (!Serial) { } // wait for Serial monitor to be ready
  Serial.begin(9600);
  
  uint8_t testsPassed = 0;
  
  testsPassed += testSuite_start();
  testsPassed += testSuite_stop();
  testsPassed += testSuite_faultDetected();
  testsPassed += testSuite_setTime();
  
  outputOverallResult(testsPassed);
}

// used to set up global variables for next test case
void setUp(void) {
  mockTimeScale = new MockTimeScale();
}

// deletes global variables after test case done
void tearDown(void) {
  delete mockTimeScale;
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
  bool expected = true;
  bool actual;
  bool result;
  
  actual = mockTimeScale->start();
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
  mockTimeScale->stop();
  
  Serial.println(F("stop() test case 1 passed."));
  testsPassed++;
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
  bool actual, expected = true;

  actual = mockTimeScale->faultDetected();
  
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

uint8_t testSuite_setTime(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += setTime_testCase1();
  tearDown();

  return testsPassed;
}

uint8_t setTime_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected = false;

  actual = mockTimeScale->setTime(2, 30, 12);
  
  if (actual == expected) {
    Serial.println(F("setTime() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("setTime() test case 1 failed."));
    Serial.print(F("Expected return(): ")); Serial.println(expected);
    Serial.print(F("Actual return(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

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
  Serial.println(F("Check Serial monitor for \"ITimeScale destroyed\" text"));
}

void loop() {
  //Should only run tests once
  //Hence, nothing should be here
}
