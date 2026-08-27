#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
 

class TurtleSpawner : public rclcpp::Node {
public:
    TurtleSpawner() : Node("turtle_spawner")  { 
        RCLCPP_INFO(this->get_logger(), "TurtleSpawner node has been started.");
    }
 
private:
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSpawner>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}