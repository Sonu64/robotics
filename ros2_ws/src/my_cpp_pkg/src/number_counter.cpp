// this will act as Subscriber to the topic published by number_publisher.cpp and Publiish the count of numbers received to another topic called "number_count"
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders; 
// This is needed to use std::bind with member functions. It allows us to use _1, _2, etc. as placeholders for the arguments that will be passed to the callback function when it is called by the ROS 2 executor.

using Integer64 = example_interfaces::msg::Int64; // Type alias for the Int64 message

class NumberCounterNode : public rclcpp::Node {
    public: 
        NumberCounterNode() : Node("number_counter"), number_count_(0) {
            this->subscriber_ = this->create_subscription<Integer64>(
            "number", 10, std::bind(&NumberCounterNode::get_number_callback, this, _1)
        );

        this->publisher_ = this->create_publisher<Integer64>("number_count", 10);


        RCLCPP_WARN(this->get_logger(), "Number Counter has started Listening to /number and Simultaneosly publishing to the /number_count");

        }

    private:
        int64_t number_received_;
        int64_t number_count_;

        rclcpp::Subscription<Integer64>::SharedPtr subscriber_;
        rclcpp::Publisher<Integer64>::SharedPtr publisher_;
      

        void get_number_callback(const Integer64::SharedPtr msg) {
            number_received_ = msg->data; // Update the count with the received number
            number_count_++; // Increment the count of numbers received

            RCLCPP_ERROR(this->get_logger(), "Number of numbers received: %ld", number_count_);
            RCLCPP_WARN(this->get_logger(), "Received number: %ld \n\n", number_received_);

            auto number_count_msg = Integer64(); // construction of this msg as an entire Integer64 is needed to publish the count of numbers received, you cant directly use msg as it contains the received number, not the count of numbers received
            number_count_msg.data = number_count_;
            this->publisher_->publish(number_count_msg); // Publish the count of numbers received
        }
        
    };

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}