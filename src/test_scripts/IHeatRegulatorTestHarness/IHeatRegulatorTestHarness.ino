/*
 * @author Harrison Outram
 * Last Updated: 30/04/2020 (d/m/y UTC+08:00)
 * @version 1.0
 * @brief test script for IHeatRegulator interface
 * Project: Climbing Clock (2019-20)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: 6/6 test cases pass
 * @attention Hardware Dependancies: Arduino
 */

// Inclued code to be tested
#include <IHeatRegulator.h>

// total number of tests
#define NUM_TESTS 6

class MockHeatReg : public IHeatRegulator {
  public:
    MockHeatReg() { }

    bool start(void) { return true; }
    void stop(void) { }
    int getTempt(void) { return 100; }
    int faultDetected(void) { return 2; }
    bool setCooling(uint8_t power) { return false; }
    uint8_t temptToPower(int power) { return power; }

    ~MockHeatReg() { Serial.println(F("MockHeatReg destroyed")); }
};

//global variables needed
MockHeatReg *mockHeatReg;

void setup(void) {
  while (!Serial) { } // wait for Serial monitor to be ready
  Serial.begin(9600);
  
  uint8_t testsPassed = 0;

  setUp();
  testsPassed += testSuite_start();
  testsPassed += testSuite_stop();
  testsPassed += testSuite_getTempt();
  testsPassed += testSuite_setCooling();
  testsPassed += testSuite_faultDetected();
  testsPassed += testSuite_temptToPower();
  tearDown();
  
  outputOverallResult(testsPassed);
}

// used to set up global variables for next test case
void setUp(void) {
  mockHeatReg = new MockHeatReg();
}

// deletes global variables after test case done
void tearDown(void) {
  delete mockHeatReg;
}

// test initialise hardware devices here
uint8_t testSuite_start(void) {
  uint8_t testsPassed = 0;

  testsPassed += start_testCase1();
  
  return testsPassed;
}

uint8_t start_testCase1(void) {
  uint8_t testsPassed = 0;
  bool expected = true;
  bool actual;
  bool result;
  
  // test devices have started up correctly
  actual = mockHeatReg->start();
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
  
  testsPassed += stop_testCase1();

  return testsPassed;
}

uint8_t stop_testCase1(void) {
  uint8_t testsPassed = 0;

  // make sure calling method does not cause run-time error
  mockHeatReg->stop();
  
  Serial.println(F("stop() test case 1 passed."));
  testsPassed++;
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t testSuite_getTempt(void) {
  uint8_t testsPassed = 0;
  
  testsPassed += getTempt_testCase1();
  
  return testsPassed;
}

uint8_t getTempt_testCase1(void) {
  uint8_t testsPassed = 0;
  int actual, expected = 100;

  actual = mockHeatReg->getTempt();
  
  if (actual == expected) {
    Serial.println(F("getTempt() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("getTempt() test case 1 failed."));
    Serial.print(F("Expected return: ")); Serial.println(expected);
    Serial.print(F("Actual return: ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t testSuite_setCooling(void) {
  uint8_t testsPassed = 0;
  
  testsPassed += setCooling_testCase1();

  return testsPassed;
}

uint8_t setCooling_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected = false;

  actual = mockHeatReg->setCooling((uint8_t)30);
  
  if (actual == expected) {
    Serial.println(F("setCooling() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("setCooling() test case 1 failed."));
    Serial.print(F("Expected return(): ")); Serial.println(expected);
    Serial.print(F("Actual return(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t testSuite_faultDetected(void) {
  uint8_t testsPassed = 0;
  
  testsPassed += faultDetected_testCase1();

  return testsPassed;
}

uint8_t faultDetected_testCase1(void) {
  uint8_t testsPassed = 0;
  int actual, expected = 2;

  actual = mockHeatReg->faultDetected();
  
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

uint8_t testSuite_temptToPower(void) {
  uint8_t testsPassed = 0;
  
  testsPassed += temptToPower_testCase1();

  return testsPassed;
}

uint8_t temptToPower_testCase1(void) {
  uint8_t testsPassed = 0;
  uint8_t actual, expected = (uint8_t)30;

  actual = mockHeatReg->temptToPower(30);
  
  if (actual == expected) {
    Serial.println(F("temptToPower() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("temptToPower() test case 1 failed."));
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
  Serial.println(F("Check Serial monitor for \"IHeatRegulator destroyed\" and \"MockHeatReg destroyed\" text"));
}

void loop() {
  //Should only run tests once
  //Hence, nothing should be here
}
