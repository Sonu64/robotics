// Include the standard input/output library for console output
#include <iostream>
// Include Eigen library for linear algebra operations (Dense matrices/vectors)
// command to include this external lib whilst compilation with g++ goes like - 
// "g++ -I usr/include/eigen3 02_eigen_example.cpp -o 02_eigen_example"
// so the external lib folder is stored in usr/include/eigen3 folder.
#include <eigen3/Eigen/Dense>
using namespace std;

int main() {
    // Create a column vector of size 3x1 (3 rows, 1 column)
    // Note: Eigen::Vector3d is a COLUMN vector by default, not a row vector
    // So v = [10]  (vertical orientation)
    //         [20]
    //         [30]
    Eigen::Vector3d v(10, 20, 30);
    
    // v.transpose() converts the column vector (3x1) to a row vector (1x3) for display
    // Why transpose() is needed: Without it, cout would print v vertically (on 3 lines)
    // With transpose(), it prints horizontally on 1 line as: 10 20 30
    // This is purely for readable output formatting, not a mathematical requirement
    cout << v.transpose() << endl;
}

