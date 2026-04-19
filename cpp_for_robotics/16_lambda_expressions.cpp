#include <iostream>
#include <vector>
#include <algorithm>  // Include for std::sort
 
int main() {
    // Example list of sensor readings (could be temperatures, distances, etc.)
    std::vector<int> sensorReadings = {90, 85, 60, 75, 100};
 
    // Print original readings
    std::cout << "Original readings: ";
    for (int reading : sensorReadings) {
        std::cout << reading << " ";
    }
    std::cout << std::endl;
 















    // Using a lambda expression to sort the readings in descending order
    std::sort(sensorReadings.begin(), sensorReadings.end(), [](int a, int b) {
        return a > b;  // Comparison criterion defined inline
    });

    

    //     std::sort(...): This function takes three arguments: where to start, where to end, and how to compare.

    // sensorReadings.begin(), sensorReadings.end(): This tells the algorithm to process the entire "Data Stream."

    // []: The Capture Clause. It’s empty because this reflex doesn't need any external variables to do its job.

    // (int a, int b): The Parameters. The sorting algorithm picks two readings from your list and asks the lambda, "Which one comes first?"

    // { return a > b; }: The Logic. If a is greater than b, it returns true, telling the algorithm to put a before b. This results in a Descending Sort.
 


















    // Print sorted readings
    std::cout << "Sorted readings (desc): ";
    for (int reading : sensorReadings) {
        std::cout << reading << " ";
    }
    std::cout << std::endl;
}
 
 