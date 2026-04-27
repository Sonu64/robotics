#include <iostream>
#include <memory>

using namespace std;
 
// Sensor class representing a sensor with a name and a value
class Sensor {
private:
    string name;
    double value;
 
public:

    // Below, name is taken by ref just to avoid Extra copying for long strings, a large data chunk.. But value is a small data chunk, which makes more sense to be passed by value. Copying a small, primitive type is actually faster and more efficient than creating a reference (which is essentially a pointer under the hood) and dereferencing it.

    Sensor(const string& name, double value) : name(name), value(value) {}
 
    void printInfo() const {
        cout << "Sensor: " << name << ", Value: " << value << endl;
    }
};
 
int main() {
    // Create a unique_ptr to a Sensor object
    unique_ptr<Sensor> sensor1 = make_unique<Sensor>("TemperatureSensor", 25.5);
    sensor1->printInfo();

 
    // Create a shared_ptr to a Sensor object
    shared_ptr<Sensor> sensor2 = make_shared<Sensor>("HumiditySensor", 60.0);
    sensor2->printInfo();
 
    // Create a weak_ptr to the shared_ptr
    weak_ptr<Sensor> weak_sensor = sensor2;

    if (auto shared_sensor = weak_sensor.lock()) { // if the sensor2 still exists and is valid... then temporarily make the weak_ptr a shared_ptr by locking and then prinnt the info.

        shared_sensor->printInfo();
        // PRACTICE: Using the newly locked 'shared_sensor' instead of the original 'sensor2' guarantees thread-safe, temporary ownership. It ensures the object won't be deleted (e.g., by another thread) while we are actively using it inside this block. 
        
        // Because sensor2 may come from another file, and inside that file there maybe some logic which will try to delete the sensor2 object, but we can't afford that to happen, if we are using it here, though temporarily. Once we are out of here, that file can delete it safely. But while we are here, no other file can delete it ! Even the main owner can't, because we are also an "Owner", maybe temporary, but "Owner" is owner !!! File ~ Thread ~ Module...whatever it may be ! Its like Temporary Insurance :) 
    }
 
    return 0;
}