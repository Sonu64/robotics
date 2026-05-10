#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    //...
    //.. NOTE TO MYSELF :- Smart pointers like below should not confuse you anymore, you literally spent 5 days to understand smart pointers and Automatic Heap Memory management ! If you forget check the smart pointer files in the cpp_for_robotics folder :)
    auto node = std::make_shared<rclcpp::Node>("testing_cpp_node");
    RCLCPP_INFO(node->get_logger(), "Someday a Real Robot will listen this...");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

