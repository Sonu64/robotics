// TOPIC: Introduction to thread in c++ (c++11)
// QUESTIONS
// 1. What do you understand by thread and give one example in C++?
// ANSWER
// In evey application there is a default thread which is main(), in side this we create other threads.
// 1. A thread is also known as lightweight process. Idea is achieve parallelism by dividing a process into multiple threads.

// C++ thread is different theoretically than OS Process/Thread. If one OS Application is running as a process, then inside the application runs lots of  'micro-processes'. This is a Multithreaded Application and those micro-processes are Threads.

// For example:
// (a) The browser has multiple tabs that can be different threads.
// (b) MS Word must be using multiple threads, one thread to format the text, another thread to process inputs (spell checker)
// (c) Visual Studio code editor would be using threading for auto completing the code. (Intellicence)

// 14 // WAYS TO CREATE THREADS IN C++11
// 1. Function Pointers
// 2. Lambda Functions
// 3. Functors
// 4. Member Functions
// 5. Static Member functions

// REQUIREMENT in this problem.

// Find the addition of all odd number from 1 to 1900000000 and all even number from 1 to 1900000000

/*
=================================================================================================
NOTES ON TYPES AND TIMING:
1. `unsigned long long` (typedef'd as `usll`): 
   Since we are calculating the sum of numbers up to 1.9 billion, the final sum will be HUGE. 
   A standard 32-bit `int` can only hold up to ~2.14 billion, meaning it would quickly overflow. 
   `unsigned long long` is a 64-bit unsigned integer that can hold up to ~18.4 quintillion, 
   safely storing our massive sum without rolling over.

2. `high_resolution_clock` & Duration Logic:
   This comes from the `<chrono>` library. As the name implies, it's the clock with the shortest 
   tick period provided by your machine's OS. It's meant specifically for benchmarking code.
   - The logic: Take a timestamp (`now()`) right before the function runs.
   - Take another timestamp right after it finishes.
   - Subtract the two to get the elapsed time.
   - `duration_cast<microseconds>` converts that raw time difference into a manageable unit (microseconds).
   - `.count()` simply extracts the raw numerical value of that duration (the actual number of microseconds).


   ---> duration_cast<...> returns a new object of type std::chrono::duration (in this case, specifically instantiated for microseconds).

    ---> Since it's a class object, you can't just print it directly or do raw math with it like a normal integer. The .count() method is indeed a member function (like a getter) on that duration class that returns the raw internal integer value (the "tick count") so you can use it just like a normal number.
=================================================================================================
*/

#include <iostream>
#include <thread>
#include <memory>
#include <algorithm>


using namespace std;
using namespace std::chrono;

typedef unsigned long long usll;

usll findEvenSum(usll start, usll end) {
    usll even_sum = 0;
    for(usll i=start; i<=end; i++) {
        if ( (i & 1) == 0 )
            even_sum += i;
    }
    return even_sum;
}

usll findOddSum(usll start, usll end) {
    usll odd_sum = 0;
    for(usll i=start; i<=end; i++) {
        if( (i & 1) == 1)
            odd_sum += i;
    }
    return odd_sum;
}


int main() {

    usll start = 0, end =  1900000000;
    usll even_sum = 0, odd_sum = 0;

    auto startTime = high_resolution_clock::now();
    even_sum = findEvenSum(start, end);
    auto stopTime = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stopTime - startTime);
    cout << "Even Sum = " << even_sum << endl;
    cout << "Time taken: " << (duration1.count() / 1000000) << " seconds." << endl;


    startTime = high_resolution_clock::now();
    odd_sum = findOddSum(start, end);
    stopTime = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stopTime - startTime);
    cout << "Time taken: " << (duration2.count() / 1000000.0) << " seconds." << endl;
    cout << "Odd Sum = " << odd_sum << endl;
    cout << "Total time taken: " << ((duration1.count()/1000000)+(duration2.count()/1000000.0)) << " seconds." << endl;



    return 0;
}