cmake_minimum_required(VERSION 3.8)
project(sunbot_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# Below is the configuiration needed for msgs, srvs or actions. Just copy-paste it, It does not makes sense too much initially tbh ! But it is needed for msgs, srvs or actions to work properly.
find_package(rosidl_default_generators REQUIRED)

# Add further custom msgs, srvs or actions here. For example, if you have a msg file named "MyCustomMsg.msg" then add it below in the list
rosidl_generate_interfaces(${PROJECT_NAME}
  "action/CountUntil.action"
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()
