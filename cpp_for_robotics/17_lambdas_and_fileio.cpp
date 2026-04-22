#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

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



    /* DEMONSTRATION OF FILE HANDLING*/
 
    string filename = "robot_data.txt";
    ofstream output_file(filename);
 

    // Checking wheather the File opening was sucessful or not is Must using the is_open() method of ofstream, before writing anything in it using Multiline Insertion operators - '<<'.
    if (output_file.is_open()) {
        output_file << "Sensor1: 10.5\n";
        output_file << "Sensor2: 20.7\n";
        output_file << "Sensor3: 15.2\n";
        output_file.close();
        cout << "Data written to file: " << filename << std::endl;
    } else {
        cout << "Unable to open file for writing." << std::endl;
    }
 
    ifstream input_file(filename);
    string line;
 
    // Same precaution here ! Before reading every line, check wheather the file successfuly opened or not.
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            cout << line << endl;
        }
        input_file.close();
    } else {
        cout << "Unable to open file for reading." << endl;
    }
 
    cout << endl;

}