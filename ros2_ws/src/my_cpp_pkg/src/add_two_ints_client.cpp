#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp" 


class AddTwoIntsClientNode : public rclcpp::Node
{
public:
    AddTwoIntsClientNode() : Node("add_two_ints_client")  {
    client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    }

    void call_add_two_ints(int a, int b) {
        // Wait for the service to be available if no service found after 1sec.
        while (!client_->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(this->get_logger(), "Service not available, waiting again...");
        }

        //When Server is Up and Running, create a request object and fill the request data.
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        // Make Asynchronous Call here is NOT done here...we use a callback to process the response when it is received. This is a better way to do it than blocking the node.
        client_->async_send_request(request, std::bind(&AddTwoIntsClientNode::callback_add_two_ints, this, std::placeholders::_1)); //1 parameter here, cant use partial() like python here. 
        // Also, here this is not the value in future, future is the  param name in the callbacl, the value received here is assigned to future once callback is triggered.
    }

    void callback_add_two_ints(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future) {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Result: %ld", response->sum);
    }
 
private:
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_; // can also write auto.

};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsClientNode>(); 
    node->call_add_two_ints(56, 44);
    node->call_add_two_ints(100, 200);
    node->call_add_two_ints(10, 20);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}