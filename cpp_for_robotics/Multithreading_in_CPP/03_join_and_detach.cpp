#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void func_t1() {
    std::cout << "Task-1 Starts.." << endl;
    std::this_thread::sleep_for(chrono::seconds(5));
    std::cout << "Task-1 Completes " << endl;
}


int main() {
    std::cout << "main() starts... " << endl;
    std::thread t1(func_t1);

    /* .join() makes the calling thread (main) wait until t1 finishes execution. 
    Only after t1 completes does main() resume and print main() ends */
    t1.join();   

    std::cout << "main() ends... " << endl;
    return 0;
}