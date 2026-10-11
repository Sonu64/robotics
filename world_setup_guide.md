# Gazebo World Setup Guide

This guide explains how the Depot warehouse world was integrated into the ROS 2
simulation, why the original world failed to load, and how the corrected setup
works.

## 1. The important distinction: a world is not a model

Gazebo Sim loads two different kinds of SDF resources:

- A **world** describes the simulation environment: lights, gravity, ground,
  and the models placed in the scene.
- A **model** describes one reusable object: links, visuals, collisions,
  materials, meshes, and plugins.

The downloaded `Depot` directory is a model, not a complete world. Its typical
layout is:

```text
models/Depot/
├── model.config
├── model.sdf
├── meshes/
│   ├── Depot.dae
│   └── Crates.dae
└── materials/
    ├── scripts/
    └── textures/
```

`model.config` tells Gazebo that `model.sdf` is the model entry point. The
`model.sdf` then refers to assets relative to the model directory, for example:

```xml
<uri>meshes/Depot.dae</uri>
<albedo_map>materials/textures/ROOF_Albedo.png</albedo_map>
```

Therefore, the entire `Depot` directory must remain intact. Copying only
`model.sdf`, or changing the directory layout, breaks mesh and texture lookup.

## 2. Why the original world failed

The first world file contained:

```xml
<include><uri>model://sun</uri></include>
<include><uri>model://ground_plane</uri></include>
<include><uri>model://Depot</uri></include>
```

Each `model://...` URI is a name lookup. Gazebo does not search the whole
filesystem for a matching folder. It searches the directories listed in its
resource path, primarily through the `GZ_SIM_RESOURCE_PATH` environment
variable.

The launch environment was only configured with ROS/Gazebo installation
directories. It did not include the package's custom model directory:

```text
.../red_cherrybot_bringup/models
```

As a result, Gazebo reported:

```text
Unable to find uri[model://sun]
Unable to find uri[model://ground_plane]
Unable to find uri[model://Depot]
```

There were two separate lookup problems:

1. `Depot` was a downloaded custom model and was not on Gazebo's resource path.
2. The installed Gazebo environment did not provide the standard `sun` and
   `ground_plane` model folders at the locations being searched.

When the world cannot be parsed or started, `ros_gz_sim create` keeps asking
for the list of world names. It is waiting for a Gazebo server that never
successfully created the requested world; those repeated requests are a
symptom of the failed server startup, not a robot URDF problem.

## 3. Installing the model with the ROS package

The bringup package installs both the world and the model resources:

```cmake
install(
  DIRECTORY launch config models worlds
  DESTINATION share/${PROJECT_NAME}
)
```

After building, the relevant installed paths are:

```text
ros2_ws/install/red_cherrybot_bringup/share/red_cherrybot_bringup/
├── models/Depot/...
└── worlds/depot_warehouse.world
```

This matters because a ROS launch file normally resolves package resources from
the install space using:

```text
$(find-pkg-share red_cherrybot_bringup)
```

The source files can exist and still not be available to a running launch if
the package has not been rebuilt or the install space is stale.

Build from the workspace root:

```bash
cd ~/Desktop/robotics/ros2_ws
colcon build --packages-select red_cherrybot_bringup --symlink-install
source /opt/ros/jazzy/setup.bash
source install/setup.bash
```

Building from the workspace root avoids accidentally building a different
workspace or inspecting an old install tree.

## 4. Making the custom model discoverable

The launch file sets Gazebo's model search path:

```xml
<set_env
    name="GZ_SIM_RESOURCE_PATH"
    value="$(find-pkg-share red_cherrybot_bringup)/models"
/>
```

With that setting, this URI:

```xml
<uri>model://Depot</uri>
```

resolves to:

```text
<installed package share>/models/Depot/
```

Gazebo then reads `model.config`, loads `model.sdf`, and resolves the mesh and
texture paths relative to `models/Depot`.

If an existing `GZ_SIM_RESOURCE_PATH` must be preserved, multiple directories
can be supplied using the platform's path separator. On Linux, the separator
is `:`. In this project, the launch file points directly at the package's
models directory because that is the required custom resource location.

## 5. The custom world file

The world is located at:

```text
red_cherrybot_bringup/worlds/depot_warehouse.world
```

Its structure is:

```xml
<sdf version="1.6">
  <world name="default">
    <!-- light -->
    <!-- ground plane -->
    <!-- Depot model include -->
  </world>
</sdf>
```

The world uses inline definitions for the sun and ground plane:

```xml
<light name="sun" type="directional">
  ...
</light>

<model name="ground_plane">
  <static>true</static>
  ...
</model>
```

This avoids depending on separate `model://sun` and
`model://ground_plane` folders. The light and ground are now part of the world
itself, so only the custom Depot model needs resource-path lookup.

The Depot is still included as a reusable model:

```xml
<include>
  <uri>model://Depot</uri>
</include>
```

This is preferable to copying all of the Depot's links, meshes, and materials
into the world file. The world controls *where and when* the model is placed;
the model controls *what the Depot is*.

## 6. Why the world name affects the bridge

The world declares:

```xml
<world name="default">
```

Gazebo topics include the world name. For example, the robot joint-state topic
is under:

```text
/world/default/model/Red_Cherry_Bot/joint_state
```

The bridge configuration must use that exact topic:

```yaml
- ros_topic_name: "/joint_states"
  gz_topic_name: "/world/default/model/Red_Cherry_Bot/joint_state"
  ros_type_name: "sensor_msgs/msg/JointState"
  gz_type_name: "gz.msgs.Model"
  direction: "GZ_TO_ROS"
```

The previous configuration used `/world/empty`, which matched an older
empty-world setup. Even after the Depot world loaded, that stale topic would
prevent joint states from reaching ROS.

## 7. Launch sequence

The launch file performs these operations:

1. Starts `robot_state_publisher` with the generated Xacro description.
2. Starts RViz.
3. Sets `GZ_SIM_RESOURCE_PATH` for the custom model.
4. Starts Gazebo with `depot_warehouse.world`.
5. Runs `ros_gz_sim create -topic robot_description` to spawn the robot.
6. Starts `ros_gz_bridge` using the bridge YAML file.

The world file is passed to Gazebo here:

```xml
<include file="$(find-pkg-share ros_gz_sim)/launch/gz_sim.launch.py">
  <arg
      name="gz_args"
      value="$(find-pkg-share red_cherrybot_bringup)/worlds/depot_warehouse.world -r"
  />
</include>
```

The `-r` argument starts the simulation running immediately.

## 8. Useful checks when adding another downloaded model

### Check the model structure

Confirm that the model has an entry point and that every referenced asset
exists:

```bash
find red_cherrybot_bringup/models/Depot -maxdepth 3 -type f | sort
```

### Check the package install

```bash
find ~/Desktop/robotics/ros2_ws/install/red_cherrybot_bringup/share/red_cherrybot_bringup \
  -maxdepth 3 -type f | sort
```

The installed `models/Depot/model.sdf` and its mesh/texture files should be
present.

### Check the generated robot description

```bash
source /opt/ros/jazzy/setup.bash
xacro red_cherrybot_description/urdf/model.urdf.xacro > /tmp/robot.urdf
```

This checks the robot description separately from the world.

### Test the world directly

```bash
source /opt/ros/jazzy/setup.bash
source ~/Desktop/robotics/ros2_ws/install/setup.bash
gz sim -s -r \
  ~/Desktop/robotics/ros2_ws/install/red_cherrybot_bringup/share/red_cherrybot_bringup/worlds/depot_warehouse.world
```

If the world uses a custom model, ensure the model path is available in the
shell used for this direct test:

```bash
export GZ_SIM_RESOURCE_PATH="$PWD/red_cherrybot_bringup/models"
```

For normal ROS launch usage, the launch file sets this environment variable
automatically.

### Launch the complete simulation

```bash
cd ~/Desktop/robotics/ros2_ws
source /opt/ros/jazzy/setup.bash
source install/setup.bash
ros2 launch red_cherrybot_bringup red_cherrybot_gazebo.launch.xml
```

Successful startup should include messages similar to:

```text
Entity creation successful.
Creating GZ->ROS Bridge: [/clock ...]
Creating GZ->ROS Bridge: [/world/default/model/Red_Cherry_Bot/joint_state ...]
```

## 9. Common mistakes

- **Only copying `model.sdf`:** meshes and textures are missing.
- **Using `model://Depot` without adding `models` to the resource path:**
  Gazebo cannot find the model.
- **Referencing source paths from the install-space launch:** the installed
  package must contain the resources used at runtime.
- **Forgetting to rebuild after adding files:** the install tree remains stale.
- **Using `/world/empty` after renaming the world:** bridge topics no longer
  match.
- **Renaming `Depot` without updating the URI:** `model://Depot` is
  case-sensitive and must match the model directory name.
- **Changing relative paths inside `model.sdf`:** paths such as
  `meshes/Depot.dae` are resolved relative to the model directory and should
  remain consistent with its layout.

## Summary

The fix was not to merge the Depot SDF into the world. The reliable approach
is:

1. Keep the downloaded Depot model directory intact.
2. Install `models/` and `worlds/` with the ROS package.
3. Add the installed `models` directory to `GZ_SIM_RESOURCE_PATH`.
4. Define basic light and ground directly in the custom world when standard
   model packages are unavailable.
5. Include `model://Depot` from the world.
6. Match bridge topic names to the world's declared name.

That separates environment composition from model contents and makes the setup
portable across clean workspaces.
