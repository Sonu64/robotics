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
Robot::Robot(std::string robot_name) : name(robot_name) {
    cout << "Robot initialized with name: " << name << endl;
}



int main() {
    //static allocation !
    DistanceSensor sensor(100.0);
    sensor.displayRange();
    cout << "Current distance reading: " << sensor.getDistance() << " meters." << endl;

    Robot myRobot("Frankestein");
    myRobot.shout();

    return 0;
}