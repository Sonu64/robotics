#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include <string>
#include <memory>
#include <chrono>

using namespace std::chrono_literals;

using String = example_interfaces::msg::String; // This is just a type alias to make the code cleaner and easier to read. It allows us to use String instead of the full example_interfaces::msg::String every time we want to refer to that message type.
// We can also use C++ 98 typedef keyword - typedef example_interfaces::msg::String String; , but for modern C++, 'using' is more common and generally preferred for type aliases.

///@brief Please read the below Lines
/** Importing the String type in C++ files. The rules become a bit more complicated than Python. 
//  1st  we include in the file by adding the include line ---> #include "example_interfaces/msg/string.hpp" [Lowercase] 
//  2nd we add the dependency in package.xml by <depend>example_interfaces</depend> 
// 3rd Step is extra in CPP, as we gonna need CMake, so we also write find_package(example_interfaces REQUIRED) */
 
class RobotNewsStationNode : public rclcpp::Node
{
public:
    RobotNewsStationNode() : Node("robot_news_station"), robot_name_("Sonu_Bot_News_Anchor") {
        publisher_ = this->create_publisher<String>("robot_news", 10);
        // this entire expression returns a Shared Pointer, that we store in the Shared Pointer we made, i.e-> publisher_
        timer_ = this->create_wall_timer( 1s, std::bind(&RobotNewsStationNode::publish_news, this));
        RCLCPP_WARN(this->get_logger(), "Robot News Station has started publishing [This time from the Hard C++ syntax :P]");
    }
 
private:
    // The publisher type must match the message type exactly.
    // This publisher sends String messages on the "robot_news" topic.
    rclcpp::Publisher<String>::SharedPtr publisher_;
    std::string robot_name_; // Just a variable to make the news more interesting.
    rclcpp::TimerBase::SharedPtr timer_; // A timer to call the publish_news method at regular intervals. expects a create_wall_timer function to return a shared pointer to the timer object, which is then stored in the timer member variable. TimerBase is just the object type that represents the timer, and SharedPtr is a type alias for a shared pointer to that object.

    // the method to actually publish the news
    void publish_news() {
        auto msg = String();
        msg.data = std::string("Hello, this is ") + robot_name_ + " ---> Sonu just Baked a Cake out of C++! He lost his mind basically :) ";
        this->publisher_->publish(msg); // remember that publisher_ is a Shared Pointer, so we use the -> operator to call the publish method on it.
    }

};
 
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}