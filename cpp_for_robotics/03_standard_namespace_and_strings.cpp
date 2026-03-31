#include <iostream>
#include <string>

// Showing to use the Standard Namespace was the goal of this small tutorial. :)
using namespace std;

int main() {
    string robot_name = "SonuBot";
    double robot_battery = 87.3;
    bool is_robot_active = true;

    if(is_robot_active)
        cout << robot_name << " with " << robot_battery << "% Battery is Active :) " << endl;
    else
        cout << robot_name << " with " << robot_battery << "% Battery is Inactive :( " << endl;

    return 0;
}