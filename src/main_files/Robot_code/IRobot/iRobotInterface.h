/*
 * @author A. Taylor
 * Date Created: 2/04/2020 (d/m/y, UTC+08:00)
 * @brief iRobotInterface for both Hare and Tortoise Code
 */

#include "Arduino.h"

class iRobotInterface
{
    public:
        virtual bool start() = 0;
        virtual void stop() = 0;
        virtual bool goUp() = 0;
        virtual bool goDown() = 0;
        virtual int getPosition() = 0;
        virtual bool cycleDone() = 0;
};
