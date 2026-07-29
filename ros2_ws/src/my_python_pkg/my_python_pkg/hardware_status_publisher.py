#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from my_robot_interfaces.msg import HardwareStatus

class HardwareStatusPublisher(Node):
    def __init__(self):
        super().__init__("hardware_status_publisher")
        self.hardware_status_publisher_ = self.create_publisher(HardwareStatus, "hardware_status", 10)
        self.timer_ = self.create_timer(1.0, self.publish_hardware_status)
        self.get_logger().info("Hardware Status Publisher is running...")

    def publish_hardware_status(self):
        msg = HardwareStatus()
        msg.temperature = 75.0  # Example temperature value
        msg.motor_status = True  # Example motor status
        msg.debug_message = "All systems nominal"  # Example debug info
        self.hardware_status_publisher_.publish(msg)
        self.get_logger().info("Published hardware status")

def main(args=None):
    rclpy.init(args=args)
    node = HardwareStatusPublisher()
    rclpy.spin(node)
    rclpy.shutdown()
 
if __name__ == "__main__":
    main()