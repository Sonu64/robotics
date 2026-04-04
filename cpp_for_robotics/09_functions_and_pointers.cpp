#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

// Function prototype, Declaration
double calculate_distance(double x1, double y1, double x2, double y2);










int main() {

    // C++ provided functions, like from the cmath lib.
    double angle = 45.0;
    double radians = angle * M_PI / 180.0;
 
    // the cmath provided sin and cosine functions need angle values in radians,
    // but humans generally find degrees more intuitive. So we need
    // to convert angle from DEGREE to RADIANS.
    double sine = sin(radians); // 1 / √2
    double cosine = cos(radians);  // 1 / √2
 
    cout << "Sine: " << sine << endl;
    cout << "Cosine: " << cosine << endl;














    // Usage of User-defined Functions
    double required_distance = calculate_distance(0, 0, 12.5, 10);
    stringstream response_builder;
    response_builder << "Distance = " << required_distance;
    string response = response_builder.str();
    cout << response << endl;








    // Pointers, an easy way to understand the basics can be as follows... 
    // '*' stands for value at address 
    // '&' stands for address of
    int robot_id = 42;
    int* ptr = &robot_id;
 
    cout << "Robot ID: " << robot_id << endl;
    cout << "Pointer Value: " << ptr << endl;
    cout << "Dereferenced Pointer: " << *ptr << endl;
 
    *ptr = 99;
    cout << "Updated Robot ID: " << robot_id << endl;

    return 0;
}









// Function Definition.
// Function that calculates distance using your fav Distance Formula !
double calculate_distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double distance = sqrt((dx*dx) + (dy*dy));
    return distance;
}