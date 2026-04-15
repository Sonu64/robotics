/// @brief This code demonstrates Polymorphism in C++, a very important OOP concept.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ActuatorInterface {
    public:
    virtual void activate() = 0; // Pure virtual function making this class an abstract class
};

class Motor : public ActuatorInterface {
    public:
    void activate() override { // Override the pure virtual function from the ActuatorInterface
        cout << "Motor is activated!" << endl;
    }
};

class Servo : public ActuatorInterface {
    public:
    void activate() override { // Override the pure virtual function from the ActuatorInterface
        cout << "Servo is activated!" << endl;
    }
};


/// @brief this function actually takes an actuator interface from the heap ! Dynamically allocated memory for the actuator interface, which can point to any derived class object (Motor or Servo) that implements the ActuatorInterface. This allows for polymorphic behavior, where the specific type of actuator can be determined at runtime. This is called Runtime Polymorphism, which is achieved through the use of virtual functions and pointers to base class objects. By using a pointer to the ActuatorInterface, we can call the activate() function without needing to know the specific type of actuator at compile time, allowing for flexibility and extensibility in our code.
void testActuator(ActuatorInterface& actuator) {
    actuator.activate(); // Call the activate function on the actuator interface, which will invoke the appropriate implementation based on the actual type of the actuator object passed in // since we are already using reference to the base class, we can directly call the activate function without needing to dereference a pointer or use the -> operator.
}


int main() {

    Motor motor;
    Servo servo;

    testActuator(motor);
    testActuator(servo);

    return 0;
}