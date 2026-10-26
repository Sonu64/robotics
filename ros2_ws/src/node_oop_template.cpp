#include "rclcpp/rclcpp.hpp"

class MyCustomNode : public rclcpp::Node // MODIFY NAME
{
public:
    // modify node name below and also change the name of the class above to match the node name
    MyCustomNode() : Node("node_name") {
        RCLCPP_INFO(this->get_logger(), "Node has been initialized.");
        // Add your custom initialization code here
    }

private:
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyCustomNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
