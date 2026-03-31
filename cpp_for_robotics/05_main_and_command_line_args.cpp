#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Command Line Arguments passed to the program are - " << endl;
    // cout << "0th Index by default contains program name." << endl;
    for(int i = 0; i < argc; i++) {
        if (i == 0)
            cout << "Index " << i << " (Program name by default): " << argv[i] << endl;
        else
            cout << "Index " << i << ": " << argv[i] << endl; 
    }  
    return 0;
}