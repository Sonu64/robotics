#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"


using namespace std::chrono_literals;
using namespace std::placeholders; 
// This is needed to use std::bind with member functions. It allows us to use _1, _2, etc. as placeholders for the arguments that will be passed to the callback function when it is called by the ROS 2 executor.

using String = example_interfaces::msg::String;
 

class MinimalSubscriber : public rclcpp::Node
{
public:
    MinimalSubscriber() : Node("minimal_subscriber")  {
      subscription_ = this->create_subscription<String>("scribble", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
      RCLCPP_INFO(this->get_logger(), "Minimal C++ Subscriber has  started listening for messages.");
    }
 
private:
    rclcpp::Subscription<String>::SharedPtr subscription_;

    void topic_callback(const String::SharedPtr msg) {
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MinimalSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}