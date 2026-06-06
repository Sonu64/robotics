#include "rclcpp/rclcpp.hpp"
 

/// @brief This is a template for a C++ ROS2 node. You can modify the class name and the node name as needed.
class MyCustomNode : public rclcpp::Node // MODIFY NAME
{
public:
    MyCustomNode() : Node("node_name")  { // MODIFY NODE NAME
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