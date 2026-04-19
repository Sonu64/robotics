#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printElement(int x) {
    cout << x << " ";
}

int main() {

    vector<int> v{2, 4, 56, 21, 90};

    cout << "Using a normal function:" << endl;
    for_each(v.begin(), v.end(), printElement);

    cout << "\nUsing Lambda Expression:" << endl;
    for_each(v.begin(), v.end(), [] (int x) {cout << x << " ";});

    // [capture_clause] (params) {func_def}

    return 0;
}

/*  FOR_EACH DOUBT */

// std::for_each iterates over the vector and calls your function once per element. The lambda parameter is what receives that current element. If you write auto x, each element is passed by value into x. If you write auto& x, it is passed by reference. If you write const auto& x, you avoid copying while also preventing modification.