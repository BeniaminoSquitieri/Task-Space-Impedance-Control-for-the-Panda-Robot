# Task Space Impedance Control for the Panda Robot

## Project Overview

This project focuses on implementing **task space impedance control** for the Panda robot using the **ROS2/Ignition software stack**. Impedance control is a critical technique for ensuring safe and effective interactions between robots and their environments, which may include static objects, dynamic elements, or even humans.

The main objectives of the project are:
1. Implementing the impedance control algorithm using ROS2 control framework.
2. Designing a simulation scenario to demonstrate the controller's effectiveness in both free-space and obstacle-rich environments.
3. Planning interaction trajectories using **MoveIt!2**, focusing on a straight-line path within the robot’s workspace.
4. Validating the performance of the impedance controller through simulated testing.
5. Assessing the position tracking during interaction via Python plots.

This project aims to deliver a flexible and robust control solution for dynamic robotic environments.

## Key Concepts and Features

### 1. **Impedance Control**
   Impedance control allows the robot to manage interaction forces by simulating a virtual **mass-spring-damper** system (in this case, without the damper). This ensures smooth, compliant behavior during physical interactions.

   - **Effort-based control**: The robot's joints are controlled using torques (efforts) that account for external forces, ensuring dynamic response during contact.
   - **Impedance control structure**: Uses spring stiffness (K) to define the compliance in task space directions (X, Y, Z). 
   - **Dynamic Model Compensation**: Incorporates the robot's Coriolis forces and gravity compensation to manage complex dynamic behaviors.

### 2. **Action Server Integration**
   - The controller uses ROS2's action server to handle trajectory following in task space.
   - The action server receives goal trajectories (e.g., Cartesian paths for the robot’s end-effector) and manages the feedback to ensure accurate tracking.

### 3. **Stiffness and Damping Tuning**
   - **Stiffness**: Controls how rigidly the robot follows its desired trajectory in the X, Y, and Z axes.
   - **Damping**: Adjusts the robot’s velocity response to ensure smooth and stable movements.
   - Both parameters can be dynamically adjusted via YAML configuration files.

### 4. **Trajectory Handling**
   - The impedance controller can operate in static impedance control (holding a position) or dynamic trajectory following mode.
   - When a trajectory is provided, the controller computes joint torques to follow it while maintaining compliance with external forces.

## Simulation and Scenario Setup

### 1. **Simulation Scenario**
   - A Cartesian trajectory is generated for the Panda robot using **MoveIt!**, and the trajectory is visualized in **RViz**.
   - The task space client node sends this trajectory to the impedance controller, which manages its execution using ROS2 actions.
   - The performance of the robot's trajectory execution is recorded and analyzed.

### 2. **Bag File Utility**
   - A ROS2 bag file handler is implemented to log planned and executed trajectories. These files are useful for later trajectory comparison and analysis.

## Trajectory Analyzer

The trajectory analyzer is a Python tool developed to compare planned and executed trajectories. It uses data from the ROS2 bag files to calculate errors between the two paths.

### Features:
- **Error Calculation**: Calculates the **Mean Squared Error (MSE)** between planned and executed trajectories.
- **Visualization**: Plots the planned and executed trajectories and provides bar charts displaying positional and orientation errors.

## Results

### Performance
- The robot successfully followed the planned trajectory in free space. However, in obstacle-rich environments (like walls in the simulation), the robot’s movement deviated from the planned path, accumulating error on the affected axes.
- **Mean Squared Error (MSE)** was used to quantify the difference between planned and executed trajectories. While the errors were not significant in free space, obstacles increased both positional and orientational errors.

### Issues and Limitations
- **Trajectory starting position**: The trajectory starts from the robot's current position, which may exceed the robot’s workspace.
- **Controller performance variability**: Different hardware setups produced varying initial conditions during simulation, affecting performance consistency.
- **Parameter tuning**: The parameters tuned during dynamic configuration did not always stabilize the robot effectively when saved for future runs.

## Improvements

To address some of the limitations:
1. **Flexible Trajectory Generation**: A package was developed to allow users to define trajectories dynamically rather than hardcoding them. This package generates straight-line trajectories that can be fed into the simulation as a ROS2 bag file.
2. **Enhanced Simulation**: The system was extended to perform point-to-point simulations before executing the full trajectory, adding a level of control and visualization using RViz.

For any inquiries, please contact:

- Beniamino Squitieri - b.squitieri@studenti.unisa.it

