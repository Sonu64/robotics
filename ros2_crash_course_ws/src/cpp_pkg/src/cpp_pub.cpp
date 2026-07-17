#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include <string>
#include <memory>
#include <chrono>

using namespace std::chrono_literals;

using String = example_interfaces::msg::String; // This is just a type alias to make the code cleaner and easier to read. It allows us to use String instead of the full example_interfaces::msg::String every time we want to refer to that message type.
 

class MinimalPublisher : public rclcpp::Node
{
public:
    MinimalPublisher() : Node("minimal_publisher"), count(0)  {
      publisher_ = this->create_publisher<String>("scribble", 10);
      timer_ = this->create_wall_timer(100ms, std::bind(&MinimalPublisher::timer_callback, this));
      RCLCPP_INFO(this->get_logger(), "Minimal C++ Publisher has  started publishing messages.");
    }
 
private:
    rclcpp::Publisher<String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count;

    void timer_callback() {
      auto msg = String();
      msg.data = "Hello, World! " + std::to_string(count++); // print and increment the count variable, which is a member variable of the class. This allows us to keep track of how many messages have been published so far.
      publisher_->publish(msg);
    }
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MinimalPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}