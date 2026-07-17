#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts
 
 
def main(args=None):
    rclpy.init(args=args)
    node = Node("add_two_ints_client_no_oop")

    client = node.create_client(AddTwoInts, "add_two_ints")

    # Until Server is not found Up and Running
    while not client.wait_for_service(timeout_sec=1.0):
        node.get_logger().warning("Service not available, waiting again...")

    # When Server is Up and Running, Create Request
    request = AddTwoInts.Request()
    request.a = 10
    request.b = 20


    # Make Asynchronous Call to Server via Client and wait for the response
    future = client.call_async(request)
    # Spinning until the future is complete, i.e. until the response is received
    rclpy.spin_until_future_complete(node, future)

    # Store the response and print it to the console
    response = future.result()
    node.get_logger().info(f"Client GOT Result of {request.a} + {request.b} = {response.sum}") 

    rclpy.shutdown()

if __name__ == "__main__":
    main()
 