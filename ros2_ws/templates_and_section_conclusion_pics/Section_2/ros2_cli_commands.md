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
