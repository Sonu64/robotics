#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printElement(int x) {
    cout << x << " ";
}

void check(int x) {
    (x%2 == 0) ? cout << "Even\t" : cout << "Odd\t";
}

// /*  First lets see how the for_each Loop works, so that you don't get confused inside main ! They simply act like Java or JavaScript for_each Loops */

// std::for_each iterates over the vector and calls your function once per element. The lambda parameter is what receives that current element. 
// 
// If you write auto x, each element is passed by value into x. 
// If you write auto& x, it is passed by reference. 
// If you write const auto& x, you avoid copying while also preventing modification.


int main() {

    vector<int> v{2, 4, 56, 21, 90};

    int denominator;
    cout << "Enter the denominator: ";
    cin >> denominator;

    int count = 0; // external variable.

    // Lambdas resemble Anonymous functions in Javascript, you dont need to define a function separately ! I know you no more do Web Development, but this much JS you know na !... Passing them feels like JS callbacks and using them feels like anonymous functions !
    cout << "Using a normal function:" << endl;
    for_each(v.begin(), v.end(), printElement);

    cout << "\nUsing Lambda Expression:" << endl;
    for_each(v.begin(), v.end(), [] (int x) {cout << x << " ";});

    //checking even odd by normal function
    cout << "\nChecking for Even Odd by normal function:" << endl;
    for_each(v.begin(), v.end(), check);

    cout << "\nUsing Lambda Expression, copying each element." << endl;
    for_each(v.begin(), v.end(), [](int& x){(x%2 == 0) ? cout << "Even\t" : cout << "Odd\t";}); // int a copies each element

    cout << "\nUsing Lambda Expression, avoiding copying -- Things can be changed by ref here !" << endl;
    for_each(v.begin(), v.end(), [](int& x){(x%2 == 0) ? cout << "Even\t" : cout << "Odd\t";}); // int& a avoids copying.

    cout << "\nUsing Lambda Expression, avoiding copying -- Things can't be changed here, as we use const !'" << endl;
    for_each(v.begin(), v.end(), [](const int& x){(x%2 == 0) ? cout << "Even\t" : cout << "Odd\t";}); // const int& a avoids copying and also enforces our "intention" of not doing something to the original number in an even-odd checker, into an "Enforcement" !


    cout << "\nCapturing an external variable by value:" << endl;
    for_each(v.begin(), v.end(), [denominator](int x){
        (x%denominator==0) ? cout << "YES\t" : cout << "NO\t";
    });

    cout << "\nCapturing an external variable by reference, also paramter passed by ref and marked const --> BEST PRACTICE IN ROBOTICS !" << endl;
    for_each(v.begin(), v.end(), [&denominator](const int& x){
        (x%denominator==0) ? cout << "YES\t" : cout << "NO\t";
    });

    cout << "\nCapturing an external variable by reference, also paramter passed by ref and marked const --> BEST PRACTICE IN ROBOTICS !" << endl;

    // ERROR -> Cannot assign to a variable captured by copy in a non-mutable lambda
    // for_each(v.begin(), v.end(), [count](const int& x){
    //     // count++;
    // }); 

    // CORRECT WAY -> No Error ! 
    for_each(v.begin(), v.end(), [&count](const int& x){
        count++;
    });

    cout << "New Count is: " << count << endl;


    // [capture_clause] (params) {func_def}


    // Pass all external vars by Value — run lambda 5 time, but dont forget to call(invoke) it inside the loop ! Its not for_each ! A simple for it is Baby !
    for(int i=0; i<5; i++) {
        [=](){
            cout << denominator*count << "\t" ;
            // denominator++; ERROR !!! You know why !
        } (); // () invokes the lambda
    }

    cout << "\n" << endl;

    // Pass all external vars by Value — run lambda 5 time, but dont forget to call(invoke) it inside the loop ! Its not for_each ! A simple for it is Baby !
    for(int i=0; i<5; i++) {
        [&](){
            cout << denominator*count << "\t" ;
            denominator++; // No ERROR !!! You know why !
        } (); // () invokes the lambda
    }

    cout << "\nNew Denominator is: " << denominator << endl;


    return 0;
}

