#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
 

class TurtleController : public rclcpp::Node {
public:
    TurtleController() : Node("turtle_controller")  { 
        RCLCPP_INFO(this->get_logger(), "TurtleController node has been started.");
    }
 
private:
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}