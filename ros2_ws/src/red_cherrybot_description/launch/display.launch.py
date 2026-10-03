from launch import LaunchDescription
import os
from ament_index_python.packages import get_package_share_path
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
   
    # red_cherrybot_description/urdf/red_cherrybot.urdf
    urdf_path = os.path.join(get_package_share_path('red_cherrybot_description'), 'urdf', 'model.urdf.xacro')
    
    # The robot description parameter is sent to the robot_state_publisher node, which publishes the state of the robot to the /tf topic.
    robot_description = ParameterValue(Command(['xacro ', urdf_path]), value_type=str)
    
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description}],
    )
    
    
    joint_state_publisher_gui_node = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
    )
    
    rviz2_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', os.path.join(get_package_share_path('red_cherrybot_description'), 'rviz', 'urdf_config.rviz')],
    )
    
    
    return LaunchDescription([
        robot_state_publisher_node,
        joint_state_publisher_gui_node,
        rviz2_node
    ])