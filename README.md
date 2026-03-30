# robotics

A collection of C++ and ROS2 files for robotics development.

## Contents

- **C++ files** – Standalone C++ programs and utilities for robotics algorithms and hardware interfacing.
- **ROS2 packages** – ROS2 nodes, launch files, and configurations for robot control and perception.

## Requirements

- [ROS2](https://docs.ros.org/en/rolling/Installation.html) (Humble or later recommended)
- CMake 3.8+
- C++17 compatible compiler (e.g., GCC 9+, Clang 10+)

## Build

```bash
# Source your ROS2 environment
source /opt/ros/<distro>/setup.bash

# Build ROS2 packages
colcon build

# Source the workspace
source install/setup.bash
```

## License

See [LICENSE](LICENSE) for details.
