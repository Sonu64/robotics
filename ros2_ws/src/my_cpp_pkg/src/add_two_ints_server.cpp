#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::placeholders;


class AddTwoIntsServerNode : public rclcpp::Node 
{
    public:
        AddTwoIntsServerNode() : Node("add_two_ints_server")  {
            server_ = this->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", std::bind(&AddTwoIntsServerNode::callbackAddTwoInts, this, _1, _2)); // because we have 2 placeholders, we need to use std::bind to bind the callback function with the placeholders. (Think of them as param placeholders nowm without a formale name)
            RCLCPP_INFO(this->get_logger(), "Service server is running. Waiting for requests...");
        }
    
    private:
        rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;

        // Unlike Python, we dont need to return the respose here. Respone is automatically sent back to the client when we set the response->sum value.
        void callbackAddTwoInts(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request, example_interfaces::srv::AddTwoInts::Response::SharedPtr response) {
            response->sum = request->a + request->b;
            RCLCPP_INFO(this->get_logger(), "Incoming request: a=%d, b=%d", (int)request->a, (int)request->b);
            RCLCPP_INFO(this->get_logger(), "Sending back response: sum=%d", (int)response->sum);
        }

};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsServerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}