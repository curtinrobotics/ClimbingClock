/*
   file: RTClib_CRoC.cpp
   auth: anton r

   created:  06/04/2020
   modified: 06/04/2020

   purpose: TODO 
*/

#include "RTClib_CRoC.h"

uint32_t RTC_DS1307_Wrapper::nowUnix(void)
{
   return RTC_DS1307::now().unixtime();
}

DateTimeWrapper RTC_DS1307_Wrapper::nowDT(void)
{
   const DateTime &dt = RTC_DS1307::now();
   return DateTimeWrapper(dt);
}


DateTimeWrapper::DateTimeWrapper(uint32_t t)
      : DateTime(t)
{
   time = DateTime::unixtime();
}

DateTimeWrapper::DateTimeWrapper(uint16_t year, uint8_t month, uint8_t day,
      uint8_t hour, uint8_t min, uint8_t sec)
      : DateTime(year, month, day, hour, min, sec)
{
   time = DateTime::unixtime();
}


DateTimeWrapper::DateTimeWrapper(const DateTime &copy) 
      : DateTime(copy)
{
   time = copy.unixtime();
}


DateTimeWrapper::DateTimeWrapper(const char *dateString, const char *timeString)
      : DateTime(dateString, timeString)
{
   time = DateTime::unixtime();
}

DateTimeWrapper::DateTimeWrapper(const __FlashStringHelper *FSHdate, const __FlashStringHelper *FSHtime)
      : DateTime(FSHdate, FSHtime)
{
   time = DateTime::unixtime();
}


uint32_t DateTimeWrapper::unixtime(void)
{
   return time;
}