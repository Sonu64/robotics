#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>

class Robot {
    private:
        std::string name;
    public:
        Robot(std::string robot_name = "Unnamed Robot");
        void shout();
};

#endif
