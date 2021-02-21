/*
 * @authors Ashley Taylor, Harrison Outram
 * Date Created: 2/04/2020 (d/m/y, UTC+08:00)
 * @brief IRobot for both Hare and Tortoise Code
 * @see README.md file for full breakdown.
 */

#ifndef IClimbingRobot_h
#define IClimbingRobot_h

#include "Arduino.h"

enum Direction {D_UP, D_DOWN, D_TOP, D_BOTTOM, D_STILL};

class IClimbingRobot
{
    public:
        /**
         * @brief Initialises the robot's hardware
         * @return Whether the robot initialised correctly
         */
        virtual bool start() = 0;

        /**
         * @brief Stops the robot's hardware
         */
        virtual void stop() = 0;

        /**
         * @brief Tell the robot to go up
         * @return Whether the robot is actually going up or not
         */
        virtual bool goUp() = 0;

        /**
         * @brief Tell the robot to go down
         * @return Whether the robot will go down
         */
        virtual bool goDown() = 0;

        /**
         * @brief Get the position of the robot
         * @return A numbner from 0 (bottom) to a defined maximum, or -1 if
         * position is not known
         */
        virtual int getPosition() = 0;

        /**
         * @brief Get the direction the robot is moving
         * @return Code representing the direction the robot is moving
         */
        virtual Direction getDirection() = 0;

        /**
         * @brief Detect if a fault has occured
         * @details Returns 0 if no fault occured, otherwise returns an
         * implementation specific code
         * @return The fault code
         */
        virtual int faultDetected() = 0;

        /**
         * @brief Whether the robot has completed a cycle or not
         * @return `true` if enough time has passed or the robot has reached
         * the top, `false` otherwise
         */
        virtual bool cycleDone() = 0;

        virtual ~IClimbingRobot() {
            // Uncommment line below to confirm destructor works
            // Serial.println(F("IRobot destroyed"));
        }
};

#endif
