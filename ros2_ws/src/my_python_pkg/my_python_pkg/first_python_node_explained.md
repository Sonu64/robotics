# first_python_node.py — Line-by-Line Explanation

Source file: `first_python_node.py`

```python
#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

class MyNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.get_logger().info("Magic Sensor node initialized.")
        self.log_count = 0  # Counter to track how many times the warning was logged
        self.create_timer(1.0, self.timer_callback)
    
    def timer_callback(self):
        self.log_count += 1
        self.get_logger().warning("Aaila Jaadu... " + str(self.log_count))


def main(args=None):
    rclpy.init(args = args)
    node = MyNode("magic_sensor_node")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__" :
    main()
```

## Line-by-line

1. `#!/usr/bin/env python3`
   - This is a **shebang** line.
   - It tells Linux to run this file with Python 3 when executed directly (for example: `./first_python_node.py`).

2. *(blank line)*
   - Improves readability by separating sections.

3. `import rclpy`
   - Imports the main ROS 2 Python client library.
   - You need this for ROS initialization, spinning, and shutdown.

4. `from rclpy.node import Node`
   - Imports the `Node` class, which is the basic building block of ROS 2 programs.
   - A node can publish, subscribe, offer services, etc.

5. *(blank line)*
   - Readability spacer.

6. *(blank line)*
   - Readability spacer.

7. `def main(args=None):`
   - Defines the `main` function.
   - `args=None` allows optional command-line arguments to be passed into ROS 2 initialization.

8. `    rclpy.init(args = args)`
   - Initializes ROS 2 communication for this process.
   - Must be called before creating or using ROS nodes.

9. *(blank line)*
   - Readability spacer.

10. `    node = Node("testing_python_node")`
    - Creates a ROS 2 node object named `testing_python_node`.
    - This name is how the node appears in ROS tools (for example `ros2 node list`).

11. `    node.get_logger().info("Hello, I wish someday a real robot listens this...")`
    - Gets the node's logger and prints an INFO log message.
    - This is the first place where ROS 2 logging actually happens.
    - The `info()` method sends a message with severity level `INFO`.
    - ROS 2 already gives every node a logger automatically, so you do not need to create one yourself.
    - That is why the log shows up "by default" once this line runs.
    - The message appears in your terminal because the ROS 2 logging system is connected to standard output when the node runs.
    - If you changed `info()` to `warn()`, `error()`, or `debug()`, the severity would change, but the idea is the same: the node sends a log record and ROS 2 formats it for display.

12. `    rclpy.spin(node)`
    - Keeps the node alive and processing callbacks.
    - In this file there are no subscriptions/timers yet, but `spin` still blocks and keeps node running until stopped.

13. *(blank line)*
    - Readability spacer.

14. `    rclpy.shutdown()`
    - Properly shuts down ROS 2 after spinning ends (for example after Ctrl+C).

15. *(blank line)*
    - Readability spacer.

16. `if __name__ == "__main__" :`
    - Standard Python entry-point check.
    - Ensures `main()` runs only when this file is executed directly, not when imported as a module.

17. `    main()`
    - Calls the `main` function to start the node.

## What this program does overall

- Starts ROS 2.
- Creates one node called `MyNode` with the name `magic_sensor_node`.
- Logs an INFO message once: "Magic Sensor node initialized."
- Sets up a timer to fire every 1 second.
- Every 1 second, the timer fires and calls `timer_callback()`.
- In the callback, it increments a counter and logs a WARNING message with the count (e.g., "Aaila Jaadu... 1", "Aaila Jaadu... 2", etc.).
- Keeps spinning (listening) until you stop it with Ctrl+C.
- Shuts ROS 2 down cleanly.

## Expected terminal output when run

You will see ROS 2-formatted logs. The node starts with an INFO message, then prints a WARNING message every 1 second with an incrementing counter:

```text
[INFO] [<timestamp>] [magic_sensor_node]: Magic Sensor node initialized.
[WARNING] [<timestamp>] [magic_sensor_node]: Aaila Jaadu... 1
[WARNING] [<timestamp>] [magic_sensor_node]: Aaila Jaadu... 2
[WARNING] [<timestamp>] [magic_sensor_node]: Aaila Jaadu... 3
[WARNING] [<timestamp>] [magic_sensor_node]: Aaila Jaadu... 4
...
```

Each time the 1-second timer fires, a new warning appears with the next count number.

## Logging system explained simply

Think of the logger as a built-in message printer that belongs to the node.

- `node.get_logger()` gives you the logger object attached to that node.
- `.info(...)` says, "print this message as an INFO-level log."
- ROS 2 decides how the message should look in the terminal.
- The node name appears in the log because ROS 2 includes it automatically.

So the flow is:

1. You create the node.
2. ROS 2 gives that node a logger.
3. You call `info()` on that logger.
4. ROS 2 prints the message with a timestamp, severity, and node name.

## Why INFO works without extra setup

You do not need to configure logging before using `info()` because:

- ROS 2 initializes a default logging system when you call `rclpy.init(...)`.
- Every node gets a default logger automatically.
- `info()` is one of the standard logger methods that already exists on that logger.

That means this line:

```python
node.get_logger().info("Hello")
```

is enough by itself to produce a log message.

## Common confusion

- `info()` does not mean "this message is optional".
- It means the message severity level is INFO.
- The word "info" is part of the logging level name, not a special ROS 2 keyword.
- The output appears because the logger is already available on the node.
- You are not manually printing text with Python's `print()` here; ROS 2 is handling the message as a structured log.

## Beginner notes

- This node demonstrates a **class-based node** with custom initialization and a timer callback.
- It shows how to maintain state across multiple callback invocations using instance variables.
- It demonstrates periodic work (the timer fires every 1 second).
- This is a small step up from a minimal "alive + single log" node.
- Next common steps would be to add publishers, subscribers, or services.
- Style note: Python convention is usually `args=args` (without spaces around `=` in function arguments), but your current line still works correctly.

## FileName vs Node name vs Executable name

The file name and the node name are related, but they do not have to be the same.

- The file name is the Python file on disk, like `first_python_node.py`.
- The node name is the runtime name inside ROS 2, like `testing_python_node`.
- ROS 2 cares about the node name when it is running.
- Python cares about the file name when it loads or executes the script.
- There is also the **executable name** from `setup.py` in `entry_points`, like `py_node`.
- That executable name is what you run with `ros2 run my_python_pkg py_node`.
- It is separate from both the file name and the ROS node name.

You can make them similar for clarity, but it is not a rule.

For beginners, a good convention is:

- Use a file name that describes the script.
- Use a node name that describes what the node does.
- Keep both lowercase and readable.

Example:

- File: `camera_reader.py`
- Node name: `camera_reader`
- Executable name in `setup.py`: `camera_reader`

Or:

- File: `first_python_node.py`
- Node name: `testing_python_node`
- Executable name in `setup.py`: `py_node`

Both are valid.

## Should one file create multiple node objects?

Usually, for beginners, the answer is no.

If the file is meant to be a single ROS 2 node script, then it is best to create one node object in that file and let that node do one job.

Why this is the common approach:

- It keeps the code easier to understand.
- It matches the way most ROS 2 tutorials are written.
- It makes debugging simpler.
- It follows the idea that one node should have one clear responsibility.

When might multiple node objects appear in one file?

- In small experiments or learning code.
- If you are deliberately testing communication between nodes.
- If one script is acting like a launcher or demo that creates more than one node.

Even then, that is more of an advanced or special-case pattern.

For your current file, the clean beginner choice is:

- one file
- one node object
- one main purpose

That makes the code easier to read and easier to grow later.

## Timers and Periodic Callbacks (Repeated Actions Every N Seconds)

In the current `MyNode` implementation, there is a timer that prints a warning message every 1 second. Here's how it works:

### The Setup

```python
class MyNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.get_logger().info("Magic Sensor node initialized.")
        # Create a timer that fires every 1.0 second
        self.create_timer(1.0, self.timer_callback)
    
    def timer_callback(self):
        # This runs every 1 second, automatically
        self.get_logger().warning("Aaila Jaadu... ")
```

### How It Works

1. **`self.create_timer(1.0, self.timer_callback)`**
   - Creates a timer object that belongs to the node.
   - `1.0` is the period in seconds.
   - `self.timer_callback` is the function to call each time the timer fires.
   - The timer is automatically managed by ROS 2.

2. **Why it prints every 1 second**
   - When you call `rclpy.spin(node)` in `main()`, the spin loop takes over.
   - Inside the spin loop, ROS 2 checks all timers attached to the node.
   - Every 1 second, it sees that the timer has elapsed and automatically calls `timer_callback()`.
   - The callback runs, logs the warning, and then control returns to spin.
   - Spin continues waiting for the next event.

3. **Spin is like a repeating event listener**
   - `rclpy.spin(node)` does not do anything special on its own—it just waits.
   - But while it waits, it listens for all registered events:
     - Timer callbacks (like the 1-second timer here).
     - Subscription callbacks (when messages arrive).
     - Service callbacks (when a service is called).
   - The moment any event is ready, spin executes its callback and waits for the next one.

### Visual Timeline

```
Time (seconds):    0      1      2      3      4
                   |      |      |      |      |
Spin listening...  ------>@----->@----->@----->@...
                    (init) (warn) (warn) (warn) (warn)
                    
@ = Timer fires, callback runs
```

### Why This Pattern Is Useful

Timers let you:

- **Poll sensors** at regular intervals (e.g., "read the IMU every 100 ms").
- **Send heartbeat messages** to keep communication alive.
- **Update actuators** at fixed rates (e.g., "adjust robot arm position every 50 ms").
- **Log data** or check health status periodically.

### Common Timer Periods

- **0.05 seconds** (50 ms): Fast feedback loops, motor control.
- **0.1 seconds** (100 ms): Moderate updates, sensor reading.
- **1.0 second**: Slow monitoring, logging, status checks.
- **5.0 seconds**: Very slow tasks, periodic health reports.

### Changing the Period

To print every 2 seconds instead of 1 second:

```python
self.create_timer(2.0, self.timer_callback)  # Now 2 seconds
```

### Multiple Timers

A single node can have multiple timers at different rates:

```python
self.create_timer(0.5, self.fast_callback)   # Every 0.5 seconds
self.create_timer(2.0, self.slow_callback)   # Every 2.0 seconds
```

Spin will handle all of them and call their callbacks on schedule.

### Key Takeaway

- Timers are how ROS 2 nodes perform **repeated, periodic work**.
- `create_timer(period, callback)` schedules a callback to run every `period` seconds.
- `rclpy.spin(node)` automatically invokes all callbacks as their timers fire.
- You don't manually call the callback—ROS 2 does it for you on schedule.

## Instance Variables (Maintaining State Across Callbacks)

In `MyNode`, there is a variable called `self.log_count`. This is an **instance variable**.

### What Is an Instance Variable?

An instance variable belongs to a specific object (in this case, a `MyNode` object). It is created in `__init__` and persists as long as the object exists.

```python
class MyNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.log_count = 0  # Instance variable: created once in __init__
        self.create_timer(1.0, self.timer_callback)
    
    def timer_callback(self):
        self.log_count += 1  # Each call increments the same variable
        self.get_logger().warning("Aaila Jaadu... " + str(self.log_count))
```

### Why Use Instance Variables?

Instance variables let you **keep state** across multiple function calls. Without them, every time `timer_callback()` was called, there would be no way to remember how many times it had been called before.

### The Flow

1. `__init__` runs once when the node is created: `self.log_count = 0`.
2. The timer fires at 1 second: `timer_callback()` runs, increments `log_count` to 1, logs "Aaila Jaadu... 1".
3. The timer fires at 2 seconds: `timer_callback()` runs again, increments `log_count` to 2, logs "Aaila Jaadu... 2".
4. This repeats every second until the node shuts down.

The key is that `self.log_count` is not reset between calls—it persists because it belongs to the `node` object, and the `node` object stays alive as long as `rclpy.spin()` is running.

### Instance vs Class Variables

- **Instance variable** (`self.log_count`): Each object has its own copy. Different nodes would have different counts.
- **Class variable** (defined outside `__init__` in the class body): Shared by all instances of the class.

For this demo, `self.log_count` is correct because each node should track its own count.
