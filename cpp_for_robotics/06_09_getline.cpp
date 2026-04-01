#include <iostream>
#include <string>

using namespace std;

int main() {
    string command;
    cout << "Enter Robot Command: ";

    // Receive input inclusive of Spaces or other Similar charaters
    getline(cin, command);

    cout << "Your Command is " << command << endl;

    return 0;

}