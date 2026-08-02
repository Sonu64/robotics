#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from rclpy.parameter import Parameter
from example_interfaces.msg import Int64
 
 
class NumberPublisherNode(Node):
    def __init__(self):
        super().__init__("number_publisher") 

        # ROS2 Parameters below !
        self.declare_parameter("count", 0) # int
        self.declare_parameter("timer_period", 1.0) # float
        self.count_ = self.get_parameter("count").value
        self.timer_period_ = self.get_parameter("timer_period").value
        # Below line is for parameter callbacks and utilizing 'ros2 param set --- '
        self.add_post_set_parameters_callback(self.parameters_callback)
        
        self.publisher_ = self.create_publisher(Int64, "number", 10)
        self.timer_ = self.create_timer(self.timer_period_, self.publish_number_callback)   
        self.get_logger().warning("Python Number Publisher has started publishing...")

    def parameters_callback(self, params):
        for param in params:
            if param.name == "count":
                self.count_ = param.value
                self.get_logger().info(f"Count parameter updated to: {self.count_}")
            elif param.name == "timer_period":
                self.timer_period_ = param.value
                self.timer_.cancel()  # Cancel the existing timer
                self.timer_ = self.create_timer(self.timer_period_, self.publish_number_callback)  # Create a new timer with the updated period
                self.get_logger().info(f"Timer period parameter updated to: {self.timer_period_}")
        
    
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