/// @brief This code demonstrates Inheritance and Polymorphism in C++, a very important OOP concept.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/// @brief  "pure" ABSTRACT in C++ is equivalen to Java Interface. An abstract class is a class that cannot be directly used to create an object. 
// So, "pure" ABSTRACT (all  = 0) and "partially" ABSTRACT (some = 0) classes are used to define blueprints that other classes can implement. Neither can be used to directly create objects. Objects are instantiable via classes with all -> Defined !!!
class ActuatorInterface {
    public:
    virtual void activate() = 0; // Pure virtual function making this class an abstract class
};

// Motor and Servo both are inheriting from the ActuatorInterface and providing their own implementation of the activate function
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
    Motor* dynamicMotor = new Motor(); // Dynamically allocated Motor object on the heap
    (*dynamicMotor).activate(); // Activating the motor using the dynamically allocated object
    dynamicMotor->activate(); // Activating the motor using the pointer to the dynamically allocated object // Both syntaxes work ! But this ones used more commonly in C++ for accessing members of a class through a pointer

    /// @important: Always remember to deallocate memory for dynamically allocated objects to prevent memory leaks. In this case, we should delete the dynamicMotor object after we are done using it.
    delete dynamicMotor;

    testActuator(motor);
    testActuator(servo);

    return 0;
}