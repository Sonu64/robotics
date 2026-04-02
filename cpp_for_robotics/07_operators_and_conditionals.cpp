#include <iostream>
using namespace std;
 
int main() {
    // Basic arithmetic operations
    int motor_speed = 100;    // Base speed
    int speed_increment = 20; // Speed adjustment
 
    // Addition
    int increased_speed = motor_speed + speed_increment;
     
    // Subtraction
    int decreased_speed = motor_speed - speed_increment;
     
    // Multiplication
    int double_speed = motor_speed * 2;
     
    // Division
    int half_speed = motor_speed / 2;
     
    // Modulus (remainder)
    int remainder = motor_speed % 30;
 
    // Output results
    cout << "Original Speed: " << motor_speed << endl;
    cout << "Increased Speed: " << increased_speed << endl;
    cout << "Decreased Speed: " << decreased_speed << endl;
    cout << "Double Speed: " << double_speed << endl;
    cout << "Half Speed: " << half_speed << endl;
    cout << "Remainder: " << remainder << endl;



















    /*Conditionals*/
    double battery_level = 0.05;
    bool obstacle_detected = true;
 
    if (battery_level > 0.5 && !obstacle_detected) {
        cout << "Robot is moving forward." << endl;
    } 
    else if (battery_level > 0.5 && obstacle_detected) {
        cout << "Robot is avoiding the obstacle." << endl;
    } 
    else {
        cout << "Robot is stopping due to low battery." << endl;
    }
















    int distance_to_obstacle = 50;
 
    if (distance_to_obstacle < 30) {
        cout << "Robot is stopping to avoid collision." << endl;
    }
    else if (distance_to_obstacle < 60) {
        cout << "Robot is slowing down." << endl;
    } 
    else if (distance_to_obstacle < 100) {
        cout << "Robot is moving forward cautiously." << endl;
    } 
    else {
        cout << "Robot is moving forward at full speed." << endl;
    }









    // For Loops
    int robot_positions[] = {0, 10, 20, 30, 40};
 
    for (int i = 0; i < 5; i++) {
        cout << "Robot Position: " << robot_positions[i] << endl;
    }











    // While Loop
    int distance = 0;
    int target_distance = 100;
    int step_size = 10;
 
    while (distance < target_distance) {
        distance += step_size;
        cout << "Robot moved " << distance << " units" << endl;
    }
 
    cout << "Robot reached the target distance." << endl;
 
    int countdown = 5;
    while (countdown > 0) {
        cout << "Countdown: " << countdown << endl;
        countdown--;
    }
 
    cout << "Countdown finished. Launching the robot!" << endl;


    // Do-while Loop
    int new_count = 0;
 
    do {
        cout << "Robot iteration: " << new_count << endl;
        new_count++;
    } while (new_count < 3);
 

    return 0;
}