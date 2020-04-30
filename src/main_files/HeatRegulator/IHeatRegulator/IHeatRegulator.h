/*
 * Author: Ashley Taylor
 * Date Created: 9/04/2020 (d/m/y, UTC+08:00)
 * @brief IHeatRegulator for both Hare and Tortoise Code
 * @see README.md file for full breakdown. 
 */

#ifndef IHeatRegulator_h
#define IHeatRegulator_h

#include "Arduino.h"

class IHeatRegulator
{
    
    public:
        virtual bool start() = 0;
        virtual void stop() = 0;
        virtual int getTempt() = 0;
        virtual int faultDetected() = 0;
        virtual bool setCooling(uint8_t power) = 0;
        virtual uint8_t tempToPower(int tempt) = 0;

        virtual ~IHeatRegulator() { Serial.println(F("IHeatRegulator destroyed")); }

};

#endif
