#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/hardware_status.hpp"




class HardwareStatusPublisherNode : public rclcpp::Node {
public:
    HardwareStatusPublisherNode() : Node("hardware_status_publisher")  { 
        hardware_status_publisher_ = this->create_publisher<my_robot_interfaces::msg::HardwareStatus>("hardware_status", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&HardwareStatusPublisherNode::publish_hardware_status, this));
        RCLCPP_INFO(this->get_logger(), "Hardware Status Publisher Node has started publishing hardware status messages.");
    }

private:
    rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr hardware_status_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    void publish_hardware_status() {
        auto msg = my_robot_interfaces::msg::HardwareStatus();
        msg.temperature = 75.0; // Example temperature value
        msg.motor_status = true; // Example motor status
        msg.debug_message = "All systems operational"; // Example debug message
        hardware_status_publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published hardware status: Temperature: %.2f, Motor Status: %s, Debug Message: %s",
                    msg.temperature, msg.motor_status ? "ON" : "OFF", msg.debug_message.c_str());
    }
};











int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<HardwareStatusPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}