/**
 * @author Ashley Taylor
 * @author Harrison Outram
 * @date 9/04/2020 (d/m/y, UTC+08:00)
 * @brief IHeatRegulator for both Hare and Tortoise Code
 * @see README.md file for full breakdown. 
 */

#ifndef IHeatRegulator_h
#define IHeatRegulator_h

#include "Arduino.h"

/**
 * @brief Interface for heat regulators
 */
class IHeatRegulator
{
    public:
        /**
         * @brief Initialise hardware
         */
        virtual bool start() = 0;

        /**
         * @brief Stop all hardware
         */
        virtual void stop() = 0;

        /**
         * @brief Get the temperature reading in celcius
         * @return The temperature
         */
        virtual int getTempt() = 0;

        /**
         * @brief Detect if a fault occured
         * @details Returns 0 if no fault occured, otherwise returns an
         * implementation specific code
         * @return The fault code
         */
        virtual int faultDetected() = 0;

        /**
         * @brief Set the cooling power level
         * @param power The power level from temptToPower()
         */
        virtual bool setCooling(uint8_t power) = 0;

        /**
         * @brief Converts temperature reading to power level
         * @return The recommended cooling power level
         */
        virtual uint8_t temptToPower(int tempt) = 0;

        virtual ~IHeatRegulator() {
            // Use line below to confirm destructor works
            // Serial.println(F("IHeatRegulator destroyed"));
        }
};

#endif
