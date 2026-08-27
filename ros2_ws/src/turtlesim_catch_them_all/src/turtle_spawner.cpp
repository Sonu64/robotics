#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "turtlesim/msg/pose.hpp"
 

class TurtleSpawner : public rclcpp::Node {
public:
    TurtleSpawner() : Node("turtle_spawner")  { 
        RCLCPP_INFO(this->get_logger(), "TurtleSpawner node has been started.");
        alive_turtles_pub_ = this->create_publisher<turtlesim::msg::Pose>("alive_turtles", 10);
    }
 
private:

    rclcpp::Publisher<turtlesim::msg::Pose>::SharedPtr alive_turtles_pub_;


    void spawnTurtle(double x, double y, double theta) {
        auto client = this->create_client<turtlesim::srv::Spawn>("spawn");
        while (!client->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(this->get_logger(), "Spawn service not available, waiting again...");
        }
        auto request = std::make_shared<turtlesim::srv::Spawn::Request>();

        request->x = x;
        request->y = y;
        request->theta = theta;
        auto future = client->async_send_request(request, std::bind(&TurtleSpawner::spawnCallback, this, std::placeholders::_1));

        //..publish to topic here !
        alive_turtles_pub_->publish(turtlesim::msg::Pose{.x = x, .y = y, .theta = theta});
    
    }



    void spawnCallback(rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture future) {
        // we are logging the new turtle name here only, the coordinates are publihsed to alive_turtles topic in the spawnTurtle() function, so we dont need to log them here again.
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Spawned turtle with name: %s.", response->name.c_str());
    }
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSpawner>();
    node->spawnTurtle(5.0, 5.0, 0.0);
    node->spawnTurtle(2.0, 3.0, 1.57);
    node->spawnTurtle(8.0, 1.0, 3.14);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}