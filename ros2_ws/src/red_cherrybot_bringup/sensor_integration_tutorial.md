# Integrating sensors with Gazebo Sim

## Where the Sensors system plugin belongs

The `gz::sim::systems::Sensors` plugin is a **world system plugin**. Add it as
an immediate child of the `<world>` element in the SDF world that you pass to
`gz sim`:

```xml
<sdf version="1.6">
  <world name="default">
    <plugin filename="gz-sim-sensors-system"
            name="gz::sim::systems::Sensors">
      <render_engine>ogre2</render_engine>
    </plugin>

    <!-- lights, models, includes, and other world content -->
  </world>
</sdf>
```

This package now does that in
[`worlds/depot_warehouse.world`](worlds/depot_warehouse.world). The plugin is
loaded once when that world starts and services rendering-based sensors from
all models in the world, including models loaded through `<include>`.

### Why it does not go in `models/Depot/model.sdf`

`models/Depot/model.sdf` describes one model: its links, visuals, collisions,
joints, and any sensors physically attached to that model. The Sensors system
is different: it is simulation infrastructure that updates sensors and
connects them to Gazebo Transport. Putting it in a model would make the
system's lifetime and scope depend on that model and would not be the correct
world-level configuration.

The plugin does **not** create a camera or LiDAR by itself. A sensor still
has to be declared under the link of the robot or other model that owns it.
For example, a camera definition belongs inside a model:

```xml
<link name="sensor_mount">
  <sensor name="front_camera" type="camera">
    <always_on>true</always_on>
    <update_rate>30</update_rate>
    <visualize>true</visualize>
    <topic>/front_camera/image</topic>
    <camera>
      <horizontal_fov>1.047</horizontal_fov>
      <image>
        <width>640</width>
        <height>480</height>
        <format>R8G8B8</format>
      </image>
      <clip>
        <near>0.1</near>
        <far>100</far>
      </clip>
    </camera>
  </sensor>
</link>
```

The system plugin is the scheduler/implementation for the sensor; the
`<sensor>` element is the sensor's physical and publishing configuration.
For ROS 2, add the corresponding Gazebo-to-ROS topic mapping to your
`ros_gz_bridge` configuration as well.

## A large `.world` file

File size does not change the placement. Find the one root world element that
Gazebo loads:

```xml
<sdf version="1.6">
  <world name="warehouse">
    <!-- Put world systems here, before or after other world children. -->
    <plugin filename="gz-sim-sensors-system"
            name="gz::sim::systems::Sensors">
      <render_engine>ogre2</render_engine>
    </plugin>

    <include>
      <uri>model://Depot</uri>
    </include>
    <!-- the rest of the large world -->
  </world>
</sdf>
```

Do not add one copy for every model or every included file. Add one copy for
each simulated world. If a launch file can select several different world
files, each world that contains rendering sensors needs the plugin.

## A single `.sdf` world

If the file contains `<sdf><world>...</world></sdf>`, add the plugin directly
under that `<world>`, as in the first example. The extension does not matter:
`.world` and `.sdf` can both contain SDF XML. What matters is the element
hierarchy and the file actually passed to `gz sim`.

## A complex world split across a folder

A common layout is:

```text
my_sim/
├── worlds/
│   └── warehouse.world       # root world loaded by gz sim
├── models/
│   └── robot/model.sdf       # model and its sensor definitions
└── config/
    └── bridge.yaml           # optional ROS 2 topic bridges
```

Put the world system plugin in `worlds/warehouse.world`, not in every model
file. Put each physical sensor in the owning model's `model.sdf` (or in the
robot URDF/Xacro before it is spawned). Set `GZ_SIM_RESOURCE_PATH` so Gazebo
can resolve the model and mesh paths, then bridge the resulting Gazebo topics
to ROS 2.

If a world uses `<include>` to load a model, the included model does not need
to repeat the world plugin. If a generated world is assembled from fragments,
ensure the final generated root world contains exactly one Sensors plugin
before launching it.

## Checking the integration

Start the same world used by the launch file:

```bash
gz sim /path/to/red_cherrybot_bringup/worlds/depot_warehouse.world -r
```

Watch the Gazebo output for plugin-loading errors. A loaded Sensors system
alone does not imply that a topic exists: first confirm that a model contains
a sensor, then inspect Gazebo Transport topics and the ROS 2 bridge. For
example, after adding a camera, use:

```bash
gz topic -l
ros2 topic list
```

The rendering engine setting shown here selects Ogre 2, which is the renderer
used by this Gazebo Sim setup for rendering sensors. It is not a replacement
for the GUI's rendering configuration and it does not configure ROS 2 topic
names.
