#include <iostream>
#include <memory>
 
// Sensor class representing a sensor with a name and a value
class Sensor {
private:
    std::string name;
    double value;
 
public:

    // Below, name is taken by ref just to avoid Extra copying for long strings, a large data chunk.. But value is a small data chunk, which makes more sense to be passed by value. Copying a small, primitive type is actually faster and more efficient than creating a reference (which is essentially a pointer under the hood) and dereferencing it.

    Sensor(const std::string& name, double value) : name(name), value(value) {}
 
    void printInfo() const {
        std::cout << "Sensor: " << name << ", Value: " << value << std::endl;
    }
};
 
int main() {
    // Create a unique_ptr to a Sensor object
    std::unique_ptr<Sensor> sensor1 = std::make_unique<Sensor>("TemperatureSensor", 25.5);
    sensor1->printInfo();

 
    // Create a shared_ptr to a Sensor object
    std::shared_ptr<Sensor> sensor2 = std::make_shared<Sensor>("HumiditySensor", 60.0);
    sensor2->printInfo();
 
    // Create a weak_ptr to the shared_ptr
    std::weak_ptr<Sensor> weak_sensor = sensor2;

    if (auto shared_sensor = weak_sensor.lock()) { // if the sensor2 still exists and is valid... then temporarily make the weak_ptr a shared_ptr by locking and then prinnt the info.

        shared_sensor->printInfo();
        // PRACTICE: Using the newly locked 'shared_sensor' instead of the original 'sensor2' guarantees thread-safe, temporary ownership. It ensures the object won't be deleted (e.g., by another thread) while we are actively using it inside this block.
    }
 
    return 0;
}