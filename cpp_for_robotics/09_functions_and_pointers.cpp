#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

// Function prototype, Declaration
double calculate_distance(double x1, double y1, double x2, double y2);

int main() {
    double angle = 45.0;
    double radians = angle * M_PI / 180.0;
 
    // the cmath provided sin and cosine functions need angle values in radians,
    // but humans generally find degrees more intuitive. So we need
    // to convert angle from DEGREE to RADIANS.
    double sine = sin(radians); // 1 / √2
    double cosine = cos(radians);  // 1 / √2
 
    cout << "Sine: " << sine << endl;
    cout << "Cosine: " << cosine << endl;

    double required_distance = calculate_distance(0, 0, 12.5, 10);
    stringstream response_builder;
    response_builder << "Distance = " << required_distance;
    string response = response_builder.str();
    cout << response << endl;

    return 0;
}

// Function that calculates distance using your fav Distance Formula !
double calculate_distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double distance = sqrt((dx*dx) + (dy*dy));
    return distance;
}