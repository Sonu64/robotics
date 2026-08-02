#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"
#include "my_robot_interfaces/msg/led_panel_state.hpp"

class LedPanelNode : public rclcpp::Node {
    public:
        LedPanelNode() : Node("led_panel_server") {
            this->declare_parameter("led_states", std::vector<int64_t>{0, 0, 0});
            led_states_ = this->get_parameter("led_states").as_integer_array();

            // Force any non-zero startup values to 0 (all LEDs OFF at boot)
            for (size_t i = 0; i < led_states_.size(); i++) {
                if (led_states_[i] != 0) {
                    RCLCPP_WARN(this->get_logger(), "LED state parameter should be 0 for all LEDs. Resetting to 0.");
                    led_states_[i] = 0;
                }
            }

            led_panel_state_pub_ = this->create_publisher<my_robot_interfaces::msg::LedPanelState>("led_panel_state", 10);

            // Publish current state every 5 seconds, regardless of activity
            timer_ = this->create_wall_timer(
                std::chrono::seconds(5), std::bind(&LedPanelNode::publish_led_states, this));

            server_ = this->create_service<my_robot_interfaces::srv::SetLed>(
                "set_led", std::bind(&LedPanelNode::callbackSetLed, this, std::placeholders::_1, std::placeholders::_2));

            RCLCPP_INFO(this->get_logger(), "LED Panel Service Server is running. Waiting for requests...");
        }     
        
    private:
        rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr server_;
        rclcpp::Publisher<my_robot_interfaces::msg::LedPanelState>::SharedPtr led_panel_state_pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        std::vector<int64_t> led_states_;

        // Builds a message FROM the current led_states_ array and publishes it.
        // This is the ONLY place that publishes — callback and timer both call this,
        // so there's no way for the published message to disagree with led_states_.
        void publish_led_states() {
            auto msg = my_robot_interfaces::msg::LedPanelState();
            for (size_t i = 0; i < led_states_.size(); i++) {
                msg.led_panel_state[i] = led_states_[i];
            }
            led_panel_state_pub_->publish(msg);
        }

        void callbackSetLed(
            const my_robot_interfaces::srv::SetLed::Request::SharedPtr request,
            my_robot_interfaces::srv::SetLed::Response::SharedPtr response)
        {
            int led_number = request->led_number;
            bool state = request->state;

            // Reject anything outside the array's actual bounds — works for ANY size
            if (led_number < 0 || led_number >= static_cast<int>(led_states_.size())) {
                RCLCPP_WARN(this->get_logger(), "Invalid LED number received: %d", led_number);
                response->success = false;
                return;
            }

            led_states_[led_number] = state ? 1 : 0;
            publish_led_states();  // reuse the same function the timer uses

            RCLCPP_INFO(this->get_logger(), "LED %d turned %s.", led_number, state ? "ON" : "OFF");
            response->success = true;
        }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LedPanelNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}