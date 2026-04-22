#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> sensor_readings{45, 89, 12, 47, 65};

    // We will use lamdba expression in the sort algo to sort in Descending order
    sort(sensor_readings.begin(), sensor_readings.end(), [](int a, int  b){
        return a > b;
    });

    cout << "Sensor Readings in Descending order - " << endl;
    for_each(sensor_readings.begin(), sensor_readings.end(), [](int x){
        cout << x << " ";
    });

    cout << endl;

}