#include <iostream>
#include <memory>
#include <utility>

using namespace std;


class Robot {
    private:
        int battery_level;
    public:
        /// @brief Constructor
        Robot(int battery_level) {
            this->battery_level = battery_level;
            cout << "Robot Initialized..." << endl;
        }
        /// @brief Sample function to print
        void sayHello() {
            cout << "Hello ! I'm a Robot ! Beep Bop !" << endl;
            cout << "My Battery Level is " << battery_level << "%." << endl;
        }
        /// @brief Destructor
        ~Robot() {
            cout << "Robot Deleted..." << endl;
        }
};

// Normal function acting as a "factory" — creates the object in its own scope
shared_ptr<Robot> makeRobot() {
    shared_ptr<Robot> localRobot = make_shared<Robot>(99);
    cout << "[factory] localRobot use_count = " << localRobot.use_count() << endl; // 1
    return localRobot;    // ownership is transferred to caller — Robot NOT deleted here
}

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
    unique_ptr<Robot> robotPointer = make_unique<Robot>(23);

    robotPointer->sayHello();



























    /*  SHARED SMART POINTERS  */
    shared_ptr<Robot> myRobu = make_shared<Robot>(57);
    cout << "Shared Count = " << myRobu.use_count() << endl; // 1
    
    // they can be shared
    shared_ptr<Robot> bidhuShekhor = myRobu;
    cout << "Shared Count = " << myRobu.use_count() << endl; // 2 now !

    // =========================================================
    //  EXISTENCE BEYOND CURRENT SCOPE  (shared_ptr behaviour)
    // =========================================================

    // ---------------------------------------------------------
    // Example 1: Factory Function
    // A function creates a Robot on the heap and returns a
    // shared_ptr. The Robot outlives the function's own scope
    // because the caller now co-owns it.
    // ---------------------------------------------------------

    // Call the newly extracted makeRobot function
    shared_ptr<Robot> survivingRobot = makeRobot();
    cout << "[main] survivingRobot use_count = " << survivingRobot.use_count() << endl; // 1
    survivingRobot->sayHello(); // Robot is still alive and usable


    // ---------------------------------------------------------
    // Example 2: Scope Block — one owner dies, object survives
    // because a second owner (outer scope) still holds a ref.
    // ---------------------------------------------------------

    shared_ptr<Robot> outerOwner = make_shared<Robot>(42);
    cout << "\n[outer] use_count before block = " << outerOwner.use_count() << endl; // 1

    {
        // Inner scope — a second shared_ptr points to the SAME Robot
        shared_ptr<Robot> innerOwner = outerOwner;
        cout << "[inner] use_count inside block = " << outerOwner.use_count() << endl; // 2

        // innerOwner goes out of scope here — ref count drops to 1
        // Robot is NOT destroyed because outerOwner still exists
    }

    cout << "[outer] use_count after block  = " << outerOwner.use_count() << endl; // 1
    outerOwner->sayHello(); // Robot is STILL alive here — proved it survived the inner scope!

    // Now outerOwner itself goes out of scope at end of main → Robot finally gets deleted


    // ---------------------------------------------------------
    // Example 3: Contrast — unique_ptr CANNOT do this
    // A unique_ptr cannot be copied; ownership is exclusive.
    // Once the unique_ptr's scope ends, the object is GONE.
    // (Uncomment the commented lines below to see the contrast)
    // ---------------------------------------------------------

    {
        unique_ptr<Robot> exclusiveRobot = make_unique<Robot>(7);
        // unique_ptr<Robot> secondOwner = exclusiveRobot; // COMPILE ERROR — no shared ownership
        // The only option is std::move(), which leaves exclusiveRobot as nullptr
        cout << "\n[unique_ptr] Robot alive inside block." << endl;
        exclusiveRobot->sayHello();
    }  // <-- exclusiveRobot scope ends here → Robot is destroyed IMMEDIATELY (no shared refs)
    cout << "[unique_ptr] Robot is now GONE. No way to access it from outer scope." << endl;




    return 0;
}