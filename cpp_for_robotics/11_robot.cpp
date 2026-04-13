/// @file 11_robot.cpp
/// @brief This file contains the implementation of the Robot class declared in 11_robot.hpp,
/// as well as a simple demonstration of its usage in the main() function. The Robot class has private members for name and battery level, a protected member for id, and public members including a static count of Robot instances, a constructor, a destructor, and member functions to shout, show battery level, and show distance (overloaded). The main() function also demonstrates the use of a simple DistanceSensor class to show how we can use multiple classes together in a program. This file should be compiled together with 10_oops1.cpp to create an executable that demonstrates the functionality of the Robot class.



#include "11_robot.hpp"
#include <iostream>

using namespace std;

// ... Generally the below code should be in a sepearte .cpp file like 11_robot.cpp, but for simplicity and demonstration purposes, we are keeping it here in the same file. In a real project, you should separate the declaration (in .hpp) and definition (in .cpp) of your classes for better organization and maintainability.

// Defining the member function of Robot class declared in the header file
/// @brief a simple member functionn
/// @return none
/// @param none
void Robot::shout() {
    cout << "I am a Robot! Beep Boop! My name is " << name << "." << endl;
}
// Defining the constructor of Robot class declared in the header file
Robot::Robot(std::string robot_name, int battery) : name(robot_name), battery_level(battery) {
    count++; // Increment the static count whenever a new Robot is created
    cout << "Robot initialized with name: " << name << " and battery level: " << battery_level << "%." << endl;
}
//Defining Destructor of Robot class, it will be called when an object goes out of scope or is explicitly deleted, it will decrement the count of Robot instances
Robot::~Robot() {
    cout << "Robot " << name << " is being destroyed." << endl;
    count--;
    cout << "Current Robot count after destruction: " << count << endl;
}

//..defining the showBatteryLevel() member function of Robot class declared in the header file
void Robot::showBatteryLevel() {
    cout << "Battery Level: " << battery_level << "%." << endl;
}

int Robot::count = 0; // Initialize the static member variable count to 0

int Robot::getCount() {
    return count; // Return the current count of Robot instances
}

void Robot::showDistance(int distance) {
    cout << "The distance to the object is: " << distance << " meters." << endl;
}

void Robot::showDistance(double x, double y) {
    cout << "Moving to position (" << x << ", " << y << ")." << endl;
}