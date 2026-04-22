#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> sensor_readings{45, 89, 12, 47, 65};

    /* DEMONSTRATION OF LAMBDA EXPRESSIONS IN C++, TO SORT READINGS IN DESCENDING ORDER */
    // We will use lamdba expression in the sort algo to sort in Descending order
    sort(sensor_readings.begin(), sensor_readings.end(), [](int a, int  b){
        return a > b;
    });

    cout << "Sensor Readings in Descending order - " << endl;
    for_each(sensor_readings.begin(), sensor_readings.end(), [](int x){
        cout << x << " ";
    });




    /* DEMONSTRATION OF FOR_EACH LOOP */
    vector<int> distances = {100, 568, 980, 145, 321};

    // Below syntax is also RANGE_BASED_FOR
        cout << "\nOriginal distances - " << endl;
        for(int distance : distances) {
            cout << distance << " ";
        }


    // Below syntax is FOR_EACH, combined with lambda expressions.
    const int amount = 10;
    for_each(distances.begin(), distances.end(), [amount](int& distance){
        distance += amount;
    });


    cout << "\nUpdated distances - " << endl;
    for(int distance : distances) {
            cout << distance << " ";
    }


    cout << endl;

}