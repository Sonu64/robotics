#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
 

 
class MinimalPublisher(Node): 
    def __init__(self):
        super().__init__("minimal_publisher")
        self.publisher_ = self.create_publisher(String, "scribble", 10)
        self.timer = self.create_timer(1.0, self.timer_callback)
        self.count = 0
        self.get_logger().info("Minimal Python Publisher has started publishing messages.")
    def timer_callback(self):
        msg = String()
        msg.data = f"Hello World! {self.count}"
        self.publisher_.publish(msg)
        # self.get_logger().info(f"Publishing: {msg.data}")
        self.count += 1

 
 
def main(args=None):
    rclpy.init(args=args)
    node = MinimalPublisher() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()