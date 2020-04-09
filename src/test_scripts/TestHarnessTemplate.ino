/*
 * @author 
 * Last Updated:  (d/m/y UTC+08:00)
 * @version 
 * @brief test script for 
 * Project: Climbing Clock (2019-20)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: /13 test cases pass
 * !!!! Hardware Dependancies:  !!!!
 */

// Inclued code to be tested
#include <.h>

// Constants needed
#define TEST_VALUE1 
#define TEST_VALUE2 
#define TEST_VALUE3 
#define TEST_VALUE4

// total number of tests
#define NUM_TESTS 

//global variables needed


void setup(void) {
  while (!Serial) { } // wait for Serial monitor to be ready
  Serial.begin(9600);
  
  // initialise hardware here
  
  
  uint8_t testsPassed = 0;
  
  testsPassed += testSuite_constructor();
  testsPassed += testSuite_start();
  testsPassed += testSuite_method1();
  testsPassed += testSuite_method2();
  testsPassed += testSuite_method3();
  
  outputOverallResult(testsPassed);
}

// used to set up global variables for next test case
void setUp(void) {
  
}

// mock functions here
bool returnTrue(void) { return true; }

bool returnFalse(void) { return false; }

// deletes global variables after test case done
void tearDown(void) {
  delete ;
  delete ;
}

// test that object construction has worked
uint8_t testSuite_constructor(void) {
  uint8_t testsPassed = 0;

  setUp();
  testsPassed += constructor_testCase1();
  testsPassed += constructor_testCase2();
  tearDown();
  
  return testsPassed;
}

uint8_t constructor_testCase1(void) {
  uint8_t testsPassed = 0;
  int expected = 0;
  int actual1, actual2;

  // test actual and expected are the same

  if (expected == actual1 && expected == actual2) {
    Serial.println(F("constructor test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("constructor test case 1 failed."));
    Serial.print(F("Expected initial input: ")); Serial.println(expected);
    Serial.print(F("Actual input 1: ")); Serial.println(actual1);
    Serial.print(F("Actual input 2: ")); Serial.println(actual2);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t constructor_testCase2(void) {
  uint8_t testsPassed = 0;
  int expected = 0;
  int actual1, actual2;

  // test actual and expected are the same

  if (expected == actual1 && expected == actual2) {
    Serial.println(F("constructor test case 2 passed."));
    testsPassed++;
  } else {
    Serial.println(F("constructor test case 2 failed."));
    Serial.print(F("Expected initial input: ")); Serial.println(expected);
    Serial.print(F("Actual input 1: ")); Serial.println(actual1);
    Serial.print(F("Actual input 2: ")); Serial.println(actual2);
  }
  Serial.println(F(""));
  
  return testsPassed;
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
  uint16_t expected = 0;
  uint32_t actual1 = 0, actual2 = 0;
  bool result;
  
  // test devices have started up correctly

  if (result) {
    Serial.println(F("start() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("start() test case 1 failed."));
    Serial.print(F("Expected initial input: ")); Serial.println(expected);
    Serial.print(F("Actual input 1: ")); Serial.println(actual1);
    Serial.print(F("Actual input 2: ")); Serial.println(actual2);  
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// test method 1 here
uint8_t testSuite_method1(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  // path 1
  testsPassed += method1_testCase1();
  tearDown();
  
  // path 2
  setUp();
  testsPassed += method1_testCase2();
  tearDown();
  
  // path 3
  setUp();
  testsPassed += method1_testCase3();
  tearDown();

  return testsPassed;
}

// path 1
uint8_t method1_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method1() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method1() test case 1 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// path 2
uint8_t method1_testCase2(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method1() test case 2 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method1() test case 2 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// path 3
uint8_t method1_testCase3(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method1() test case 3 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method1() test case 3 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// test method 2 here
uint8_t testSuite_method2(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  // path 1
  testsPassed += method2_testCase1();
  tearDown();
  
  // path 2
  setUp();
  testsPassed += method2_testCase2();
  tearDown();
  
  // path 3
  setUp();
  testsPassed += method2_testCase3();
  tearDown();

  return testsPassed;
}

// path 1
uint8_t method2_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method2() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method2() test case 1 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// path 2
uint8_t method2_testCase2(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method2() test case 2 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method2() test case 2 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// path 3
uint8_t method2_testCase3(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method2() test case 3 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method2() test case 3 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// test method 3 here
uint8_t testSuite_method3(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  // path 1
  testsPassed += method3_testCase1();
  tearDown();
  
  // path 2
  setUp();
  testsPassed += method3_testCase2();
  tearDown();
  
  // path 3
  setUp();
  testsPassed += method3_testCase3();
  tearDown();

  return testsPassed;
}

// path 1
uint8_t method3_testCase1(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method3() test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method3() test case 1 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// path 2
uint8_t method3_testCase2(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method3() test case 2 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method3() test case 2 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// path 3
uint8_t method3_testCase3(void) {
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  
  if (actual == expected) {
    Serial.println(F("method3() test case 3 passed."));
    testsPassed++;
  } else {
    Serial.println(F("method3() test case 3 failed."));
    Serial.print(F("Expected method1(): ")); Serial.println(expected);
    Serial.print(F("Actual method1(): ")); Serial.println(actual);
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
  
  if (testsPassed == NUM_TESTS) {
    Serial.println(F("All tests passed!"));
  } else {
    Serial.print(testsPassed); Serial.println(F(" tests passed."));
    Serial.print(testsFailed); Serial.println(F(" tests failed."));
    Serial.print(F("Success rate: ")); Serial.print( (float)(NUM_TESTS - testsFailed) / (float)NUM_TESTS * 100.0); Serial.println(F("%"));
  }
}

void loop() {
  //Should only run tests once
  //Hence, nothing should be here
}
