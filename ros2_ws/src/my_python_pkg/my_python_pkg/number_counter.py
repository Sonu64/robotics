
#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64
 
 
class NumberCounterNode(Node):
    def __init__(self):
        super().__init__("number_counter") 
        self.number_received_ = 0
        self.number_count_ = 0

        self.subscriber = self.create_subscription(Int64, "number", self.get_number_callback, 10)
        self.publisher_ = self.create_publisher(Int64, "number_count", 10)

        self.get_logger().error("Python Number Counter has started counting...")
    

    def get_number_callback(self, msg):
        self.number_received_ = msg.data
        self.number_count_ += 1

        # Don't modify the original message, create a new one to publish. This may not look like a big deal, but it can cause issues if you try to publish the same message object multiple times. Its a BIG BIG ROS2 Bug and you should never do it. Always create a new message object when publishing.

        number_count_msg = Int64()
        number_count_msg.data = self.number_count_
        self.publisher_.publish(number_count_msg)
        self.get_logger().warning(f"Received number: {self.number_received_}, Count: {self.number_count_}")

 
def main(args=None):
    rclpy.init(args=args)
    node = NumberCounterNode() 
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()