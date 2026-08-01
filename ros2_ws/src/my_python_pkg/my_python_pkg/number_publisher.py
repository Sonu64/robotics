#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64
 
 
class NumberPublisherNode(Node):
    def __init__(self):
        super().__init__("number_publisher") 

        # ROS2 Parameters below !
        self.declare_parameter("count", 0) # int
        self.declare_parameter("timer_period", 1.0) # float
        self.count_ = self.get_parameter("count").value
        self.timer_period_ = self.get_parameter("timer_period").value
        
        self.publisher_ = self.create_publisher(Int64, "number", 10)
        self.timer_ = self.create_timer(self.timer_period_, self.publish_number_callback)
        self.get_logger().warning("Python Number Publisher has started publishing...")
    
    def publish_number_callback(self):
        msg = Int64()
        msg.data = self.count_
        self.publisher_.publish(msg)
        self.count_ += 1

 
def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode() 
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()