#include <iostream>
#include <memory>
#include <utility>

using namespace std;


class Robot {
    public:
        /// @brief Constructor
        Robot() {
            cout << "Robot Initialized..." << endl;
        }
        /// @brief Sample function to print
        void sayHello() {
            cout << "Hello ! I'm a Robot ! Beep Bop !" << endl;
        }
        /// @brief Destructor
        ~Robot() {
            cout << "Robot Deleted..." << endl;
        }
};



int main() {
    int a = 11;

    /* Unique Smart Pointers, mostly created by the make_unique<typename>(variable name or value we want to store the addr of) */
    unique_ptr<int> unPtr1 = make_unique<int>(a);
    cout << unPtr1.get() << endl; // Use .get() to print the memory address
    cout << *unPtr1 << endl;      // Dereference to print the value

    // Why does a pointer "pointing to the same address" show a different address on .get()?
    // Answer: Because make_unique does NOT point to the local variable 'a'. 
    // Instead, make_unique<int>(a) allocates BRAND NEW memory on the heap and copies the *value* of 'a' (11) into it.
    // So unPtr1 and unPtr2 are pointing to two completely separate memory locations that just happen to hold the same value (11).
    unique_ptr<int> unPtr2 = make_unique<int>(a);
    cout << unPtr2.get() << endl;
    cout << *unPtr2 << endl;

    // the below code will not work !
    // unique_ptr<int> unPtr3 = unPtr1;
    // but Ownership can be changed
    unique_ptr<int> unPtr3 = move(unPtr1); // now unPtr1 becomes empty (nullptr)! 
    // WARNING: Dereferencing unPtr1 (e.g., *unPtr1) now causes Undefined Behavior (usually a Segmentation Fault), NOT a NullPointerException like in Java.
    cout << unPtr3.get() << endl;
    cout << *unPtr3 << endl;
    cout << unPtr1.get() << endl; // This will print 0 (nullptr)
    
    // cout << *unPtr1 << endl; // CRASHES program! 
    // ^ Expected a Segfault? You actually got one! 
    // On Windows/MinGW, segfaults (Access Violations) often just silently crash the program 
    // and return a non-zero exit code (like Exit Code: 1 or 3221225477). 
    // It doesn't always print "Segmentation fault" to the console like Linux does.
    // But windows is highly improbabilistic in these cases, so best use Linux based OSs like Ubuntu or something else. This program may run on windows perfectly without letting you know what exit code it returned ! This can corrupt other program data, without letting you know ! So, Ubuntu is used for ROS2 C++ code.

    // Demonstraing the automatic Deallocation behaviour
   // Remember Dynamic Object allocation ! We do that here as well, but we dont have to manually delete the pointers now.
    unique_ptr<Robot> robotPointer = make_unique<Robot>();

    robotPointer->sayHello();


    return 0;
}