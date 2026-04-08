#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --- ABSTRACTION ---
// We use an Abstract Class (Interface) to define WHAT a robot must do,
// without specifying HOW it does it at this level.
class RobotInterface {
    public:
        virtual void move() = 0; // Pure Virtual Function (The blueprint)
        virtual void showStatus() = 0;
        virtual ~RobotInterface() {} // Virtual destructor for memory safety
};

// --- INHERITANCE ---
// BaseRobot acts as a parent, holding common attributes for all robots.
class BaseRobot : public RobotInterface {
    protected:
        // --- ENCAPSULATION ---
        // Attributes are hidden from the outside world. 
        // Accessed only via 'Getters' and 'Setters'.
        string robot_id;
        int battery_level;

    public:
        BaseRobot(string robot_id) {
            this->robot_id = robot_id;
            this->battery_level = 100;
        };

        // Encapsulation: Setter with a safety check (Validation)
        void updateBattery(int level) {
            if (level >= 0 && level <= 100) {
                battery_level = level;
            }
            else {
                cerr << "Invalid Battery Level !" << endl;
            }
        }
};

// --- INHERITANCE ---
// Drone inherits from BaseRobot. It is-a Robot.
class Drone : public BaseRobot {
public:
    //  : ParentClass(param) in C++ is equivalent to Java this->super(param) 
    // The only syntax difference is in Java this->super() is 1st line of constructor
    // body,  but in C++ : Parent() is called after Constructor signture, just before
    // the curly braces for the actual body starts !
    Drone(string id) : BaseRobot(id) {
        cout << "Drone Initializing..." << endl;
    }

    // --- POLYMORPHISM (Function Overriding) ---
    // The specific implementation of 'move' for a Flying Robot.
    void move() override {
        cout << "[UAV " << robot_id << "]: Taking off. Adjusting 4 rotors for flight." << endl;
    }

    void showStatus() override {
        cout << "Drone ID: " << robot_id << " | Battery: " << battery_level << "%" << endl;
    }
};

// --- INHERITANCE ---
// Rover inherits from BaseRobot.
class Rover : public BaseRobot {
public:
    Rover(string id) : BaseRobot(id) {
        cout << "Initializing Rover..." << endl;
    }

    // --- POLYMORPHISM (Function Overriding) ---
    // The specific implementation of 'move' for a Ground Robot.
    void move() override {
        cout << "[Rover " << robot_id << "]: Engaging differential drive wheels." << endl;
    }

    void showStatus() override {
        cout << "Rover ID: " << robot_id << " | Battery: " << battery_level << "%" << endl;
    }
};

int main() {
    // Creating a fleet using Polymorphism
    // We treat different objects as the base interface type.
    vector<RobotInterface*> fleet;

    fleet.push_back(new Drone("Sky-01"));
    fleet.push_back(new Rover("Ground-Alpha"));

    cout << "--- Initializing Fleet Mission ---" << endl;

    for (RobotInterface* bot : fleet) {
        bot->showStatus();
        bot->move(); // Polymorphism: The right 'move' is called at runtime!
        cout << "--------------------------------" << endl;
    }

    // Cleaning up the Heap (The Architect's duty)
    for (RobotInterface* bot : fleet) {
        delete bot;
    }

    return 0;
}