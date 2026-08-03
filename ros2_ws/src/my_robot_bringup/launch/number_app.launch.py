from launch import LaunchDescription 
from launch_ros.actions import Node

def generate_launch_description(): 
    ld = LaunchDescription()

    number_publisher = Node(
        package="my_python_pkg", 
        executable="number_publisher",
        name="renamed_number_publisher",  # Renaming node name using name argument
        remappings=[("/number", "/renamed_number")],  # Renaming topic name using remappings argument, using list of tuples to specify remappings
        )

    number_counter = Node(
        package="my_cpp_pkg",
        executable="number_counter",
        name="renamed_number_counter",  # Renaming node name using name argument
        remappings=[("/number", "/renamed_number")],  # Renaming topic name using remappings argument, using list of tuples to specify remappings
    )

    ld.add_action(number_publisher)
    ld.add_action(number_counter)

    return ld