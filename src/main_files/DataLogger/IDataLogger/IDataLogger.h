/**
 * @author Jarod Harris
 * @date 22/04/2020 (d/m/y, UTC+08:00)
 * @brief IDataLogger for ClimbingClock logger
 * @see README.md file for full breakdown. 
 */

#ifndef IDataLogger_h
#define IDataLogger_h

#include "Arduino.h"

/**
 * @brief Interface for data logging
 */
class IDataLogger
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
         * @brief Set the alert level
         */
        virtual void setLevel(int level) = 0;

        /**
         * @brief Get the alert level
         * @return The alert level as integer
         */
        virtual int getLevel() = 0;

        /**
         * @brief Log a debug message concerning the specified subsystem
         * @param message The text of the alert
         * @param timestamp Date and time string
         * @param subsystem Name of relevant subsystem for alert
         */
        virtual void logDebug(char[] timestamp, char[] subsystem, char[] message) = 0;

        /**
         * @brief Log an information message concering the specified subsystem
         * @param message The text of the alert
         * @param timestamp Date and time string
         * @param subsystem Name of relevant subsystem for alert
         */
        virtual void logInfo(char[] timestamp, char[] subsystem, char[] message) = 0;
        /**
         * @brief Log a warning message concerning the specified subsystem
         * @param message The text of the alert
         * @param timestamp Date and time string
         * @param subsystem Name of relevant subsystem for alert
         */
        virtual void logWarning(char[] timestamp, char[] subsystem, char[] message) = 0;
        /**
         * @brief Log an error message concerning specified subsystem
         * @param message The text of the alert
         * @param timestamp Date and time string
         * @param subsystem Name of relevant subsystem for alert
         */
        virtual void logError(char[] timestamp, char[] subsystem, char[] message) = 0;
           virtual ~IDataLogger() {
            // Use line below to confirm destructor works
            // Serial.println(F("IDataLogger destroyed"));
        }
};

#endif
