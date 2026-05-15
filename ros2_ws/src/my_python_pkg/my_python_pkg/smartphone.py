#!/usr/bin/env python3
from example_interfaces.msg import String

import rclpy
from rclpy.node import Node
 
 
class SmartphoneNode(Node):
    def __init__(self):
        super().__init__("smartphone")
        self.smartphone_name_ = "Smartphone"
        self.subscriber_ = self.create_subscription(String, "robot_news", self.robot_news_callback,  10) # We are creating a subscriber that listens to the "robot_news" topic. Whenever a message is published on this topic, the news_callback function will be called with the message as an argument.
        self.get_logger().warning("Smartphone is Ready to Use...")
    
    # The callback function that will be called whenever a message is received on the "robot_news" topic.
    def robot_news_callback(self, msg: String):
        self.get_logger().info(f"{self.smartphone_name_} received news: {msg.data} from Publisher ---msg.publisher_name---") # # msg.publisher_name is not a standard field in the String message type, so it will not work unless you have modified the message definition to include a publisher field. If you want to log the publisher's name, you would need to include that information in the message data or use a custom message type that includes a publisher field.
 
 
def main(args=None):
    rclpy.init(args=args)
    node = SmartphoneNode()
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()