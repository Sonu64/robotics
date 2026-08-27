cmake_minimum_required(VERSION 3.8)
project(turtlesim_catch_them_all)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)

# Executables
add_executable(turtle_controller src/turtle_controller.cpp)
add_executable(turtle_spawner src/turtle_spawner.cpp)

# Dependencies
ament_target_dependencies(turtle_controller rclcpp turtlesim)
ament_target_dependencies(turtle_spawner rclcpp turtlesim)


# Dont forget the executables installation, otherwise you won't be able to run them using ros2 run command. It will say "No executable found" if you forget to add this part.
install(TARGETS
  turtle_controller
  turtle_spawner
  # Don't forget to add the new node here as well, otherwise it won't be installed and you won't be able to run it using ros2 run command.
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
