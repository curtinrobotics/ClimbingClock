/*
 * Author: Ashley Taylor
 * Date Created: 9/04/2020 (d/m/y, UTC+08:00)
 * @brief ??
 * @see README.md file for full breakdown. 
 */

#ifdef ITimeScale_h
#define ITimeScale_h

#include "Arduino.h"

class ITimeScale
{
    
    public:
        virtual bool start() = 0;
        virtual void stop() = 0;
        virtual bool faultDetected() = 0;
        virtual bool setTime(/*parameter?*/) = 0;

        virtual ~ITimeScale() { Serial.println(F("ITimeScale destroyed")); }

};

#endif