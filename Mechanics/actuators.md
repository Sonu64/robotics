

## ## 🦾 Robotics Kernel: Actuators

An **Actuator** is the component responsible for moving or controlling a mechanism or system. It is the "muscle" that converts energy (usually electrical) into physical motion.

*   **Why they are needed:** Without actuators, a robot is just a stationary computer. They allow the system to interact with the environment—lifting tools, rotating propellers, or moving wheels.
*   **The Workflow:** Your C++ Lambda sends a low-power signal $\rightarrow$ An Electronic Driver amplifies that power $\rightarrow$ The Actuator converts it into Torque ($T = F \times r$) or Linear Force.



---

## ## 🏗️ Actuator Types & Use Cases

Choosing the right "muscle" depends on the mission. Here is the lean breakdown based on **Screenshot 2026-04-22 090749.jpg**:

| Actuator Type | Core Application | Key Strength |
| :--- | :--- | :--- |
| **Servo Motor** | Robot arms | High precision; can hold a specific position. |
| **DC Motor** | Mobile robots | Continuous rotation; simple and inexpensive. |
| **BLDC (Brushless)** | Drones | High speed and efficiency; low maintenance. |
| **Linear Actuator** | Lifting systems | Converts rotation into straight-line motion. |
| **Stepper Motor** | 3D Printers | Moves in fixed "steps" for high accuracy without sensors. |



---

## ## ⚙️ The Selection "Mogojastro"

According to **Screenshot 2026-04-22 090749.jpg**, you must evaluate these **Key Factors** when designing your system:

*   **Torque & Speed:** You must match the load and motion requirements. Ensure the motor provides enough "twist" to overcome the **Equivalent Couple**.
*   **Precision:** Determine if you need **Position Control** (e.g., $45^{\circ}$) or **Continuous Rotation** (e.g., a wheel).
*   **Power Requirements:** You must match the Voltage, Current, and Efficiency to your battery capacity.
*   **Control Method:** This is where the "Binaries" meet the motor. Common protocols include **PWM**, **CAN**, **EtherCAT**, or specialized **ROS drivers**.
*   **Duty Cycle:** Is the motor meant for **Continuous** or **Intermittent** use?.
*   **Mechanical Fit:** Consider the size, mounting points, and if you need a **gearbox** to increase torque.

---

## ## 🗒️ Notepad Summary: The Lean Logic

*   **Definition:** Energy converter (Electrical Signal $\rightarrow$ Physical Motion).
*   **The "Rule of Three":** Match **Torque** to the physics, **Precision** to the task, and **Control Method** to your C++ code.
*   **Selection Cheat-Sheet:** 
    *   Precision Arm? $\rightarrow$ **Servo**.
    *   Aerial/High Speed? $\rightarrow$ **BLDC**.
    *   Basic Mobility? $\rightarrow$ **DC Motor**.

> [!TIP]
> **Architect's Tip:** In your simulation tomorrow, don't worry about the physics of the motor internals. Focus on the **Interface**: how your ROS2 node sends a velocity or position command to the "Muscle."

---

**Now that your morning "Mogojastro" is documented, are we shifting focus back to the Subnetting lecture, or is the system ready to dive deeper into those C++ Lambdas?**