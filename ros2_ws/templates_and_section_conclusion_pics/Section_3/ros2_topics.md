# ROS 2 Topics

## Overview

A **topic** is a named bus over which ROS nodes exchange messages. It provides a unidirectional data stream between a publisher (sender) and one or more subscribers (receivers).

## Key Characteristics

- **Named Bus**: Topics have unique names (e.g., `freq_98.7`, `freq_101.3`, `car_location`) that identify the communication channel
- **Publisher/Subscriber Model**: Unidirectional communication where publishers send data and subscribers receive it
- **Anonymous Communication**: Publishers and subscribers don't need to know each other's identities
- **Typed Messages**: Each topic has a defined message type that structure the data being published
- **Language Agnostic**: Topics can be written in Python, C++, or other languages directly inside ROS nodes
- **Multiple Connections**: A single node can have multiple publishers and subscribers for different topics simultaneously

## Example Use Cases

- **freq_98.7**: A music/audio topic that multiple devices can subscribe to
- **freq_101.3**: Another broadcast channel (e.g., radio frequency) for vehicle locations
- **car_location**: GPS topic containing latitude and longitude data from a car publisher to a monitoring station subscriber

## Why Topics?

Topics decouple nodes from each other—nodes don't need to know about one another. They simply publish or subscribe to topics of interest, making the system flexible and scalable.

## Creating a Python Publisher

This section explains how the Python publisher in `robot_news_station.py` is built, and clarifies the intent of the inline comments in that file.

### How The Publisher Is Made

1. **Create a ROS 2 node class**
	 - The class inherits from `Node` and calls `super().__init__("robot_news_station")`.
	 - This `super()` call must happen before creating ROS entities like publishers and timers.

2. **Create the publisher object**
	 - `self.publisher_ = self.create_publisher(String, "robot_news", 10)`
	 - `String`: message type (`example_interfaces/msg/String`)
	 - `"robot_news"`: topic name
	 - `10`: queue depth (buffer size)

3. **Create a timer to publish repeatedly**
	 - `self.timer_ = self.create_timer(2, self.publish_news)`
	 - This calls `publish_news()` every 2 seconds.

4. **Construct and publish a message**
	 - Inside `publish_news()`, create a `String()` message.
	 - Set `msg.data = "..."` because the `String` interface stores text in the `data` field.
	 - Publish with `self.publisher_.publish(msg)`.

### Comment Clarification (Important)

- **"Create the Publisher object ... after super()"**
	- Correct intent: Publisher creation should happen after node initialization (`super().__init__`) so the node context exists.

- **"Add dependency in package.xml for example_interfaces"**
	- Correct intent: Since `String` comes from `example_interfaces`, the package should declare that dependency in [package.xml](ros2_ws/src/my_python_pkg/package.xml).

- **"Queue size is 10 ... buffer size"**
	- Correct intent: If subscribers are slow, outgoing messages can queue up to depth 10 before old messages are dropped (QoS queue behavior).

- **"ros2 topic list" and "ros2 topic echo" comments**
	- Correct intent: These CLI commands are for validating that the publisher exists and that messages are being published.
	- `ros2 topic list` shows available topic names.
	- `ros2 topic echo /topic_name` prints live message data from a topic.

### CLI Usage And Expected Output

After starting your node, use these commands to verify behavior:

```bash
# 1) List all topics
ros2 topic list

# 2) Inspect the specific topic
ros2 topic info /robot_news

# 3) Echo live messages from the topic
ros2 topic echo /robot_news
```

Example output (representative):

```text
$ ros2 topic list
/parameter_events
/robot_news
/rosout

$ ros2 topic info /robot_news
Type: example_interfaces/msg/String
Publisher count: 1
Subscription count: 0

$ ros2 topic echo /robot_news
data: Did you hear? Sonu just opened a bakery today!
---
data: Did you hear? Sonu just opened a bakery today!
---
```

> Note: `ros2 topic echo` itself acts as a temporary subscriber in the terminal. You can still build a dedicated subscriber node when you want to process data programmatically.
