# Java vs C++ for OOP in Robotics

<p>
	<span style="color:#0A7F5A;"><strong>Format:</strong></span> Translation notes for Java developers learning C++ OOP.
</p>

---

## <span style="color:#1F6FEB;">Topic 1: Translation Layer (Java vs C++)</span>

### 1) Pure Interface
- <span style="color:#B45309;"><strong>Java</strong></span>: `interface Robot { void move(); }`
- <span style="color:#0F766E;"><strong>C++</strong></span>: A class with only pure virtual functions, for example: `virtual void move() = 0;`

### 2) Abstract Class
- <span style="color:#B45309;"><strong>Java</strong></span>: `abstract class BaseRobot { ... }`
- <span style="color:#0F766E;"><strong>C++</strong></span>: Any class with at least one pure virtual function becomes abstract automatically.

### 3) Super Calls (Constructors)
- <span style="color:#B45309;"><strong>Java</strong></span>: `super(id);` (must be the first statement in constructor body)
- <span style="color:#0F766E;"><strong>C++</strong></span>: `: BaseClass(id)` (initializer list, runs before constructor body)

### 4) Extends / Implements
- <span style="color:#B45309;"><strong>Java</strong></span>: `class Drone extends BaseRobot implements RobotInterface`
- <span style="color:#0F766E;"><strong>C++</strong></span>: `class Drone : public BaseRobot`

---

## <span style="color:#1F6FEB;">Topic 2: Destructor Lifecycle (Stack Analogy)</span>

<span style="color:#6B7280;"><strong>C++ object lifecycle follows LIFO behavior:</strong></span>

### Construction (Top-Down)
- Parent constructor runs first
- Child constructor runs second
- Reason: foundation first, then specialization

### Destruction (Bottom-Up)
- Child destructor runs first
- Parent destructor runs second
- Reason: specialized resources must be released before base resources

### Virtual Destructor Rule (Mandatory for Polymorphic Base Classes)
If you do:

```cpp
Base* b = new Child();
delete b;
```

- Without `virtual ~Base()`: only base destructor may run, causing leaks/partial cleanup
- With `virtual ~Base()`: `~Child()` runs first, then `~Base()` automatically

---

## <span style="color:#1F6FEB;">Topic 3: Strict Safety Rules (Error Prevention)</span>

### 1) No Objects of Abstract Classes
- Invalid: `new BaseRobot()`
- Why: pure virtual functions are incomplete and must be implemented in a concrete derived class

### 2) Override All Required Pure Virtual Functions
- A leaf class like `Drone` must implement every inherited pure virtual function
- If not, the leaf class remains abstract

### 3) Manual Memory Cleanup
- C++ has no automatic garbage collector like Java
- Every `new` should have a matching `delete` (or prefer smart pointers)

### 4) Do Not Chain Parent Destructors Manually in Signature
- Do not try syntax like calling `~BaseClass()` in derived destructor declaration
- C++ automatically chains destructors in correct order

### 5) Pointer Safety After Delete
- After `delete bot1;`, do `bot1 = nullptr;`
- Prevents accidental access through a dangling pointer

---

## Quick Mental Mapping

| Java Concept | C++ Equivalent |
|---|---|
| `interface` | pure virtual interface class |
| `abstract class` | class with at least one pure virtual function |
| `super(args)` | constructor initializer list `: Base(args)` |
| GC cleanup | explicit `delete` or smart pointers |
| runtime polymorphism | virtual methods + base pointers/references |