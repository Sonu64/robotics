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
    }
 
private:
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr master_turtle_sub_;
    rclcpp::Subscription<turtlegame_interfaces::msg::TurtleArray>::SharedPtr alive_turtles_sub_;

    // Global vars for master turtle position, only x and y, not a dedicated POSE type.
    double master_turtle_x_ = 0.0;
    double master_turtle_y_ = 0.0;
    rclcpp::<turtlegame_interfaces::msg::TurtleArray>::SharedPtr alive_turtles_msg_;

    void masterTurtlePoseCallback(const turtlesim::msg::Pose::SharedPtr msg) {
        master_turtle_x_ = msg->x;
        master_turtle_y_ = msg->y;
        // RCLCPP_INFO(this->get_logger(), "Master turtle position updated: (x: %.2f, y: %.2f)", master_turtle_x_, master_turtle_y_);
    }

    void catchTurtleCallback() {

        // WARNING: This function is called when a turtle is caught. and there is no msg here, so we need to get the latest alive turtles from the alive_turtles_msg_ member variable, which is updated in the aliveTurtlesCallback() function. OR USE global other vars or other ways -------- TODO !!!!!!!!

        // Log the names of the alive turtles
        RCLCPP_INFO(this->get_logger(), "1st alive turtle - %s with coordinates (x: %.2f, y: %.2f):", msg->turtles.empty() ? "None" : msg->turtles[0].name.c_str(), msg->turtles.empty() ? 0.0f : msg->turtles[0].x, msg->turtles.empty() ? 0.0f : msg->turtles[0].y);

        double target_x = msg->turtles.empty() ? 0.0f : msg->turtles[0].x;
        double target_y = msg->turtles.empty() ? 0.0f : msg->turtles[0].y;

        // Need to get the master turtles position to calculate the distance to the target turtle
        // For this, we can use a member variable to store the latest master turtle position
        if (!msg->turtles.empty()) {
            double distance = std::sqrt(std::pow(target_x - master_turtle_x_, 2) + std::pow(target_y - master_turtle_y_, 2));
            RCLCPP_INFO(this->get_logger(), "Distance to target turtle: %.2f", distance);
        }
    }

    void aliveTurtlesCallback(const turtlegame_interfaces::msg::TurtleArray::SharedPtr msg) {
        // This callback will be called whenever the list of alive turtles is updated.
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