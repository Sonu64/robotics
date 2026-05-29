// this will act as Subscriber to the topic published by number_publisher.cpp and Publiish the count of numbers received to another topic called "number_count"
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using Integer64 = example_interfaces::msg::Int64; // Type alias for the Int64 message

class NumberCounterNode : public rclcpp::Node { 

    public:

    private:
        

}



int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyCustomNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}