#include <iostream>

using namespace std;

// Constant-like macro: preprocessor does a simple text substitution everywhere PI is used.
// Rule: a macro must be DEFINED before the line that uses it (preprocessor reads top-to-bottom).
#define PI 3.14159

// Function-like macro: expands the argument textually at the call site.
// Brackets rule: ALWAYS wrap each argument in () inside the macro body.
//   Without them: AREA_CIRCLE(r + 1) → PI * r + 1 * r + 1  ← wrong precedence!
//   With them:    AREA_CIRCLE(r + 1) → PI * (r + 1) * (r + 1) ← correct
#define AREA_CIRCLE(radius) (PI * (radius) * (radius))


int main() {
    int radius = 10;
    double area = AREA_CIRCLE(radius); // expands to: (3.14159 * (radius) * (radius))
    cout << "Area of circle is " << area << " unit squared." << endl;

    return 0;
}
 