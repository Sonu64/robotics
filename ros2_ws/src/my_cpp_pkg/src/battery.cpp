#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"


class BatteryNode : public rclcpp::Node {
public:
    BatteryNode() : Node("battery"), is_full_(true), seconds_elapsed_(0)  { 
        // define client
        client_ = this->create_client<my_robot_interfaces::srv::SetLed>("set_led");
        // ticks every 1 second, always
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1), std::bind(&BatteryNode::update_battery_status, this));
        RCLCPP_INFO(this->get_logger(), "Battery Node has started checking battery status.");
    }



    private:
        bool is_full_;
        int seconds_elapsed_;
        rclcpp::Client<my_robot_interfaces::srv::SetLed>::SharedPtr client_; // can also write auto.
        rclcpp::TimerBase::SharedPtr timer_;


        void update_battery_status() {
            // note that the seconds_elapsed_ variable is incremented every second, and the LED is turned on or off based on the battery status and elapsed time. is_full also updated here. This avoids the need for separate functions to turn the battery down or recharge it, as the logic is handled within the update_battery_status function. Also avoiding nested timers --> Claude suggested this, but this is really good pattern to follow.
            seconds_elapsed_++;
            if (is_full_ && seconds_elapsed_ >= 4) {
                // turn LEDs on and battery down
                RCLCPP_INFO(this->get_logger(), "Battery down..sending request to turn on LED.");
                call_set_led(3, true);
                is_full_ = false;
                seconds_elapsed_ = 0;
            }
            else if (!is_full_ && seconds_elapsed_ >= 6) {
                // turn LEDs off and recharge battery
                RCLCPP_INFO(this->get_logger(), "Battery recharged..sending request to turn off LED.");
                call_set_led(3, false);
                is_full_ = true;
                seconds_elapsed_ = 0;
            }
        }


        void call_set_led(int64_t led_number, bool state) {
            // Wait for the service to be available if no service found after 1sec.
            while (!client_->wait_for_service(std::chrono::seconds(1))) {
                if (!rclcpp::ok()) {  // <-- add this check, otherwise Ctrl+C wont close the node properly.
            RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for service. Exiting.");
            return;
        }
                RCLCPP_WARN(this->get_logger(), "Service not available, waiting again...");
            }

            auto request = std::make_shared<my_robot_interfaces::srv::SetLed::Request>();
            request->led_number = led_number;
            request->state = state;

            client_->async_send_request(request, std::bind(&BatteryNode::callback_set_led, this, std::placeholders::_1));
        }

        void callback_set_led(rclcpp::Client<my_robot_interfaces::srv::SetLed>::SharedFuture future) {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "LED set successfully.");
        }

};



int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BatteryNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}