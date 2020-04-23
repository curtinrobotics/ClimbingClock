/*
   file: RTClib_CRoC.h
   auth: anton r

   created:  06/04/2020
   modified: 16/04/2020
*/

#ifndef RTC_LIB_CROC_H
#  define RTC_LIB_CROC_H

#  include <RTClib.h>


/*
   DateTimeWrapper:

   Wrapper for the DateTime class
*/
class DateTimeWrapper : public DateTime
{
   public:
      DateTimeWrapper(uint32_t t = SECONDS_FROM_1970_TO_2000)
         : DateTime(t) {};
      DateTimeWrapper(uint16_t year, uint8_t month, uint8_t day,
         uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0)
         : DateTime(year, month, day, hour, min, sec) {};
      DateTimeWrapper(const DateTime &copy)
         : DateTime(copy) {};
      DateTimeWrapper(const __FlashStringHelper* date, const __FlashStringHelper* time)
         : DateTime(date, time) {};
      DateTimeWrapper(const char* date, const char* time)
         : DateTime(date, time) {};

      bool operator<(const DateTime &other);
      bool operator>(const DateTime &other);
      bool operator==(const DateTime &other);
      bool operator<=(const DateTime &other);
      bool operator>=(const DateTime &other);
};

/*
   RTC_DS1307_Wrapper:

   Wrapper for the RTC_DS1307 class, returns a DateTimeWrapper instead of DateTime
*/
class RTC_DS1307_Wrapper : public RTC_DS1307
{
   public:
      DateTimeWrapper now() { return DateTimeWrapper(RTC_DS1307::now()); }
};

#endif