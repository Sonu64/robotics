#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "turtlesim/msg/pose.hpp"
 

class TurtleSpawner : public rclcpp::Node {
public:

    TurtleSpawner() : Node("turtle_spawner")  { 
        RCLCPP_INFO(this->get_logger(), "TurtleSpawner node has been started.");
        alive_turtles_pub_ = this->create_publisher<turtlesim::msg::Pose>("alive_turtles", 10);
        
        timer_ = this->create_wall_timer(
      std::chrono::seconds(1),
      std::bind(&TurtleSpawner::spawnTurtle, this));
    }


     void spawnTurtle() {
        
        double x = static_cast<double>(rand()) / RAND_MAX * 10.0;
        double y = static_cast<double>(rand()) / RAND_MAX * 10.0;
        double theta = static_cast<double>(rand()) / RAND_MAX * 2.0 * 3.14159; // Random angle between 0 and 2π


        auto client = this->create_client<turtlesim::srv::Spawn>("spawn");
        while (!client->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(this->get_logger(), "Spawn service not available, waiting again...");
        }
        auto request = std::make_shared<turtlesim::srv::Spawn::Request>();

        request->x = x;
        request->y = y;
        request->theta = theta;
        auto future = client->async_send_request(request, std::bind(&TurtleSpawner::spawnCallback, this, std::placeholders::_1));

        last_spawned_turtle_pose_.x = x;
        last_spawned_turtle_pose_.y = y;
        last_spawned_turtle_pose_.theta = theta;
        alive_turtles_pub_->publish(last_spawned_turtle_pose_);


        //..publish to topic here !
        alive_turtles_pub_->publish(last_spawned_turtle_pose_);
        
    }
private:

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<turtlesim::msg::Pose>::SharedPtr alive_turtles_pub_;
    turtlesim::msg::Pose last_spawned_turtle_pose_;


    void spawnCallback(rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture future) {
        // we are logging the new turtle name here only, the coordinates are publihsed to alive_turtles topic in the spawnTurtle() function, so we dont need to log them here again.
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Spawned turtle with name: %s.", response->name.c_str());
    }
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSpawner>();  
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}