# panda_moveit_planning_demo
## Trajectory controller 

This package provides a demo for MoveIt!2 planning capabilities by using the `MoveGroupInterface` class.
The source code is quite self-explanatory, so step through its main functions to grasp what the demo does.
At execution, the `acg_resources_panda_moveit_config` package must be installed (see usage instructions below).

### Usage

In a first shell launch the `move_group` node and utility nodes, like RViz, from the `acg_resources_panda_moveit_config` package.
Make sure to select the appropriate RViz configuration:

```bash
ros2 launch acg_resources_panda_moveit_config demo.launch.py rviz_config:=planning_demo.rviz
```

In another shell run this package's planning demo:

```bash
ros2 run panda_moveit_planning_demo panda_moveit_planning_node
```

Use the **RVizVisualToolsGUI** to step through the demo.

### Debug the node

The launch file `launch/demo.launch.py` executes the same demo from a launch file. This is only needed to debug the node through the VSCode ROS extension.

## Cartesian Trajectory Planning and Execution System(panda_moveit_cartesian_demo_nobag.cpp)

### Overview
This repository implements a robotic control system that enables a robot to follow planned Cartesian trajectories and provides utilities for generating, visualizing, and executing these trajectories in a 3D space using ROS2 and MoveIt!.

### Key Features:
The system includes functionalities such as:

1. Generate Cartesian Trajectories: Generates a series of waypoints representing the desired trajectory.
2. Visualize in RViz: The trajectories and waypoints can be visualized in RViz using spheres and trajectory lines.
3. Execute Trajectories: The planned trajectories can be executed by a robot with feedback available during execution.
4. Store and Replay Trajectories: Custom ROS bag utilities allow recording and playing back trajectories.

### Key Components

#### task_space_client_utils
This is the main node responsible for handling the robot's trajectory planning and execution. It creates an action client to send Cartesian trajectories to the robot for execution. The node also interacts with ROS2 parameters for configuring the planning group, feedback sampling period, and topics for publishing trajectories.

##### Key functions:
* task_space_goal_forwarding: Sends a task space trajectory to the action server and waits for a response.
* cartesian_path_generation: Generates a Cartesian path from a set of waypoints.
* plan_checking: Validates the planned trajectory to ensure it meets the tolerance requirements.


#### moveit_utils
Contains utility functions for:

* Drawing prompts and titles in RViz.
* Displaying planned trajectories and waypoints.
##### Key functions:

* draw_title: Displays a title in RViz for the current task (e.g., planning or executing).
* visualize_waypoints: Publishes a series of waypoints as colored spheres in RViz.
* display_planned_trajectory: Publishes and visualizes a planned trajectory.

#### bag_file_utils
Handles ROS bag file operations to save and load trajectory data. This allows for recording planned trajectories and playing them back later.

##### Key functions:
* create_bag_topics: Creates topics in the ROS bag file for recording trajectories.
* write_trajectory: Writes serialized trajectory data to the bag file.
* bag_file_path: Reads the stored trajectories from a ROS bag file.

##  panda_moveit_cartesian_demo_nobag.cpp
This demo initializes a ROS2 node that utilizes MoveIt! for planning and executing Cartesian trajectories for a robot, with real-time visualization in RViz. It generates dense waypoints in an oblique trajectory, visualizes them, and plans the motion using the MoveGroupInterface. The robot's current state is monitored, and once the trajectory is planned, the system prompts the user to execute it. The trajectory data is recorded in a ROS bag for playback or analysis. Throughout the process, collision objects can be managed, and the results are visualized in RViz for real-time feedback and control.


### Usage

In a first shell launch the `move_group` node and utility nodes, like RViz, from the `acg_resources_panda_moveit_config` package.
Make sure to select the appropriate RViz configuration:

```bash
ros2 launch acg_resources_panda_moveit_config gazebo_impedance_controller.launch.py     
```
In another shell run this package's planning demo:

```bash
ros2 launch panda_moveit_planning_demo panda_moveit_cartesian_demo.launch.py 
```

Use the **RVizVisualToolsGUI** to step through the demo.

## Cartesian Trajectory Planning and Execution System(panda_moveit_cartesian_demo.cpp)