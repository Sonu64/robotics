#include <iostream>
#include <thread>
#include <memory>


void printTableUpto4(int num) {
    for(int i=1; i<=4; i++) {
        std::cout << num << " * " << i << " = " << (num*i) << std::endl;
    }
}


int main() {
    // Type-1: Most basic way to create Thread in C++ -> Function Pointers

    // Multiple threads created @ same time -> No guarantee which one will run first ! So you may get abrupt outputs below :)))
    // 🧠 The "Abrupt Output" Debug
    // The technical term for what you're seeing is a Race Condition on a shared resource(std::cout).
    // std::cout is not inherently thread-safe for interleaved characters.
    // Thread 1 might print 20 * 1 =  and then, before it can print 20, the Scheduler pauses it and lets Thread 2 print 5 * 1 = 5.
    // The Result: A jumbled mess of numbers on your screen.

    std::thread t1(printTableUpto4, 20);
    std::thread t2(printTableUpto4, 5);
    t1.join();
    t2.join();










    // Type-2, Injecting Named Lambdas in thread creation line 
    auto myFunction = [] (int x) {
        std::cout << "\n\n";
        while (x-- > 0) {
            std::cout << x << std::endl;
        }
    };
    //....similar to funcPointers
    std::thread t3(myFunction, 12);
    t3.join();
    //.. Direct Injection of Lambda definitions in thread creation line
    std::thread t4( [](int x) {
        std::cout << "\n\nC++ giving JavaScript callback Functions vibe !! ";
    }, 10);
    t4.join();





    // Type-3: Injecting any functor Object in thread creation line
    // --- I haven't leart Functors yet...so consider sort of "Black Box" for now...I will revisit this topic after classes
    class PrintMultiplicationTable {
        public:
            PrintMultiplicationTable(int num) {
                this->num = num;
            }
            void operator()() {
                for(int i=1; i<=4; i++) {
                    std::cout << num << " * " << i << " = " << (num*i) << std::endl;
                }
            }
        private:
            int num;
    };
    PrintMultiplicationTable p(20);
    std::thread t5(p);
    t5.join();       







    // Type-4 : Non-Static member function
    class Sample {
        public:
            /// @brief Non-static member function below
            void printTable(int x) {
                for(int i=1; i<=4; i++) {
                    std::cout << x << " * " << i << " = " << (x*i) << std::endl;
                }
            }
    };
    // Step-1: Create an object of that class

    // ---------- Static allocation
    Sample sampleObject;
    // 🧠 Why `&sampleObject`? 
    // `sampleObject` is an actual instance on the stack. `std::thread` needs a pointer to the object 
    // to invoke its non-static member function, so we use the address-of operator `&` to get its raw pointer.
    std::thread t6(&Sample::printTable, &sampleObject, 3);
    t6.join();

    // ---------- Dynamic Heap Allocation using a smart pointer
    std::unique_ptr<Sample> heapSampleObject = std::make_unique<Sample>();
    // 🧠 Why `heapSampleObject.get()`?
    // `heapSampleObject` is a smart pointer wrapper. Using `&` on it would give the memory address of the smart pointer 
    // itself. Instead, `.get()` extracts the underlying raw pointer to our heap-allocated `Sample` instance.
    std::thread t7(&Sample::printTable, heapSampleObject.get(), 4);
    t7.join();



    
    


    
    
    return 0;
}