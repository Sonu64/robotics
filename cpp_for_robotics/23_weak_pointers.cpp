#include <iostream>
#include <memory>

using namespace std;

class Robot;  // forward declaration

// ----------------------
// Sensor class
// ----------------------
class Sensor {
private:
    weak_ptr<Robot> robot_ptr;   // weak reference

public:
    void attachRobot(shared_ptr<Robot> robot) {
        robot_ptr = robot;
    }

    void sendData();
};

// ----------------------
// Robot class
// ----------------------
class Robot {
public:
    void processSensorData() {
        cout << "Robot: Processing sensor data...\n";
    }

    ~Robot() {
        cout << "Robot destroyed.\n";
    }
};

// ----------------------
// Sensor method definition
// ----------------------
void Sensor::sendData() {
    // Try to safely access Robot
    if (auto robot = robot_ptr.lock()) {
        robot->processSensorData(); // behaving like shared_ptr.
    } else {
        cout << "Robot no longer exists.\n";
    }
}

// ----------------------
// Main
// ----------------------
int main() {
    auto robot = make_shared<Robot>();
    Sensor lidar;

    lidar.attachRobot(robot);

    lidar.sendData();   // Robot exists

    robot.reset();      // Robot destroyed here

    lidar.sendData();   // Safe check using weak_ptr

    return 0;
}