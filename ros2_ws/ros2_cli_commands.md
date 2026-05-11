# ROS 2 CLI Commands

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
