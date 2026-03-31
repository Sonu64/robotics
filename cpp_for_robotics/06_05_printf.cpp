#include <cstdio>
 
int main() {
    const char* robot_name = "RoboMate";
    float battery_percentage = 75.5f;
    int x_coordinate = 10;
    int y_coordinate = 20;
 
    printf("Robot Name: %s\n", robot_name);
    printf("Battery Level: %.4f%%\n", battery_percentage);
    printf("Robot Position: (%d, %d)\n", x_coordinate, y_coordinate);
 
    printf("Sending command to the robot...\n");
 
    // Simulating command execution
    printf("Command executed successfully!\n");
 
    return 0;
}