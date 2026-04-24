#include <iostream>
#include <string>

using namespace std;

// Template based functions are called "Generic Functions", which can be used generically with any data type as specified by user.

template <typename T>
T addNumbers(T a, T b) {
    return a + b;
}

// !!! Generic function braces finish, that generic typename T can't be used anymore, need to redefine before making another generic !!

// redefining generic typename
template <typename T>
T multiply(T a, T b) {
    return a*b;
}

int main() {
    cout << addNumbers(5, 10) << endl;
    cout << addNumbers(10.5, 20.5) << endl;
    cout << multiply(45, 2) << endl;
    cout << multiply(45.5, 2.6) << endl;
    return 0;
}