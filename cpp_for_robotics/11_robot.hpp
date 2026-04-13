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
        /// @brief the constructor
        /// @param robot_name the name of the robot, default is "Unnamed Robot"
        /// @param battery the initial battery level of the robot, default is 100%
        /// @return none
        Robot(std::string robot_name = "Unnamed Robot", int battery = 100);
        /// @brief  the destructor, it will be called when an object goes out of scope or is explicitly deleted, it will decrement the count of Robot instances
        /// @return none
        ~Robot(); // Destructor declaration, it will be called when an object goes out of scope or is explicitly deleted, it will decrement the count of Robot instances
        /// @brief a simple member function to print a message with the robot's name
        /// @return none
        /// @param none
        void shout();
        /// @brief a member function to show the current battery level of the robot
        /// @return none
        /// @param none
        void showBatteryLevel();

        // functions to be overloaded
        void showDistance(int distance);
        void showDistance(double x, double y);

        static int getCount(); // Static member function to get the count of Robot instances, static functions only have access to static members of the class, they cannot access non-static members like name or battery_level


};

#endif
