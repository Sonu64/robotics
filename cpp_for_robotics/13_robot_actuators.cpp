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


/// @brief  Here, the test_actuator function takes a reference (Actuator&) to an Actuator object. Using a reference ensures that no copying of the object occurs, which enhances efficiency by saving memory and processing time. It also guarantees that the passed object is valid since references cannot be null, adding a layer of safety to our function. 
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