
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
        msg.data = self.number_count_
        self.publisher_.publish(msg)
        self.get_logger().warning(f"Received number: {self.number_received_}, Count: {self.number_count_}")

 
def main(args=None):
    rclpy.init(args=args)
    node = NumberCounterNode() 
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()