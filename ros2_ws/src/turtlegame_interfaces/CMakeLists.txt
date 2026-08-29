cmake_minimum_required(VERSION 3.8)
project(turtlegame_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(turtlesim REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# Below lines for Custom ROS2 interfaces, prefer copy-pasting
find_package(rosidl_default_generators REQUIRED)

# No COMMA below !!
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/TurtleArray.msg"
  DEPENDENCIES turtlesim
)
ament_export_dependencies(rosidl_default_runtime)

ament_package()
