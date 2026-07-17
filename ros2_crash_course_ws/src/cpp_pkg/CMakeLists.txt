cmake_minimum_required(VERSION 3.8)
project(cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(example_interfaces REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Adding executables
add_executable(cpp_pub src/cpp_pub.cpp)
add_executable(cpp_sub src/cpp_sub.cpp)

# Executable dependencies
ament_target_dependencies(cpp_pub rclcpp example_interfaces)
ament_target_dependencies(cpp_sub rclcpp example_interfaces)



install(TARGETS 
  cpp_pub
  cpp_sub
  DESTINATION lib/${PROJECT_NAME})

#-----------Removed testing code for simplicity-------------------

ament_package()
