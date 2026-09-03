#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "turtlesim/msg/pose.hpp"
#include "turtlegame_interfaces/msg/turtle.hpp"
#include "turtlegame_interfaces/msg/turtle_array.hpp"
#include "turtlegame_interfaces/srv/catch_turtle.hpp"
 
class TurtleSpawner : public rclcpp::Node {
public:

    TurtleSpawner() : Node("turtle_spawner")  { 
        RCLCPP_INFO(this->get_logger(), "TurtleSpawner node has been started.");
        alive_turtles_pub_ = this->create_publisher<turtlegame_interfaces::msg::TurtleArray>("alive_turtles", 10);

        spawn_client_ = this->create_client<turtlesim::srv::Spawn>("spawn"); // Make it here !

        catch_turtle_service_ = this->create_service<turtlegame_interfaces::srv::CatchTurtle>(
            "catch_turtle",
            std::bind(&TurtleSpawner::catchTurtleCallback, this, std::placeholders::_1, std::placeholders::_2));
        
        timer_ = this->create_wall_timer(
      std::chrono::seconds(5),
      std::bind(&TurtleSpawner::spawnTurtle, this));
    
      kill_client = this->create_client<turtlesim::srv::Kill>("kill");
    
    }


     void spawnTurtle() {

        double x = static_cast<double>(rand()) / RAND_MAX * 11.0;
        double y = static_cast<double>(rand()) / RAND_MAX * 11.0;
        double theta = static_cast<double>(rand()) / RAND_MAX * 2.0 * 3.14159; // Random angle between 0 and 2π



        while (!spawn_client_->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(this->get_logger(), "Spawn service not available, waiting again...");
            return;  // don't block forever inside a timer callback
        }
        auto request = std::make_shared<turtlesim::srv::Spawn::Request>();

        request->x = x;
        request->y = y;
        request->theta = theta;


        last_spawned_turtle_.x = x;
        last_spawned_turtle_.y = y;
        // The name will be filled in the callback after the spawn service responds, response doesnt contain x and y, so we need to store them here in the last_spawned_turtle_ variable.
        last_spawned_turtle_.name = ""; // Will be filled in the callback

        auto future = spawn_client_->async_send_request(request, std::bind(&TurtleSpawner::spawnCallback, this, std::placeholders::_1));
        
    }
private:

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_;  // member now
    rclcpp::Publisher<turtlegame_interfaces::msg::TurtleArray>::SharedPtr alive_turtles_pub_;
    turtlegame_interfaces::msg::Turtle last_spawned_turtle_;
    turtlegame_interfaces::msg::TurtleArray alive_turtles_;  // <-- your variable, holds full state

    // making the catch_turtle_service
    rclcpp::Service<turtlegame_interfaces::srv::CatchTurtle>::SharedPtr catch_turtle_service_;

    rclcpp::Client<turtlesim::srv::Kill>::SharedPtr kill_client;



    void spawnCallback(rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture future) {
        // we are logging the new turtle name here only, the coordinates are publihsed to alive_turtles topic in the spawnTurtle() function, so we dont need to log them here again.
        auto response = future.get();

        // The spawn response contains the generated name; its x and y are not returned.
        last_spawned_turtle_.name = response->name;
        alive_turtles_.turtles.push_back(last_spawned_turtle_);
        alive_turtles_pub_->publish(alive_turtles_);

        RCLCPP_INFO(this->get_logger(), "Spawned turtle with name: %s.", response->name.c_str());
    }


    void catchTurtleCallback(const std::shared_ptr<turtlegame_interfaces::srv::CatchTurtle::Request> request,
                             std::shared_ptr<turtlegame_interfaces::srv::CatchTurtle::Response> response) {
        /* Implement the logic to catch a turtle */
        std::string turtle_name_to_catch = request->name;

        // FInding the appropriate turtle in the alive_turtles_ array
        auto it = std::find_if(alive_turtles_.turtles.begin(), alive_turtles_.turtles.end(), [&](const turtlegame_interfaces::msg::Turtle &turtle) {
            return turtle.name == turtle_name_to_catch;
        });

        if (it != alive_turtles_.turtles.end()) {
            // Turtle found, remove it from the array
            alive_turtles_.turtles.erase(it);

            // Publish the updated list of alive turtles
            // Also kill the turtle in actual sim screen
            
            while (!kill_client->wait_for_service(std::chrono::seconds(1))) {
                RCLCPP_WARN(this->get_logger(), "Kill service not available, waiting again...");
                response->success = false;  // indicate failure to catch the turtle
                return;  // don't block forever inside a timer callback
            }
            auto kill_request = std::make_shared<turtlesim::srv::Kill::Request>();
            kill_request->name = turtle_name_to_catch;
            auto kill_future = kill_client->async_send_request(kill_request);



            response->success = true;
            alive_turtles_pub_->publish(alive_turtles_);     // publish the whole thing
            RCLCPP_INFO(this->get_logger(), "Caught turtle: %s", turtle_name_to_catch.c_str());
        } else {
            // Turtle not found
            response->success = false;
            RCLCPP_WARN(this->get_logger(), "Turtle not found: %s", turtle_name_to_catch.c_str());
        }
    }
};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSpawner>();  
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}