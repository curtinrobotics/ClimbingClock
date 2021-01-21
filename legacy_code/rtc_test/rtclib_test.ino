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
#include "RTClib_CRoC.h"

// total number of tests
#define NUM_TESTS 31

//global variables needed
RTC_DS1307_Wrapper rtc;
DateTimeWrapper startTime;

void setup(void)
{
  Serial.begin(9600);
  while (!Serial) {} // wait for Serial monitor to be ready

  // device initialisation here
  rtc.begin();
  rtc.adjust(DateTimeWrapper(F(__DATE__), F(__TIME__)));
  startTime = rtc.now();

  uint8_t testsPassed = 0;

  testsPassed += testSuite_lessThan();
  testsPassed += testSuite_moreThan();
  testsPassed += testSuite_equals();

  outputOverallResult(testsPassed);
}

// used to set up global variables for next test case
void setUp(void)
{
}

// deletes global variables after test case done
void tearDown(void)
{
}

// test less than operator
uint8_t testSuite_lessThan(void)
{
  uint8_t testsPassed = 0;

  testsPassed += lessThan_testCase1();
  testsPassed += lessThan_testCase2();
  testsPassed += lessThan_testCase3();
  testsPassed += lessThan_testCase4();
  testsPassed += lessThan_testCase5();
  testsPassed += lessThan_testCase6();
  testsPassed += lessThan_testCase7();
  testsPassed += lessThan_testCase8();
  testsPassed += lessThan_testCase9();
  testsPassed += lessThan_testCase10();
  testsPassed += lessThan_testCase11();
  testsPassed += lessThan_testCase12();

  return testsPassed;
}

uint8_t lessThan_testCase1(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  expected = true;
  DateTimeWrapper less(startTime.year() - 1, startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 1 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 1 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t lessThan_testCase2(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper less(startTime.year(), startTime.month() - 1, startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 2 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 2 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t lessThan_testCase3(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper less(startTime.year(), startTime.month(), startTime.day() - 1,
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 3 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 3 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t lessThan_testCase4(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper less(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour() - 1, startTime.minute(), startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 4 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 4 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t lessThan_testCase5(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper less(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute() - 1, startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 5 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 5 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t lessThan_testCase6(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper less(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second() - 1);
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 6 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 6 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t lessThan_testCase7(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper less(startTime.year() + 1, startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 7 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 7 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t lessThan_testCase8(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper less(startTime.year(), startTime.month() + 1, startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 8 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 8 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
  
}
uint8_t lessThan_testCase9(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper less(startTime.year(), startTime.month(), startTime.day() + 1,
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 9 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 9 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;

}
uint8_t lessThan_testCase10(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper less(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour() + 1, startTime.minute(), startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 10 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 10 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;

}
uint8_t lessThan_testCase11(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper less(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute() + 1, startTime.second());
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 11 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 11 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;

}
uint8_t lessThan_testCase12(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper less(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second() + 1);
  actual = less < startTime;

  if (actual == expected)
  {
    Serial.println(F("lessThan() test case 12 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("lessThan() test case 12 failed."));
    Serial.print(F("Expected lessThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual lessThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;

}

// test more than operator
uint8_t testSuite_moreThan(void)
{
  uint8_t testsPassed = 0;

  testsPassed += moreThan_testCase1();
  testsPassed += moreThan_testCase2();
  testsPassed += moreThan_testCase3();
  testsPassed += moreThan_testCase4();
  testsPassed += moreThan_testCase5();
  testsPassed += moreThan_testCase6();
  testsPassed += moreThan_testCase7();
  testsPassed += moreThan_testCase8();
  testsPassed += moreThan_testCase9();
  testsPassed += moreThan_testCase10();
  testsPassed += moreThan_testCase11();
  testsPassed += moreThan_testCase12();

  return testsPassed;
}

uint8_t moreThan_testCase1(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  expected = true;
  DateTimeWrapper more(startTime.year() + 1, startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 1 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 1 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t moreThan_testCase2(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper more(startTime.year(), startTime.month() + 1, startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 2 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 2 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t moreThan_testCase3(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper more(startTime.year(), startTime.month(), startTime.day() + 1,
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 3 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 3 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t moreThan_testCase4(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper more(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour() + 1, startTime.minute(), startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 4 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 4 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t moreThan_testCase5(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper more(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute() + 1, startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 5 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 5 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t moreThan_testCase6(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper more(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second() + 1);
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 6 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 6 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t moreThan_testCase7(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper more(startTime.year() - 1, startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 7 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 7 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t moreThan_testCase8(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper more(startTime.year(), startTime.month() - 1, startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 8 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 8 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
  
}
uint8_t moreThan_testCase9(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper more(startTime.year(), startTime.month(), startTime.day() - 1,
                       startTime.hour(), startTime.minute(), startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 9 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 9 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;

}
uint8_t moreThan_testCase10(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper more(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour() - 1, startTime.minute(), startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 10 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 10 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;

}
uint8_t moreThan_testCase11(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper more(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute() - 1, startTime.second());
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 11 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 11 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;

}
uint8_t moreThan_testCase12(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper more(startTime.year(), startTime.month(), startTime.day(),
                       startTime.hour(), startTime.minute(), startTime.second() - 1);
  actual = more > startTime;

  if (actual == expected)
  {
    Serial.println(F("moreThan() test case 12 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("moreThan() test case 12 failed."));
    Serial.print(F("Expected moreThan(): "));
    Serial.println(expected);
    Serial.print(F("Actual moreThan(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;

}

// test the equals opeartor
uint8_t testSuite_equals(void)
{
  uint8_t testsPassed = 0;

  testsPassed += equals_testCase1();
  testsPassed += equals_testCase2();
  testsPassed += equals_testCase3();
  testsPassed += equals_testCase4();
  testsPassed += equals_testCase5();
  testsPassed += equals_testCase6();
  testsPassed += equals_testCase7();

  return testsPassed;
}

uint8_t equals_testCase1(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = true;
  DateTimeWrapper equal(startTime.year(), startTime.month(), startTime.day(), 
                        startTime.hour(), startTime.minute(), startTime.second());
  actual = equal == startTime;

  if (actual == expected)
  {
    Serial.println(F("equals() test case 1 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("equals() test case 1 failed."));
    Serial.print(F("Expected equals(): "));
    Serial.println(expected);
    Serial.print(F("Actual equals(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t equals_testCase2(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper equal(startTime.year() + 1, startTime.month(), startTime.day(), 
                        startTime.hour(), startTime.minute(), startTime.second());
  actual = equal == startTime;

  if (actual == expected)
  {
    Serial.println(F("equals() test case 2 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("equals() test case 2 failed."));
    Serial.print(F("Expected equals(): "));
    Serial.println(expected);
    Serial.print(F("Actual equals(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t equals_testCase3(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper equal(startTime.year(), startTime.month() + 1, startTime.day(), 
                        startTime.hour(), startTime.minute(), startTime.second());
  actual = equal == startTime;

  if (actual == expected)
  {
    Serial.println(F("equals() test case 3 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("equals() test case 3 failed."));
    Serial.print(F("Expected equals(): "));
    Serial.println(expected);
    Serial.print(F("Actual equals(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t equals_testCase4(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper equal(startTime.year(), startTime.month(), startTime.day() + 1, 
                        startTime.hour(), startTime.minute(), startTime.second());
  actual = equal == startTime;

  if (actual == expected)
  {
    Serial.println(F("equals() test case 4 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("equals() test case 4 failed."));
    Serial.print(F("Expected equals(): "));
    Serial.println(expected);
    Serial.print(F("Actual equals(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t equals_testCase5(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper equal(startTime.year(), startTime.month(), startTime.day(), 
                        startTime.hour() + 1, startTime.minute(), startTime.second());
  actual = equal == startTime;

  if (actual == expected)
  {
    Serial.println(F("equals() test case 5 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("equals() test case 5 failed."));
    Serial.print(F("Expected equals(): "));
    Serial.println(expected);
    Serial.print(F("Actual equals(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t equals_testCase6(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper equal(startTime.year(), startTime.month(), startTime.day(), 
                        startTime.hour(), startTime.minute() + 1, startTime.second());
  actual = equal == startTime;

  if (actual == expected)
  {
    Serial.println(F("equals() test case 6 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("equals() test case 6 failed."));
    Serial.print(F("Expected equals(): "));
    Serial.println(expected);
    Serial.print(F("Actual equals(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}
uint8_t equals_testCase7(void)
{
  uint8_t testsPassed = 0;
  bool actual, expected;

  // test actual and expected here
  expected = false;
  DateTimeWrapper equal(startTime.year(), startTime.month(), startTime.day(), 
                        startTime.hour(), startTime.minute(), startTime.second() + 1);
  actual = equal == startTime;

  if (actual == expected)
  {
    Serial.println(F("equals() test case 7 passed."));
    testsPassed++;
  }
  else
  {
    Serial.println(F("equals() test case 7 failed."));
    Serial.print(F("Expected equals(): "));
    Serial.println(expected);
    Serial.print(F("Actual equals(): "));
    Serial.println(actual);
  }
  Serial.print(F("\n"));

  return testsPassed;
}

// final output of program
void outputOverallResult(uint8_t testsPassed)
{
  uint8_t testsFailed = NUM_TESTS - testsPassed;

  Serial.println(F("============================="));
  Serial.print(NUM_TESTS);
  Serial.println(F(" tests performed"));
  Serial.println(F("============================="));

  if (testsPassed == NUM_TESTS)
  {
    Serial.println(F("All tests passed!"));
  }
  else
  {
    Serial.print(testsPassed);
    Serial.println(F(" tests passed."));
    Serial.print(testsFailed);
    Serial.println(F(" tests failed."));
    Serial.print(F("Success rate: "));
    Serial.print((float)(NUM_TESTS - testsFailed) / (float)NUM_TESTS * 100.0);
    Serial.println('%');
  }
}

void loop(void)
{
  ///aaa
}