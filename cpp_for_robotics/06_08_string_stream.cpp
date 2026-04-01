#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    stringstream myStream;
    int motorSpeed;
    double batteryLevel;

    myStream << "Enter Motor Speed (m/s) and Battery Level of the Robot\n";

    string prompt = myStream.str();
    cout << prompt;

    cin >> motorSpeed;
    if (!cin) {
        cerr << "Please provide Valid Input !";
        return 1;
    }

    cin >> batteryLevel;
        if (!cin) {
        cerr << "Please provide Valid Input !";
        return 1;
    }


    // Clearing the Stream with Empty String !
    
    myStream.str("");
    myStream << "Robot Details\nMotor Speed: " << motorSpeed << "m/s, Battery Level: " << batteryLevel << endl;

    cout << myStream.str();
    
    return 0;

}
