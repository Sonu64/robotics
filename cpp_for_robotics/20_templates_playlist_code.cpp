#include <iostream>
 
// Template class for a point in 2D space
template <typename T>
class Point {
private:
    T x;
    T y;
 
public:
    Point(T x, T y) : x(x), y(y) {} // modern constructor definition, dont get confused !!
 
    T getX() const { return x; } // While defining GETTERS, BEST PRACTICE is to mark them constant functions !
    T getY() const { return y; }

    // As the below point does not change current objects x or y, we should also mark it const, for best practice.
    void printPoint() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};
 
int main() {
    Point<int> int_point(5, 10);
    Point<double> double_point(3.14, 2.71);
 
    std::cout << "Integer point: ";
    int_point.printPoint();
 
    std::cout << "Double point: ";
    double_point.printPoint();
 
    return 0;
}