#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
 
# @brief This is a template for a Python ROS2 node. You can modify the class name and the node name as needed.
 
class MyCustomNode(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("node_name") # MODIFY NAME
 
 
def main(args=None):
    rclpy.init(args=args)
    node = MyCustomNode() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()