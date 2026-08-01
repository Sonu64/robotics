#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"
#include "my_robot_interfaces/msg/led_panel_state.hpp"

class LedPanelNode : public rclcpp::Node {
    public:
        LedPanelNode() : Node("led_panel_server")  {

            // declare a parameter for the LED states, and set a default value of [0, 0, 0]
            this->declare_parameter("led_states", std::vector<int64_t>{0, 0, 0});
            // get the parameter value and store it in the member variable
            led_states_ = this->get_parameter("led_states").as_integer_array();

            server_ = this->create_service<my_robot_interfaces::srv::SetLed>("set_led", std::bind(&LedPanelNode::callbackSetLed, this, std::placeholders::_1, std::placeholders::_2));
            RCLCPP_INFO(this->get_logger(), "LED Panel Service Server is running. Waiting for requests...");
            led_panel_state_pub_ = this->create_publisher<my_robot_interfaces::msg::LedPanelState>("led_panel_state", 10);
        }     
        
    private:
        rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr server_;
        rclcpp::Publisher<my_robot_interfaces::msg::LedPanelState>::SharedPtr led_panel_state_pub_;
        std::vector<int64_t> led_states_;  // <-- new member, this is now your source of truth coming from the YAML param file.

        
        void callbackSetLed(const my_robot_interfaces::srv::SetLed::Request::SharedPtr request, my_robot_interfaces::srv::SetLed::Response::SharedPtr response) {
            int led_number = request->led_number;
            bool state = request->state;

            if(led_number == 3 && state == true) {
                auto led_state_msg = my_robot_interfaces::msg::LedPanelState();
                led_state_msg.led_panel_state[0] = 0;
                led_state_msg.led_panel_state[1] = 0;
                led_state_msg.led_panel_state[2] = 1; // LED 3 is ON
                led_panel_state_pub_->publish(led_state_msg);
                RCLCPP_INFO(this->get_logger(), "LED 3 turned ON.");
                response->success = true;
            }
            else if(led_number == 3 && state == false) {
                auto led_state_msg = my_robot_interfaces::msg::LedPanelState();
                led_state_msg.led_panel_state[0] = 0;
                led_state_msg.led_panel_state[1] = 0;
                led_state_msg.led_panel_state[2] = 0; // LED 3 is OFF
                led_panel_state_pub_->publish(led_state_msg);
                RCLCPP_INFO(this->get_logger(), "LED 3 turned OFF.");
                response->success = true;
            }
            else {
                RCLCPP_WARN(this->get_logger(), "Invalid LED number or state received.");
                response->success = false;
            }
            
        }
        
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LedPanelNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

