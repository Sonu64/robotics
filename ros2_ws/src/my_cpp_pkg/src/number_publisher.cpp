#include <chrono>

#include "example_interfaces/msg/int64.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

// Type alias for the Int64 message
using Integer64 = example_interfaces::msg::Int64;

class NumberPublisherNode : public rclcpp::Node {
public:
  NumberPublisherNode() : Node("number_publisher") {
    // ROS 2 parameters
    this->declare_parameter("count", 0);
    this->declare_parameter("timer_period", 1.0);

    count_ = this->get_parameter("count").as_int();
    timer_period_ = this->get_parameter("timer_period").as_double();

    param_callback_handle_ = this->add_post_set_parameters_callback(
      std::bind(&NumberPublisherNode::parametersCallback, this, std::placeholders::_1));

    publisher_ = this->create_publisher<Integer64>("number", 10);
    timer_ = this->create_wall_timer(
      std::chrono::duration<double>(timer_period_),
      std::bind(&NumberPublisherNode::publish_number, this));
    RCLCPP_WARN(this->get_logger(), "Number Publisher Node has started publishing numbers...");
  }

private:
  rclcpp::Publisher<Integer64>::SharedPtr publisher_;

  int64_t count_;
  double timer_period_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::node_interfaces::NodeParametersInterface::OnSetParametersCallbackHandle::SharedPtr
    param_callback_handle_;
  int number_{};

  // Callback of timer to publish number
  void publish_number() {
    auto msg = Integer64();
    msg.data = count_;
    count_++;
    publisher_->publish(msg);
  }

  void parametersCallback(const std::vector<rclcpp::Parameter>& parameters) {
    for (const auto& param : parameters) {
      if (param.get_name() == "number") {
        number_ = param.as_int();
      }
    }
  }
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<NumberPublisherNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}