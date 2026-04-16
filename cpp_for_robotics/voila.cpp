#include <iostream>
#include <string>

using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 0, y = 0;
    cout << "Enter two integers: ";
    cin >> x >> y;
    cout << "Before swapping: x = " << x << ", y = " << y << endl;
    swap(x, y);
    cout << "After swapping: x = " << x << ", y = " << y << endl;
    return 0;
}

// When you write void swap(int& a, int& b), you are telling the compiler:
// "When this function runs, a is not a copy of the input. a is simply another name for the variable passed in. Whatever I do to a, do it directly to the original memory."

// In C++ (References): You just pass x. The compiler sees the & in the function signature and automatically handles the address-grabbing for you. It’s "Syntactic Sugar" that prevents human error. THIS SYNTAX WILL NOT WORK IN C ! So C--->C++ is VALID but C++--->C is NOT VALID.

















// ## 1. The C Logic: "The Delivery Service"
// In C, the function and the variable live in different worlds. To connect them, you must act like a delivery driver.

// The Signature (int *a): The function creates a "mailbox" (the pointer variable) to hold an address.

// The Call (&x): You manually look up the GPS coordinates of x and put that paper in the mailbox.

// The Work (*a): Inside the function, you have to manually "dereference"—meaning you look at the paper, see the address, and physically drive to that memory location to change the data.

// ## 2. The C++ Logic: "The Magic Portal"
// In C++, the function and the variable are "wired" together by the compiler.

// The Signature (int &a): This is the Alias. It’s not a separate box; it’s a second name for the same memory.

// The Call (x): You just pass the name. No & needed. It’s clean.

// The "Magic" (Automatic Dereferencing): Because you defined a as a reference (&), the Compiler does the "going-inside" for you. When you write a = 5, the compiler translates that directly into: "Go to the memory address of x and put a 5 there."

// ## 3. The "Refined" Breakdown (Notepad-Ready)
// * (Pointer): A separate variable that stores an address. You must manually "dive in" using the * operator. (Think: A map in your hand).

// & (Reference): A direct alias (nickname). The compiler "dives in" for you automatically. (Think: A direct portal to the room).

// Why this is "Elite":
// The C++ way is safer because an alias (&) cannot be empty (Null), whereas a pointer (*) can point to a location that doesn't exist and crash your system.