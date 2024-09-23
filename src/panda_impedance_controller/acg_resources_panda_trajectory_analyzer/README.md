# acg_resources_panda_trajectory_analyzer
## Overview
The Trajectory Analyzer is a Python package designed to analyze the difference between a planned trajectory and an executed trajectory. The package computes the Mean Squared Error (MSE) for both positions and orientations from ROS2 bag files, and provides visualizations that help understand how well the executed trajectory follows the planned trajectory.

This package is particularly useful for robotics applications, where evaluating the precision of executed movements (both in terms of position and orientation) is essential.

## Features

- ROS2 bag file reading: Reads trajectory data from ROS2 bag files.
- MSE Calculation: Computes Mean Squared Error (MSE) for:
   Positions: MSE along the X, Y, and Z axes.
   Orientations: MSE of quaternion-based orientations.
- Visualization: Generates 3D trajectory plots and MSE bar charts for both positions and orientations.

## Installation
### Dependencies

Make sure the following dependencies are installed before using the package:

- ROS2 (for rosbag2_py and rclpy)
- Python 3.8+
- Python libraries:
- rosbag2_py
- rclpy
- matplotlib
- numpy
- scipy

## Usage
Once the package is installed, you can use it by running the trajectory analysis from the terminal. The package includes a main script (trajectory_analyzer.py) that takes two ROS2 bag files (planned and executed trajectories) as input, computes the MSE, and generates visual plots.
### Command-Line Interface (CLI)
The trajectory_analyzer CLI can be invoked with the following command:

No_obstacle: 

```bash
   ros2 run acg_resources_panda_trajectory_analyzer trajectory_analyzer /home/beniamino/ros2_ws/src/panda_impedance_controller/trajectories_executed/no_obstacle/planned_line_trajectory_2024_09_11_16_20_29.bag /home/beniamino/ros2_ws/src/panda_impedance_controller/trajectories_executed/no_obstacle/executed_line_trajectory_2024_09_11_16_20_28.bag  --planned_topic /planned_panda_feed --executed_topic /panda_feed

Obstacle: 

```bash
   ros2 run acg_resources_panda_trajectory_analyzer trajectory_analyzer /home/beniamino/ros2_ws/src/panda_impedance_controller/trajectories_executed/obstacle/planned_line_trajectory_2024_09_11_16_38_52.bag /home/beniamino/ros2_ws/src/panda_impedance_controller/trajectories_executed/obstacle/executed_line_trajectory_2024  --planned_topic /planned_panda_feed --executed_topic /panda_feed

```


### Parameters:

<planned_bagfile>: Path to the ROS2 bag file containing the planned trajectory.
<executed_bagfile>: Path to the ROS2 bag file containing the executed trajectory.
--planned_topic: The ROS2 topic name in the planned bag file that contains the planned trajectory data (default is /planned_point_to_point).
--executed_topic: The ROS2 topic name in the executed bag file that contains the executed trajectory data (default is /point_to_point

## Output
The package produces the following output:

- 3D Trajectory Plot: A 3D plot that visually compares the planned trajectory with the executed trajectory, helping you see any deviations in space.

- MSE Bar Charts: 
* Position Error: A bar chart showing the Mean Squared Error for the X, Y, and Z axes.
* Orientation Error: A bar chart showing the Mean Squared Error for the quaternion-based orientation.

## Understanding the MSE

* MSE for Position: Measures the average squared difference between the planned and executed positions along the X, Y, and Z axes.
* MSE for Orientation: Measures the average squared angular difference (in radians) between the planned and executed orientations, using quaternions.

## Functionality Breakdown

1. read_messages()
This function reads messages from a ROS2 bag file, allowing filtering by a specific topic. It deserializes the messages and yields them along with their timestamp.

2. extract_positions_and_orientations_from_messages()
This function extracts both position and orientation data from the ROS2 messages. It processes data from the geometry_msgs message format, returning positions as NumPy arrays and orientations as quaternion arrays.

3. calculate_mse_with_orientation()
This function computes the Mean Squared Error (MSE) for both:

Positions (X, Y, Z coordinates): Finds the nearest points between the planned and executed trajectories using a k-d tree and calculates the MSE for each axis.
Orientations: Compares quaternions representing the planned and executed orientations, calculates the rotational difference, and computes the MSE for the orientation.
4. plot_trajectories_with_separate_errors()
This function generates the graphical output:

3D Plot: Visualizes the planned vs executed trajectories in 3D.
MSE Bar Charts: Displays the MSE for positions (X, Y, Z) and a separate plot for orientation error.

## Limitations
The script assumes that both the planned and executed trajectories are sampled in a way that allows for meaningful comparisons (i.e., they cover similar time periods and resolutions).
