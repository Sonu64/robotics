# 📘 Lesson 16 — Lambda Expressions in C++ : The Full Biography

> **File**: `cpp_for_robotics/16_lambda_in_detail.cpp`
> **Series**: C++ for Robotics

---

## What is a Lambda?

A **lambda** is an **anonymous, inline function** — you write it right where you need it, without giving it a name or defining it separately.

```cpp
// Old way — define a named function somewhere else, then pass its name
for_each(v.begin(), v.end(), printElement);

// Lambda way — write the function body inline, right here
for_each(v.begin(), v.end(), [](int x){ cout << x << " "; });
```

If you've written JavaScript, this is identical in spirit:

```js
// JS
arr.forEach((x) => console.log(x));

// C++ Lambda
for_each(v.begin(), v.end(), [](int x){ cout << x << " "; });
```

---

## The Lambda Syntax

```
[capture_clause]  (parameters)  { body }
       │               │            │
       │               │            └── Logic — what the lambda does
       │               └────────────── What it receives per element
       └────────────────────────────── What outer variables it can see
```

---

## Part 1 — Parameter Modes

Controls how each vector element is handed to your lambda.

| Syntax | Name | Copy? | Mutable? | Use When |
|---|---|---|---|---|
| `(int x)` | By value | ✅ Yes | ✅ Yes | Simple reads on small types |
| `(int& x)` | By reference | ❌ No | ✅ Yes | You need to mutate the element |
| `(const int& x)` | Const reference | ❌ No | ❌ No | Read-only — **prefer this** for non-trivial types |

```cpp
// Copy — safe but duplicates each element
[](int x){ cout << x; }

// Reference — no copy, can modify the original vector element
[](int& x){ x *= 2; } // doubles every element in-place

// Const reference — no copy, compiler blocks accidental writes ✅
[](const int& x){ cout << x; }
```

> **Rule**: Always default to `const T&` for read-only lambdas. It's zero-cost and self-documenting.

---

## Part 2 — The Capture Clause `[ ]`

By default, a lambda lives in its own bubble — it cannot see variables from `main()`. The **capture clause** is how you "import" outer variables into the lambda.

### Capture by Value `[var]`

```cpp
int denominator = 2;
for_each(v.begin(), v.end(), [denominator](int x){
    cout << (x % denominator == 0 ? "YES" : "NO");
});
```
- A **copy** of `denominator` is made at lambda creation — frozen snapshot.
- Changes after this point have no effect inside the lambda.
- **Cannot modify** `denominator` inside — it's immutable.

```cpp
[denominator](int x){
    denominator++; // ❌ COMPILE ERROR
}
```

### Capture by Reference `[&var]`

```cpp
for_each(v.begin(), v.end(), [&denominator](const int& x){
    cout << (x % denominator == 0 ? "YES" : "NO");
});
```
- **Live reference** — lambda always sees the current value of `denominator`.
- Can modify `denominator` — changes affect the real variable.
- `[&var]` + `(const T& x)` = zero-copy for everything, read-only on elements ⭐

> ### ⭐ Robotics Best Practice
> ```cpp
> [&threshold](const sensor_msg& msg){ ... }
> ```
> Used everywhere in **ROS2 subscriber callbacks** — threshold lives in outer scope, lambda sees live value; message is const-ref so no copy of large msg objects.

### Capture All by Value `[=]`
- Every outer variable is snapshotted — all **immutable** inside lambda.

### Capture All by Reference `[&]`
- Every outer variable is a live reference — all **mutable** inside lambda.

---

## Part 3 — The Common Mutability Mistake

```cpp
int count = 0;

// ❌ WRONG
for_each(v.begin(), v.end(), [count](const int& x){
    count++; // COMPILE ERROR — frozen copy
});

// ✅ CORRECT
for_each(v.begin(), v.end(), [&count](const int& x){
    count++; // works — live reference
});
cout << count; // 5
```

---

## Part 4 — IIFE (Immediately Invoked Lambda)

```cpp
// ❌ Wrong — lambda created but never called (warning: expression result unused)
for(int i=0; i<5; i++) {
    [=](){ cout << denominator; };
}

// ✅ Correct — () at the end INVOKES it
for(int i=0; i<5; i++) {
    [=](){ cout << denominator; } ();
}
```

> **Mental model**: `[=](){...}` is the function definition. The `()` is the call.

**`[=]` loop** — all vars are frozen snapshots → same output every iteration.
**`[&]` loop** — `denominator++` runs each time → output grows each iteration.

---

## Full Cheat Sheet

```
Capture       Effect
────────────────────────────────────────────────────
[]            No capture — isolated from outer scope
[x]           x copied — snapshot, immutable
[&x]          x by reference — live, mutable
[=]           ALL outer vars copied — all immutable
[&]           ALL outer vars by reference — all mutable
[=, &x]       All by value EXCEPT x (by ref)
[&, x]        All by reference EXCEPT x (by value)

Parameter     Effect
────────────────────────────────────────────────────
(T x)         element copied
(T& x)        element by reference, mutable
(const T& x)  element by reference, read-only ← PREFER
```

---

## Program Output (denominator = 2)

```
Enter the denominator: 2
Using a normal function:
2 4 56 21 90
Using Lambda Expression:
2 4 56 21 90
...
Capturing an external variable by value:
YES     YES     YES     NO      YES
Capturing by reference (BEST PRACTICE):
YES     YES     YES     NO      YES
New Count is: 5
10      10      10      10      10     ← [=] — frozen denominator=2, count=5

10      15      20      25      30     ← [&] — denominator mutates: 2,3,4,5,6
New Denominator is: 7
```

---

## What's Next?

- `mutable` lambdas — modify value-captured vars without switching to `[&]`
- Returning lambdas from functions — higher-order functions in C++
- `std::function` — storing lambdas as typed variables
- Lambdas in ROS2 — real subscriber callback patterns
