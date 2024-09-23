# acg_resources_panda_description

The URDF provided in this package has been copied from the official `moveit_resources_panda_description` binary-installed package on July 26, 2023. Then, inertial tags have been added manually because at the time of this modification no official Panda model with inertial tags was available for ROS2.

## Usage

In order to parse the URDF to visualize the Panda robot, after building, use the launch file provided with this package:

```bash
ros2 launch acg_resources_panda_description display.launch.py
```

RViz will be launched and the Panda robot visualized (with its reference frames).
Use the Joint State Publisher's GUI to move single joints.
