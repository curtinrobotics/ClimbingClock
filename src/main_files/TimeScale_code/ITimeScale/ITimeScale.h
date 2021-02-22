/**
 * @author Ashley Taylor
 * @author Harrison Outram
 * @date 9/04/2020 (d/m/y, UTC+08:00)
 * @brief Interface for Time Scale classes
 * @see README.md file for full breakdown. 
 */

#ifndef ITimeScale_h
#define ITimeScale_h

#include "Arduino.h"

/**
 * @brief Interface for time scales
 */
class ITimeScale
{
    public:

        /**
         * @brief Initialise the time scale's hardware
         * @return Whether the time scale initialised correctly
         */
        virtual bool start() = 0;

        /**
         * @brief Stops the time scale
         */
        virtual void stop() = 0;

        /**
         * @brief Detect if a fault occured
         * @details Returns 0 if no fault occured, otherwise returns an
         * implementation specific code
         * @return The fault code
         */
        virtual int faultDetected() = 0;

        /**
         * @brief Sets the time
         * @param hours The hour of the day from 0-23
         * @param minutes The minutes from 0-59
         * @param seconds The seconds from 0-59
         * @return Whether the time was set or not
         */
        virtual bool setTime(uint8_t hours, uint8_t minutes, uint8_t seconds) = 0;

        virtual ~ITimeScale() {
            // Uncomment line below to confirm destructor works
            // Serial.println(F("ITimeScale destroyed"));
        }
};

#endif
