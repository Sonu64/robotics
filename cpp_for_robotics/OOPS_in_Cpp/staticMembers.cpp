#include <iostream>
#include <string>
using namespace std;

class RobotInitializer {
    private:
        string robot_name;
    public:
        // Static Member Variables, belongs to class, not objects.
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

        // Static Member Method, can only access Static Member Vars, no 'this' keyword, as there
        // is no concept of 'current-object' here.
        static void showClassDetails() {
            cout << "This class is used to initialize Robots with a name." << endl;
            cout << "It created " << robot_count << " Robots till now." << endl;
        }

        ~RobotInitializer() {
            cout << "Bot Deleted, Memory Freed !" << endl;
        }
    };

int RobotInitializer::robot_count = 0;
// definition + initialization of static member must be set outside class


string getValidatedInput() {
    // Function to check Valid RobotNames, can't be empty or All-spaces. Special Chars allowed for now.
    string input;
    bool isValid = false;

    while (!isValid) {
        cout << "Enter New Robot Name: ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Error: Name cannot be empty!" << endl;
            continue;
        }

        // Check for all spaces
        bool hasNonSpace = false;
        for (char c : input) {
            if (c != ' ') {
                hasNonSpace = true;
                break;
            }
        }

        if (!hasNonSpace) {
            cout << "Error: Name cannot be just spaces!" << endl;
        } else {
            isValid = true;
        }
    }
    return input;
}

int main(int argc, char* argv[]) {
    if( argc != 2) {
        cerr << "Please specify One Robot Name !" << endl;
        cout << "Command Usage : ./a.out [ROBOTNAME]" << endl;
        return 1;
    }
    string robot_name = argv[1], new_bot_name = "";

    

    RobotInitializer* bot1 = new RobotInitializer(robot_name);
    cout << "Robot Name is - " << bot1->getRobotName() << endl;
    new_bot_name = getValidatedInput();
    bot1->setRobotName(new_bot_name);
    cout << "New Robot Name is - " << bot1->getRobotName() << endl;

    delete bot1;


    RobotInitializer* bot2 = new RobotInitializer(robot_name);
    cout << "Robot Name is - " << bot2->getRobotName() << endl;
    new_bot_name = getValidatedInput();
    bot2->setRobotName(new_bot_name);
    cout << "New Robot Name is - " << bot2->getRobotName() << endl;
    delete bot2;

    // Calling Static member function
    RobotInitializer::showClassDetails();

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