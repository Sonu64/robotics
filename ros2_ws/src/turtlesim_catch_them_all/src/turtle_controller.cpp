#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "turtlesim/msg/pose.hpp"
#include "turtlegame_interfaces/msg/turtle_array.hpp"
#include "turtlegame_interfaces/srv/catch_turtle.hpp"
 

class TurtleController : public rclcpp::Node {
public:
    TurtleController() : Node("turtle_controller")  { 
        RCLCPP_INFO(this->get_logger(), "TurtleController node has been started.");
        master_turtle_sub_ = this->create_subscription<turtlesim::msg::Pose>(
            "turtle1/pose", 10,
            std::bind(&TurtleController::masterTurtlePoseCallback, this, std::placeholders::_1));

        alive_turtles_sub_ = this->create_subscription<turtlegame_interfaces::msg::TurtleArray>(
            "alive_turtles", 10,
            std::bind(&TurtleController::aliveTurtlesCallback, this, std::placeholders::_1));

        catch_turtle_timer_ = this->create_wall_timer(
            std::chrono::seconds(2),
            std::bind(&TurtleController::catchTurtleCallback, this));
    }
 
private:
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr master_turtle_sub_;
    rclcpp::Subscription<turtlegame_interfaces::msg::TurtleArray>::SharedPtr alive_turtles_sub_;
    rclcpp::TimerBase::SharedPtr catch_turtle_timer_;

    // Global vars for master turtle position, only x and y, not a dedicated POSE type.
    double master_turtle_x_ = 0.0;
    double master_turtle_y_ = 0.0;
    double master_turtle_theta_ = 0.0;
    rclcpp::turtlegame_interfaces::msg::TurtleArray::SharedPtr alive_turtles_msg_ = nullptr;  // Global variable to hold the latest alive turtles message

    void masterTurtlePoseCallback(const turtlesim::msg::Pose::SharedPtr msg) {
        master_turtle_x_ = msg->x;
        master_turtle_y_ = msg->y;
        master_turtle_theta_ = msg->theta;
        // RCLCPP_INFO(this->get_logger(), "Master turtle position updated: (x: %.2f, y: %.2f)", master_turtle_x_, master_turtle_y_);
    }

    void catchTurtleCallback() {

        // WARNING: This function is called when a turtle is caught. The global alive_turtles_msg_ variable is updated in the aliveTurtlesCallback function, which is called whenever the list of alive turtles is updated. So, we can use the alive_turtles_msg_ variable here to get the latest list of alive turtles.

        if (!alive_turtles_msg_) {
            RCLCPP_WARN(this->get_logger(), "No alive_turtles message received yet.");
            return;
        }

        if (alive_turtles_msg_->turtles.empty()) {
            RCLCPP_INFO(this->get_logger(), "No turtles to catch.");
            return;
        }

        // const& avoids copying the Turtle (it owns a std::string, not free to copy);
        // rule of thumb: use const auto& when reading structs/strings/vectors, plain copy is fine for small primitives like double/int. const ensures we don't accidentally modify the target turtle.
        const auto &target = alive_turtles_msg_->turtles[0];
        
        RCLCPP_INFO(this->get_logger(), "1st alive turtle - %s with coordinates (x: %.2f, y: %.2f)",
            target.name.c_str(), target.x, target.y);

        double target_x = alive_turtles_msg_->turtles[0].x;
        double target_y = alive_turtles_msg_->turtles[0].y;

        // Need to get the master turtles position to calculate the distance to the target turtle
        // For this, we can use a member variable to store the latest master turtle position
        double distance = std::sqrt(std::pow(target_x - master_turtle_x_, 2) + std::pow(target_y - master_turtle_y_, 2));
        RCLCPP_INFO(this->get_logger(), "Distance to target turtle: %.2f", distance);

        double angle_to_target = atan2(target_y - master_turtle_y_, target_x - master_turtle_x_);
        double angle_diff = angle_to_target - master_turtle_theta_;

        // Angle Normalization: Ensure the angle difference is within the range [-π, π]. I still dont properly understand why this is needed, but it seems to be a common practice in robotics to avoid issues with angle wrapping. - THIS IS A TODO TO UNDERSTAND LATER, FOR NOW I JUST COPY PASTE IT FROM THE INTERNET.
        while (angle_diff > M_PI) angle_diff -= 2 * M_PI;
        while (angle_diff < -M_PI) angle_diff += 2 * M_PI;

        RCLCPP_INFO(this->get_logger(), "Angle to target turtle: %.2f, Angle difference: %.2f", angle_to_target, angle_diff);
    }

    void aliveTurtlesCallback(const turtlegame_interfaces::msg::TurtleArray::SharedPtr msg) {
        // This callback will be called whenever the list of alive turtles is updated.

        // update global member variable turtles with the latest alive turtles message
        alive_turtles_msg_ = msg;

        RCLCPP_INFO(this->get_logger(), "Received updated list of alive turtles. Total: %zu", msg->turtles.size());
        // Implement your logic to decide which turtle to catch in a timer based function, not here.
    }
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}