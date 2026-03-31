#include <iostream>
 
// Declare a Global constant for the maximum speed of the robot
const float MAX_SPEED = 5.0;  // Maximum speed in meters per second
 
int main() {

    // Declaring Local Constant.
    const double MAIN_POWER = 78.56;
    std::cout << "The maximum speed of the robot is: " << MAX_SPEED << " m/s" << std::endl;
    std::cout << "The maximum power allowed to the robot here is : " << MAIN_POWER << " m/s" << std::endl;
    // Attempting to change the constant will cause a compile-time error
    // MAX_SPEED = 6.0;  // Uncommenting these lines will result in an error
    // MAIN_POWER = 89;

 
    return 0;
}