/// @brief Operator overloading is a powerful feature in C++ that allows you to define custom behavior for operators when applied to user-defined types.

#include <iostream>

using namespace std;


class Distance {
    private:
        int distance;
    public:
        Distance(int m = 0) : distance(m) {};

        int getDistance() const { // This function is marked as const, which means it promises not to modify any member variables of the class. This allows us to call this function on const objects of the Distance class, ensuring that we can safely retrieve the distance value without altering the state of the object.
            return distance;
        }

        Distance operator + (const Distance& otherDistance) const {
            // distance++; // This line is modifying the member variable distance, which is not allowed in a const function ! "Intentions" => "Enforcements". The compiler will throw an error if we try to modify any member variable inside this function, ensuring that the contract of being a read-only function is upheld.
            return Distance(distance + otherDistance.distance);
        }
};

int main() {
    Distance d1(90);
    Distance d2(65);
    const Distance sum = d1 + d2;
    // sum = d1 + d1; // This would cause a compile error since sum is const

    cout << "The total Distance is " << sum.getDistance() << " units." << endl;
    
    return 0;
}


// ## Notepad Summary: The Trailing const
// Safety: Turns "Intention" into "Enforcement." Catching = vs == typos.

// Contract: Legally binds the function to be Read-Only.

// Accessibility: Necessary to allow const objects (like fixed limits or sensor snapshots) to use the function.

// Robotics Rule: All "Getters" and "Sensing" logic must be const.