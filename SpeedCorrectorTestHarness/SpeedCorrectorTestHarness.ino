/*
 * @author Harrison Outram
 * Last Updated: 13/12/2019 (d/m/y UTC+08:00)
 * @version 1.4
 * @brief test script for SpeedCorrector class
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 * Working status: all test cases pass
 */

#include <SpeedCorrector.h>
#include <SpeedChangeFunctions.h>

SpeedCorrector *speedCorr1, *speedCorr2, *speedCorr3;

#define TEST_INITIAL_PWM 200
#define TEST_CORRECT_TIME 10000
#define ALT_MAX_NUM_PWMS 8
#define ALT_SPEED_INC 20
#define ALT_MIN_SPEED_INC 10
#define ALT_SPEED_INC_CHANGE 2

#define EXPECTED_DEFAULT_NUM_PWM 10
#define EXPECTED_DEFAULT_SPEED_INC 10
#define EXPECTED_MIN_SPEED_INC 1
#define EXPECTED_SPEED_INC_CHANGE 3
#define EXPECTED_MAX_PWM 255

#define NUM_TESTS 9

void setup(void) {
  Serial.begin(9600);
  uint8_t testsPassed = 0;
  testsPassed += testSuite_getCorrectedPwm();
  testsPassed += testSuite_addNewCorrectedPwm();
  outputOverallResult(testsPassed);
}

void setUp(void) {
  speedCorr1 = new SpeedCorrector(TEST_INITIAL_PWM, TEST_CORRECT_TIME, &(SpeedChangeFunctions::linearChange));
  speedCorr2 = new SpeedCorrector(TEST_INITIAL_PWM, TEST_CORRECT_TIME, ALT_MAX_NUM_PWMS, ALT_SPEED_INC,
                                  ALT_MIN_SPEED_INC, &(SpeedChangeFunctions::exponentialChange), ALT_SPEED_INC_CHANGE);
  speedCorr3 = new SpeedCorrector(TEST_INITIAL_PWM, TEST_CORRECT_TIME, ALT_MAX_NUM_PWMS, ALT_SPEED_INC,
                                  ALT_MIN_SPEED_INC, &(SpeedChangeFunctions::noChange), 255);
}

void tearDown(void) {
  delete speedCorr1;
  delete speedCorr2;
  delete speedCorr3;
}

uint8_t testSuite_getCorrectedPwm(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  testsPassed += getCorrectedPwm_testCase1();
  tearDown();

  setUp();
  testsPassed += getCorrectedPwm_testCase2();
  tearDown();

  setUp();
  testsPassed += getCorrectedPwm_testCase3();
  testsPassed += getCorrectedPwm_testCase4();
  testsPassed += getCorrectedPwm_testCase5();
  tearDown();

  testsPassed += getCorrectedPwm_testCase6();
  
  return testsPassed;
}

// When correctTime > actualTime
uint8_t getCorrectedPwm_testCase1(void) {
  uint8_t testsPassed = 0;
  uint16_t actualTime = TEST_CORRECT_TIME / 2;
  uint8_t expectedCorrPwm = 100;
  
  uint8_t actualCorrPwm1 = speedCorr1->getCorrectedPwm(actualTime, false);
  uint8_t actualCorrPwm2 = speedCorr2->getCorrectedPwm(actualTime, false);
  uint8_t actualCorrPwm3 = speedCorr3->getCorrectedPwm(actualTime, false);
  
  if (actualCorrPwm1 == expectedCorrPwm && actualCorrPwm2 == expectedCorrPwm
      && actualCorrPwm3 == expectedCorrPwm) {
    Serial.print("Corrected PWM test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 1 failed.\n");
    Serial.print("Expected corrected PWM: "); Serial.print(expectedCorrPwm);
    Serial.print(", actual corrected PWM 1: "); Serial.print(actualCorrPwm1);
    Serial.print(", actual corrected PWM 2: "); Serial.print(actualCorrPwm2);
    Serial.print(", actual corrected PWM 3: "); Serial.print(actualCorrPwm3);
    Serial.print("\n\n");
  }
  
  return testsPassed;
}

// When correctTime <= actualTime and topReached is true
uint8_t getCorrectedPwm_testCase2(void) {
  uint8_t testsPassed = 0;
  uint16_t actualTime = TEST_CORRECT_TIME - 1;
  uint8_t expectedCorrPwm = TEST_INITIAL_PWM;
  
  uint8_t actualCorrPwm1 = speedCorr1->getCorrectedPwm(actualTime, true);
  uint8_t actualCorrPwm2 = speedCorr2->getCorrectedPwm(actualTime, true);
  uint8_t actualCorrPwm3 = speedCorr3->getCorrectedPwm(actualTime, true);

  if (actualCorrPwm1 == expectedCorrPwm && actualCorrPwm2 == expectedCorrPwm
      && actualCorrPwm3 == expectedCorrPwm) {
    Serial.print("Corrected PWM test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 1 failed.\n");
    Serial.print("Expected corrected PWM : "); Serial.print(expectedCorrPwm);
    Serial.print(", actual corrected PWM 1: "); Serial.print(actualCorrPwm1);
    Serial.print(", actual corrected PWM 2: "); Serial.print(actualCorrPwm2);
    Serial.print(", actual corrected PWM 3: "); Serial.print(actualCorrPwm3);
    Serial.print("\n\n");
  }

  return testsPassed;
}

// When correctTime <= actualTime and topReached is false for linearChange()
uint8_t getCorrectedPwm_testCase3(void) {
  uint8_t testsPassed = 0, i;
  bool testPassed = true;
  uint16_t actualTime = TEST_CORRECT_TIME;
  uint8_t expectedPwms[5];
  uint8_t actualPwm;
  uint8_t currSpeedInc = EXPECTED_DEFAULT_SPEED_INC;

  for (i = 0; i < 5; i++) {
    expectedPwms[i] = TEST_INITIAL_PWM + currSpeedInc;
    if (currSpeedInc - EXPECTED_SPEED_INC_CHANGE >= EXPECTED_MIN_SPEED_INC)
      currSpeedInc -= EXPECTED_SPEED_INC_CHANGE;
    else
      currSpeedInc = EXPECTED_MIN_SPEED_INC;
  }
    
  i = 0;
  while (testPassed && i < 5) {
    actualPwm = speedCorr1->getCorrectedPwm(actualTime, false);
    
    if (actualPwm != expectedPwms[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.print("Corrected PWM test case 3 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 3 failed.\n");
    Serial.print("Expected corrected PWM: "); Serial.print(expectedPwms[i - 1]);
    Serial.print(", actual corrected PWM: "); Serial.print(actualPwm);
    Serial.print(", index: "); Serial.print(i - 1);
    Serial.print("\n\n");
  }

  return testsPassed;
}

// When correctTime <= actualTime and topReached is false for exponentialChange()
uint8_t getCorrectedPwm_testCase4(void) {
  uint8_t testsPassed = 0, i;
  bool testPassed = true;
  uint16_t actualTime = TEST_CORRECT_TIME;
  uint8_t expectedPwms[] = {0, 0, 0};
  uint8_t actualPwm;
  uint8_t currSpeedInc = ALT_SPEED_INC;

  for (i = 0; i < 3; i++) {
    expectedPwms[i] = TEST_INITIAL_PWM + currSpeedInc;
    if (currSpeedInc / ALT_SPEED_INC_CHANGE >= ALT_MIN_SPEED_INC)
      currSpeedInc /= ALT_SPEED_INC_CHANGE;
    else
      currSpeedInc = ALT_MIN_SPEED_INC;
  }

  i = 0;
  while (testPassed && i < 3) {
    actualPwm = speedCorr2->getCorrectedPwm(actualTime, false);

    if (actualPwm != expectedPwms[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.print("Corrected PWM test case 4 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 4 failed.\n");
    Serial.print("Expected corrected PWM: "); Serial.print(expectedPwms[i - 1]);
    Serial.print(", actual corrected PWM: "); Serial.print(actualPwm);
    Serial.print(", index: "); Serial.print(i - 1);
    Serial.print("\n\n");
  }

  return testsPassed;
}

// When correctTime <= actualTime and topReached is false for noChange()
uint8_t getCorrectedPwm_testCase5(void) {
  uint8_t testsPassed = 0, i;
  bool testPassed = true;
  uint16_t actualTime = TEST_CORRECT_TIME;
  uint16_t expectedPwms[3];
  uint16_t actualPwm;

  for (i = 0; i < 3; i++) {
    expectedPwms[i] = TEST_INITIAL_PWM + ALT_SPEED_INC;
  }

  i = 0;
  while (testPassed && i < 3) {
    actualPwm = speedCorr3->getCorrectedPwm(actualTime, false);

    if (actualPwm != expectedPwms[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.print("Corrected PWM test case 5 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 5 failed.\n");
    Serial.print("Expected corrected PWM: "); Serial.print(expectedPwms[i - 1]);
    Serial.print(", actual corrected PWM: "); Serial.print(actualPwm);
    Serial.print(", index: "); Serial.print(i - 1);
    Serial.print("\n\n");
  }

  return testsPassed;
}

uint8_t getCorrectedPwm_testCase6(void) {
  uint8_t testsPassed = 0;
  uint8_t expected, actual;
  SpeedCorrector speedCorr = SpeedCorrector(EXPECTED_MAX_PWM, TEST_CORRECT_TIME,
                                            &(SpeedChangeFunctions::linearChange));

  actual = speedCorr.getCorrectedPwm(TEST_CORRECT_TIME, false);
  expected = EXPECTED_MAX_PWM;

  if (actual == expected) {
    Serial.print("Corrected PWM test case 6 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 5 failed.\n");
    Serial.print("Expected corrected PWM: "); Serial.print(expected);
    Serial.print(", actual corrected PWM: "); Serial.print(actual);
    Serial.print("\n\n");
  }

  return testsPassed;
}

// Also tests getCurrentPwm(), getMeanPwm(), and getPwmOffset() methods by extension
uint8_t testSuite_addNewCorrectedPwm(void) {
  uint8_t testsPassed = 0;
  
  setUp();
  // Tests speedCorr1 methods
  testsPassed += addNewCorrectedPwm_testCase1();

  // Tests speedCorr2 methods
  testsPassed += addNewCorrectedPwm_testCase2();

  // Tests speedCorr3 methods
  testsPassed += addNewCorrectedPwm_testCase3();
  tearDown();

  return testsPassed;
}

// 
uint8_t addNewCorrectedPwm_testCase1(void) {
  uint8_t testsPassed = 0;
  bool initialPwmTestPassed = true, allTestsPassed_notFull = true, allTestsPassed_full = true;
  uint8_t i = 0;
  uint8_t actualPwm;

  // Row 1 for when pwmArray is not full
  // Row 2 for when pwmArray is full
  uint8_t testPwms[2][9] = { {100, 102, 50, 150, 250, 205, 180, 190, 80},
                             {109, 129, 177, 230, 200} };  
  uint8_t expectedPwms[2][9] = { {150, 134, 113, 120, 142, 151, 154, 158, 150},
                                 {141, 144, 152, 170, 175} };
  
  if (speedCorr1->getCurrentPwm() != TEST_INITIAL_PWM) {
    allTestsPassed_notFull = false;
    initialPwmTestPassed = false;
  }
  
  while (i < EXPECTED_DEFAULT_NUM_PWM - 1 && allTestsPassed_notFull) {
    speedCorr1->addNewCorrectedPwm(testPwms[0][i]);
    actualPwm = speedCorr1->getCurrentPwm();
    
    if (actualPwm != expectedPwms[0][i])
      allTestsPassed_notFull = false;
    
    i++;
  }

  if (allTestsPassed_notFull) {
    i = 0;
  
    while (i < 5 && allTestsPassed_full) {
      speedCorr1->addNewCorrectedPwm(testPwms[1][i]);
      actualPwm = speedCorr1->getCurrentPwm();
      
      if (actualPwm != expectedPwms[1][i])
        allTestsPassed_full = false;
      
      i++;
    }
  }

  if (allTestsPassed_notFull && allTestsPassed_full) {
    Serial.print("Add new PWM test case 1 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Add new PWM test case 1 failed.\n");
    if (!initialPwmTestPassed) {
      Serial.print("Initial PWM failed\n");
      Serial.print("Expected: "); Serial.print(TEST_INITIAL_PWM);
      Serial.print(", actual: "); Serial.print(actualPwm);
    }
    else if (!allTestsPassed_notFull) {
      Serial.print("Expected current PWM before being full: "); Serial.print(expectedPwms[0][i - 1]);
      Serial.print(", actual PWM: "); Serial.print(actualPwm);
    } else {
      Serial.print("Expected current PWM after being full: "); Serial.print(expectedPwms[1][i - 1]);
      Serial.print(", actual PWM: "); Serial.print(actualPwm);
    }
    Serial.print(", index: "); Serial.print(i - 1);
    Serial.print("\n\n");
  }
  
  return testsPassed;
}

uint8_t addNewCorrectedPwm_testCase2(void) {
  uint8_t testsPassed = 0, i;
  bool initialPwmTestPassed = true, allTestsPassed_notFull = true, allTestsPassed_full = true;
  uint16_t actualPwm;

  // Row 1 for when pwmArray is not full
  // Row 2 for when pwmArray is full
  uint8_t testPwms[2][7] = { {150, 200, 199, 180, 111, 110, 132},
                             {230, 240, 167, 123, 143} };  
  uint8_t expectedPwms[2][7] = { {175, 183, 187, 185, 173, 164, 160},
                                 {164, 175, 171, 161, 157} };
  
  if (speedCorr2->getCurrentPwm() != TEST_INITIAL_PWM) {
    allTestsPassed_notFull = false;
    initialPwmTestPassed = false;
  }
  
  while (i < ALT_MAX_NUM_PWMS - 1 && allTestsPassed_notFull) {
    speedCorr2->addNewCorrectedPwm(testPwms[0][i]);
    actualPwm = speedCorr2->getCurrentPwm();
    
    if (actualPwm != expectedPwms[0][i])
      allTestsPassed_notFull = false;

    i++;
  }

  if (allTestsPassed_notFull) {
    i = 0;
    while (i < 5 && allTestsPassed_full) {
      speedCorr2->addNewCorrectedPwm(testPwms[1][i]);
      actualPwm = speedCorr2->getCurrentPwm();
      
      if (actualPwm != expectedPwms[1][i])
        allTestsPassed_full = false;

      i++;
    }
  }

  if (allTestsPassed_notFull && allTestsPassed_full) {
    Serial.print("Add new PWM test case 2 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Add new PWM test case 2 failed.\n");
    if (!initialPwmTestPassed) {
      Serial.print("Initial PWM failed\n");
      Serial.print("Expected: "); Serial.print(TEST_INITIAL_PWM);
      Serial.print(", actual: "); Serial.print(actualPwm);
    }
    else if (!allTestsPassed_notFull) {
      Serial.print("Expected PWM before being full: "); Serial.print(expectedPwms[0][i - 1]);
      Serial.print(", actual PWM: "); Serial.print(actualPwm);
    } else {
      Serial.print("Expected PWM after being full: "); Serial.print(expectedPwms[1][i - 1]);
      Serial.print(", actual PWM: "); Serial.print(actualPwm);
    }
    Serial.print(", index: "); Serial.print(i - 1);
    Serial.print("\n\n");
  }
  
  return testsPassed;
}

uint8_t addNewCorrectedPwm_testCase3(void) {
  uint8_t testsPassed = 0, i = 0;
  bool initialPwmTestPassed = true, allTestsPassed_notFull = true, allTestsPassed_full = true;
  uint8_t actualPwm;

  // Row 1 for when pwmArray is not full
  // Row 2 for when pwmArray is full
  uint8_t testPwms[2][7] = { {200, 210, 190, 180, 150, 160, 175},
                             {205, 202, 188, 199, 192} };
  uint8_t expectedPwms[2][7] = { {200, 203, 200, 196, 188, 184, 183},
                                 {183, 184, 181, 182, 183} };
  
  if (speedCorr3->getCurrentPwm() != TEST_INITIAL_PWM) {
    allTestsPassed_notFull = false;
    initialPwmTestPassed = false;
  }
  
  while (i < ALT_MAX_NUM_PWMS - 1 && allTestsPassed_notFull) {
    speedCorr3->addNewCorrectedPwm(testPwms[0][i]);
    actualPwm = speedCorr3->getCurrentPwm();
    
    if (actualPwm != expectedPwms[0][i])
      allTestsPassed_notFull = false;

    i++;
  }

  if (allTestsPassed_notFull) {
    i = 0;
    
    while (i < 5 && allTestsPassed_full) {
      speedCorr3->addNewCorrectedPwm(testPwms[1][i]);
      actualPwm = speedCorr3->getCurrentPwm();
      
      if (actualPwm != expectedPwms[1][i])
        allTestsPassed_full = false;

      i++;
    }
  }

  if (allTestsPassed_notFull && allTestsPassed_full) {
    Serial.print("Add new PWM test case 3 passed.\n\n");
    testsPassed++;
  } else {
    Serial.print("Add me PWM test case 3 failed.\n");
    if (!initialPwmTestPassed) {
      Serial.print("Initial PWM failed\n");
      Serial.print("Expected: "); Serial.print(TEST_INITIAL_PWM);
      Serial.print(", actual: "); Serial.print(actualPwm);
    }
    else if (!allTestsPassed_notFull) {
      Serial.print("Expected PWM before being full: "); Serial.print(expectedPwms[0][i - 1]);
      Serial.print(", actual PWM: "); Serial.print(actualPwm);
    } else {
      Serial.print("Expected PWM after being full: "); Serial.print(expectedPwms[1][i - 1]);
      Serial.print(", actual PWM: "); Serial.print(actualPwm);
    }
    Serial.print(", index: "); Serial.print(i - 1);
    Serial.print("\n\n");
  }
  
  return testsPassed;
}

void outputOverallResult(uint8_t testsPassed) {
  uint8_t testsFailed = NUM_TESTS - testsPassed;

  Serial.print("=========================\n");
  Serial.print(NUM_TESTS); Serial.print(" tests performed\n");
  Serial.print("=========================\n");
  
  if (testsPassed == NUM_TESTS)
    Serial.print("All tests passed!\n");
  else
  {
    Serial.print(testsPassed);
    Serial.print(" tests passed.\n");
    Serial.print(testsFailed);
    Serial.print(" tests failed.\n");
  }
    
}

void loop() {
  //Should only run tests once
  //Hence, nothing should be here
}
