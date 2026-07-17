#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
 
class MinimalSubscriber(Node):
    def __init__(self):
        super().__init__("minimal_subscriber")
        self.subscription_ = self.create_subscription(String, "scribble", self.topic_callback, 10)
        self.get_logger().info("Minimal Python Subscriber has started listening for messages.")
    def topic_callback(self, msg):
        self.get_logger().info(f"Received: {msg.data}")
 
 
def main(args=None):
    rclpy.init(args=args)
    node = MinimalSubscriber() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()