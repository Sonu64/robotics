#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts
from functools import partial
 
class AddTwoIntsClient(Node): 
    def __init__(self):
        super().__init__("add_two_ints_client") 
        self.client = self.create_client(AddTwoInts, "add_two_ints")

    def call_add_two_ints(self, a: int, b: int):
        # Until Server is not found Up and Running
        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().warning("Service not available, waiting again...")

        # When Server is Up and Running, Create Request
        request = AddTwoInts.Request()
        request.a = a
        request.b = b

        # Make Asynchronous Call to Server via Client and wait for the response to come.
        future = self.client.call_async(request)
        # Once future is complete, call the callback function to process the response

        ## IMPORTANT ## Use partial to pass the request object to the callback function, so that we can access the request 
        # parameters in the callback. This is because the callback function only receives the future object as an argument,
        # and we need to access the request parameters to log them in the callback.

        future.add_done_callback(partial(self.callback_call_add_two_ints, request=request))

    def callback_call_add_two_ints(self, future, request):
        response = future.result()
        self.get_logger().info(f"Request params were {request.a}, {request.b}, Client GOT Result of {response.sum}")


def main(args=None):
    rclpy.init(args=args)
    node = AddTwoIntsClient() 
    node.call_add_two_ints(10, 20)
    node.call_add_two_ints(30, 40)
    node.call_add_two_ints(50, 60)
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()