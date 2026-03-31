/*. In robotics, global variables can be used to manage state information 
that various parts of your program might need to access
, like sensor data or system status.*/
#include <iostream>
 
// Global variable for sensor status
bool sensor_triggered = false;
 
void checkSensor() {
    // Simulate sensor being triggered
    sensor_triggered = true;
}
 
int main() {
    std::cout << "Sensor initially triggered: " << (sensor_triggered ? "Yes" : "No") << std::endl;
    checkSensor();
    std::cout << "Sensor status after checking: " << (sensor_triggered ? "Yes" : "No") << std::endl;
    return 0;
}