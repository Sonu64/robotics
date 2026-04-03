#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {

    // ARRAYS 
    const int size = 5;
    int sensor_readings[size];
 
    // Initializing the array
    for (int i = 0; i < size; i++) {
        sensor_readings[i] = i * 10;
    }
 
    // Accessing array elements
    cout << "Sensor Readings:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Sensor " << i + 1 << ": " << sensor_readings[i] << endl;
    }












    // VECTORS
    vector<int> motor_speeds;
 
    // Adding elements to the vector
    motor_speeds.push_back(100);
    motor_speeds.push_back(200);
    motor_speeds.push_back(150);
 
    // Accessing vector elements
    cout << "Motor Speeds:" << endl;
    for (int i = 0; i < motor_speeds.size(); i++) {
        cout << "Motor " << i + 1 << ": " << motor_speeds[i] << endl;
    }
 
    return 0;
}