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

DateTime  RTC_DS1307_Wrapper::nowDT(void)
{
   return RTC_DS1307::now();
}


DateTimeWrapper::DateTimeWrapper(uint32_t t = SECONDS_FROM_1970_TO_2000)
      : DateTime(t)
{
   time = DateTime::unixtime();
}

DateTimeWrapper::DateTimeWrapper(uint16_t year, uint8_t month, uint8_t day,
      uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0)
      : DateTime(year, month, day, hour, min, sec)
{
   time = DateTime::unixtime();
}


DateTimeWrapper::DateTimeWrapper(DateTime &copy) 
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