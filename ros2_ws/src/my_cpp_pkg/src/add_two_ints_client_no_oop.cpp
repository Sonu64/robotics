#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("add_two_ints_client_no_oop");
    

    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    // Until Server is available, wait for it to be ready. If after 1 second it is not ready, print a message and wait again. If the program is interrupted, exit.
    while (!client->wait_for_service(std::chrono::seconds(1))) {
        RCLCPP_WARN(node->get_logger(), "Service not available, waiting again...");
    }

    // Server found, request creation time
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>(); 
    // This is a little inconsistency in C++, in Msgs, we didn't have to create Shared Pointer if you remember ! Only creation of the type object was enough. But in Services, we have to create a Shared Pointer to the Request object.
    request->a = 56;
    request->b = 44;
    
    // Make Asynchronous Call to Server via Client and wait for the response to come.
    auto future = client->async_send_request(request);
    // Spin the node until the future is complete. This will block until the response is received.
    rclcpp::spin_until_future_complete(node, future);

    // Store the response in a variable and print it to the console.
    auto response = future.get();
    RCLCPP_INFO(node->get_logger(), "Response from Server: %ld + %ld = %ld", request->a, request->b, response->sum);



    rclcpp::shutdown();
    return 0;
}