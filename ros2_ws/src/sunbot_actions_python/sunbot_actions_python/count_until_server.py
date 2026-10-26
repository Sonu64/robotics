#!/usr/bin/env python3
import rclpy
import time
from rclpy.node import Node
from sunbot_interfaces.action import CountUntil
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.action.server import ServerGoalHandle









class CountUntilServerNode(Node): 
    def __init__(self):
        super().__init__("count_until_server")
        self.count_until_server_ = ActionServer(
                        self,
                        CountUntil,
                        "count_until",
                        execute_callback=self.execute_callback)
        
        self.get_logger().info("CountUntil Action Server has been started.")
        
    
    # In Python, rejecting a goal is Optional. So by default is accept and when the goal is accepted this callback is called. Thats why above we put execute_callback=self.execute_callback. goal_handle is the goal that was accepted (You can say its the REQUEST that was accepted from the client with all raw data that needs further extraction).
    def execute_callback(self, goal_handle: ServerGoalHandle):
        # Get request from goal
        target_number = goal_handle.request.target_number       
        period = goal_handle.request.period
        self.get_logger().info(f"Received goal request to count until {target_number} and period of {period} seconds.")
        # Execute action
        self.get_logger().info("Executing goal...")
        counter = 0
        for i in range(target_number):
            counter += 1
            self.get_logger().info(f"Current count: {counter}")
            time.sleep(period) #Simulating a time slot
        # Once done, set goal final state
        goal_handle.succeed()
        # and send the result
        result = CountUntil.Result()
        result.reached_number = counter
        self.get_logger().info(f"Goal completed. Final count: {result.reached_number}")
        return result
        




def main(args=None):
    rclpy.init(args=args)
    node = CountUntilServerNode() 
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
