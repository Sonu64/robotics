#include <iostream>
#include <string>
#include <cmath> // added for sqrt

using namespace std;

// Template based functions are called "Generic Functions"
template <typename T>
T addNumbers(T a, T b) {
    return a + b;
}

// redefining generic typename
template <typename T>
T multiply(T a, T b) {
    return a * b;
}

// 🚨 WARNING: A template declaration (like `template <typename T>`) only applies to the IMMEDIATELY following function or class! 🚨
// 🚨 You must explicitly redefine `template <typename T>` for every new generic function or class. 🚨

// Template Based classes are called "Template Classes"
template <typename T>
class Vector3d {
    private:
        T x, y, z;
    public:
        Vector3d(T x, T y, T z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        void print() const { // Good practice to make print const
            cout << "(" << x << ", " << y << ", " << z << ")" << endl;
        }
        T magnitude() const { // Good practice to make read-only methods const
            return sqrt(x*x + y*y + z*z);
        }
        void setX(T x) { this->x = x; }
        void setY(T y) { this->y = y; }
        void setZ(T z) { this->z = z; }
        T getX() const { return x; }
        T getY() const { return y; }   
        T getZ() const { return z; }
        
        T dotProduct(const Vector3d& other) const {
            // Removed invalid (this->x)++ since this is a const method
            return this->x*other.x + this->y*other.y + this->z*other.z;
        }
        
        Vector3d operator+(const Vector3d& other) const {
            return Vector3d(this->x + other.x, this->y + other.y, this->z + other.z);
        }
        
        Vector3d operator-(const Vector3d& other) const {
            return Vector3d(this->x - other.x, this->y - other.y, this->z - other.z);
        }
};

int main() {
    cout << "--- Template Functions ---" << endl;
    cout << "Int Add: " << addNumbers(5, 10) << endl;
    cout << "Double Add: " << addNumbers(10.5, 20.5) << endl;
    cout << "Int Multiply: " << multiply(45, 2) << endl;
    cout << "Double Multiply: " << multiply(45.5, 2.6) << endl;
    
    cout << "\n--- Template Class (Vector3d) ---" << endl;
    // Instantiating Vector3d with integers
    Vector3d<int> v1(1, 2, 3);
    Vector3d<int> v2(4, 5, 6);
    
    cout << "v1: "; v1.print();
    cout << "v2: "; v2.print();
    
    cout << "v1 magnitude: " << v1.magnitude() << endl;
    cout << "Dot Product: " << v1.dotProduct(v2) << endl;
    
    Vector3d<int> v3 = v1 + v2;
    cout << "v1 + v2: "; v3.print();

    // Instantiating Vector3d with doubles
    Vector3d<double> v_double(1.5, 2.5, 3.5);
    cout << "\nv_double: "; v_double.print();

    return 0;
}