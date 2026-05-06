/*=================JOIN NOTES=================
0. Once a thread is started we wait for this thread to finish by calling join() function on thread object.
1. Double join will result into program termination because double joining on same thread object makes no sense.
2. If needed we should check thread is joinable before joining. ( using joinable() function)
==============================================*/


/*=================DETACH NOTES=================
0. This is used to detach newly created thread from the parent thread.
1. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and 
   double detach() will result into program termination.
2. If we have detached thread and main function is returning then the detached thread execution is suspended.
==============================================*/


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

    // ..... lots of code here .....
    // now  you may forget that t1 is still joinable ... so always check for joinable() before joining!
    if (t1.joinable()) {
        t1.join(); // No double join here
    } else {
        cout << "Thread is not joinable, cannot join." << endl;
    }

    std::cout << "main() ends... " << endl;
    return 0;
}