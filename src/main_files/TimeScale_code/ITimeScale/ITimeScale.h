/*
 * @author Ashley Taylor
 * Date Created: 9/04/2020 (d/m/y, UTC+08:00)
 * @brief Interface for Time Scale classes
 * @see README.md file for full breakdown. 
 */

#ifndef ITimeScale_h
#define ITimeScale_h

#include "Arduino.h"

class ITimeScale
{
    public:
        virtual bool start() = 0;
        virtual void stop() = 0;
        virtual bool faultDetected() = 0;
        virtual bool setTime(uint8_t hours, uint8_t minutes, uint8_t seconds) = 0;

        virtual ~ITimeScale() { Serial.println(F("ITimeScale destroyed")); }
};

#endif
