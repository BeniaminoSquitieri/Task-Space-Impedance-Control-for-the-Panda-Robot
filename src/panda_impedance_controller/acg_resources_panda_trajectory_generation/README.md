# acg_resources_panda_trajectory_generation

## Overview

This project contains a ROS 2 node, trajectory_node.py, designed to generate a straight line trajectory and write the resulting poses to a rosbag file. The generated trajectory can be customized by specifying parameters such as the length of the line, the offset in 3D space, and the rotation angles (gamma) applied to the trajectory.


## Features

- **Trajectory Generation**: Generates a straight line trajectory based on user-defined parameters.
- **Rosbag Writing**: Writes the generated trajectory to a rosbag file for later analysis or playback.
- **Parameterization**: The trajectory can be customized bsy specifying its length, offset, and rotation angles.
- **Input Validation**: Comprehensive input validation mechanisms are integrated into the node to ensure that user-provided parameters fall within acceptable ranges, enhancing robustness and reliability.

## Prerequisites

- **ROS 2**: Ensure that you have ROS 2 installed and sourced in your environment.
- **Python Libraries**: The following Python libraries are required: rclpy, geometry_msgs , rosbag2_py , numpy

## Parameters
The node allows customization of the trajectory through the following parameters:
- `length` (float): The length of the straight line trajectory.
- `offset`(list of float): The offset applied to the trajectory in the x, y, z directions.
- `gamma` (list of float): The rotation angles (in radians) applied to the trajectory around the x, y, z axes.



### Position
- increase x takes the trajectory to the opposite direction of the robot 
- increase y takes the trajectory to the left direction of the robot(from the point of view of user in rviz)
- increase z takes the trajectory to an upper position from the ground
### Orientation(radians)
- increase x makes the trajectory rotate with respect to the x axis of the `world`link. 
- increase y makes the trajectory rotate with respect to the y axis of the `world`link. 
- increase z makes the trajectory rotate with respect to the z axis of the `world`link. 

## Usage

To run the node, execute the following command after sourcing your ROS 2 environment:
 
```bash
 ros2 run acg_resources_panda_trajectory_generation data_generator_executable 
```

## User Input
When running the node, you will be prompted to provide the following parameters:

1. Length: Enter the length of the straight line trajectory.
2. Offset: Enter the offset as comma-separated x, y, z coordinates (e.g., 1.0,0.5,0.0).
3. Gamma Angles: Enter the rotation angles in radians as comma-separated x, y, z values (e.g., 0.0,0.0,1.5708).


### Example

```bash
 Enter the length of the straight line trajectory: 2.0
 Enter the offset as x,y,z: 1.0,0.0,0.0
 Enter the angle (in radians) as x,y,z: 0.0,0.0,1.5708
```
## Output
The node outputs a rosbag file containing a PoseArray topic with the sequence of poses representing the generated straight line trajectory.

## Rosbag
The rosbag file is named based on the trajectory length (e.g., line_trajectory_2.0.bag) and can be used for playback and analysis of the trajectory.

