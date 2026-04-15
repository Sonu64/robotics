/// @brief This file demonstrates some more object-oriented programming concepts in C++, such as inheritance, polymorphism, and virtual functions. We will create a base class called "Robot" and a derived class called "AdvancedRobot" that inherits from Robot. The AdvancedRobot class will override some of the member functions of the Robot class to provide additional functionality. We will also demonstrate the use of virtual functions to achieve polymorphism, allowing us to call the overridden functions through a base class pointer. Finally, we will show how to use dynamic memory allocation to create objects on the heap and manage their lifetimes properly.

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class RobotClass{


    private:
        string name;
        int battery_level;
    public:

        /// @brief Demonstration of simple virtual functions
        virtual void move() {
            cout << this->name << " is Moving..." << endl;
        }

        static int count; // Static member variable to keep track of the number of Robot instances !!! Public Static Var-> Directly accessible outside class using the class name without needing an object

        // Constructor to initialize the Robot object with a name and battery level
        RobotClass(string robot_name, int battery) : name(robot_name), battery_level(battery) {
            count++; // Increment the static count whenever a new Robot is created
            cout << "Robot initialized with name: " << name << " and battery level: " << battery_level << "%." << endl;
        }
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

        static int calculateDistance(double x1, double y1, double x2, double y2) {
            double dx = x2 - x1;
            double dy = y2 - y1;
            cout << "Can I access static variables ? YES -> count = " << RobotClass::count << endl; // Accessing static member variable inside a static member function
            cout << "Can I access non-static variables ? NO -> name = " << "Cannot access non-static member variable in static member function" << endl; // Cannot access non-static member variable inside a static member function
            return static_cast<int>(sqrt(dx * dx + dy * dy));
        }
};

class Drone : public RobotClass {

    public:
        // Constructor to initialize the Drone object using the base class constructor
        Drone(string drone_name, int battery) : RobotClass(drone_name, battery) {}  

    void move() override { // Override the move function from the base class to provide specific behavior for the Drone class
        cout << getName() << " is flying..." << endl; // Using the getter function to access the name of the drone
    }
};

int RobotClass::count = 0; // Initialize the static member variable count to 0, this must be done outside the class definition, and it is necessary to allocate storage for the static member variable. This line is crucial to avoid linker errors when using the static member variable in the program.

int main() {
    RobotClass robot1("Robo1", 100);
    RobotClass robot2("Robo2", 80);
    Drone* drone1 = new Drone("Drone1", 90);

    cout << "Current Robot count: " << RobotClass::count << endl; // Accessing static member variable directly using the class name

    cout << "Distance between (0,0) and (3,4) is: " << RobotClass::calculateDistance(0, 0, 3, 4) << " meters." << endl; // Calling static member function directly using the class name

    cout << "Calling move function for robot1: " << endl;
    robot1.move(); // Calls the move function of the RobotClass
    cout << "Calling move function for drone1: " << endl;
    drone1->move(); // Calls the overridden move function of the Drone class\

    // retouching pointers
    int number = 10;
    int* ptr = &number; // Pointer to an integer variable
    cout << "Value of number: " << number << endl; // Output: 10
    cout << "Value pointed to by ptr: " << *ptr << endl; // Output: 10

    cout << "While the value stored inside the ptr var is a hex address : " << ptr << endl; // Output: Hexadecimal address of the variable number

    *ptr = 20; // Modifying the value of number through the pointer
    cout << "Value of number after modification through pointer: " << number << endl; // Output: 20

    return 0;
}