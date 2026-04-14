/// @brief This file demonstrates some more object-oriented programming concepts in C++, such as inheritance, polymorphism, and virtual functions. We will create a base class called "Robot" and a derived class called "AdvancedRobot" that inherits from Robot. The AdvancedRobot class will override some of the member functions of the Robot class to provide additional functionality. We will also demonstrate the use of virtual functions to achieve polymorphism, allowing us to call the overridden functions through a base class pointer. Finally, we will show how to use dynamic memory allocation to create objects on the heap and manage their lifetimes properly.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Robot{
    private:
        string name;
        int battery_level;
    public:
        /// @brief Demonstration of setters and getters
        void setName(string robot_name) {
            this->name = robot_name;
        }
        string getName() {
            return this->name;
        }
        void setBatteryLevel(int battery) {
            this->battery_level = battery;
        }
        int getBatteryLevel() {
            return this->battery_level;
        }
}