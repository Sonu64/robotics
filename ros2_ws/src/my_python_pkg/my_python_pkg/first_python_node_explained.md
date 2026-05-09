# first_python_node.py — Line-by-Line Explanation

Source file: `first_python_node.py`

```python
#!/usr/bin/env python3

import rclpy
from rclpy.node import Node


def main(args=None):
    rclpy.init(args = args)

    node = Node("testing_python_node")
    node.get_logger().info("Hello, I wish someday a real robot listens this...")
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
- Creates one node named `testing_python_node`.
- Prints one INFO log line.
- Waits (spins) until you stop it.
- Shuts ROS 2 down cleanly.

## Expected terminal output when run

You will see ROS 2-formatted logs. Exact timestamps/process IDs vary, but it will look similar to:

```text
[INFO] [<timestamp>] [testing_python_node]: Hello, I wish someday a real robot listens this...
```

If launched with `ros2 run`, ROS may also print startup/shutdown lines around this log.

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

- The node is currently a minimal "alive + log" node.
- Next common step is to add a timer, publisher, or subscriber.
- Style note: Python convention is usually `args=args` (without spaces around `=` in function arguments), but your current line still works correctly.

## File name vs node name

The file name and the node name are related, but they do not have to be the same.

- The file name is the Python file on disk, like `first_python_node.py`.
- The node name is the runtime name inside ROS 2, like `testing_python_node`.
- ROS 2 cares about the node name when it is running.
- Python cares about the file name when it loads or executes the script.

You can make them similar for clarity, but it is not a rule.

For beginners, a good convention is:

- Use a file name that describes the script.
- Use a node name that describes what the node does.
- Keep both lowercase and readable.

Example:

- File: `camera_reader.py`
- Node name: `camera_reader`

Or:

- File: `first_python_node.py`
- Node name: `testing_python_node`

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
