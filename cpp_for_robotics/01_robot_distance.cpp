#include <iostream>
using namespace std;

int main() {
    double speed = 0.5; //in m/s
    double time = 10; //in seconds

    /* Calculating Distance
        * The formula to calculate distance is:
        * distance = speed * time
    */
   
    double distance = speed * time; //distance = speed * time

    cout << "The robot will travel " << distance << " meters in " << time << " seconds." << endl;
    return 0;
}