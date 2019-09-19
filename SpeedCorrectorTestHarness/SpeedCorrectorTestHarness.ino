/*
 * Author: Harrison Outram
 * Date: 19/09/2019
 * Version: 1.0
 * Purpose: test script for SpeedCorrector class
 * Project: Climbing Clock (2019)
 * Organisation: Curtin Robotics Club (CRoC)
 */

#include <SpeedCorrector.h>
#include <SpeedChangeFunctions.h>

SpeedCorrector *speedCorr1, *speedCorr2, *speedCorr3;

#define TEST_INITIAL_PWM 5000
#define TEST_CORRECT_TIME 1000
#define ALT_MAX_NUM_PWMS 8
#define ALT_SPEED_INC 20
#define ALT_MIN_SPEED_INC 10
#define ALT_SPEED_INC_CHANGE 2
#define NUM_TESTS 8

#define EXPECTED_DEFAULT_NUM_PWM 10
#define EXPECTED_DEFAULT_SPEED_INC 10
#define EXPECTED_MIN_SPEED_INC 5
#define EXPECTED_SPEED_INC_CHANGE 5

void setup(void) {
  Serial.begin(9600);
  uint8_t testsPassed = 0;
  testsPassed += testSuite_getCorrectedPwm();
  testsPassed += testSuite_getMeanPwn();
  outputOverallResult(testsPassed);
}

void setUp(void) {
  speedCorr1 = new SpeedCorrector(TEST_INITIAL_PWM, TEST_CORRECT_TIME);
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
  
  return testsPassed;
}

uint8_t getCorrectedPwm_testCase1(void) {
  uint8_t testsPassed = 0;
  uint16_t actualTime = 999;
  uint8_t currentPwm = 100;
  uint16_t expectedCorrPwm = 99;
  
  uint16_t actualCorrPwm1 = speedCorr1->getCorrectedPwm(actualTime, currentPwm, false);
  uint16_t actualCorrPwm2 = speedCorr2->getCorrectedPwm(actualTime, currentPwm, false);
  uint16_t actualCorrPwm3 = speedCorr3->getCorrectedPwm(actualTime, currentPwm, false);
  
  if (actualCorrPwm1 == expectedCorrPwm && actualCorrPwm2 == expectedCorrPwm
      && actualCorrPwm3 == expectedCorrPwm) {
    Serial.print("Corrected PWM test case 1 passed.\n");
    testsPassed++;
  } else
    Serial.print("Corrected PWM test case 1 failed.\n");

  return testsPassed;
}

uint8_t getCorrectedPwm_testCase2(void) {
  uint8_t testsPassed = 0;
  uint16_t actualTime = 1000, currentPwm = 100;
  uint16_t expectedCorrPwm = currentPwm;
  
  uint16_t actualCorrPwm1 = speedCorr1->getCorrectedPwm(actualTime, currentPwm, true);
  uint16_t actualCorrPwm2 = speedCorr2->getCorrectedPwm(actualTime, currentPwm, true);
  uint16_t actualCorrPwm3 = speedCorr3->getCorrectedPwm(actualTime, currentPwm, true);

  if (actualCorrPwm1 == expectedCorrPwm && actualCorrPwm2 == expectedCorrPwm
      && actualCorrPwm3 == expectedCorrPwm) {
    Serial.print("Corrected PWM test case 2 passed.\n");
    testsPassed++;
  } else
    Serial.print("Corrected PWM test case 2 failed.\n");

  return testsPassed;
}

uint8_t getCorrectedPwm_testCase3(void) {
  uint8_t testsPassed = 0, i = 0;
  bool testPassed = true;
  uint16_t actualTime = 1000;
  uint8_t currentPwm[] = {100, 200, 150};
  uint16_t expectedCorrPwm[] = {110, 205, 155};

  while (testPassed && i < 3) {
    uint16_t actualCorrPwm1 = speedCorr1->getCorrectedPwm(actualTime, currentPwm[i], false);
    
    if (actualCorrPwm1 != expectedCorrPwm[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.print("Corrected PWM test case 3 passed.\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 3 failed.\n");
  }

  return testsPassed;
}

uint8_t getCorrectedPwm_testCase4(void) {
  uint8_t testsPassed = 0, i = 0;
  bool testPassed = true;
  uint16_t actualTime = 1000;
  uint8_t currentPwm[] = {100, 200, 150};
  uint16_t expectedCorrPwm[] = {120, 210, 160};

  while (testPassed && i < 3) {
    uint16_t actualCorrPwm2 = speedCorr2->getCorrectedPwm(actualTime, currentPwm[i], false);

    if (actualCorrPwm2 != expectedCorrPwm[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.print("Corrected PWM test case 4 passed.\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 4 failed.\n");
  }

  return testsPassed;
}

uint8_t getCorrectedPwm_testCase5(void) {
  uint8_t testsPassed = 0, i = 0;
  bool testPassed = true;
  uint16_t actualTime = 1000;
  uint8_t currentPwm[] = {100, 200, 150};
  uint16_t expectedCorrPwm[] = {100, 200, 150};

  while (testPassed && i < 3) {
    uint16_t actualCorrPwm3 = speedCorr3->getCorrectedPwm(actualTime, currentPwm[i], false);

    if (actualCorrPwm3 != expectedCorrPwm[i])
      testPassed = false;
    
    i++;
  }

  if (testPassed) {
    Serial.print("Corrected PWM test case 5 passed.\n");
    testsPassed++;
  } else {
    Serial.print("Corrected PWM test case 5 failed.\n");
  }

  return testsPassed;
}

// Also tests addNewCorrected, getPwmOffset, and calcNewSpeedIncrement methods by extension
uint8_t testSuite_getMeanPwn(void) { // Also tests addNewCorrecetedPwm by necessity
  uint8_t testsPassed = 0;
  
  setUp();
  // Tests speedCorr1 methods
  testsPassed += getMeanPwm_testCase1();

  // Tests speedCorr2 methods
  testsPassed += getMeanPwm_testCase2();

  // Tests speedCorr3 methods
  testsPassed += getMeanPwm_testCase3();
  tearDown();

  return testsPassed;
}

uint8_t getMeanPwm_testCase1(void) {
  uint8_t testsPassed = 0;
  bool allTestsPassed = true;

  // When pwmArray is full
  uint16_t testPwms[] = {4000, 4500, 3200, 3400, 3300, 3900, 4555, 5500, 5200};  
  uint16_t expectedMeanPwms[] = {4500, 4500, 4175, 4020, 3900, 3900, 3981, 4150, 4255};

  // When pwmArray is not full
  uint16_t testPwms2[] = {5506, 2030, 7000, 6210, 6000};
  uint16_t expectedMeanPwms2[] = {4306, 4109, 4359, 4660, 4920};
  
  if (speedCorr1->getMeanPwm() != TEST_INITIAL_PWM)
    allTestsPassed = false;
  
  for (uint8_t i = 0; i < EXPECTED_DEFAULT_NUM_PWM - 1; i++) {
    speedCorr1->addNewCorrectedPwm(testPwms[i]);
    
    if (speedCorr1->getMeanPwm() != expectedMeanPwms[i])
      allTestsPassed = false;
  }

  for (uint8_t i = 0; i < 5; i++) {
    speedCorr1->addNewCorrectedPwm(testPwms2[i]);
    
    if (speedCorr1->getMeanPwm() != expectedMeanPwms2[i])
      allTestsPassed = false;
  }

  if (allTestsPassed) {
    Serial.print("Mean PWM test case 1 passed.\n");
    testsPassed++;
  }
  else
    Serial.print("Mean PWM test case 1 failed.\n");
  
  return testsPassed;
}

uint8_t getMeanPwm_testCase2(void) {
  uint8_t testsPassed = 0;
  bool allTestsPassed = true;

  // When pwmArray is full
  uint16_t testPwms[] = {4000, 4500, 3200, 3400, 3300, 3900, 4555};  
  uint16_t expectedMeanPwms[] = {4500, 4500, 4175, 4020, 3900, 3900, 3981};

  // When pwmArray is not full
  uint16_t testPwms2[] = {5506, 2030, 7000, 6210, 6000};
  uint16_t expectedMeanPwms2[] = {4045, 3798, 4111, 4487, 4812};
  
  if (speedCorr2->getMeanPwm() != TEST_INITIAL_PWM)
    allTestsPassed = false;
  
  for (uint8_t i = 0; i < ALT_MAX_NUM_PWMS - 1; i++) {
    speedCorr2->addNewCorrectedPwm(testPwms[i]);
    
    if (speedCorr2->getMeanPwm() != expectedMeanPwms[i])
      allTestsPassed = false;
  }

  for (uint8_t i = 0; i < 5; i++) {
    speedCorr2->addNewCorrectedPwm(testPwms2[i]);
    
    if (speedCorr2->getMeanPwm() != expectedMeanPwms2[i])
      allTestsPassed = false;
  }

  if (allTestsPassed) {
    Serial.print("Mean PWM test case 2 passed.\n");
    testsPassed++;
  }
  else
    Serial.print("Mean PWM test case 2 failed.\n");
  
  return testsPassed;
}

uint8_t getMeanPwm_testCase3(void) {
  uint8_t testsPassed = 0;
  bool allTestsPassed = true;

  // When pwmArray is full
  uint16_t testPwms[] = {4000, 4500, 3200, 3400, 3300, 3900, 4555};  
  uint16_t expectedMeanPwms[] = {4500, 4500, 4175, 4020, 3900, 3900, 3981};

  // When pwmArray is not full
  uint16_t testPwms2[] = {5506, 2030, 7000, 6210, 6000};
  uint16_t expectedMeanPwms2[] = {4045, 3798, 4111, 4487, 4812};
  
  if (speedCorr3->getMeanPwm() != TEST_INITIAL_PWM)
    allTestsPassed = false;
  
  for (uint8_t i = 0; i < ALT_MAX_NUM_PWMS - 1; i++) {
    speedCorr3->addNewCorrectedPwm(testPwms[i]);
    
    if (speedCorr3->getMeanPwm() != expectedMeanPwms[i])
      allTestsPassed = false;
  }

  for (uint8_t i = 0; i < 5; i++) {
    speedCorr3->addNewCorrectedPwm(testPwms2[i]);
    
    if (speedCorr3->getMeanPwm() != expectedMeanPwms2[i])
      allTestsPassed = false;
  }

  if (allTestsPassed) {
    Serial.print("Mean PWM test case 3 passed.\n");
    testsPassed++;
  }
  else
    Serial.print("Mean PWM test case 3 failed.\n");
  
  return testsPassed;
}

void outputOverallResult(uint8_t testsPassed) {
  uint8_t testsFailed = NUM_TESTS - testsPassed;

  Serial.print("\n=========================\n");
  Serial.print(NUM_TESTS);
  Serial.print(" tests performed\n");
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
