cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)


### ------- TESTING code removed ------- ###



# Adding executables

# the demo node that we created in Section 1
add_executable(cpp_node src/first_cpp_node.cpp) # No commas here !!!
ament_target_dependencies(cpp_node rclcpp)

add_executable(robot_news_station src/robot_news_station.cpp)
add_executable(smartphone src/smartphone.cpp)
add_executable(number_publisher src/number_publisher.cpp) 
add_executable(number_counter src/number_counter.cpp) 
add_executable(add_two_ints_server src/add_two_ints_server.cpp)


# Don't forget to add the new node here as well, otherwise it won't be built and you won't be able to run it using ros2 run command.
ament_target_dependencies(robot_news_station rclcpp example_interfaces)
ament_target_dependencies(smartphone rclcpp example_interfaces)
ament_target_dependencies(number_publisher rclcpp example_interfaces)
ament_target_dependencies(number_counter rclcpp example_interfaces) 
ament_target_dependencies(add_two_ints_server rclcpp example_interfaces)

#installing executables for ros2
install(TARGETS
  cpp_node
  robot_news_station
  smartphone
  number_publisher
  number_counter 
  add_two_ints_server
  # Don't forget to add the new node here as well, otherwise it won't be installed and you won't be able to run it using ros2 run command.
  DESTINATION lib/${PROJECT_NAME}
)

   # Dont forget to add the new nodes (pubs/subs) here as well, otherwise it won't be installed and you won't be able to run it using ros2 run command.

ament_package()
