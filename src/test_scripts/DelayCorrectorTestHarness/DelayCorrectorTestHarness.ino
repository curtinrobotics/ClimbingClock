/*!
 * @author Harrison Outram
 * Last Updated: 14/05/2020 (d/m/y UTC+08:00)
 * @version 1.0
 * @brief test script for DelayCorrector class
 * Project: Climbing Clock (2019-20)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: Tested and working
 */

#include <DelayCorrector.h>
#include <BiasChangeFunctions.h>

DelayCorrector *delayCorr1, *delayCorr2, *delayCorr3;

#define TEST_INITIAL_DELAY 200
#define TEST_CORRECT_TIME 10000UL
#define ALT_MAX_NUM_DELAYS 4
#define ALT_DELAY_DEC -20
#define ALT_MIN_DELAY_DEC -5
#define ALT_DELAY_DEC_CHANGE -2

#define EXPECTED_DEFAULT_NUM_DELAY 8
#define EXPECTED_DEFAULT_DELAY_DEC -10
#define EXPECTED_MIN_DELAY_DEC -1
#define EXPECTED_DELAY_DEC_CHANGE -3

#define NUM_TESTS 8

void setup(void) {
  Serial.begin(9600);
  uint8_t testsPassed = 0;
  testsPassed += testSuite_getCorrectedDelay();
  testsPassed += testSuite_addNewCorrectedDelay();
  outputOverallResult(testsPassed);
}

void setUp(void) {
  delayCorr1 = new DelayCorrector(TEST_INITIAL_DELAY, TEST_CORRECT_TIME,
                                  &linearChange);
  delayCorr2 = new DelayCorrector(TEST_INITIAL_DELAY, TEST_CORRECT_TIME, 3, ALT_DELAY_DEC,
                                  ALT_MIN_DELAY_DEC, &exponentialChange, ALT_DELAY_DEC_CHANGE);
  delayCorr3 = new DelayCorrector(TEST_INITIAL_DELAY, TEST_CORRECT_TIME, 4, ALT_DELAY_DEC,
                                  ALT_MIN_DELAY_DEC, &noChange, 255);
}

void tearDown(void) {
  delete delayCorr1;
  delete delayCorr2;
  delete delayCorr3;
}

uint8_t testSuite_getCorrectedDelay(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += getCorrectedDelay_testCase1();
  tearDown();

  setUp();
  testsPassed += getCorrectedDelay_testCase2();
  tearDown();

  setUp();
  testsPassed += getCorrectedDelay_testCase3();
  testsPassed += getCorrectedDelay_testCase4();
  testsPassed += getCorrectedDelay_testCase5();
  tearDown();

  return testsPassed;
}

// When correctTime > actualTime
uint8_t getCorrectedDelay_testCase1(void) {
  uint8_t testsPassed = 0;
  uint16_t actualTime = TEST_CORRECT_TIME / 2;
  uint32_t expectedCorrDelay = 400UL;
  
  uint32_t actualCorrDelay1 = delayCorr1->getCorrectedDelay(actualTime, false);
  uint32_t actualCorrDelay2 = delayCorr2->getCorrectedDelay(actualTime, false);
  uint32_t actualCorrDelay3 = delayCorr3->getCorrectedDelay(actualTime, false);
  
  if (actualCorrDelay1 == expectedCorrDelay && actualCorrDelay2 == expectedCorrDelay
      && actualCorrDelay3 == expectedCorrDelay) {
    Serial.println(F("Corrected Delay test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("Corrected Delay test case 1 failed."));
    Serial.print(F("Expected corrected Delay: ")); Serial.println(expectedCorrDelay);
    Serial.println(F("Actual corrected Delay 1: ")); Serial.println(actualCorrDelay1);
    Serial.println(F("Actual corrected Delay 2: ")); Serial.println(actualCorrDelay2);
    Serial.println(F("Actual corrected Delay 3: ")); Serial.println(actualCorrDelay3);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

// When correctTime <= actualTime and topReached is true
uint8_t getCorrectedDelay_testCase2(void) {
  uint8_t testsPassed = 0;
  uint16_t actualTime = TEST_CORRECT_TIME;
  uint32_t expectedCorrDelay = TEST_INITIAL_DELAY;
  
  uint32_t actualCorrDelay1 = delayCorr1->getCorrectedDelay(actualTime, true);
  uint32_t actualCorrDelay2 = delayCorr2->getCorrectedDelay(actualTime, true);
  uint32_t actualCorrDelay3 = delayCorr3->getCorrectedDelay(actualTime, true);

  if (actualCorrDelay1 == expectedCorrDelay && actualCorrDelay2 == expectedCorrDelay
      && actualCorrDelay3 == expectedCorrDelay) {
    Serial.println(F("Corrected Delay test case 2 passed."));
    testsPassed++;
  } else {
    Serial.println(F("Corrected Delay test case 2 failed."));
    Serial.print(F("Expected corrected Delay : ")); Serial.println(expectedCorrDelay);
    Serial.print(F("Actual corrected Delay 1: ")); Serial.println(actualCorrDelay1);
    Serial.print(F("Actual corrected Delay 2: ")); Serial.println(actualCorrDelay2);
    Serial.print(F("Actual corrected Delay 3: ")); Serial.println(actualCorrDelay3);
  }
  Serial.println(F(""));

  return testsPassed;
}

// When correctTime <= actualTime and topReached is false for linearChange()
uint8_t getCorrectedDelay_testCase3(void) {
  uint8_t testsPassed = 0, i;
  bool testPassed = true;
  uint32_t actualTime = TEST_CORRECT_TIME;
  uint32_t expectedDelays[4];
  uint32_t actualDelay;
  int8_t currDelayDec = EXPECTED_DEFAULT_DELAY_DEC;

  for (i = 0; i < 4; i++) {
    expectedDelays[i] = TEST_INITIAL_DELAY + currDelayDec;
    if (currDelayDec - EXPECTED_DELAY_DEC_CHANGE <= EXPECTED_MIN_DELAY_DEC)
      currDelayDec -= EXPECTED_DELAY_DEC_CHANGE;
    else
      currDelayDec = EXPECTED_MIN_DELAY_DEC;
  }
  
  i = 0;
  while (testPassed && i < 4) {
    actualDelay = delayCorr1->getCorrectedDelay(actualTime, false);
    
    if (actualDelay != expectedDelays[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.println(F("Corrected Delay test case 3 passed."));
    testsPassed++;
  } else {
    Serial.println(F("Corrected Delay test case 3 failed."));
    Serial.print(F("Expected corrected Delay: ")); Serial.println(expectedDelays[i - 1]);
    Serial.print(F("Actual corrected Delay: ")); Serial.println(actualDelay);
    Serial.print(F("Index: ")); Serial.println(i - 1);
  }
  Serial.println(F(""));

  return testsPassed;
}

// When correctTime <= actualTime and topReached is false for exponentialChange()
uint8_t getCorrectedDelay_testCase4(void) {
  uint8_t testsPassed = 0, i;
  bool testPassed = true;
  uint32_t actualTime = TEST_CORRECT_TIME;
  uint32_t expectedDelays[] = {0, 0, 0};
  uint32_t actualDelay;
  int8_t currDelayDec = ALT_DELAY_DEC;
  
  for (i = 0; i < 3; i++) {
    expectedDelays[i] = TEST_INITIAL_DELAY + currDelayDec;
    if (currDelayDec / ALT_DELAY_DEC_CHANGE >= ALT_MIN_DELAY_DEC)
      currDelayDec /= ALT_DELAY_DEC_CHANGE;
    else
      currDelayDec = ALT_MIN_DELAY_DEC;
  }

  i = 0;
  while (testPassed && i < 3) {
    actualDelay = delayCorr2->getCorrectedDelay(actualTime, false);

    if (actualDelay != expectedDelays[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.println(F("Corrected Delay test case 4 passed."));
    testsPassed++;
  } else {
    Serial.println(F("Corrected Delay test case 4 failed."));
    Serial.print(F("Expected corrected Delay: ")); Serial.println(expectedDelays[i - 1]);
    Serial.print(F("Actual corrected Delay: ")); Serial.println(actualDelay);
    Serial.print(F("Index: ")); Serial.println(i - 1);
  }
  Serial.println(F(""));

  return testsPassed;
}

// When correctTime <= actualTime and topReached is false for noChange()
uint8_t getCorrectedDelay_testCase5(void) {
  uint8_t testsPassed = 0, i;
  bool testPassed = true;
  uint32_t actualTime = TEST_CORRECT_TIME;
  uint32_t expectedDelays[3];
  uint32_t actualDelay;

  for (i = 0; i < 3; i++)
    expectedDelays[i] = TEST_INITIAL_DELAY + ALT_DELAY_DEC;

  i = 0;
  while (testPassed && i < 3) {
    actualDelay = delayCorr3->getCorrectedDelay(actualTime, false);

    if (actualDelay != expectedDelays[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.println(F("Corrected Delay test case 5 passed."));
    testsPassed++;
  } else {
    Serial.println(F("Corrected Delay test case 5 failed."));
    Serial.print(F("Expected corrected Delay: ")); Serial.println(expectedDelays[i - 1]);
    Serial.println(F("Actual corrected Delay: ")); Serial.println(actualDelay);
    Serial.println(F("Index: ")); Serial.println(i - 1);
  }
  Serial.println(F(""));

  return testsPassed;
}

// Also tests getCurrentDelay(), getMeanDelay(), and getDelayOffset() methods by extension
uint8_t testSuite_addNewCorrectedDelay(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  // Tests delayCorr1 methods
  testsPassed += addNewCorrectedDelay_testCase1();

  // Tests delayCorr2 methods
  testsPassed += addNewCorrectedDelay_testCase2();

  // Tests delayCorr3 methods
  testsPassed += addNewCorrectedDelay_testCase3();
  tearDown();

  return testsPassed;
}

uint8_t addNewCorrectedDelay_testCase1(void) {
  uint8_t testsPassed = 0;
  bool initialDelayTestPassed = true, allTestsPassed_notFull = true, allTestsPassed_full = true;
  uint8_t i = 0;
  uint32_t actualDelay;

  // Row 1 for when delay array is not full
  // Row 2 for when delay array is full
  uint32_t testDelays[2][7] = { {100, 102, 50, 150, 250, 205, 180},
                             {109} };
  uint32_t expectedDelays[2][7] = { {150, 134, 113, 120, 142, 151, 154},
                                 {143} };
  
  if (delayCorr1->getCurrentDelay() != TEST_INITIAL_DELAY) {
    allTestsPassed_notFull = false;
    initialDelayTestPassed = false;
  }
  
  while (i < EXPECTED_DEFAULT_NUM_DELAY - 1 && allTestsPassed_notFull) {
    delayCorr1->addNewCorrectedDelay(testDelays[0][i]);
    actualDelay = delayCorr1->getCurrentDelay();
    
    if (actualDelay != expectedDelays[0][i])
      allTestsPassed_notFull = false;
    
    i++;
  }

  if (allTestsPassed_notFull) {
    i = 0;
  
    while (i < 1 && allTestsPassed_full) {
      delayCorr1->addNewCorrectedDelay(testDelays[1][i]);
      actualDelay = delayCorr1->getCurrentDelay();
      
      if (actualDelay != expectedDelays[1][i])
        allTestsPassed_full = false;
      
      i++;
    }
  }

  if (allTestsPassed_notFull && allTestsPassed_full) {
    Serial.println(F("Add new Delay test case 1 passed."));
    testsPassed++;
  } else {
    Serial.println(F("Add new Delay test case 1 failed."));
    if (!initialDelayTestPassed) {
      Serial.println(F("Initial Delay failed"));
      Serial.print(F("Expected: ")); Serial.println(TEST_INITIAL_DELAY);
      Serial.print(F("Actual: ")); Serial.println(actualDelay);
    }
    else if (!allTestsPassed_notFull) {
      Serial.print(F("Expected current Delay before being full: ")); Serial.println(expectedDelays[0][i - 1]);
      Serial.print(F("Actual Delay: ")); Serial.println(actualDelay);
    } else {
      Serial.print(F("Expected current Delay after being full: ")); Serial.println(expectedDelays[1][i - 1]);
      Serial.print(F("Actual Delay: ")); Serial.println(actualDelay);
    }
    Serial.print(F("Index: ")); Serial.println(i - 1);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t addNewCorrectedDelay_testCase2(void) {
  uint8_t testsPassed = 0, i;
  bool initialDelayTestPassed = true, allTestsPassed_notFull = true, allTestsPassed_full = true;
  uint32_t actualDelay;

  // Row 1 for when pwmArray is not full
  // Row 2 for when pwmArray is full
  uint32_t testDelays[2][3] = { {150, 200, 199},
                                {230} };  
  uint32_t expectedDelays[2][3] = { {175, 183, 187},
                                    {194} };
  
  if (delayCorr2->getCurrentDelay() != TEST_INITIAL_DELAY) {
    allTestsPassed_notFull = false;
    initialDelayTestPassed = false;
  }
  
  while (i < ALT_MAX_NUM_DELAYS - 1 && allTestsPassed_notFull) {
    delayCorr2->addNewCorrectedDelay(testDelays[0][i]);
    actualDelay = delayCorr2->getCurrentDelay();
    
    if (actualDelay != expectedDelays[0][i])
      allTestsPassed_notFull = false;

    i++;
  }

  if (allTestsPassed_notFull) {
    i = 0;
    while (i < 1 && allTestsPassed_full) {
      delayCorr2->addNewCorrectedDelay(testDelays[1][i]);
      actualDelay = delayCorr2->getCurrentDelay();
      
      if (actualDelay != expectedDelays[1][i])
        allTestsPassed_full = false;

      i++;
    }
  }

  if (allTestsPassed_notFull && allTestsPassed_full) {
    Serial.println(F("Add new Delay test case 2 passed."));
    testsPassed++;
  } else {
    Serial.println(F("Add new Delay test case 2 failed."));
    if (!initialDelayTestPassed) {
      Serial.println(F("Initial Delay failed"));
      Serial.print(F("Expected: ")); Serial.println(TEST_INITIAL_DELAY);
      Serial.print("Actual: "); Serial.println(actualDelay);
    }
    else if (!allTestsPassed_notFull) {
      Serial.print(F("Expected Delay before being full: ")); Serial.println(expectedDelays[0][i - 1]);
      Serial.print(F("Actual Delay: ")); Serial.println(actualDelay);
    } else {
      Serial.print(F("Expected Delay after being full: ")); Serial.println(expectedDelays[1][i - 1]);
      Serial.print(F("Actual Delay: ")); Serial.println(actualDelay);
    }
    Serial.print(F("Index: ")); Serial.println(i - 1);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

uint8_t addNewCorrectedDelay_testCase3(void) {
  uint8_t testsPassed = 0, i = 0;
  bool initialDelayTestPassed = true, allTestsPassed_notFull = true, allTestsPassed_full = true;
  uint32_t actualDelay;

  // Row 1 for when pwmArray is not full
  // Row 2 for when pwmArray is full
  uint32_t testDelays[2][3] = { {200, 210, 190},
                                {205} };
  uint32_t expectedDelays[2][3] = { {200, 203, 200},
                                    {201} };
  
  if (delayCorr3->getCurrentDelay() != TEST_INITIAL_DELAY) {
    allTestsPassed_notFull = false;
    initialDelayTestPassed = false;
  }
  
  while (i < ALT_MAX_NUM_DELAYS - 1 && allTestsPassed_notFull) {
    delayCorr3->addNewCorrectedDelay(testDelays[0][i]);
    actualDelay = delayCorr3->getCurrentDelay();
    
    if (actualDelay != expectedDelays[0][i])
      allTestsPassed_notFull = false;

    i++;
  }

  if (allTestsPassed_notFull) {
    i = 0;
    
    while (i < 1 && allTestsPassed_full) {
      delayCorr3->addNewCorrectedDelay(testDelays[1][i]);
      actualDelay = delayCorr3->getCurrentDelay();
      
      if (actualDelay != expectedDelays[1][i])
        allTestsPassed_full = false;

      i++;
    }
  }

  if (allTestsPassed_notFull && allTestsPassed_full) {
    Serial.println(F("Add new Delay test case 3 passed."));
    testsPassed++;
  } else {
    Serial.println(F("Add me Delay test case 3 failed."));
    if (!initialDelayTestPassed) {
      Serial.println(F("Initial Delay failed"));
      Serial.print(F("Expected: ")); Serial.println(TEST_INITIAL_DELAY);
      Serial.print(F("Actual: ")); Serial.println(actualDelay);
    }
    else if (!allTestsPassed_notFull) {
      Serial.print(F("Expected Delay before being full: ")); Serial.println(expectedDelays[0][i - 1]);
      Serial.print(F("Actual Delay: ")); Serial.println(actualDelay);
    } else {
      Serial.print(F("Expected Delay after being full: ")); Serial.println(expectedDelays[1][i - 1]);
      Serial.print(F("Actual Delay: ")); Serial.println(actualDelay);
    }
    Serial.println(F("Index: ")); Serial.println(i - 1);
  }
  Serial.println(F(""));
  
  return testsPassed;
}

void outputOverallResult(uint8_t testsPassed) {
  uint8_t testsFailed = NUM_TESTS - testsPassed;

  Serial.println(F("====================================="));
  Serial.print(NUM_TESTS); Serial.println(F(" tests performed"));
  Serial.println(F("====================================="));
  
  if (testsPassed == NUM_TESTS)
    Serial.println(F("All tests passed!"));
  else {
    Serial.print(testsPassed); Serial.println(F(" tests passed."));
    Serial.print(testsFailed); Serial.println(F(" tests failed."));
  }
}

void loop() {
  //Should only run tests once
  //Hence, nothing should be here
}
