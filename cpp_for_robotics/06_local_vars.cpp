#include <iostream>
 
int main() {
    // Integer variable
    int distance = 100; // Distance in centimeters
 
    // Floating-point variable
    float speed = 5.5; // Speed in meters per second
 
    // Character variable
    char direction = 'N'; // Direction as a cardinal point
 
    // Boolean variable
    bool is_active = true; // Status of the robot's motor
 
    // Output the variables
    std::cout << "Robot Status:" << std::endl;
    std::cout << "Distance: " << distance << " cm" << std::endl;
    std::cout << "Speed: " << speed << " m/s" << std::endl;
    std::cout << "Direction: " << direction << std::endl;
    std::cout << "Motor Active: " << (is_active ? "Yes" : "No") << std::endl;
 
    return 0;
}