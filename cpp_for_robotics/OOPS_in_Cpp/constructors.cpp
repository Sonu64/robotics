#include <iostream>

using namespace std;

class CodeHelp {
public:
    int subs;
    int views;

    // ✅ Default Constructor
    CodeHelp() {
        subs = 0;
        views = 0;
        cout << "Default Constructor Called." << endl;
    }

    // ⚙️ Parameterized Constructor
    CodeHelp(int s, int v) {
        subs = s;
        views = v;
        cout << "Parameterized Constructor Called" << endl;
    }

    // 📋 Copy Constructor
    CodeHelp(CodeHelp &obj) {
        subs = obj.subs;
        views = obj.views;
        cout << "Copy Constructor Called" << endl;
    }

    // Method to display values
    void display() {
        cout << "Subscribers: " << subs << ", Views: " << views << endl;
    }
};

int main() {
    CodeHelp obj1;                 // Default Constructor
    obj1.display();

    CodeHelp obj2(100, 2500);      // Parameterized Constructor
    obj2.display();

    CodeHelp obj3 = obj2;          // Copy Constructor
    obj3.display();

    return 0;
}