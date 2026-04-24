#include <iostream>
#include <memory>

using namespace std;

class Robot {
    private:
        int battery_level = 87;
    public:
        Robot() {
            cout << "Robot initialized.." << endl;
        }
        void shout() {
            cout << "Hello, I',m a Robot! Beep Bop !" << endl;
        }
        int getBatteryLevel() const {
            return this->battery_level;
        }
        ~Robot() {
            cout << "Robot being destroyed..." << endl;
        }
};

Robot* createRobot() {
    //static allocation
    Robot myRobot;
    return &myRobot;
}
//....once the function call is over, myRobot memory is cleared from stack, but the pointer is still pointing to that address -> Resulting in a Bomb Blast at Hiroshima 💥 Dangling Pointers resuklting in Segmentation fault !!! Extremely Unsafe Code !!! You will not have any idea WTF will happen next !!!!!!

unique_ptr<Robot> createRobotSmartly() {
    //heap allocation with smart pointer
    auto myRobot = make_unique<Robot>();
    return myRobot;
}
// Smart Pointers are Safe and Beautiful, they persist and extend their Scope !!!! Fortunately no scope Limits or Dangling Pointers now ! And you want the Java vibe in C++ ? Smart pointers got you covered --> They automatically deallocate memory ! Such a cool thing they engineered ! C++ 🔥

int main() {
    auto robot = createRobot(); 
    // WHY DOES THIS WORK?!
    // 1. The memory for 'myRobot' was freed, but the OS hasn't overwritten those bytes with new data yet.
    // 2. shout() does not access any member variables (like int health or string name). 
    //    It only prints a static string. The compiler just jumps to the shout() instruction in memory,
    //    and since it doesn't need to read the corrupted "this" pointer, it doesn't crash!
    // Try adding "int id;" to Robot, assigning it in the constructor, and printing it in shout().
    // You will likely see a garbage value printed!
    robot->shout(); 
    // cout << robot->getBatteryLevel() << endl; // THIS CRASHES THE PROGRAM SILENTLY ON WINDOWS, AND EXPLICITLY STATING SEGMENTATION FAULT ON LINUX BASED SYSTEMS !
    
    cout << "\n--- Smart Pointer Output below ---" << endl;

    auto smartRobot = createRobotSmartly();
    smartRobot->shout();
    cout << smartRobot->getBatteryLevel() << endl;
}