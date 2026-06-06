#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

 
class AddTwoIntsServerNode(Node): 
    def __init__(self):
        super().__init__("add_two_ints_node")
        self.server_ = self.create_service(AddTwoInts, "add_two_ints", self.callback_add_two_ints)
        self.get_logger().warning("Add Two Ints Server has been started...")

    # Callback function
    def callback_add_two_ints(self, request: AddTwoInts.Request, response: AddTwoInts.Response):
        response.sum = request.a + request.b
        self.get_logger().info(f"{request.a} + {request.b} = {response.sum}")
        # Don't forget to return the response !
        return response



 
def main(args=None):
    rclpy.init(args=args)
    node = AddTwoIntsServerNode() 
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()