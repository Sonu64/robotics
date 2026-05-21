#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"


using namespace std::chrono_literals;
using namespace std::placeholders; 
// This is needed to use std::bind with member functions. It allows us to use _1, _2, etc. as placeholders for the arguments that will be passed to the callback function when it is called by the ROS 2 executor.

using String = example_interfaces::msg::String;
 
class SmartphoneNode : public rclcpp::Node  
{
public:
    SmartphoneNode() : Node("smartphone"), smartphone_name_("Smartphone")  {   
        this->subscriber_ = this->create_subscription<String>(
            "robot_news", 10, std::bind(&SmartphoneNode::robot_news_callback, this, _1)
        );
        RCLCPP_WARN(this->get_logger(), "Smartphone Node has started subscribing/listening to robot news [This time from the Hard C++ syntax :P]");
    }
 
private:
    std::string smartphone_name_;
    rclcpp::Subscription<String>::SharedPtr subscriber_;

    void robot_news_callback(const String::SharedPtr msg) {
        RCLCPP_ERROR(this->get_logger(), "%s received news: '%s'", smartphone_name_.c_str(), msg->data.c_str());
    }
    
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartphoneNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}