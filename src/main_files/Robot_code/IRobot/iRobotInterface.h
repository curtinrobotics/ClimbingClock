//Author: A. Taylor
//Date Created: 2/04/2020
//Purpose: iRobotInterface for both Hare and Tortoise Code

#include <string>
#include <iostream>

class iRobotInterface
{
    //virtual functions 
    public:
        virtual std:: bool start() = 0;
        virtual std:: void stop() = 0;
        virtual std:: bool goUp() = 0;
        virtual std:: bool goDown() = 0;
        virtual std:: int getPosition() = 0;
        virtual std:: bool cycleDone() = 0;

};