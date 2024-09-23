"""
@file trajectory_node.py
@brief ROS 2 node for generating and writing straight line trajectories to a rosbag file.
"""

import rclpy
from rclpy.node import Node
from rclpy.clock import Clock
from rclpy.serialization import serialize_message
from geometry_msgs.msg import Pose, PoseArray
import rosbag2_py
import numpy as np
import os
import shutil
import time


class TrajectoryNode(Node):
    """
    @brief Constructor for the TrajectoryNode class.
    
    This class inherits from the Node class of ROS 2 and is responsible for the logic of the program.
    """
    
    def __init__(self, length, offset, gamma):
        """
        @brief Constructor method for the TrajectoryNode class.
        
        This method initializes the TrajectoryNode instance.
        It sets up parameters and generates and writes the trajectory.
        
        @param length The length of the straight line trajectory.
        @param offset The offset as x, y, z coordinates.
        @param gamma The rotation angles in radians as x, y, z.
        """
        super().__init__('trajectory_node')
        self.declare_parameter('length', length)
        self.declare_parameter('offset', offset)
        self.declare_parameter('gamma', gamma)
        
        self.generate_and_write_trajectory()

    def get_rotation_matrix(self, gamma):
        """
        @brief Method to get the rotation matrix for a given gamma angle.
        
        This method returns a 3x3 rotation matrix for a given gamma angle.
        
        @param gamma The rotation angles in radians as x, y, z.
        
        @return The rotation matrix.
        """
        rotation_matrix_x = np.array([
            [1, 0, 0],
            [0, np.cos(gamma[0]), -np.sin(gamma[0])],
            [0, np.sin(gamma[0]), np.cos(gamma[0])]
        ])

        rotation_matrix_y = np.array([
            [np.cos(gamma[1]), 0, np.sin(gamma[1])],
            [0, 1, 0],
            [-np.sin(gamma[1]), 0, np.cos(gamma[1])]
        ])

        rotation_matrix_z = np.array([
            [np.cos(gamma[2]), -np.sin(gamma[2]), 0],
            [np.sin(gamma[2]), np.cos(gamma[2]), 0],
            [0, 0, 1]
        ])

        return np.dot(rotation_matrix_x, np.dot(rotation_matrix_y, rotation_matrix_z))

    def generate_and_write_trajectory(self):
        """
        @brief Method to generate and write the trajectory to a rosbag file.
        
        This method retrieves node parameters, generates the trajectory, and writes it to a rosbag.
        """
        # Get parameters
        length = self.get_parameter('length').value
        offset = self.get_parameter('offset').value
        gamma = self.get_parameter('gamma').value
        
        # Calculate rotation matrix from gamma
        rotation_matrix = self.get_rotation_matrix(gamma)

        # Generate start and end points for the straight line trajectory
        start_point = np.array([0.0, 0.0, 0.0])  # start at origin
        end_point = np.array([0.0, 0.0, length])  # straight line along z-axis

        # Apply rotation and offset to start and end points
        start_point_rotated = np.dot(rotation_matrix, start_point) + offset
        end_point_rotated = np.dot(rotation_matrix, end_point) + offset

        # Generate a unique filename based on the current time
        time_stamp = Clock().now()
        filename = f'line_trajectory_{length}.bag'
        
        # Check if bag file exists and delete if present
        if os.path.isdir(filename):
            shutil.rmtree(filename)
            
        # Create PoseArray with only two waypoints (start and end)
        poses = PoseArray()

        # Create start pose
        start_pose = Pose()
        start_pose.position.x = start_point_rotated[0]
        start_pose.position.y = start_point_rotated[1]
        start_pose.position.z = start_point_rotated[2]
        start_pose.orientation.w = -0.000002
        start_pose.orientation.x = 0.923880
        start_pose.orientation.y = -0.382683
        start_pose.orientation.z = 0.000004
        poses.poses.append(start_pose)

        # Create end pose
        end_pose = Pose()
        end_pose.position.x = end_point_rotated[0]
        end_pose.position.y = end_point_rotated[1]
        end_pose.position.z = end_point_rotated[2]
        end_pose.orientation.w = -0.000002
        end_pose.orientation.x = 0.923880
        end_pose.orientation.y = -0.382683
        end_pose.orientation.z = 0.000004
        poses.poses.append(end_pose)

        # Setup ROS Bag
        writer = rosbag2_py.SequentialWriter()
        storage_options = rosbag2_py.StorageOptions(uri=filename, storage_id='sqlite3')
        converter_options = rosbag2_py.ConverterOptions('', '')
        writer.open(storage_options, converter_options)
        
        # Create a topic for PoseArray data
        topic_info = rosbag2_py.TopicMetadata(name='line_trajectory', type='geometry_msgs/msg/PoseArray', serialization_format='cdr')
        writer.create_topic(topic_info)
        
        # Write PoseArray data to the Bag file
        writer.write('line_trajectory', serialize_message(poses), time_stamp.nanoseconds)

def main(args=None):
    """
    @brief Main function and entry point for the program.
    """
    rclpy.init(args=args)
    length = float(input("Enter the length of the straight line trajectory: "))
    
    offset_input = input("Enter the offset as x,y,z: ").split(',')
    try:
        offset = [float(val) for val in offset_input]
        if len(offset) != 3:
            raise ValueError("Invalid input. Please enter exactly three numerical values separated by commas.")
    except (ValueError, IndexError):
        print("Invalid input. Please enter exactly three numerical values separated by commas.")
        rclpy.shutdown()
        return

    gamma_input = input("Enter the angle (in radians) as x,y,z: ").split(',')
    try:
        gamma = [float(val) for val in gamma_input]
        if len(gamma) != 3:
            raise ValueError("Invalid input. Please enter exactly three numerical values separated by commas.")
    except (ValueError, IndexError):
        print("Invalid input. Please enter exactly three numerical values separated by commas.")
        rclpy.shutdown()
        return

    trajectory_node = TrajectoryNode(length, offset, gamma)

    # Generate and write the trajectory, then destroy the node and shutdown rclpy
    trajectory_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
