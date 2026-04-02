#include <iostream>
 
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
    std::cout << "Original Speed: " << motor_speed << std::endl;
    std::cout << "Increased Speed: " << increased_speed << std::endl;
    std::cout << "Decreased Speed: " << decreased_speed << std::endl;
    std::cout << "Double Speed: " << double_speed << std::endl;
    std::cout << "Half Speed: " << half_speed << std::endl;
    std::cout << "Remainder: " << remainder << std::endl;

















    

    /*Conditionals*/
    double battery_level = 0.05;
    bool obstacle_detected = true;
 
    if (battery_level > 0.5 && !obstacle_detected) {
        std::cout << "Robot is moving forward." << std::endl;
    } 
    else if (battery_level > 0.5 && obstacle_detected) {
        std::cout << "Robot is avoiding the obstacle." << std::endl;
    } 
    else {
        std::cout << "Robot is stopping due to low battery." << std::endl;
    }
















    int distance_to_obstacle = 50;
 
    if (distance_to_obstacle < 30) {
        std::cout << "Robot is stopping to avoid collision." << std::endl;
    }
    else if (distance_to_obstacle < 60) {
        std::cout << "Robot is slowing down." << std::endl;
    } 
    else if (distance_to_obstacle < 100) {
        std::cout << "Robot is moving forward cautiously." << std::endl;
    } 
    else {
        std::cout << "Robot is moving forward at full speed." << std::endl;
    }

    return 0;
}