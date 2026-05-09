#!/usr/bin/env python3
# This is a shebang line.
# It tells Linux to run this file with Python 3 when executed directly (for example: ./first_python_node.py).

import rclpy
from rclpy.node import Node


def main(args=None):
    rclpy.init(args = args)

    node = Node("testing_python_node")
    node.get_logger().info("Hello, I wish someday a real robot listens this...")
    rclpy.spin(node)

    rclpy.shutdown()

if __name__ == "__main__" :
    main()

#....putting this file as an executable now via the setup.py file in this nodes parent folder's...in the entrypoints dict key.