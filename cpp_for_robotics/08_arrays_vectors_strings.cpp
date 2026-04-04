#include <iostream>
#include <vector>
#include <string>
#include <cctype>
 
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







    /* String Manipulation */
    string robot_name = "A-Dreamy-Bot-to-do-all-Dreamy-Tasks";
     
    // Accessing string characters
    cout << "Robot Name: " << robot_name << endl;
    cout << "First Character: " << robot_name[0] << endl;
     
    // Modifying strings, Character must,  Double quotes not allowed !
    robot_name[8] = '=';
    cout << "Modified Robot Name: " << robot_name << endl;

    // Concatenating strings, Double Quotes must !
    string model = "X100";
    string full_name = robot_name + " " + model;
    cout << "Full Name: " << full_name << endl;














    /* Employing Character functions */
    char command = 'f'; 
    // this should be a character ! so stringName[index] should also work !
 
    // Checking character properties
    if (islower(command)) {
        cout << "Command is lowercase" << endl;
    }
 
    // Converting character case
    char uppercase_command = toupper(command);
    cout << "Uppercase Command: " << uppercase_command << endl;
 
    // Checking character equality
    if (command == 'f') {
        cout << "Command is 'f'" << endl;
    }

    return 0;
}