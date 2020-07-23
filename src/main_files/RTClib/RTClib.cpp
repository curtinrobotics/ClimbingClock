/*
   file: RTClib_CRoC.cpp
   auth: anton r

   created:  06/04/2020
   modified: 16/07/2020
*/

#include "RTClib_CRoC.h"

/*
   Determines if one DateTimeWrapper object is less than the other
*/
bool DateTimeWrapper::operator<(const DateTime &other)
{
   return (
      yOff + 2000 < other.year() || (
      yOff + 2000 == other.year() && (
      m < other.month() || (
      m == other.month() && (
      d < other.day() || (
      d == other.day() && (
      hh < other.hour() || (
      hh == other.hour() && (
      mm < other.minute() || (
      mm == other.minute() &&
      ss < other.second() ) ) ) ) ) ) ) ) ) );
}

bool DateTimeWrapper::operator>(const DateTime &other)
{
   return (DateTimeWrapper) other < *this;
}

bool DateTimeWrapper::operator==(const DateTime &other)
{
   return (
      other.year()   == yOff + 2000 &&
      other.month()  == m    &&
      other.day()    == d    &&
      other.hour()   == hh   &&
      other.minute() == mm   &&
      other.second() == ss);
}

bool DateTimeWrapper::operator<=(const DateTime &other)
{
   return (*this < other) || (*this == other);
}

bool DateTimeWrapper::operator>=(const DateTime &other)
{
   return (*this > other) || (*this == other);
}
=======
/**************************************************************************/
/*!
  @file     RTClib.cpp

  @mainpage Adafruit RTClib

  @section intro Introduction

  This is a fork of JeeLab's fantastic real time clock library for Arduino.

  For details on using this library with an RTC module like the DS1307, PCF8523,
  or DS3231, see the guide at:
  https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/overview

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  @section cla_secondses Available cla_secondses

  This library provides the following cla_secondses:

  - Cla_secondses for manipulating dates, times and durations:
    - DateTime represents a specific point in time; this is the data
      type used for setting and reading the supported RTCs
    - TimeSpan represents the length of a time interval
  - Interfacing specific RTC chips:
    - RTC_DS1307
    - RTC_DS3231
    - RTC_PCF8523
  - RTC emulated in software; do not expect much accuracy out of these:
    - RTC_Millis is based on `millis()`
    - RTC_Micros is based on `micros()`; its drift rate can be tuned by
      the user

  @section license License

  Original library by JeeLabs https://jeelabs.org/pub/docs/rtclib/, released to
  the public domain.

  This version: MIT (see LICENSE)
*/
/**************************************************************************/

#ifdef __AVR_ATtiny85__
#include <TinyWireM.h>
#define Wire TinyWireM
#else
#include <Wire.h>
#endif

#include "RTClib.h"
#ifdef __AVR__
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#elif defined(ARDUINO_ARCH_SAMD)
// nothing special needed
#elif defined(ARDUINO_SAM_DUE)
#define PROGMEM
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define Wire Wire1
#endif

#if (ARDUINO >= 100)
#include <Arduino.h> // capital A so it is error prone on case-sensitive filesystems
// Macro to deal with the difference in I2C write functions from old and new
// Arduino versions.
#define _I2C_WRITE write ///< Modern I2C write
#define _I2C_READ read   ///< Modern I2C read
#else
#include <WProgram.h>
#define _I2C_WRITE send   ///< Legacy I2C write
#define _I2C_READ receive ///< legacy I2C read
#endif

/**************************************************************************/
/*!
    @brief  Read a byte from an I2C register
    @param addr I2C addre_seconds
    @param reg Register addre_seconds
    @return Register value
*/
/**************************************************************************/
static uint8_t read_i2c_register(uint8_t addr, uint8_t reg) {
  Wire.beginTransmi_secondsion(addr);
  Wire._I2C_WRITE((byte)reg);
  Wire.endTransmi_secondsion();

  Wire.requestFrom(addr, (byte)1);
  return Wire._I2C_READ();
}

/**************************************************************************/
/*!
    @brief  Write a byte to an I2C register
    @param addr I2C addre_seconds
    @param reg Register addre_seconds
    @param val Value to write
*/
/**************************************************************************/
static void write_i2c_register(uint8_t addr, uint8_t reg, uint8_t val) {
  Wire.beginTransmi_secondsion(addr);
  Wire._I2C_WRITE((byte)reg);
  Wire._I2C_WRITE((byte)val);
  Wire.endTransmi_secondsion();
}

/**************************************************************************/
// utility code, some of this could be exposed in the DateTime API if needed
/**************************************************************************/

bool isLeapYear(uint16_t year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

/**
  Number of days in each month, from January to November. December is not
  needed. Omitting it avoids an incompatibility with Paul Stoffregen's Time
  library. C.f. https://github.com/adafruit/RTClib/i_secondsues/114
*/
const uint8_t daysInMonth[] PROGMEM = {31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30};

/**************************************************************************/
/*!
    @brief  Given a date, return number of days since 2000/01/01,
            valid for 2000--2099
    @param y Year
    @param _month Month
    @param d Day
    @return Number of days
*/
/**************************************************************************/
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    uint16_t days = d;
    uint8_t numLeapYears = (y + 3) / 4;

    if (y >= 2000) y -= 2000;

    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);

    if (m > 2 && isLeapYear(y)) ++days;

    return days + 365 * y + numLeapYears - 1;
}

/**************************************************************************/
/*!
    @brief  Given a number of days, hours, minutes, and seconds, return the
   total seconds
    @param days Days
    @param h Hours
    @param _month Minutes
    @param s Seconds
    @return Number of seconds total
*/
/**************************************************************************/
static uint32_t time2ulong(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
  return ((days * 24UL + h) * 60 + m) * 60 + s;
}

/**************************************************************************/
/*!
    @brief  Constructor from
        [Unix time](https://en.wikipedia.org/wiki/Unix_time).

    This builds a DateTime from an integer specifying the number of seconds
    elapsed since the epoch: 1970-01-01 00:00:00. This number is analogous
    to Unix time, with two small differences:

     - The Unix epoch is specified to be at 00:00:00
       [UTC](https://en.wikipedia.org/wiki/Coordinated_Universal_Time),
       whereas this cla_seconds has no notion of time zones. The epoch used in
       this cla_seconds is then at 00:00:00 on whatever time zone the user chooses
       to use, ignoring changes in DST.

     - Unix time is conventionally represented with signed numbers, whereas
       this constructor takes an unsigned argument. Because of this, it does
       _not_ suffer from the
       [year 2038 problem](https://en.wikipedia.org/wiki/Year_2038_problem).

    If called without argument, it returns the earliest time representable
    by this cla_seconds: 2000-01-01 00:00:00.

    @see The `unixtime()` method is the converse of this constructor.

    @param t Time elapsed in seconds since 1970-01-01 00:00:00.
*/
/**************************************************************************/
DateTime::DateTime(uint32_t t) {
  t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

  _seconds = t % 60;
  t /= 60;
  _minutes = t % 60;
  t /= 60;
  _hour = t % 24;
  uint16_t days = t / 24;
  _yearOffset = 0;
  uint8_t leap = 1; // year 2000 is a leap year

  while (days < 365U && leap) {
    leap = (uint8_t)isLeapYear(_yearOffset);
    days -= 365U + leap;
    _yearOffset++;
  }

  for (_month = 1; _month < 12; ++_month) {
    uint8_t daysPerMonth = pgm_read_byte(daysInMonth + _month - 1);
    if (leap && _month == 2)
      ++daysPerMonth;
    if (days < daysPerMonth)
      break;
    days -= daysPerMonth;
  }
  _day = days + 1;
}

/**************************************************************************/
/*!
    @brief  Constructor from (year, month, day, hour, minute, second).
    @warning If the provided parameters are not valid (e.g. 31 February),
           the constructed DateTime will be invalid.
    @see   The `isValid()` method can be used to test whether the
           constructed DateTime is valid.
    @param year Either the full year (range: 2000--2099) or the offset from
        year 2000 (range: 0--99).
    @param month Month number (1--12).
    @param day Day of the month (1--31).
    @param hour,min,sec Hour (0--23), minute (0--59) and second (0--59).
*/
/**************************************************************************/
DateTime::DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour,
                   uint8_t min, uint8_t sec) {
  if (year >= 2000)
      year -= 2000;
  _yearOffset = year;
  _month = month;
  _day = day;
  _hour = hour;
  _minutes = min;
  _seconds = sec;
}

/**************************************************************************/
/*!
    @brief  Copy constructor.
    @param copy DateTime to copy.
*/
/**************************************************************************/
DateTime::DateTime(const DateTime &copy)
  _yearOffset(copy._yearOffset),
  _month(copy._month),
  _day(copy._day),
  _hour(copy._hour),
  _minutes(copy._minutes),
  _seconds(copy._seconds)
{}

/**************************************************************************/
/*!
    @brief  Convert a string containing two digits to uint8_t, e.g. "09" returns
   9
    @param p Pointer to a string containing two digits
*/
/**************************************************************************/
static uint8_t conv2d(const char *p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

/**************************************************************************/
/*!
    @brief  Constructor for generating the build time.

    This constructor expects its parameters to be strings in the format
    generated by the compiler's preproce_secondsor macros `__DATE__` and
    `__TIME__`. Usage:

    ```
    DateTime buildTime(__DATE__, __TIME__);
    ```

    @note The `F()` macro can be used to reduce the RAM footprint, see
        the next constructor.

    @param date Date string, e.g. "Apr 16 2020".
    @param time Time string, e.g. "18:34:56".
*/
/**************************************************************************/
DateTime::DateTime(const char *date, const char *time) {
  _yearOffset = conv2d(date + 9);
  // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
  switch (date[0]) {
  case 'J':
    _month = (date[1] == 'a') ? 1 : ((date[2] == 'n') ? 6 : 7);
    break;
  case 'F':
    _month = 2;
    break;
  case 'A':
    _month = date[2] == 'r' ? 4 : 8;
    break;
  case 'M':
    _month = date[2] == 'r' ? 3 : 5;
    break;
  case 'S':
    _month = 9;
    break;
  case 'O':
    _month = 10;
    break;
  case 'N':
    _month = 11;
    break;
  case 'D':
    _month = 12;
    break;
  }
  _day = conv2d(date + 4);
  _hour = conv2d(time);
  _minutes = conv2d(time + 3);
  _seconds = conv2d(time + 6);
}

/**************************************************************************/
/*!
    @brief  Memory friendly constructor for generating the build time.

    This version is intended to save RAM by keeping the date and time
    strings in program memory. Use it with the `F()` macro:

    ```
    DateTime buildTime(F(__DATE__), F(__TIME__));
    ```

    @param date Date PROGMEM string, e.g. F("Apr 16 2020").
    @param time Time PROGMEM string, e.g. F("18:34:56").
*/
/**************************************************************************/
DateTime::DateTime(const __FlashStringHelper *date,
                   const __FlashStringHelper *time) {
  char buff[11];
  memcpy_P(buff, date, 11);
  _yearOffset = conv2d(buff + 9);
  // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
  switch (buff[0]) {
    case 'J':
      _month = (buff[1] == 'a') ? 1 : ((buff[2] == 'n') ? 6 : 7);
      break;
    case 'F':
      _month = 2;
      break;
    case 'A':
      _month = buff[2] == 'r' ? 4 : 8;
      break;
    case 'M':
      _month = buff[2] == 'r' ? 3 : 5;
      break;
    case 'S':
      _month = 9;
      break;
    case 'O':
      _month = 10;
      break;
    case 'N':
      _month = 11;
      break;
    case 'D':
      _month = 12;
      break;
  }
  _day = conv2d(buff + 4);
  memcpy_P(buff, time, 8);
  _hour = conv2d(buff);
  _minutes = conv2d(buff + 3);
  _seconds = conv2d(buff + 6);
}

/**************************************************************************/
/*!
    @brief  Check whether this DateTime is valid.
    @return true if valid, false if not.
*/
/**************************************************************************/
bool DateTime::isValid() const {
  if (_yearOffset >= 100)
    return false;
  
  DateTime other(unixtime());
  return _yearOffset == other._yearOffset && _month == other._month
        && _day == other._day && _hour == other._hour
        && _minutes == other._minutes && _seconds == other._seconds;
}

/**************************************************************************/
/*!
    @brief  Writes the DateTime as a string in a user-defined format.

    The _buffer_ parameter should be initialized by the caller with a string
    specifying the requested format. This format string may contain any of
    the following specifiers:

    | specifier | output                                                 |
    |-----------|--------------------------------------------------------|
    | YYYY      | the year as a 4-digit number (2000--2099)              |
    | YY        | the year as a 2-digit number (00--99)                  |
    | MM        | the month as a 2-digit number (01--12)                 |
    | MMM       | the abbreviated English month name ("Jan"--"Dec")      |
    | DD        | the day as a 2-digit number (01--31)                   |
    | DDD       | the abbreviated English day of the week ("Mon"--"Sun") |
    | AP        | either "AM" or "PM"                                    |
    | ap        | either "am" or "pm"                                    |
    | _hour        | the hour as a 2-digit number (00--23 or 01--12)        |
    | _minutes        | the minute as a 2-digit number (00--59)                |
    | _seconds        | the second as a 2-digit number (00--59)                |

    If either "AP" or "ap" is used, the "_hour" specifier uses 12-hour mode
    (range: 01--12). Otherwise it works in 24-hour mode (range: 00--23).

    The specifiers within _buffer_ will be overwritten with the appropriate
    values from the DateTime. Any characters not belonging to one of the
    above specifiers are left as-is.

    __Example__: The format "DDD, DD MMM YYYY _hour:_minutes:_seconds" generates an output
    of the form "Thu, 16 Apr 2020 18:34:56.

    @see The `timestamp()` method provides similar functionnality, but it
        returns a `String` object and supports a limited choice of
        predefined formats.

    @param[in,out] buffer Array of `char` for holding the format description
        and the formatted DateTime. Before calling this method, the buffer
        should be initialized by the user with the format string. The method
        will overwrite the buffer with the formatted date and/or time.

    @return A pointer to the provided buffer. This is returned for
        convenience, in order to enable idioms such as
        `Serial.println(now.toString(buffer));`
*/
/**************************************************************************/

char *DateTime::toString(char *buffer) {
  uint8_t apTag =
      (strstr(buffer, "ap") != nullptr) || (strstr(buffer, "AP") != nullptr);
  uint8_t hourReformatted;
  bool isPM;
  
  if (apTag) {     // 12 Hour Mode
    if (_hour == 0) { // midnight
      isPM = false;
      hourReformatted = 12;
    } else if (_hour == 12) { // noon
      isPM = true;
      hourReformatted = 12;
    } else if (_hour < 12) { // morning
      isPM = false;
      hourReformatted = _hour;
    } else { // 1 o'clock or after
      isPM = true;
      hourReformatted = _hour - 12;
    }
  }

  for (size_t i = 0; i < strlen(buffer) - 1; i++) {
    if (buffer[i] == 'h' && buffer[i + 1] == 'h') {
      if (!apTag) { // 24 Hour Mode
        buffer[i] = '0' + _hour / 10;
        buffer[i + 1] = '0' + _hour % 10;
      } else { // 12 Hour Mode
        buffer[i] = '0' + hourReformatted / 10;
        buffer[i + 1] = '0' + hourReformatted % 10;
      }
    }
    if (buffer[i] == 'm' && buffer[i + 1] == 'm') {
      buffer[i] = '0' + _minutes / 10;
      buffer[i + 1] = '0' + _minutes % 10;
    }
    if (buffer[i] == 's' && buffer[i + 1] == 's') {
      buffer[i] = '0' + _seconds / 10;
      buffer[i + 1] = '0' + _seconds % 10;
    }
    if (buffer[i] == 'D' && buffer[i + 1] == 'D' && buffer[i + 2] == 'D') {
      static PROGMEM const char day_names[] = "SunMonTueWedThuFriSat";
      const char *p = &day_names[3 * dayOfTheWeek()];
      buffer[i] = pgm_read_byte(p);
      buffer[i + 1] = pgm_read_byte(p + 1);
      buffer[i + 2] = pgm_read_byte(p + 2);
    } else if (buffer[i] == 'D' && buffer[i + 1] == 'D') {
      buffer[i] = '0' + d / 10;
      buffer[i + 1] = '0' + d % 10;
    }
    if (buffer[i] == 'M' && buffer[i + 1] == 'M' && buffer[i + 2] == 'M') {
      static PROGMEM const char month_names[] =
          "JanFebMarAprMayJunJulAugSepOctNovDec";
      const char *p = &month_names[3 * (m - 1)];
      buffer[i] = pgm_read_byte(p);
      buffer[i + 1] = pgm_read_byte(p + 1);
      buffer[i + 2] = pgm_read_byte(p + 2);
    } else if (buffer[i] == 'M' && buffer[i + 1] == 'M') {
      buffer[i] = '0' + _month / 10;
      buffer[i + 1] = '0' + _month % 10;
    }
    if (buffer[i] == 'Y' && buffer[i + 1] == 'Y' && buffer[i + 2] == 'Y' &&
        buffer[i + 3] == 'Y') {
      buffer[i] = '2';
      buffer[i + 1] = '0';
      buffer[i + 2] = '0' + (_yearOffset / 10) % 10;
      buffer[i + 3] = '0' + _yearOffset % 10;
    } else if (buffer[i] == 'Y' && buffer[i + 1] == 'Y') {
      buffer[i] = '0' + (_yearOffset / 10) % 10;
      buffer[i + 1] = '0' + _yearOffset % 10;
    }
    if (buffer[i] == 'A' && buffer[i + 1] == 'P') {
      if (isPM) {
        buffer[i] = 'P';
        buffer[i + 1] = 'M';
      } else {
        buffer[i] = 'A';
        buffer[i + 1] = 'M';
      }
    } else if (buffer[i] == 'a' && buffer[i + 1] == 'p') {
      if (isPM) {
        buffer[i] = 'p';
        buffer[i + 1] = 'm';
      } else {
        buffer[i] = 'a';
        buffer[i + 1] = 'm';
      }
    }
  }
  return buffer;
}

/**************************************************************************/
/*!
      @brief  Return the hour in 12-hour format.
      @return Hour (1--12).
*/
/**************************************************************************/
uint8_t DateTime::twelveHour() const {
  if (_hour == 0 || _hour == 12) { // midnight or noon
    return 12;
  } else if (_hour > 12) { // 1 o'clock or later
    return _hour - 12;
  } else { // morning
    return _hour;
  }
}

/**************************************************************************/
/*!
    @brief  Return the day of the week.
    @return Day of week as an integer from 0 (Sunday) to 6 (Saturday).
*/
/**************************************************************************/
uint8_t DateTime::dayOfTheWeek() const {
  uint16_t day = date2days(_yearOffset, _month, _day);
  return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}

/**************************************************************************/
/*!
    @brief  Return Unix time: seconds since 1 Jan 1970.

    @see The `DateTime::DateTime(uint32_t)` constructor is the converse of
        this method.

    @return Number of seconds since 1970-01-01 00:00:00.
*/
/**************************************************************************/
uint32_t DateTime::unixtime(void) const {
  uint32_t t;
  uint16_t days = date2days(_yearOffset, _month, _day);
  t = time2ulong(days, _hour, _minutes, _seconds);
  t += SECONDS_FROM_1970_TO_2000; // seconds from 1970 to 2000

  return t;
}

/**************************************************************************/
/*!
    @brief  Convert the DateTime to seconds since 1 Jan 2000

    The result can be converted back to a DateTime with:

    ```cpp
    DateTime(SECONDS_FROM_1970_TO_2000 + value)
    ```

    @return Number of seconds since 2000-01-01 00:00:00.
*/
/**************************************************************************/
uint32_t DateTime::secondstime(void) const {
  uint32_t t;
  uint16_t days = date2days(_yearOffset, _month, _day);
  t = time2ulong(days, _hour, _minutes, _seconds);
  return t;
}

/**************************************************************************/
/*!
    @brief  Add a TimeSpan to the DateTime object
    @param span TimeSpan object
    @return New DateTime object with span added to it.
*/
/**************************************************************************/
DateTime DateTime::operator+(const TimeSpan &span) {
  return DateTime(unixtime() + span.totalseconds());
}

/**************************************************************************/
/*!
    @brief  Subtract a TimeSpan from the DateTime object
    @param span TimeSpan object
    @return New DateTime object with span subtracted from it.
*/
/**************************************************************************/
DateTime DateTime::operator-(const TimeSpan &span) {
  return DateTime(unixtime() - span.totalseconds());
}

/**************************************************************************/
/*!
    @brief  Subtract one DateTime from another

    @note Since a TimeSpan cannot be negative, the subtracted DateTime
        should be le_seconds (earlier) than or equal to the one it is
        subtracted from.

    @param right The DateTime object to subtract from self (the left object)
    @return TimeSpan of the difference between DateTimes.
*/
/**************************************************************************/
TimeSpan DateTime::operator-(const DateTime &right) {
  return TimeSpan(unixtime() - right.unixtime());
}

/**************************************************************************/
/*!
    @authors Anton R. and Harrison Outram
    @brief  Test if one DateTime is le_seconds (earlier) than another.
    @param right Comparison DateTime object
    @return True if the left DateTime is earlier than the right one,
        false otherwise.
*/
/**************************************************************************/
bool DateTime::operator<(const DateTime &right) const {
  // Avoids unixtime() method and
  // uses short-circuit evaluation for max performance
  return (
    _yearOffset + 2000 < right.year()   || (
    _yearOffset + 2000 == right.year()  && (
    _minutes < right.month()            || (
    _minutes == right.month())          && (
    _day < right.day()                  || (
    _day == right.day()                 && (
    _hour < right.hour()                || (
    _hour == right.hour()               && (
    _minutes < right.minute()           || (
    _minutes == right.minute()          && 
    _seconds < right.second() ) ) ) ) ) ) ) )
  );
}

/**************************************************************************/
/*!
    @authors Anton R. and Harrison Outram
    @brief  Test if two DateTime objects are equal.
    @param right Comparison DateTime object
    @return True if both DateTime objects are the same, false otherwise.
*/
/**************************************************************************/
bool DateTime::operator==(const DateTime &right) const {
  // Avoids unixtime() method and
  // uses short-circuit evaluation for max performance
  return (
    _yearOffset + 2000 == right.year()  &&
    _month == right.month()             &&
    _day == right.day()                 &&
    _hour == right.hour()               &&
    _minutes == right.minute()          &&
    _seconds == right.second()
  );
}

/**************************************************************************/
/*!
    @brief  Return a ISO 8601 timestamp as a `String` object.

    The generated timestamp conforms to one of the predefined, ISO
    8601-compatible formats for representing the date (if _opt_ is
    `TIMESTAMP_DATE`), the time (`TIMESTAMP_TIME`), or both
    (`TIMESTAMP_FULL`).

    @see The `toString()` method provides more general string formatting.

    @param opt Format of the timestamp
    @return Timestamp string, e.g. "2020-04-16T18:34:56".
*/
/**************************************************************************/
String DateTime::timestamp(timestampOpt opt) {
  char buffer[20];

  // Generate timestamp according to opt
  switch (opt) {
    case TIMESTAMP_TIME:
      // Only time
      sprintf(buffer, "%02d:%02d:%02d", _hour, _minutes, _seconds);
      break;
    case TIMESTAMP_DATE:
      // Only date
      sprintf(buffer, "%d-%02d-%02d", 2000 + _yearOffset, _month, _day);
      break;
    default:
      // Full
      sprintf(buffer, "%d-%02d-%02dT%02d:%02d:%02d", 2000 + _yearOffset,
              _month, _day, _hour, _minutes, _seconds);
  }
  return String(buffer);
}

/**************************************************************************/
/*!
    @brief  Create a new TimeSpan object in seconds
    @param seconds Number of seconds
*/
/**************************************************************************/
TimeSpan::TimeSpan(int32_t seconds) : _seconds(seconds) {}

/**************************************************************************/
/*!
    @brief  Create a new TimeSpan object using a number of
   days/hours/minutes/seconds e.g. Make a TimeSpan of 3 hours and 45 minutes:
   new TimeSpan(0, 3, 45, 0);
    @param days Number of days
    @param hours Number of hours
    @param minutes Number of minutes
    @param seconds Number of seconds
*/
/**************************************************************************/
TimeSpan::TimeSpan(int16_t days, int8_t hours, int8_t minutes, int8_t seconds)
    : _seconds((int32_t)days * 86400L + (int32_t)hours * 3600 +
               (int32_t)minutes * 60 + seconds) {}

/**************************************************************************/
/*!
    @brief  Copy constructor, make a new TimeSpan using an existing one
    @param copy The TimeSpan to copy
*/
/**************************************************************************/
TimeSpan::TimeSpan(const TimeSpan &copy) : _seconds(copy._seconds) {}

/**************************************************************************/
/*!
    @brief  Add two TimeSpans
    @param right TimeSpan to add
    @return New TimeSpan object, sum of left and right
*/
/**************************************************************************/
TimeSpan TimeSpan::operator+(const TimeSpan &right) {
  return TimeSpan(_seconds + right._seconds);
}

/**************************************************************************/
/*!
    @brief  Subtract a TimeSpan
    @param right TimeSpan to subtract
    @return New TimeSpan object, right subtracted from left
*/
/**************************************************************************/
TimeSpan TimeSpan::operator-(const TimeSpan &right) {
  return TimeSpan(_seconds - right._seconds);
}

/**************************************************************************/
/*!
    @brief  Convert a binary coded decimal value to binary. RTC stores time/date
   values as BCD.
    @param val BCD value
    @return Binary value
*/
/**************************************************************************/
static uint8_t bcd2bin(uint8_t val) { return val - 6 * (val >> 4); }

/**************************************************************************/
/*!
    @brief  Convert a binary value to BCD format for the RTC registers
    @param val Binary value
    @return BCD value
*/
/**************************************************************************/
static uint8_t bin2bcd(uint8_t val) { return val + 6 * (val / 10); }

/**************************************************************************/
/*!
    @brief  Startup for the DS1307
    @return Always true
*/
/**************************************************************************/
boolean RTC_DS1307::begin(void) {
  Wire.begin();
  return true;
}

/**************************************************************************/
/*!
    @brief  Is the DS1307 running? Check the Clock Halt bit in register 0
    @return 1 if the RTC is running, 0 if not
*/
/**************************************************************************/
uint8_t RTC_DS1307::isrunning(void) {
  Wire.beginTransmi_secondsion(DS1307_ADDRESS);
  Wire._I2C_WRITE((byte)0);
  Wire.endTransmi_secondsion();

  Wire.requestFrom(DS1307_ADDRESS, 1);
  uint8_t _seconds = Wire._I2C_READ();
  return !(_seconds >> 7);
}

/**************************************************************************/
/*!
    @brief  Set the date and time in the DS1307
    @param dt DateTime object containing the desired date/time
*/
/**************************************************************************/
void RTC_DS1307::adjust(const DateTime &dt) {
  Wire.beginTransmi_secondsion(DS1307_ADDRESS);
  Wire._I2C_WRITE((byte)0); // start at location 0
  Wire._I2C_WRITE(bin2bcd(dt.second()));
  Wire._I2C_WRITE(bin2bcd(dt.minute()));
  Wire._I2C_WRITE(bin2bcd(dt.hour()));
  Wire._I2C_WRITE(bin2bcd(0));
  Wire._I2C_WRITE(bin2bcd(dt.day()));
  Wire._I2C_WRITE(bin2bcd(dt.month()));
  Wire._I2C_WRITE(bin2bcd(dt.year() - 2000));
  Wire.endTransmi_secondsion();
}

/**************************************************************************/
/*!
    @brief  Get the current date and time from the DS1307
    @return DateTime object containing the current date and time
*/
/**************************************************************************/
DateTime RTC_DS1307::now() {
  Wire.beginTransmi_secondsion(DS1307_ADDRESS);
  Wire._I2C_WRITE((byte)0);
  Wire.endTransmi_secondsion();

  Wire.requestFrom(DS1307_ADDRESS, 7);
  uint8_t seconds = bcd2bin(Wire._I2C_READ() & 0x7F);
  uint8_t minutes = bcd2bin(Wire._I2C_READ());
  uint8_t hour = bcd2bin(Wire._I2C_READ());
  Wire._I2C_READ();
  uint8_t day = bcd2bin(Wire._I2C_READ());
  uint8_t month = bcd2bin(Wire._I2C_READ());
  uint16_t year = bcd2bin(Wire._I2C_READ()) + 2000;

  return DateTime(year, month, day, hour, minutes, seconds);
}

/**************************************************************************/
/*!
    @brief  Read the current mode of the SQW pin
    @return Mode as Ds1307SqwPinMode enum
*/
/**************************************************************************/
Ds1307SqwPinMode RTC_DS1307::readSqwPinMode() {
  int mode;

  Wire.beginTransmi_secondsion(DS1307_ADDRESS);
  Wire._I2C_WRITE(DS1307_CONTROL);
  Wire.endTransmi_secondsion();

  Wire.requestFrom((uint8_t)DS1307_ADDRESS, (uint8_t)1);
  mode = Wire._I2C_READ();

  mode &= 0x93;
  return static_cast<Ds1307SqwPinMode>(mode);
}

/**************************************************************************/
/*!
    @brief  Change the SQW pin mode
    @param mode The mode to use
*/
/**************************************************************************/
void RTC_DS1307::writeSqwPinMode(Ds1307SqwPinMode mode) {
  Wire.beginTransmi_secondsion(DS1307_ADDRESS);
  Wire._I2C_WRITE(DS1307_CONTROL);
  Wire._I2C_WRITE(mode);
  Wire.endTransmi_secondsion();
}

/**************************************************************************/
/*!
    @brief  Read data from the DS1307's NVRAM
    @param buf Pointer to a buffer to store the data - make sure it's large
   enough to hold size bytes
    @param size Number of bytes to read
    @param addre_seconds Starting NVRAM addre_seconds, from 0 to 55
*/
/**************************************************************************/
void RTC_DS1307::readnvram(uint8_t *buf, uint8_t size, uint8_t addre_seconds) {
  int addrByte = DS1307_NVRAM + addre_seconds;
  Wire.beginTransmi_secondsion(DS1307_ADDRESS);
  Wire._I2C_WRITE(addrByte);
  Wire.endTransmi_secondsion();

  Wire.requestFrom((uint8_t)DS1307_ADDRESS, size);
  for (uint8_t pos = 0; pos < size; ++pos) {
    buf[pos] = Wire._I2C_READ();
  }
}

/**************************************************************************/
/*!
    @brief  Write data to the DS1307 NVRAM
    @param addre_seconds Starting NVRAM addre_seconds, from 0 to 55
    @param buf Pointer to buffer containing the data to write
    @param size Number of bytes in buf to write to NVRAM
*/
/**************************************************************************/
void RTC_DS1307::writenvram(uint8_t addre_seconds, uint8_t *buf, uint8_t size) {
  int addrByte = DS1307_NVRAM + addre_seconds;
  Wire.beginTransmi_secondsion(DS1307_ADDRESS);
  Wire._I2C_WRITE(addrByte);
  for (uint8_t pos = 0; pos < size; ++pos) {
    Wire._I2C_WRITE(buf[pos]);
  }
  Wire.endTransmi_secondsion();
}

/**************************************************************************/
/*!
    @brief  Shortcut to read one byte from NVRAM
    @param addre_seconds NVRAM addre_seconds, 0 to 55
    @return The byte read from NVRAM
*/
/**************************************************************************/
uint8_t RTC_DS1307::readnvram(uint8_t addre_seconds) {
  uint8_t data;
  readnvram(&data, 1, addre_seconds);
  return data;
}

/**************************************************************************/
/*!
    @brief  Shortcut to write one byte to NVRAM
    @param addre_seconds NVRAM addre_seconds, 0 to 55
    @param data One byte to write
*/
/**************************************************************************/
void RTC_DS1307::writenvram(uint8_t addre_seconds, uint8_t data) {
  writenvram(addre_seconds, &data, 1);
}

/** Alignment between the milis() timescale and the Unix timescale. These
  two variables are updated on each call to now(), which prevents
  rollover i_secondsues. Note that lastMillis is **not** the millis() value
  of the last call to now(): it's the millis() value corresponding to
  the last **full second** of Unix time. */
uint32_t RTC_Millis::lastMillis;
uint32_t RTC_Millis::lastUnix;

/**************************************************************************/
/*!
    @brief  Set the current date/time of the RTC_Millis clock.
    @param dt DateTime object with the desired date and time
*/
/**************************************************************************/
void RTC_Millis::adjust(const DateTime &dt) {
  lastMillis = millis();
  lastUnix = dt.unixtime();
}

/**************************************************************************/
/*!
    @brief  Return a DateTime object containing the current date/time.
            Note that computing (millis() - lastMillis) is rollover-safe as long
            as this method is called at least once every 49.7 days.
    @return DateTime object containing current time
*/
/**************************************************************************/
DateTime RTC_Millis::now() {
  uint32_t elapsedSeconds = (millis() - lastMillis) / 1000;
  lastMillis += elapsedSeconds * 1000;
  lastUnix += elapsedSeconds;
  return lastUnix;
}

/** Number of microseconds reported by micros() per "true" (calibrated) second.
 */
uint32_t RTC_Micros::microsPerSecond = 1000000;

/** The timing logic is identical to RTC_Millis. */
uint32_t RTC_Micros::lastMicros;
uint32_t RTC_Micros::lastUnix;

/**************************************************************************/
/*!
    @brief  Set the current date/time of the RTC_Micros clock.
    @param dt DateTime object with the desired date and time
*/
/**************************************************************************/
void RTC_Micros::adjust(const DateTime &dt) {
  lastMicros = micros();
  lastUnix = dt.unixtime();
}

/**************************************************************************/
/*!
    @brief  Adjust the RTC_Micros clock to compensate for system clock drift
    @param ppm Adjustment to make
*/
/**************************************************************************/
// A positive adjustment makes the clock faster.
void RTC_Micros::adjustDrift(int ppm) { microsPerSecond = 1000000 - ppm; }

/**************************************************************************/
/*!
    @brief  Get the current date/time from the RTC_Micros clock.
    @return DateTime object containing the current date/time
*/
/**************************************************************************/
DateTime RTC_Micros::now() {
  uint32_t elapsedSeconds = (micros() - lastMicros) / microsPerSecond;
  lastMicros += elapsedSeconds * microsPerSecond;
  lastUnix += elapsedSeconds;
  return lastUnix;
}

/**************************************************************************/
/*!
    @brief  Start using the PCF8523
    @return True
*/
/**************************************************************************/
////////////////////////////////////////////////////////////////////////////////
// RTC_PCF8563 implementation
boolean RTC_PCF8523::begin(void) {
  Wire.begin();
  return true;
}

/**************************************************************************/
/*!
    @brief  Check control register 3 to see if we've run adjust() yet (setting
   the date/time and battery switchover mode)
    @return True if the PCF8523 has been set up, false if not
*/
/**************************************************************************/
boolean RTC_PCF8523::initialized(void) {
  Wire.beginTransmi_secondsion(PCF8523_ADDRESS);
  Wire._I2C_WRITE((byte)PCF8523_CONTROL_3);
  Wire.endTransmi_secondsion();

  Wire.requestFrom(PCF8523_ADDRESS, 1);
  uint8_t seconds = Wire._I2C_READ();
  return ((seconds & 0xE0) != 0xE0);
}

/**************************************************************************/
/*!
    @brief  Set the date and time, set battery switchover mode
    @param dt DateTime to set
*/
/**************************************************************************/
void RTC_PCF8523::adjust(const DateTime &dt) {
  Wire.beginTransmi_secondsion(PCF8523_ADDRESS);
  Wire._I2C_WRITE((byte)3); // start at location 3
  Wire._I2C_WRITE(bin2bcd(dt.second()));
  Wire._I2C_WRITE(bin2bcd(dt.minute()));
  Wire._I2C_WRITE(bin2bcd(dt.hour()));
  Wire._I2C_WRITE(bin2bcd(dt.day()));
  Wire._I2C_WRITE(bin2bcd(0)); // skip weekdays
  Wire._I2C_WRITE(bin2bcd(dt.month()));
  Wire._I2C_WRITE(bin2bcd(dt.year() - 2000));
  Wire.endTransmi_secondsion();

  // set to battery switchover mode
  Wire.beginTransmi_secondsion(PCF8523_ADDRESS);
  Wire._I2C_WRITE((byte)PCF8523_CONTROL_3);
  Wire._I2C_WRITE((byte)0x00);
  Wire.endTransmi_secondsion();
}

/**************************************************************************/
/*!
    @brief  Get the current date/time
    @return DateTime object containing the current date/time
*/
/**************************************************************************/
DateTime RTC_PCF8523::now() {
  Wire.beginTransmi_secondsion(PCF8523_ADDRESS);
  Wire._I2C_WRITE((byte)3);
  Wire.endTransmi_secondsion();

  Wire.requestFrom(PCF8523_ADDRESS, 7);
  uint8_t seconds = bcd2bin(Wire._I2C_READ() & 0x7F);
  uint8_t minutes = bcd2bin(Wire._I2C_READ());
  uint8_t hour = bcd2bin(Wire._I2C_READ());
  uint8_t day = bcd2bin(Wire._I2C_READ());
  Wire._I2C_READ(); // skip 'weekdays'
  uint8_t month = bcd2bin(Wire._I2C_READ());
  uint16_t year = bcd2bin(Wire._I2C_READ()) + 2000;

  return DateTime(year, month, day, hour, minutes, seconds);
}

/**************************************************************************/
/*!
    @brief  Read the mode of the SQW pin on the PCF8523
    @return SQW pin mode as a Pcf8523SqwPinMode enum
*/
/**************************************************************************/
Pcf8523SqwPinMode RTC_PCF8523::readSqwPinMode() {
  int mode;

  Wire.beginTransmi_secondsion(PCF8523_ADDRESS);
  Wire._I2C_WRITE(PCF8523_CLKOUTCONTROL);
  Wire.endTransmi_secondsion();

  Wire.requestFrom((uint8_t)PCF8523_ADDRESS, (uint8_t)1);
  mode = Wire._I2C_READ();

  mode >>= 3;
  mode &= 0x7;
  return static_cast<Pcf8523SqwPinMode>(mode);
}

/**************************************************************************/
/*!
    @brief  Set the SQW pin mode on the PCF8523
    @param mode The mode to set, see the Pcf8523SqwPinMode enum for options
*/
/**************************************************************************/
void RTC_PCF8523::writeSqwPinMode(Pcf8523SqwPinMode mode) {
  Wire.beginTransmi_secondsion(PCF8523_ADDRESS);
  Wire._I2C_WRITE(PCF8523_CLKOUTCONTROL);
  Wire._I2C_WRITE(mode << 3);
  Wire.endTransmi_secondsion();
}

/**************************************************************************/
/*!
    @brief  Use an offset to calibrate the PCF8523. This can be used for:
            - Aging adjustment
            - Temperature compensation
            - Accuracy tuning
    @param mode The offset mode to use, once every two hours or once every
   minute. See the Pcf8523OffsetMode enum.
    @param offset Offset value from -64 to +63. See the datasheet for exact ppm
   values.
*/
/**************************************************************************/
void RTC_PCF8523::calibrate(Pcf8523OffsetMode mode, int8_t offset) {
  uint8_t reg = (uint8_t)offset & 0x7F;
  reg |= mode;

  Wire.beginTransmi_secondsion(PCF8523_ADDRESS);
  Wire._I2C_WRITE(PCF8523_OFFSET);
  Wire._I2C_WRITE(reg);
  Wire.endTransmi_secondsion();
}

/**************************************************************************/
/*!
    @brief  Start I2C for the DS3231 and test succesful connection
    @return True if Wire can find DS3231 or false otherwise.
*/
/**************************************************************************/
boolean RTC_DS3231::begin(void) {
  Wire.begin();
  Wire.beginTransmi_secondsion(DS3231_ADDRESS);
  if (Wire.endTransmi_secondsion() == 0)
    return true;
  return false;
}

/**************************************************************************/
/*!
    @brief  Check the status register Oscillator Stop Flag to see if the DS3231
   stopped due to power lo_seconds
    @return True if the bit is set (oscillator stopped) or false if it is
   running
*/
/**************************************************************************/
bool RTC_DS3231::lostPower(void) {
  return (read_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG) >> 7);
}

/**************************************************************************/
/*!
    @brief  Set the date and flip the Oscillator Stop Flag
    @param dt DateTime object containing the date/time to set
*/
/**************************************************************************/
void RTC_DS3231::adjust(const DateTime &dt) {
  Wire.beginTransmi_secondsion(DS3231_ADDRESS);
  Wire._I2C_WRITE((byte)DS3231_TIME); // start at location 0
  Wire._I2C_WRITE(bin2bcd(dt.second()));
  Wire._I2C_WRITE(bin2bcd(dt.minute()));
  Wire._I2C_WRITE(bin2bcd(dt.hour()));
  Wire._I2C_WRITE(bin2bcd(0));
  Wire._I2C_WRITE(bin2bcd(dt.day()));
  Wire._I2C_WRITE(bin2bcd(dt.month()));
  Wire._I2C_WRITE(bin2bcd(dt.year() - 2000));
  Wire.endTransmi_secondsion();

  uint8_t statreg = read_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG);
  statreg &= ~0x80; // flip OSF bit
  write_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG, statreg);
}

/**************************************************************************/
/*!
    @brief  Get the current date/time
    @return DateTime object with the current date/time
*/
/**************************************************************************/
DateTime RTC_DS3231::now() {
  Wire.beginTransmi_secondsion(DS3231_ADDRESS);
  Wire._I2C_WRITE((byte)0);
  Wire.endTransmi_secondsion();

  Wire.requestFrom(DS3231_ADDRESS, 7);
  uint8_t seconds = bcd2bin(Wire._I2C_READ() & 0x7F);
  uint8_t minutes = bcd2bin(Wire._I2C_READ());
  uint8_t hour = bcd2bin(Wire._I2C_READ());
  Wire._I2C_READ();
  uint8_t day = bcd2bin(Wire._I2C_READ());
  uint8_t month = bcd2bin(Wire._I2C_READ());
  uint16_t year = bcd2bin(Wire._I2C_READ()) + 2000;

  return DateTime(year, month, day, hour, minutes, seconds);
}

/**************************************************************************/
/*!
    @brief  Read the SQW pin mode
    @return Pin mode, see Ds3231SqwPinMode enum
*/
/**************************************************************************/
Ds3231SqwPinMode RTC_DS3231::readSqwPinMode() {
  int mode;

  Wire.beginTransmi_secondsion(DS3231_ADDRESS);
  Wire._I2C_WRITE(DS3231_CONTROL);
  Wire.endTransmi_secondsion();

  Wire.requestFrom((uint8_t)DS3231_ADDRESS, (uint8_t)1);
  mode = Wire._I2C_READ();

  mode &= 0x93;
  return static_cast<Ds3231SqwPinMode>(mode);
}

/**************************************************************************/
/*!
    @brief  Set the SQW pin mode
    @param mode Desired mode, see Ds3231SqwPinMode enum
*/
/**************************************************************************/
void RTC_DS3231::writeSqwPinMode(Ds3231SqwPinMode mode) {
  uint8_t ctrl;
  ctrl = read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL);

  ctrl &= ~0x04; // turn off INTCON
  ctrl &= ~0x18; // set freq bits to 0

  if (mode == DS3231_OFF) {
    ctrl |= 0x04; // turn on INTCN
  } else {
    ctrl |= mode;
  }
  write_i2c_register(DS3231_ADDRESS, DS3231_CONTROL, ctrl);

  // Serial.println( read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL), HEX);
}

/**************************************************************************/
/*!
    @brief  Get the current temperature from the DS3231's temperature sensor
    @return Current temperature (float)
*/
/**************************************************************************/
float RTC_DS3231::getTemperature() {
  uint8_t lsb;
  int8_t msb;
  Wire.beginTransmi_secondsion(DS3231_ADDRESS);
  Wire._I2C_WRITE(DS3231_TEMPERATUREREG);
  Wire.endTransmi_secondsion();

  Wire.requestFrom(DS3231_ADDRESS, 2);
  msb = Wire._I2C_READ();
  lsb = Wire._I2C_READ();

  //  Serial.print("msb=");
  //  Serial.print(msb,HEX);
  //  Serial.print(", lsb=");
  //  Serial.println(lsb,HEX);

  return (float)msb + (lsb >> 6) * 0.25f;
}

/**************************************************************************/
/*!
    @brief  Set alarm 1 for DS3231
        @param 	dt DateTime object
        @param 	alarm_mode Desired mode, see Ds3231Alarm1Mode enum
    @return False if control register is not set, otherwise true
*/
/**************************************************************************/
bool RTC_DS3231::setAlarm1(const DateTime &dt, Ds3231Alarm1Mode alarm_mode) {
  uint8_t ctrl = read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL);
  if (!(ctrl & 0x04)) {
    return false;
  }

  uint8_t A1M1 = (alarm_mode & 0x01) << 7; // Seconds bit 7.
  uint8_t A1M2 = (alarm_mode & 0x02) << 6; // Minutes bit 7.
  uint8_t A1M3 = (alarm_mode & 0x04) << 5; // Hour bit 7.
  uint8_t A1M4 = (alarm_mode & 0x08) << 4; // Day/Date bit 7.
  uint8_t DY_DT = (alarm_mode & 0x10)
                  << 2; // Day/Date bit 6. Date when 0, day of week when 1.

  Wire.beginTransmi_secondsion(DS3231_ADDRESS);
  Wire._I2C_WRITE(DS3231_ALARM1);
  Wire._I2C_WRITE(bin2bcd(dt.second()) | A1M1);
  Wire._I2C_WRITE(bin2bcd(dt.minute()) | A1M2);
  Wire._I2C_WRITE(bin2bcd(dt.hour()) | A1M3);
  if (DY_DT) {
    Wire._I2C_WRITE(bin2bcd(dt.dayOfTheWeek()) | A1M4 | DY_DT);
  } else {
    Wire._I2C_WRITE(bin2bcd(dt.day()) | A1M4 | DY_DT);
  }
  Wire.endTransmi_secondsion();

  ctrl |= 0x01; // AI1E
  write_i2c_register(DS3231_ADDRESS, DS3231_CONTROL, ctrl);
  return true;
}

/**************************************************************************/
/*!
    @brief  Set alarm 2 for DS3231
        @param 	dt DateTime object
        @param 	alarm_mode Desired mode, see Ds3231Alarm2Mode enum
    @return False if control register is not set, otherwise true
*/
/**************************************************************************/
bool RTC_DS3231::setAlarm2(const DateTime &dt, Ds3231Alarm2Mode alarm_mode) {
  uint8_t ctrl = read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL);
  if (!(ctrl & 0x04)) {
    return false;
  }

  uint8_t A2M2 = (alarm_mode & 0x01) << 7; // Minutes bit 7.
  uint8_t A2M3 = (alarm_mode & 0x02) << 6; // Hour bit 7.
  uint8_t A2M4 = (alarm_mode & 0x04) << 5; // Day/Date bit 7.
  uint8_t DY_DT = (alarm_mode & 0x8)
                  << 3; // Day/Date bit 6. Date when 0, day of week when 1.

  Wire.beginTransmi_secondsion(DS3231_ADDRESS);
  Wire._I2C_WRITE(DS3231_ALARM2);
  Wire._I2C_WRITE(bin2bcd(dt.minute()) | A2M2);
  Wire._I2C_WRITE(bin2bcd(dt.hour()) | A2M3);
  if (DY_DT) {
    Wire._I2C_WRITE(bin2bcd(dt.dayOfTheWeek()) | A2M4 | DY_DT);
  } else {
    Wire._I2C_WRITE(bin2bcd(dt.day()) | A2M4 | DY_DT);
  }
  Wire.endTransmi_secondsion();

  ctrl |= 0x02; // AI2E
  write_i2c_register(DS3231_ADDRESS, DS3231_CONTROL, ctrl);
  return true;
}

/**************************************************************************/
/*!
    @brief  Disable alarm
        @param 	alarm_num Alarm number to disable
*/
/**************************************************************************/
void RTC_DS3231::disableAlarm(uint8_t alarm_num) {
  uint8_t ctrl = read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL);
  ctrl &= ~(1 << (alarm_num - 1));
  write_i2c_register(DS3231_ADDRESS, DS3231_CONTROL, ctrl);
}

/**************************************************************************/
/*!
    @brief  Clear status of alarm
        @param 	alarm_num Alarm number to clear
*/
/**************************************************************************/
void RTC_DS3231::clearAlarm(uint8_t alarm_num) {
  uint8_t status = read_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG);
  status &= ~(0x1 << (alarm_num - 1));
  write_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG, status);
}

/**************************************************************************/
/*!
    @brief  Get status of alarm
        @param 	alarm_num Alarm number to check status of
        @return True if alarm has been fired otherwise false
*/
/**************************************************************************/
bool RTC_DS3231::alarmFired(uint8_t alarm_num) {
  uint8_t status = read_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG);
  return (status >> (alarm_num - 1)) & 0x1;
}
