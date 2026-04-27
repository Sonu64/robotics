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


#include <iostream>
#include <thread>
#include <memory>
#include <algorithm>

using namespace std;
using namespace std::chrono;


int main() {



    return 0;
}