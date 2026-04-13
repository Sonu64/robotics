// compiler specifed includes
#include <iostream>
// user defined includes
#include "11_robot.hpp" // Linker "stiches" the declaration of the class from the header file with its definition in the .cpp file, it allows us to separate the interface (in .hpp) from the implementation (in .cpp), which is a good practice for better organization and maintainability of code. Command should compile both the files together, for example: g++ 10_oops1.cpp 11_robot.cpp -o robot_program or simply g++ 10_oops1.cpp 11_robot.cpp to create an executable named a.out by default.

// g++ 10_oops1.cpp 11_robot.cpp -o robot_app
/* 
    What just happened?
        10_oops1.cpp: Compiles the main() logic.
        11_robot.cpp: Compiles the Robot logic.
        The Linker (ld): Joins them together into one executable called robot_app.
 */

using namespace std;
/// @brief a simple class to demonstrate Object Oriented Programming concepts in C++. It has private members for name and battery level, a protected member for id, and public members including a static count of Robot instances, a constructor, a destructor, and member functions to shout, show battery level, and show distance (overloaded).
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



int main() {
    //static allocation !
    DistanceSensor sensor(100.0);
    sensor.displayRange();
    cout << "Current distance reading: " << sensor.getDistance() << " meters." << endl;

    Robot myRobot("Frankestein", 80);
    myRobot.shout();
    myRobot.showBatteryLevel();
    myRobot.showDistance(5); // calling the first overloaded function
    myRobot.showDistance(3.5, 4.2); // calling the second

    cout << "Getting total Robot Instances from the static member function: " << Robot::getCount() << endl;

    return 0;
}