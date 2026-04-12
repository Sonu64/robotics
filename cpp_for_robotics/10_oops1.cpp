// compiler specifed includes
#include <iostream>
// user defined includes
#include "11_robot.hpp"

using namespace std;

class DistanceSensor {
    private:
        double distance;
    public:
        DistanceSensor(double max_distance) : distance(max_distance) {
            cout << "Distance Sensor initialized with max distance: " << distance << " meters." << endl;
        }
        
        double getDistance() {
            return distance;
        }

        void displayRange() {
            cout << "Distance Sensor Range: 0 to " << distance << " meters." << endl;
        }
};

// ... Generally the below code should be in a sepearte .cpp file like 11_robot.cpp, but for simplicity and demonstration purposes, we are keeping it here in the same file. In a real project, you should separate the declaration (in .hpp) and definition (in .cpp) of your classes for better organization and maintainability.

// Defining the member function of Robot class declared in the header file
void Robot::shout() {
    cout << "I am a Robot! Beep Boop! My name is " << name << "." << endl;
}
// Defining the constructor of Robot class declared in the header file
Robot::Robot(std::string robot_name, int battery) : name(robot_name), battery_level(battery) {
    count++; // Increment the static count whenever a new Robot is created
    cout << "Robot initialized with name: " << name << " and battery level: " << battery_level << "%." << endl;
}
//..defining the showBatteryLevel() member function of Robot class declared in the header file
void Robot::showBatteryLevel() {
    cout << "Battery Level: " << battery_level << "%." << endl;
}

int Robot::count = 0; // Initialize the static member variable count to 0

int Robot::getCount() {
    return count; // Return the current count of Robot instances
}



int main() {
    //static allocation !
    DistanceSensor sensor(100.0);
    sensor.displayRange();
    cout << "Current distance reading: " << sensor.getDistance() << " meters." << endl;

    Robot myRobot("Frankestein", 80);
    myRobot.shout();
    myRobot.showBatteryLevel();
    cout << "Total number of Robot instances: [Remember that the static var was public, that's why it was directly accessible, else we should use a getter as below...]" << Robot::count << endl;
    cout << "Getting total Robot Instances from the static member function: " << Robot::getCount() << endl;

    return 0;
}