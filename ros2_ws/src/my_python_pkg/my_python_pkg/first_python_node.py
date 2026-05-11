#!/usr/bin/env python3
# This is a shebang line.
# It tells Linux to run this file with Python 3 when executed directly (for example: ./first_python_node.py).


#----------- THE OFFICIAL ROS COMMUNITY  ADVISED APPROACH TO CREATE NODES ----------#

import rclpy
from rclpy.node import Node

# Class to make a node in ROS2. It inherits from the Node class provided by rclpy.
class MyNode(Node):
    def __init__(self, node_name):
        # MyNode doesn't process the name itself; it just passes it to the parent.
        # Only the parent Node class (from rclpy) has the actual logic to register 
        # the node name in ROS 2. MyNode just extends Node with custom behavior (like logging).
        super().__init__(node_name)
        self.get_logger().info("Testing Python node initialized.")
        self.log_count = 0 # This is not a class level counter...its normal counter just to keep track of how many times the printing of the warning log was done.
        # create_timer(period, callback) creates a recurring timer.
        # period=1.0 means the timer fires every 1 second.
        # Each time it fires, it calls timer_callback().
        # This is how you run code repeatedly in ROS 2 nodes (like polling a sensor every N seconds).
        self.create_timer(1.0, self.timer_callback)
    
    def timer_callback(self):
        # This function runs every 1 second (due to the create_timer call above).
        # The ROS 2 spin() loop automatically invokes this callback on schedule.
        self.log_count += 1
        self.get_logger().warning("Aaila Jaadu... " + str(self.log_count))
        self.__getattribute__("get_logger")().error("This is an error log from the timer callback.")
        self.get_logger().info("This is an info log from the timer callback.")


def main(args=None):
    rclpy.init(args = args)
    node = MyNode("testing_python_node")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__" :
    main()

#....putting this file as an executable now via the setup.py file in this nodes parent folder's...in the entrypoints dict key.