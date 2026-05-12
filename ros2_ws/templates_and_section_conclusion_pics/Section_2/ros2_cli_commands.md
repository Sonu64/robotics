# ROS 2 CLI Commands (Section 2 Summary)

Quick reference for common ROS 2 command-line usage.

## Setup

Before running ROS 2 commands, source your environment and workspace:

```bash
source /opt/ros/<distro>/setup.bash
source ~/Desktop/robotics/ros2_ws/install/setup.bash
```

---

## Run a Node

General form:

```bash
ros2 run <package_name> <executable_name> [--ros-args] [args]
```

Examples:

```bash
ros2 run my_cpp_pkg my_node
ros2 run my_cpp_pkg my_node --ros-args --log-level info
ros2 run my_cpp_pkg my_node --ros-args -p robot_name:=r2d2
```

---

## Change Node Name at Runtime

Use a ROS 2 remap rule to change the node name when launching it:

```bash
ros2 run my_cpp_pkg cpp_node --ros-args -r __node:=new_node_name
```

We can also use the complete `--remap`, argument instead if the `-r` shorthand.

---

## Inspect Nodes

List all active nodes:

```bash
ros2 node list
```

Show information about a specific node:

```bash
ros2 node info /node_name
```

---

## Help Commands

Show help for the node command group:

```bash
ros2 node -h
```

Show help for the run command:

```bash
ros2 run -h
```

---

## Common Patterns

- `ros2 run <package_name> <executable_name>` starts a node executable from a package.
- `ros2 node list` shows the currently running nodes.
- `ros2 node info /node_name` prints publishers, subscribers, services, and actions for a node.
- `--ros-args` lets you pass ROS-specific options such as parameters and logging levels.

---

## Building the Workspace

Build your ROS 2 workspace with:

```bash
colcon build
```

After a successful build, **always** source the environment:

```bash
source ~/Desktop/robotics/ros2_ws/install/setup.bash
```

> ⚠️ **CRITICAL:** Forgetting to source after `colcon build` will cause package import errors. The sourcing step updates your environment variables and makes the newly built packages discoverable.

---

## Building Python Nodes Faster (Symlink Install)

To speed up Python node development and avoid rebuilding after every change, use `--symlink-install`:

```bash
colcon build --symlink-install
```

This creates symbolic links instead of copying files, so your Python changes take effect immediately without a full rebuild.



```bash
source ~/Desktop/robotics/ros2_ws/install/setup.bash
```

> ⚠️ **CRITICAL : As with normal `colcon build`, you **MUST** source the environment after every build:  If you skip sourcing, you will get package import errors! The sourcing step updates your environment variables and makes the newly built packages discoverable to Python.

### Chmod Permission Issue

You may encounter a "Permission denied" error when running Python entry points. If this happens, manually set executable permissions:

```bash
chmod +x ~/Desktop/robotics/ros2_ws/install/my_python_pkg/lib/my_python_pkg/py_node
```

Then source and try again:

```bash
source ~/Desktop/robotics/ros2_ws/install/setup.bash
ros2 run my_python_pkg py_node
```

**Note:** If the chmod approach doesn't fully resolve the issue right away, don't worry—it's not a major setback. The build process should eventually complete without this manual step. Try a clean rebuild if needed:

```bash
colcon build --symlink-install --cmake-clean-cache
```

---

## Visualizing the Node Graph with rqt and rqt_graph

### Launch rqt

`rqt` is a graphical user interface framework for ROS 2 tools:

```bash
rqt
```

This opens the rqt main window where you can load different plugins and tools.

### Visualize Node Connections with rqt_graph

To see the communication graph of your running nodes (publishers, subscribers, topics, services), launch:

```bash
rqt_graph
```

This opens a new window displaying:
- **Nodes** as boxes
- **Topics** as intermediate circles or connection points
- **Edges** showing publisher-subscriber relationships

### The Debug Checkbox in rqt_graph

The **Debug Checkbox** is located in the rqt_graph toolbar. When enabled:

- Displays **hidden nodes** (e.g., nodes like `/rosout`, internal ROS 2 infrastructure nodes)
- Shows **all internal ROS 2 topics** that are normally filtered out
- Helps you understand the complete system topology, including debug and diagnostic nodes

**How to use:**
1. Launch `rqt_graph`
2. Look for the **Debug** checkbox in the toolbar (usually near the top)
3. Check the box to reveal hidden nodes and topics
4. Uncheck to go back to the simplified view

This is useful for debugging complex node interactions and understanding the full communication structure of your ROS 2 system.

---

## Turtlesim: A Simple Simulation Tool

### What is Turtlesim?

**Turtlesim** is a simple ROS 2 tool that provides a lightweight 2D simulation environment. It's perfect for learning ROS 2 fundamentals without complex robotics hardware. Turtlesim displays a virtual "turtle" in a graphical window that you can control through ROS 2 topics and services.

### Starting the Turtlesim Node

Launch the turtlesim node:

```bash
ros2 run turtlesim turtlesim_node
```

A window will open showing a small turtle in the center of a blue square canvas. The turtle starts at the center facing right.

### Controlling the Turtle with turtle_teleop_key

To control the turtle using keyboard input, open a new terminal and run:

```bash
ros2 run turtlesim turtle_teleop_key
```

**Keyboard Controls:**
- **Arrow Keys** (↑ ↓ ← →): Move the turtle forward/backward and rotate left/right
- **G**: Reset the simulation (clear drawing)
- **C**: Clear the screen
- **Q**: Quit the teleop program

### How It Works

The `turtlesim_node` publishes the turtle's position and subscribes to velocity commands. The `turtle_teleop_key` node captures your keyboard input and publishes velocity commands that the turtlesim node receives and executes.

You can inspect this interaction using:

```bash
ros2 node list
ros2 topic list
ros2 topic echo /turtle1/cmd_vel
```

This is an excellent way to understand the publisher-subscriber model in ROS 2 before working with real robots!

---

## 🎉 Section 2 Conclusion: Celebrating Your Journey

### 🏆 You've Made It Through!

This section marks an incredible milestone in your **ROS 2 learning journey**. Let's celebrate what you've accomplished:

---

### 💪 Your Grit & Resilience

You've demonstrated **remarkable determination** in your pursuit of robotics knowledge:

- **🏥 Despite physical challenges**: You've pushed forward through surgeries and health issues that would have derailed most learners. Your body may have been healing, but your mind remained focused on growth.

- **❤️ Through relationship turbulence**: You navigated personal relationship difficulties while maintaining your discipline and commitment to learning. That takes extraordinary character.

- **🧠 Overcoming mental setbacks**: You faced moments of doubt, discouragement, and mental strain—yet you kept showing up. That's the hallmark of true resilience.

- **📚 Staying disciplined and focused**: Amidst chaos, health concerns, and emotional challenges, you maintained your study routine and didn't lose sight of your goals. **That is the definition of discipline.**

---

### 🎯 What This Means

The fact that you've reached here isn't just about learning ROS 2 commands and concepts. It's about proving to yourself that:

✅ **You can persevere** through adversity  
✅ **You can stay focused** when everything feels difficult  
✅ **You can grow** even in your darkest moments  
✅ **You are stronger** than your circumstances  

Your journey is a testament to **human resilience** and the power of showing up, day after day, despite overwhelming odds.

---

### 🚀 What's Coming Next: The Deep Dive Awaits!

Buckle up! The **next section** is going to be where things get **EXTREMELY FUN** and **INCREDIBLY DETAILED**. 

You'll dive deep into:

- 🤖 **Advanced robotics concepts**
- 🔬 **In-depth ROS 2 architecture**
- 📡 **Complex communication patterns**
- 🛠️ **Hands-on project implementations**
- 💡 **Real-world robotics challenges**

This isn't just theoretical learning anymore—you're about to **unlock the power** to build sophisticated robotic systems. Every command, every concept, every line of code will come alive with new meaning.

---

### 💫 A Personal Note

Your journey of **Grit**, **Resilience**, **Discipline**, and **Focus** has brought you to this point. You've already proven you can handle complexity and adversity. The skills you've built—both technical and personal—are your foundation for greatness.

**Keep pushing. The best is yet to come. 🌟**

---
