**ROS2 Services — Client/Server Overview**

Services in ROS2 implement a synchronous request/response (RPC-like) pattern between nodes. One node offers a service (the server) and another node calls it (the client). A single service interaction consists of: a client sending a request message, the server processing it, and the server returning a response message.

**Why use services**
- **Request/response semantics:** suitable for operations that need a single result (e.g., compute a value, perform a configuration change).
- **Deterministic single-shot exchange:** not intended for streaming or high-frequency data — use topics or actions for those.

**Basic components**
- **Service type (`.srv`)**: defines the request and response fields (like function arguments and return values). Types can use primitive fields (ints, floats, bool, string), arrays, fixed-size arrays, nested message types, and user-defined message types.
- **Server node**: advertises a service name and the service type, and implements a callback to handle requests.
- **Client node**: constructs a request of the service type and calls the server; can call synchronously (wait for response) or asynchronously (attach a future/callback).

**Service naming convention**
- **Verb-based names are common**: choose names that read like actions, e.g. `add_two_ints`, `get_map`, `set_pose`, `compute_trajectory`. Verbs make it clear the endpoint performs an operation rather than just representing data.
- **Hierarchical names**: you can namespace service names (e.g. `/robot1/navigation/get_map`) to avoid collisions and express scope.
- **Keep names short and descriptive**: prefer `compute_path` over vague names like `service1`.

**Data types you can use**
- **Primitive types**: `int8/16/32/64`, `float32/64`, `bool`, `string`.
- **Arrays and bounded sequences**: variable-length sequences or fixed-size arrays are supported in `.srv` definitions.
- **Composite types**: a service request/response can include other message types (from `std_msgs`, `geometry_msgs`, or custom messages), enabling structured data.
- **Custom `.srv` files**: when built into a package, ROS2 generates language bindings (Python, C++, etc.) for that service type.

**Why we import `AddTwoInts` instead of creating a new service here**
- **Reusability:** `AddTwoInts` (commonly provided by `example_interfaces`) is a canonical, simple interface for demonstrating RPC semantics. Reusing a standard interface avoids duplicating types and makes examples immediately understandable.
- **Interoperability:** other nodes and tools that know `AddTwoInts` can interact without extra setup. If you defined an identical custom `.srv`, other code would still need to depend on your package to use it.
- **Simplicity for examples and learning:** using an existing, minimal service type keeps the example focused on client/server mechanics rather than defining message types.

**When to create your own `.srv`**
- If your request/response needs fields not covered by existing types, define a custom `.srv` in your package and add it to `package.xml` and `CMakeLists.txt` (or the Python build config). Then rebuild to generate language bindings.

**Common misconceptions (cleared)**
- **"Services are like topics" — not exactly.** Topics are asynchronous pub/sub streams; services are synchronous request/response exchanges intended for single interactions.
- **"Service names must be verbs" — not strictly.** It's a strong convention to use verbs for clarity, but the system does not enforce it. Choose names that best communicate intent.
- **"Services maintain a persistent connection" — they do not.** Each request/response is a distinct interaction; transport and middleware handle the actual network layer, but semantics remain single-shot.
- **"Services are always synchronous/blocking" — clients can call asynchronously.** In Python and C++ you can use futures or callbacks to avoid blocking the calling thread.

**Quick example (conceptual)**
- The `AddTwoInts.srv` interface looks like:

```
int64 a
int64 b
---
int64 sum
```

- A server implements a callback that takes a request (`a`, `b`) and returns a response (`sum`). A client fills a request message and calls the server.

**Next steps / Tips**
- For a real robot service that changes hardware state, keep service handlers fast and offload long-running tasks to worker threads to avoid blocking other requests.
- Use actions (ROS2 `action` interface) for cancellable, long-running tasks that need feedback.

If you'd like, I can add a short code snippet for a Python client and server using `AddTwoInts` into this file, or show how to define a custom `.srv` and wire it into your package build.
