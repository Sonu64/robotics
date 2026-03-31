#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    string robot_name;
    int robot_status;
    double x_pos, y_pos;

    cout << "Enter your Robot Name: ";
    cin >> robot_name;

    cout << "Enter Robot Status: (1 for ACTIVE, 0 for INACTIVE): ";
    cin >> robot_status;
    if (robot_status != 0 && robot_status != 1) {
        cout << "Invalid Input !\n";
        return 1;
    }

    cout << "X-Position: ";
    cin >> x_pos;

    cout << "Y-Position: ";
    cin >> y_pos;

    cout << "Initializing your Robot ";
    cout.flush(); // <--- ADD THIS LINE HERE TO REMOVE BUFFER
    for(int i = 0; i < 5; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << ".";
        cout.flush();
    }
    cout << endl;

    cout << "\nRobot Initialized Successfully !\n" << endl;
    cout << "--------- Robot Details ---------" << endl;
    cout << "Robot Name: " << robot_name << endl;
    robot_status == 1 ? cout << "Robot Status: ACTIVE" << endl : cout << "Robot Status: INACTIVE" << endl;
    cout << "Robot Coordinates: (" << x_pos << ", " << y_pos << ")" << endl;

}