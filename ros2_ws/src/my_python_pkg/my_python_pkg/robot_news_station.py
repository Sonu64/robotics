#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String
 
 
class RobotNewsStationNode(Node): 
    def __init__(self):
        super().__init__("robot_news_station")
        #....Create the Publisher object. It will publish messages of type String on the topic "news". <Keep in mind that 'where' we are creating the publiser. It's after the super() call.>

        # Add dependency in package.xml for example_interfaces to get example_interfaces.msg import String.

        # Queue size is 10. It means that if the subscriber is not receiving messages fast enough, the publisher will store up to 10 messages before it starts dropping old messages. --> It's the Buffer size :)
        self.publisher_ = self.create_publisher(String, "robot_news", 10) # the topic name is "robot_news", So if we see its info while its running, we will see that this node has publisher for the "robot_news" topic.

        # We can also list the topics via the ROS2 CLI command "ros2 topic list".
        # While "ros2 topic echo /topic_name shows the pulished data...Though we have to write  Subscriber Node to listen it and then process it ahead."

        self.timer_ = self.create_timer(2, self.publish_news)
        self.get_logger().warning("Robot News Station is Publishing...")

    def publish_news(self):
        msg = String()
        msg.data = "Did you hear? Sonu just opened a bakery today!" #because the interface String has a field type named "data" which is of string type
        self.publisher_.publish(msg)

 
def main(args=None):
    rclpy.init(args=args)
    node = RobotNewsStationNode()
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()