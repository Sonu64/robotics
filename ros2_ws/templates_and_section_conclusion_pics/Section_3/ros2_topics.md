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
data: Breaking News from Robo Anchor! Sonu just opened a Bakery today in Darjeeling :)
---
data: Breaking News from Robo Anchor! Sonu just opened a Bakery today in Darjeeling :)
---
```

### Introspecting Topics with the ROS 2 CLI

- `ros2 topic list`
	- Lists all active topic names on the ROS 2 network.

- `ros2 topic info /topic_name`
	- Shows summary information about the topic, including the `Type:` line (for example `example_interfaces/msg/String`), publisher and subscription counts, and basic QoS details.
	- Copy the value shown after `Type:` and call it `typeName` for the next step.

- `ros2 interface show typeName`
	- Example: `ros2 interface show example_interfaces/msg/String`
	- Prints the full message/interface definition (fields and their types). Use this to see what data the topic carries and the exact field names you should access in code.

What the `Type` tells us

- The `Type` is the message interface (schema) used on the topic. It defines the fields and their types that publishers put on the topic and that subscribers receive.
- Publishers must publish messages that conform to that interface, and subscribers expect the same interface to deserialize and access fields correctly.
- In practice this means the subscriber code should use the same message type (for example, `example_interfaces::msg::String` in C++ or `example_interfaces.msg.String` in Python) so the message fields line up exactly.
- ROS 2 is language agnostic: as long as both sides use the same message/interface definition, a Python publisher will connect to a C++ subscriber and vice‑versa.

> Tip: If `ros2 topic info` shows a different type than you expect, double‑check the publisher node and the package dependencies (e.g., `example_interfaces`) to ensure both sides use the same interface.

> Note: `ros2 topic echo` itself acts as a temporary subscriber in the terminal. You can still build a dedicated subscriber node when you want to process data programmatically.

### Measuring Topic Frequency: `ros2 topic hz`

- Use `ros2 topic hz /topicName` to measure how frequently messages are being published on a topic.
	- Example for this document: `ros2 topic hz /robot_news`
- The command prints the average frequency in Hertz (messages per second) and the equivalent period in seconds (time between messages).
- Typical output looks like:

```text
subscribed to [ /robot_news ]
average rate: 0.50 Hz
average period: 2.000 s
min: 2.000s max: 2.000s std dev: 0.00000s window: 10
```

- Interpretation:
	- `average rate` is how many messages per second the node observed (Hz).
	- `average period` is the inverse (seconds between messages). In this example the publisher sends one message every 2 seconds (0.5 Hz).

- Use this to verify timers and expected publish rates, and to spot problems like unexpectedly slow publishers or noisy timing.


### Measuring Topic Bandwidth: `ros2 topic bw`

- Use `ros2 topic bw /topicName` to measure the data throughput on a topic (bandwidth).
	- Example for this document: `ros2 topic bw /robot_news`
- The command reports the observed bandwidth (bytes/sec or KB/s), average message size, and the message rate (Hz). This helps estimate the data load of a topic and whether network or processing limits might be hit.
- Typical output (illustrative):

```text
subscribed to [ /robot_news ]
average bandwidth: 0.10 KB/s
average message size: 20 B
average rate: 0.50 Hz
min: 0.50Hz max: 0.50Hz std dev: 0.00000Hz window: 10
```

- Interpretation:
	- `average bandwidth` is the data throughput observed on the topic (bytes per second).
	- `average message size` helps you understand how heavy each message is.
	- Combine bandwidth and frequency to reason about total network usage (bandwidth ≈ message_size × rate).

- Use `ros2 topic bw` when profiling and optimizing communication, or when choosing serialization/compression or appropriate QoS settings.


### Temporary Publisher from the CLI: `ros2 topic pub`

- You can publish test messages directly from the shell with `ros2 topic pub`.
- Corrected example (publish at 1 Hz to `/robot_news` using `example_interfaces/msg/String`):

```bash
ros2 topic pub -r 1 /robot_news example_interfaces/msg/String '{data: "A Temporary publisher is currently publishing in the topic, but it is not possible to do this for complex types like arrays, classes or nested subtypes."}'
```

- Notes:
	- Use `--once` to publish a single message instead of a repeated rate: `ros2 topic pub --once /robot_news example_interfaces/msg/String '{data: "one-off"}'`.
	- For complex message fields (arrays, nested messages), provide valid YAML/JSON and be careful with shell quoting. Example array: `'{arr: [1, 2, 3]}'`.
	- Some complex ROS 2 types are cumbersome to construct on the CLI; for those, write a short node in Python or C++ to publish reliable test messages.

### Dynamic Robot Name and f-strings

- **`self.robot_name_`**: The publisher now sets `self.robot_name_ = "Robo Anchor"` in `__init__`. That value is inserted into each outgoing message so the same node can identify the source robot dynamically.

- **How it's used**: The code constructs the message with an f-string:

```py
msg.data = f"Breaking News from {self.robot_name_}! Sonu just opened a Bakery today in Darjeeling :)"
```

- **Comment correction**: The code comment mentioning "backticks" is misleading — Python f-strings use the `f"..."` prefix and normal double/single quotes, not backticks. Backticks are not used in modern Python for string interpolation.

- **How to change the robot name**:
	- Edit the assignment in the class: `self.robot_name_ = "New Name"`.
	- Or extend the node to accept a parameter/command-line argument and set `self.robot_name_` from that value for runtime configurability.

- **Updated CLI output**: When `self.robot_name_` is `Robo Anchor`, `ros2 topic echo /robot_news` will show messages like:

```text
data: Breaking News from Robo Anchor! Sonu just opened a Bakery today in Darjeeling :)
---
```

This makes log lines and terminal echoes more informative when multiple publishers exist (each can embed a unique source name inside the message).

## Creating a Python Subscriber

This section explains how the Python subscriber in `smartphone.py` is built, and clarifies the intent of the inline comments in that file.

### How The Subscriber Is Made

1. **Create a ROS 2 node class**
	 - The class inherits from `Node` and calls `super().__init__("smartphone")`.
	 - This initializes the node with the name `"smartphone"` in the ROS 2 network.

2. **Create the subscriber object**
	 - `self.subscriber_ = self.create_subscription(String, "robot_news", self.robot_news_callback, 10)`
	 - `String`: message type (`example_interfaces/msg/String`)
	 - `"robot_news"`: topic name to listen on (must match the publisher's topic name)
	 - `self.robot_news_callback`: callback function that runs when a message arrives
	 - `10`: queue depth (buffer size for incoming messages)

3. **Define the callback function**
	 - `robot_news_callback(self, msg: String)` is automatically invoked whenever a message is published on `"robot_news"`.
	 - The `msg` parameter contains the received message (type `String`).
	 - Use `msg.data` to access the string content from the publisher.

4. **Initialize and spin the node**
	 - In `main()`, initialize ROS 2 with `rclpy.init(args=args)`.
	 - Create the subscriber node: `node = SmartphoneNode()`.
	 - Run `rclpy.spin(node)` to keep the node alive and processing incoming messages.
	 - Call `rclpy.shutdown()` to clean up when the node exits.

### Comment Clarification (Important)

- **"create_subscription ... robot_news_callback will be called with the message"**
	- Correct intent: Whenever the publisher sends a message on `"robot_news"`, ROS 2 automatically calls `robot_news_callback()` with that message. This is the **event-driven** pattern.

- **"msg.publisher_name is not a standard field"**
	- Correct intent: The `String` message type from `example_interfaces` only has a single `data` field (which holds the text). There is no built-in `publisher_name` field, so `msg.publisher_name` will cause an error if you try to access it.
	- **Solution**: If you need to know the publisher's identity, either:
		- Embed the name inside the message data (as the publisher does with the f-string `f"Breaking News from {self.robot_name_}!..."`).
		- Use a custom message type that includes both data and publisher information.

- **"Queue depth 10"**
	- Correct intent: If the subscriber's callback function is slow or busy, up to 10 incoming messages can be queued. After that, old messages are dropped. This is QoS (Quality of Service) behavior.

### Typical Output When Running

When you run both the publisher (`robot_news_station.py`) and the subscriber (`smartphone.py`):

```bash
# Terminal 1: Run the publisher
ros2 run my_python_pkg robot_news_station

# Terminal 2: Run the subscriber
ros2 run my_python_pkg smartphone
```

You will see logs like:

```text
[smartphone-1] [INFO] [rclpy]: Smartphone is Ready to Use...
[smartphone-1] [INFO] [smartphone]: Smartphone received news: Breaking News from Robo Anchor! Sonu just opened a Bakery today in Darjeeling :) from Publisher
[smartphone-1] [INFO] [smartphone]: Smartphone received news: Breaking News from Robo Anchor! Sonu just opened a Bakery today in Darjeeling :) from Publisher
```

The messages repeat every 2 seconds because the publisher has a 2-second timer.

### Key Differences: Publisher vs. Subscriber

| Aspect | Publisher | Subscriber |
|--------|-----------|-----------|
| **Method** | `create_publisher()` | `create_subscription()` |
| **Message Flow** | Sends data out | Receives data in |
| **Timing** | Uses a timer for periodic publishing | Uses a callback for event-driven processing |
| **Role** | Speaker | Listener |

### Python vs. C++ Topic Syntax

- In Python, you can usually set up a member in one line inside the constructor, like `self.var_name = value`.
- In C++, the structure is split more explicitly: member declarations are kept in the class, usually under `private:`, and the constructor is defined separately in the `.cpp` file.
- For ROS 2 pub/sub code, the main idea is the same in both languages: create the node, create the publisher or subscriber, and use the callback or timer to move data.

### ROS 2 Is Language Agnostic

- ROS 2 topics do not care whether a node is written in Python or C++.
- A Python publisher can communicate with a C++ subscriber.
- A C++ publisher can communicate with a Python subscriber.
- What matters is the topic name and the message type matching on both sides.

### Renaming Topics at Runtime

You can rename a topic when launching a node by using a ROS 2 remap rule. This is useful when you want the same code to publish or subscribe to a different topic name without changing the source file.

Example for the publisher side:

```bash
ros2 run my_cpp_pkg robot_news_station --ros-args -r robot_news:=NewRobotNews
```

In this command, the publisher originally creates `robot_news`, but ROS 2 remaps it to `NewRobotNews` at runtime.

Important: the subscriber must use the same remapped topic name too. If the publisher is remapped to `NewRobotNews` but the subscriber still listens on `robot_news`, they will no longer connect, so you will get no output.

Example for the subscriber side:

```bash
ros2 run my_cpp_pkg smartphone --ros-args -r robot_news:=NewRobotNews
```

Now both nodes are talking on the same runtime topic name, so messages flow normally again.

You can think of this as changing the topic label at launch time instead of editing the code. The message type stays the same, but the name used to connect the nodes changes.

---

> **Congrats!** 🎉 You've taken another step in your robotics journey! Now your nodes talk with each other. One speaks, the other listens... And the same nodes can be Pubs/Subs for other topics simultaneously. One Node can be a Publisher AND a Subscriber at the same time! This is the power of ROS 2's decoupled architecture—nodes communicate via topics without knowing each other directly.
