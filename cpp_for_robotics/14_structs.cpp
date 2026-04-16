#include <iostream>
#include <string>
 
struct RobotSpec {
    std::string model;
    int max_speed;
    double weight;
};
 
void print_robot_spec(const RobotSpec& spec) {
    std::cout << "Model: " << spec.model << std::endl;
    std::cout << "Max Speed: " << spec.max_speed << " m/s" << std::endl;
    std::cout << "Weight: " << spec.weight << " kg" << std::endl;
}
 
int main() {
    RobotSpec robot = {"MobileBot", 5, 10.5};
    print_robot_spec(robot); 
    
    // nullptr cant be passed here ! So using the modern C++ style of passing the variable inside the function call directly without needing to create a pointer or reference variable for it. This is more concise and easier to read. And also safer because &robot can be null, but robot itself cannot be null. So we can directly pass the robot variable to the function without worrying about null pointers or references. 

    /// @important Notice that at the call site print_robot_spec(robot);, there is no & or *. It looks clean.
    // Pointers: print_robot_spec(&robot); (Manual addressing).
    // References: print_robot_spec(robot); (Automatic aliasing).

    return 0;
}