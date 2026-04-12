#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>

class Robot {
    private:
        std::string name;
        
        int battery_level;
    protected:
        int id;
    public:
        static int count; // static member to keep track of the number of Robot instances, by deafult it is initialized to 0
        Robot(std::string robot_name = "Unnamed Robot", int battery = 100);
        void shout();
        void showBatteryLevel();

        static int getCount(); // Static member function to get the count of Robot instances, static functions only have access to static members of the class, they cannot access non-static members like name or battery_level
};

#endif
