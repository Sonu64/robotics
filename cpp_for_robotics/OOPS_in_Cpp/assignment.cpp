#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Interface
class RobotInterface {
    public:
        virtual void move() = 0;
        virtual void showStatus() = 0;
        virtual ~RobotInterface() {}
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
    //...protected members are inherited already---> But they dont't have their values yet , so if we wanna give values, we will take them as args herein constrcutor and then chain that for the parent constrcutor call... 
    protected:
        int altitude;
    public:
        Drone(int drone_id, string drone_name, int drone_battery_level, int altitude) : MovingRobot(drone_id, drone_name, drone_battery_level) {
            this->altitude = altitude;
            cout << "Initializing Drone..." << endl;
        }
        void move() {
            cout << "Soaring into the heights... [Altitude = " << this->altitude << " meters]" << endl;
        }
        ~Drone() {
            cout << "Deleting Drone..." << endl;
        }
};






class UnderWaterBot : public MovingRobot {
    //...protected members are inherited already---> But they dont't have their values yet , so if we wanna give values, we will take them as args herein constrcutor and then chain that for the parent constrcutor call... 
    protected:
        int depth;
    public:
        UnderWaterBot(int underwater_bot_id, string underwater_bot_name, int underwater_bot_battery_level, int depth) : MovingRobot(underwater_bot_id, underwater_bot_name, underwater_bot_battery_level) {
            this->depth = depth;
            cout << "Initializing Underwater Bot..." << endl;
        }
        void move() {
            cout << "Diving into the depths... [Depth = " << this->depth << " meters]" << endl;
        }
        ~UnderWaterBot() {
            cout << "Deleting Underwater Bot..." << endl;
        }
};






class Rover : public MovingRobot {
    //...protected members are inherited already---> But they dont't have their values yet , so if we wanna give values, we will take them as args herein constrcutor and then chain that for the parent constrcutor call... 
    protected:
        int distance_traveled;
    public:
        Rover(int rover_id, string rover_name, int rover_battery_level, int distance_traveled) : MovingRobot(rover_id, rover_name, rover_battery_level) {
            this->distance_traveled = distance_traveled;
            cout << "Initializing Rover..." << endl;
        }
        void move() {
            cout << "Traversing the terrain... [Distance Traveled = " << this->distance_traveled << " meters]" << endl;
        }
        ~Rover() {
            cout << "Deleting Rover..." << endl;
        }
};


int main() {
    // mind the line below
    // -> A Vector containing Dynamically allocated Robots (Polymorphic objects)
    /// thats why using * notation.
    vector<RobotInterface*> fleet;

    fleet.push_back(new Drone(1, "Sky-01", 85, 120));
    fleet.push_back(new UnderWaterBot(2, "Aqua-Explorer", 90, 50));
    fleet.push_back(new Rover(3, "Ground-Alpha", 75, 200));

    cout << "--- Initializing Fleet Mission ---" << endl;

    for (RobotInterface* bot : fleet) {
        bot->showStatus();
        bot->move(); // Polymorphism: The right 'move' is called at runtime!
        cout << "--------------------------------" << endl;
    }

    // Cleaning up the Heap (The Architect's duty)
    for (RobotInterface* bot : fleet) {
        delete bot; // This will call the appropriate destructor due to virtual destructors in the base class.
    }
    fleet.clear();

    return 0;
}