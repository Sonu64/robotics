/*
 * ============================================================
 *  Lesson 16 — Lambda Expressions in C++ : The Full Biography
 * ============================================================
 *
 *  SYNTAX:  [capture_clause] (parameters) { function_body }
 *
 *  Think of lambdas as anonymous functions — just like in JavaScript !
 *  You don't define them separately, you write them inline right where needed.
 *
 *  JS equivalent:
 *      arr.forEach((x) => console.log(x));          // JS
 *      for_each(v.begin(), v.end(), [](int x){...}); // C++ Lambda
 *
 *  Topics covered in this file:
 *      1. Normal functions vs. Lambda replacements
 *      2. Parameter passing: value / reference / const-reference
 *      3. Capture clause: [var] / [&var] / [=] / [&]
 *      4. Mutability rules (why [=] blocks writes, [&] allows them)
 *      5. IIFE — Immediately Invoked Lambda (no for_each needed)
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ─── Normal named functions (the "old way" before lambdas) ───────────────────

void printElement(int x) {
    cout << x << " ";
}

void check(int x) {
    (x%2 == 0) ? cout << "Even\t" : cout << "Odd\t";
}

// ─── How std::for_each works ─────────────────────────────────────────────────
//
//  for_each(v.begin(), v.end(), CALLABLE);
//
//  It iterates over the range [begin, end) and calls CALLABLE once per element.
//  The CALLABLE receives the current element — its parameter type controls copying:
//
//      (int x)         → element COPIED into x            (safe, slight overhead)
//      (int& x)        → element passed by REFERENCE      (no copy, can mutate)
//      (const int& x)  → reference, but IMMUTABLE         (no copy, read-only ✅)
//
// ─────────────────────────────────────────────────────────────────────────────

int main() {

    vector<int> v{2, 4, 56, 21, 90};

    // Runtime input — used later to demonstrate capture clauses dynamically
    int denominator;
    cout << "Enter the denominator: ";
    cin >> denominator;

    int count = 0; // external variable — will be captured by lambdas below

    // ── SECTION 1: Normal Function vs. Lambda ────────────────────────────────
    //
    //  Lambdas are anonymous functions. Same result, zero boilerplate.
    //  Passing them to for_each feels exactly like JS callbacks !

    cout << "Using a normal function:" << endl;
    for_each(v.begin(), v.end(), printElement);              // named function

    cout << "\nUsing Lambda Expression:" << endl;
    for_each(v.begin(), v.end(), [] (int x) {cout << x << " ";}); // inline lambda — same output !

    // ── SECTION 2: Parameter Modes ───────────────────────────────────────────

    cout << "\nChecking for Even Odd by normal function:" << endl;
    for_each(v.begin(), v.end(), check);

    // (int x) — copy. Each element is duplicated into x. Fine for ints.
    cout << "\nUsing Lambda Expression, copying each element." << endl;
    for_each(v.begin(), v.end(), [](int& x){(x%2 == 0) ? cout << "Even\t" : cout << "Odd\t";});

    // (int& x) — reference. No copy. x IS the element. You CAN modify the original vector here.
    cout << "\nUsing Lambda Expression, avoiding copying -- Things can be changed by ref here !" << endl;
    for_each(v.begin(), v.end(), [](int& x){(x%2 == 0) ? cout << "Even\t" : cout << "Odd\t";});

    // (const int& x) — const-reference. No copy + compiler-enforced no-mutation.
    // Turns your *intention* ("I won't touch this") into an *enforcement* at compile time.
    // → BEST for read-only operations on any non-trivial types.
    cout << "\nUsing Lambda Expression, avoiding copying -- Things can't be changed here, as we use const !'" << endl;
    for_each(v.begin(), v.end(), [](const int& x){(x%2 == 0) ? cout << "Even\t" : cout << "Odd\t";});


    // ── SECTION 3: Capture Clause — Accessing Outer Scope ───────────────────
    //
    //  Normal lambdas [] cannot see variables outside their body.
    //  The capture clause [ ] is how you "import" external variables.
    //
    //  [denominator]   → capture denominator by VALUE (snapshot copy made at lambda creation)
    //  [&denominator]  → capture denominator by REFERENCE (live link — sees changes)
    //  [=]             → capture ALL outer variables by value
    //  [&]             → capture ALL outer variables by reference

    // Capture by VALUE — denominator is snapshotted, lambda cannot modify it
    cout << "\nCapturing an external variable by value:" << endl;
    for_each(v.begin(), v.end(), [denominator](int x){
        (x%denominator==0) ? cout << "YES\t" : cout << "NO\t";
    });

    // Capture by REFERENCE + const param — BEST PRACTICE IN ROBOTICS
    // [&denominator] → live reference, zero copy of denominator
    // (const int& x) → zero copy of element, read-only
    // → This combination is the gold standard for sensor/threshold callbacks in ROS2 !
    cout << "\nCapturing an external variable by reference, also paramter passed by ref and marked const --> BEST PRACTICE IN ROBOTICS !" << endl;
    for_each(v.begin(), v.end(), [&denominator](const int& x){
        (x%denominator==0) ? cout << "YES\t" : cout << "NO\t";
    });

    cout << "\nCapturing an external variable by reference, also paramter passed by ref and marked const --> BEST PRACTICE IN ROBOTICS !" << endl;

    // ── WHY YOU CANNOT MODIFY A VALUE-CAPTURED VARIABLE ─────────────────────
    //
    //  ERROR → Cannot assign to a variable captured by copy in a non-mutable lambda
    //  for_each(v.begin(), v.end(), [count](const int& x){
    //      count++;   // ❌ COMPILE ERROR — count is a frozen copy inside this lambda
    //  });
    //
    //  To mutate, you MUST capture by reference:

    // CORRECT WAY — [&count] gives the lambda a live reference to the real count
    for_each(v.begin(), v.end(), [&count](const int& x){
        count++; // ✅ modifies the actual count variable in main()
    });

    cout << "New Count is: " << count << endl; // prints 5 — one increment per element


    // ── SECTION 4: IIFE — Immediately Invoked Lambda (no for_each) ──────────
    //
    //  [capture_clause] (params) { body } (arguments);
    //                                      ^^^^^^^^^^
    //                                      This () is the CALL — without it the lambda
    //                                      is just created and immediately discarded (warning!)
    //
    //  Rule: lambdas are objects. Writing [=](){...}; just builds one and throws it away.
    //        You must add () at the end to actually invoke it.

    // [=] — capture ALL by value. denominator and count are frozen snapshots here.
    // Trying denominator++ inside would be a COMPILE ERROR (value-captured = immutable by default)
    for(int i=0; i<5; i++) {
        [=](){
            cout << denominator*count << "\t" ;
            // denominator++; // ❌ ERROR — [=] captures by value, mutation blocked !
        } (); // () → INVOKE the lambda right here, right now
    }

    cout << "\n" << endl;

    // [&] — capture ALL by reference. Both denominator and count are live links.
    // denominator++ here ACTUALLY changes the denominator variable in main() !
    // Watch the output: each iteration denominator grows → product changes each time
    for(int i=0; i<5; i++) {
        [&](){
            cout << denominator*count << "\t" ;
            denominator++; // ✅ No error — [&] = full write access to outer scope !
        } (); // () → invoke
    }

    cout << "\nNew Denominator is: " << denominator << endl; // shows denominator has been mutated

    // ── QUICK REFERENCE ─────────────────────────────────────────────────────
    // [capture_clause] (params) { func_def }
    //
    //  Capture    │ Effect
    //  ──────────────────────────────────────────────────────────────
    //  []         │ No capture — lambda is self-contained
    //  [x]        │ x copied in — snapshot, immutable inside lambda
    //  [&x]       │ x by reference — live, mutable
    //  [=]        │ ALL outer vars copied in — all immutable
    //  [&]        │ ALL outer vars by reference — all mutable
    //
    //  Param      │ Effect
    //  ──────────────────────────────────────────────────────────────
    //  (T x)      │ element copied
    //  (T& x)     │ element by ref, mutable
    //  (const T&) │ element by ref, immutable ← PREFER THIS for reads

    return 0;
}
