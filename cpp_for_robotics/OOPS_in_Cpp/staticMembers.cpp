#include <iostream>
#include <string>
using namespace std;

class RobotInitializer {
    private:
        string robot_name;
    public:
        static int robot_count; // declaration only allowed here

        RobotInitializer(string robot_name) {
            this->robot_name = robot_name;
            robot_count++;
            cout << "Initializing Robot number: " << robot_count << endl;
        }

        void setRobotName(string robot_name) {
            this->robot_name = robot_name;
        }
        string getRobotName() {
            return this->robot_name;
        }

        ~RobotInitializer() {
            cout << "Bot Deleted, Memory Freed !" << endl;
        }
    };

int RobotInitializer::robot_count = 0;
// definition + initialization of static member must be set outside class

int main(int argc, char* argv[]) {
    if( argc != 2) {
        cerr << "Please specify One Robot Name !" << endl;
        cout << "Command Usage : ./a.out [ROBOTNAME]" << endl;
        return 1;
    }
    string robot_name = argv[1], new_bot_name = "";
    RobotInitializer* bot1 = new RobotInitializer(robot_name);
    cout << "Robot Name is - " << bot1->getRobotName() << endl;
    cout << "Enter New Robot Name: ";
    cin >> new_bot_name;
    bot1->setRobotName(new_bot_name);
    cout << "New Robot Name is - " << bot1->getRobotName() << endl;

    delete bot1;

    
    RobotInitializer* bot2 = new RobotInitializer(robot_name);
    cout << "Robot Name is - " << bot2->getRobotName() << endl;
    cout << "Enter New Robot Name: ";
    cin >> new_bot_name;
    bot2->setRobotName(new_bot_name);
    cout << "New Robot Name is - " << bot2->getRobotName() << endl;
    delete bot2;

    return 0;
}


/* * ARCHITECT'S NOTE:
 * We use std::string for 'robot_name' to ensure "Deep Copy" and "Memory Safety."
 * * Why it's safer: 
 * 1. Automatically converts 'const char*' (literals like "Doraemon") to 'std::string'.
 * 2. Prevents "Dangling Pointers" by creating its own memory buffer on the Heap.
 * 3. Handles its own deallocation (No manual 'free' needed for the string itself).
 * * Use raw 'char*' only when:
 * - Interfacing with C-based hardware APIs (LiDAR/Sensors).
 * - Writing ultra-low-latency code where object overhead must be zero.
 */