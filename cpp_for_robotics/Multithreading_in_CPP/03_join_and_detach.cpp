/*=================JOIN NOTES=================
0. Once a thread is started we wait for this thread to finish by calling join() function on thread object.
1. Double join will result into program termination because double joining on same thread object makes no sense.
2. If needed we should check thread is joinable before joining. ( using joinable() function)


/*=================DETACH NOTES=================
0. This is used to detach newly created thread from the parent thread.
1. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and 
   double detach() will result into program termination.
2. If we have detached thread and main function is returning then the detached thread execution is suspended.


/*================= NOTES =================
Either join() or detach() should be called on thread object, otherwise during thread objects destructor it will terminate the program. 
Because inside destructor it checks if thread is still joinable? if yes then it terminates the program.
=============================================*/

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void func_t1() {
    std::cout << "Task-1 Starts.." << endl;
    std::this_thread::sleep_for(chrono::seconds(5));
    std::cout << "Task-1 Completes " << endl;
}

void functionRunningOnItsOwnRules() {
    std::cout << "The Swag function starts..." << endl;
    std::this_thread::sleep_for(chrono::seconds(4));
    std::cout << "The Swag function ends..." << endl;
}


int main() {
    
    std::cout << ".join() demo starts... " << endl;
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
    std::cout << ".join() demo ends... " << endl;




    std::cout << "\n\n.detach() demo starts..." << endl;
    std::thread t2(functionRunningOnItsOwnRules);

    // Detaching a thread, now there will be no-order in this Async Code ! 
    // You had seen this behaviour earlier while studying async programming in JS !
    if (t2.joinable()) {
        t2.detach();
    }
    else {
        std::cout << "Non-joinable threads are not detachable as well !" << endl;
    }
        //  OUTPUT----->
        //    .detach() demo starts...
        // The Swag function starts...      ← t2 prints this quickly before sleeping
        // .detach() demo ends...           ← main prints this and immediately returns
        //                                  ← "The Swag function ends..." is MISSING ❌
        // NOTE

        // The order of the first two lines may even swap! After detach(), main and t2 run truly concurrently with no guaranteed ordering — just like async JavaScript with no await

    // return -90;
    // If we return from here abruptly, the child thread execution will be suspended and we will never see the "detach() demo ends..." and any remaining function outputs ! :(

    std::cout << ".detach() demo ends..." << endl;
    std::cout << "Why no printing of the last line of the function ? Because the thread slept for 4 big seconds and OS finished main() exectuion before that and totally ignored that the thread is finished or not." << endl;
    return 0;
}