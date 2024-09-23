# Panda Impedance Controller

The **Panda Impedance Controller** is a ROS2-based impedance control implementation for the Franka Panda robotic arm. This controller is designed to handle complex interaction tasks by adjusting stiffness and damping gains based on the desired end-effector positions and orientations.

## Features

- Dynamic impedance control with real-time updates for stiffness and damping gains.
- Full integration with the MoveIt! framework for kinematic computations.
- Provides state and command interfaces for joint positions, velocities, and efforts.
- Supports gravity compensation and torque rate saturation to ensure smooth transitions.
- Action-based goal trajectory execution for  Cartesian movements.

## Key Files

- **`impedance_controller.hpp`**: Header file defining the impedance controller class and its key methods.
- **`impedance_controller.cpp`**: Implementation file for the controller, containing the logic for impedance control, trajectory execution, and interface configurations.

## Dependencies

This controller depends on the following ROS2 and external libraries:

- **`rclcpp`**: Core ROS2 library for node management and lifecycle operations.
- **`controller_interface`**: ROS2 package for writing custom hardware controllers.
- **`Eigen`**: For matrix and vector operations used in computing control efforts.
- **`kdl_parser`**: For parsing and loading kinematic models.
- **`pluginlib`**: To dynamically load the controller as a ROS2 plugin.

## Controller Lifecycle Phases

The Panda Impedance Controller follows the standard ROS2 controller lifecycle and includes several key phases:

### 1. Initialization (`on_init`)
During initialization, the controller validates and loads necessary parameters, such as:
- `robot_base_link`: The base link of the robot.
- `end_effector_link`: The end-effector link.
- `gains`: Stiffness and damping gains for control.

This phase uses the `check_parameters()` method to ensure that all required parameters are set in the ROS2 node. If any required parameter is not set, an error message is logged.

### 2. Configuration (`on_configure`)
During the configuration phase, the controller loads the robot's kinematic model using the **MoveIt!** framework. This process occurs in a separate thread to avoid blocking the main node. Joint limits are also set at this stage based on the robot's kinematic model.

### 3. Activation (`on_activate`)
Once activated, the controller reads the current state of the robot from the hardware interfaces and updates dynamic parameters such as stiffness, damping, and gravity compensation.

### 4. Update Cycle (`update`)
In the update cycle, the controller computes the joint efforts needed to maintain the desired end-effector position and orientation or to follow a trajectory. The method `compute_effort()` performs this calculation using a combination of position and orientation errors, stiffness and damping gains, and robot dynamics (gravity, inertia, and Coriolis forces).

## Dynamic Parameters

The controller listens for ROS2 parameter updates and dynamically adjusts stiffness and damping gains if changes are detected on the ROS parameter server. Gravity compensation can be enabled or disabled using the `gravity_compensation` parameter.

### Parameter Structure

Key parameters managed by the controller include:

- **`robot_base_link`**: The base link of the robot.
- **`end_effector_link`**: The end-effector link.
- **`gains.stiffness`**: Stiffness gains for the control in the `x`, `y`, `z`, `orientation_x`, `orientation_y`, and `orientation_z` directions.
- **`gains.damping`**: Damping gains for the same dimensions.
- **`gravity_compensation`**: Boolean flag to enable or disable gravity compensation.

## Interfaces

The impedance controller interacts with both command and state interfaces.

### Command Interfaces:
- **Effort**: Used to control the torque applied to each joint.

### State Interfaces:
- **Position**: Used to read the current joint positions.
- **Velocity**: Used to read the current joint velocities.

## Usage

### Launching the Controller

To launch the controller, add the following configuration to your `ros2_control` YAML file:

```yaml
controllers:
  panda_impedance_controller:
    type: "panda_impedance_controller/ImpedanceController"
    parameters:
      robot_base_link: "base_link"
      end_effector_link: "ee_link"
      joint_model_group_name: "arm"
      gains:
        stiffness:
          x: 100.0
          y: 100.0
          z: 100.0
        orientation_x: 50.0
        orientation_y: 50.0
        orientation_z: 50.0
      gravity_compensation: true
``` 

### Action Server

The impedance controller exposes an action server for following Cartesian trajectories. The action server runs under the name panda_impedance_controller/follow_cartesian_trajectory. You can send a goal containing desired waypoints to execute a trajectory. The action-based architecture allows for precise Cartesian movements and interaction control.

## Usage
If you want to test the controller run the following scripts: 

Shell 1:
```bash
ros2 launch acg_resources_panda_moveit_config gazebo_impedance_controller.launch.py 

```

This script will load the controller with no mock_hardware but the ignition Gazebo tool.
Once ignition Gazebo tool has started you can test the controller both with a single point and a more complex simulation, where the trajectory can be both a default one and a trajectory coming from a bag file. 

### Desired_positon example: 
Shell 2: 
```bash
ros2 action send_goal /panda_impedance_controller/follow_cartesian_trajectory cartesian_control_msgs/action/FollowCartesianTrajectory "{trajectory: {header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'}, points: [{time_from_start: {sec: 1, nanosec: 0}, point: {pose: {position: {x: 0.3, y: 0.3, z: 0.3}, orientation: {w: 1.0, x: 0.0, y: 0.0, z: 0.0}}}}]}}"
Waiting for an action server to become available...
Sending goal:
     trajectory:
  header:
    stamp:
      sec: 0
      nanosec: 0
    frame_id: base_link
  tracked_frame: ''
  points:
  - point:
      pose:
        position:
          x: 0.3
          y: 0.3
          z: 0.3
        orientation:
          x: 0.0
          y: 0.0
          z: 0.0
          w: 1.0
      velocity:
        linear:
          x: 0.0
          y: 0.0
          z: 0.0
        angular:
          x: 0.0
          y: 0.0
          z: 0.0
      acceleration:
        linear:
          x: 0.0
          y: 0.0
          z: 0.0
        angular:
          x: 0.0
          y: 0.0
          z: 0.0
    time_from_start:
      sec: 1
      nanosec: 0

Goal accepted with ID: 0156a692c685405bb044418596d1dfd1

```

### More complex simulations: 

#### Default trajectory
Shell 2: 
```bash
ros2 launch panda_moveit_planning_demo panda_moveit_cartesian_demo.launch.py 

```

#### Bag file trajectory

Shell 2: 
```bash
ros2 launch panda_moveit_planning_demo panda_moveit_cartesian_demo.launch.py bagfile_path_name:=/home/beniamino/ros2_ws/src/panda_impedance_controller/trajectories/line_trajectory_0.55.bag

```