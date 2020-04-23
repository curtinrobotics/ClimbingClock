/*
   file: RTClib_CRoC.h
   auth: anton r

   created:  06/04/2020
   modified: 06/04/2020

   purpose: TODO 
*/

#ifndef RTC_LIB_CROC_H
#define RTC_LIB_CROC_H

#include <Arduino.h>
#include <stdint.h>
#include <RTClib.h>

class RTC_DS1307_Wrapper : RTC_DS1307
{
   public:
      uint32_t nowUnix(void);
      DateTime nowDT(void);
};

class DateTimeWrapper : DateTime
{
   private:
      uint32_t time;
   public:
      DateTimeWrapper(uint32_t t = SECONDS_FROM_1970_TO_2000);
      DateTimeWrapper(uint16_t year, uint8_t month, uint8_t day,
            uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0);
      DateTimeWrapper(DateTime &copy);
      //DateTimeWrapper(DateTimeWrapper &copy);
      DateTimeWrapper(const char *date, const char *time);
      DateTimeWrapper(const __FlashStringHelper *date, const __FlashStringHelper *time);

      uint32_t unixtime(void);
};

#endif