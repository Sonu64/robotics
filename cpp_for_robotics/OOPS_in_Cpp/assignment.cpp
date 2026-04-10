#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Interface
class RobotInterface {
    public:
        virtual void move() = 0;
        virtual void showStatus() = 0;
        ~RobotInterface() {}
};

// Abstract class,  extending from the interface
class MovingRobot : public RobotInterface {
    protected:
        int id;
        string robotName;
        int battery_level;
    public:
        MovingRobot(int id, string robot_name, int battery_level) {
            this->id = id;
            this->robotName = robot_name;
            this->battery_level = battery_level;
        }
        void showStatus() {
            cout << "A Moving Robot with ID = " << this->id << endl;
            cout << "Moving Robot Name: " << this->robotName << ", Battery Level: " << this->battery_level << "%. " << endl;
        }
        ~MovingRobot() {
            cout << "Deleting MovingRobot with ID = " << this->id << endl;
        }
        // still got a pure virtual, undefined func, move() !!!, so we need lowest level abstraction for that
};

class Drone : public MovingRobot {
    
}