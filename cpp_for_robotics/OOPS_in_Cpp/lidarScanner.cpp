#include <iostream>
#include <string>

class LidarScanner {
public:
    int* data;
    int resolution;

    // 1. Constructor (Allocating Memory)
    LidarScanner(int res) {
        resolution = res;
        data = new int[resolution]; // Dynamic Allocation
        // C Logic: ptr = (int*)malloc(resolution * sizeof(int));
        for(int i=0; i<resolution; i++) {
            data[i] = 0;
        }
        std::cout << "Scanner initialized at " << resolution << " pts.\n";
    }

    // 2. Deep Copy Constructor (The "Reference" Rule)
    LidarScanner(const LidarScanner& other) {
        resolution = other.resolution;
        data = new int[resolution]; // Create a NEW memory block
        for(int i=0; i<resolution; i++) {
            data[i] = other.data[i];
        }
        std::cout << "Deep Copy created (New Memory Address).\n";
    }

    // 3. Destructor (Crucial for Robotics to prevent Memory Leaks)
    ~LidarScanner() {
        delete[] data; 
        std::cout << "Memory Freed (Preventing Leak).\n";
    }
};

int main() {
    // A. STATIC ALLOCATION (Stack)
    // Memory is handled automatically. It's fast but small.
    LidarScanner frontSensor(360); 

    // B. DYNAMIC ALLOCATION (Heap)
    // Manual control. Essential for large sensor arrays.
    LidarScanner* rearSensor = new LidarScanner(720);

    // C. SHALLOW COPY (The Danger)
    // If we didn't define a Deep Copy constructor, C++ would just 
    // copy the POINTER address. Both objects would point to the same 
    // memory, causing a "Double Free" crash on destruction.

    // D. DEEP COPY (The Safety)
    LidarScanner sideSensor = frontSensor; // Calls our Deep Copy Ctor

    delete rearSensor; // Manual cleanup required for Dynamic Allocation
    return 0;
}