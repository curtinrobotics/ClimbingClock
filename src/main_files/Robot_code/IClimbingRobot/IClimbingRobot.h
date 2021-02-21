/*
 * @authors Ashley Taylor, Harrison Outram
 * Date Created: 2/04/2020 (d/m/y, UTC+08:00)
 * @brief IRobot for both Hare and Tortoise Code
 * @see README.md file for full breakdown.
 */

#ifndef IClimbingRobot_h
#define IClimbingRobot_h

#include "Arduino.h"

class IClimbingRobot
{
    public:
        virtual bool start() = 0;
        virtual void stop() = 0;
        virtual bool goUp() = 0;
        virtual bool goDown() = 0;
        virtual int getPosition() = 0;
        virtual int getDirection() = 0;
        virtual int faultDetected() = 0;
        virtual bool cycleDone() = 0;
        
        virtual ~IClimbingRobot() { Serial.println(F("IRobot destroyed")); }
};

#endif
