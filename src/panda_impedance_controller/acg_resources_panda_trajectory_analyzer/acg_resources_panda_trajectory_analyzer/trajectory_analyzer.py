import rosbag2_py as rosbag  # Import ROS2 Python API for handling ROS bag files.
import matplotlib.pyplot as plt  # Import Matplotlib for plotting.
import argparse  # Import for parsing command line arguments.
from rclpy.serialization import deserialize_message  # Import for deserializing ROS2 messages.
from rosidl_runtime_py.utilities import get_message  # Import utility for getting ROS message types.
import rclpy  # Import ROS2 Python client library.
import numpy as np  # Import NumPy for numerical operations.
from scipy.spatial.transform import Rotation as R  # Import SciPy's Rotation module for handling 3D rotations.
from scipy.spatial import cKDTree  # Import cKDTree from SciPy for efficient spatial searches.

def read_messages(input_bag: str, topic_filter: str = None):
    """
    @brief Reads messages from a ROS2 bag file and filters them by a specific topic.
    
    @param input_bag The path to the ROS2 bag file.
    @param topic_filter The topic to filter messages by (default is None, which means no filtering).
    @return Yields tuples of (topic, deserialized message, timestamp) for each message in the bag file.
    """
    reader = rosbag.SequentialReader()  # Create a SequentialReader object to read messages from the bag file.
    reader.open(
        rosbag.StorageOptions(uri=input_bag, storage_id="sqlite3"),  # Specify the bag file storage options (using sqlite3).
        rosbag.ConverterOptions(
            input_serialization_format="cdr", output_serialization_format="cdr"  # Specify serialization format as CDR.
        ),
    )

    topic_types = reader.get_all_topics_and_types()  # Retrieve all topics and their types from the bag file.

    print("Available topics in bag file:")  # Print the available topics in the bag file for user reference.
    for topic_type in topic_types:
        print(f" - {topic_type.name} ({topic_type.type})")  # Display each topic's name and type.

    def type_help(topic_name):
        """
        @brief Helper function to find the type of a given topic.
        
        @param topic_name The name of the topic.
        @return The type of the topic if found; raises a ValueError otherwise.
        """
        for topic_type in topic_types:
            if topic_type.name == topic_name:
                if not topic_type.type:
                    print(f"Skipping topic {topic_name} due to missing type.")  # Skip topics with missing type information.
                    return None
                return topic_type.type  # Return the topic type if found.
        raise ValueError(f"Topic {topic_name} not in bag")  # Raise an error if the topic is not found.

    while reader.has_next():
        topic, data, timestamp = reader.read_next()  # Read the next message from the bag file.
        if topic_filter and topic != topic_filter:
            continue  # Skip messages not matching the topic filter.
        try:
            message_type = type_help(topic)  # Get the message type for the current topic.
            if message_type is None:
                continue  # Skip messages with unknown types.
            message_deserialized = deserialize_message(data, get_message(message_type))  # Deserialize the message data.
            yield topic, message_deserialized, timestamp  # Yield the topic, deserialized message, and timestamp.
        except Exception as e:
            print(f"Failed to process topic {topic}: {e}")  # Print an error message if deserialization fails.
            raise

    del reader  # Delete the reader object to free up resources.

def extract_positions_and_orientations_from_messages(messages):
    """
    @brief Extracts position and orientation data from a list of messages.
    
    @param messages A list of deserialized ROS messages.
    @return Two arrays: one for positions and one for orientations (quaternions) extracted from the messages.
    """
    positions = []  # Initialize an empty list to store positions.
    orientations = []  # Initialize an empty list to store orientations.
    for message in messages:
        if hasattr(message, 'points'):  # Check if the message has 'points' attribute (for planned trajectories).
            for point in message.points:
                positions.append([
                    point.point.pose.position.x,
                    point.point.pose.position.y,
                    point.point.pose.position.z
                ])  # Append the position data to the list.
                orientations.append([
                    point.point.pose.orientation.x,
                    point.point.pose.orientation.y,
                    point.point.pose.orientation.z,
                    point.point.pose.orientation.w
                ])  # Append the orientation data (as quaternion) to the list.
        elif hasattr(message, 'feedback'):  # Check if the message has 'feedback' attribute (for executed trajectories).
            positions.append([
                message.feedback.actual.point.pose.position.x,
                message.feedback.actual.point.pose.position.y,
                message.feedback.actual.point.pose.position.z
            ])  # Append the position data to the list.
            orientations.append([
                message.feedback.actual.point.pose.orientation.x,
                message.feedback.actual.point.pose.orientation.y,
                message.feedback.actual.point.pose.orientation.z,
                message.feedback.actual.point.pose.orientation.w
            ])  # Append the orientation data (as quaternion) to the list.
    return np.array(positions), np.array(orientations)  # Return positions and orientations as NumPy arrays.

def calculate_mse_with_orientation(planned_coords, executed_coords, planned_orientations, executed_orientations):
    """
    @brief Calculates the Mean Squared Error (MSE) between the planned and executed trajectories and orientations.
    
    @param planned_coords The coordinates of the planned trajectory.
    @param executed_coords The coordinates of the executed trajectory.
    @param planned_orientations The orientations of the planned trajectory (as quaternions).
    @param executed_orientations The orientations of the executed trajectory (as quaternions).
    @return Two lists: One for MSE of each coordinate axis (X, Y, Z) and another for orientation error.
    """
    # Calculate MSE for positions
    tree = cKDTree(planned_coords)  # Create a k-d tree for the planned coordinates for efficient nearest-neighbor search.
    distances, indices = tree.query(executed_coords)  # Find the closest points in the planned trajectory for each executed point.

    matched_planned_coords = planned_coords[indices]  # Get the closest points from the planned trajectory.

    mse_x = np.mean((matched_planned_coords[:, 0] - executed_coords[:, 0]) ** 2)  # MSE for X
    mse_y = np.mean((matched_planned_coords[:, 1] - executed_coords[:, 1]) ** 2)  # MSE for Y
    mse_z = np.mean((matched_planned_coords[:, 2] - executed_coords[:, 2]) ** 2)  # MSE for Z

    # Calculate MSE for orientations (quaternions)
    matched_planned_orientations = planned_orientations[indices]  # Get the closest orientations from the planned trajectory.

    # Use the rotation difference to calculate the orientation error
    planned_rotations = R.from_quat(matched_planned_orientations)
    executed_rotations = R.from_quat(executed_orientations)
    relative_rotations = executed_rotations.inv() * planned_rotations  # Calculate relative rotation
    orientation_errors = relative_rotations.magnitude()  # Compute the angle of rotation differences

    mse_orientation = np.mean(orientation_errors ** 2)  # MSE for orientation

    return [mse_x, mse_y, mse_z], mse_orientation  # Return MSE for positions and orientation

def plot_trajectories_with_separate_errors(planned_coords, executed_coords, mse_positions, mse_orientation):
    """
    @brief Plots the planned and executed trajectories, and displays the MSE for positions and orientations in the same figure using subplots.
    
    @param planned_coords The coordinates of the planned trajectory.
    @param executed_coords The coordinates of the executed trajectory.
    @param mse_positions The Mean Squared Error values for each coordinate axis (X, Y, Z).
    @param mse_orientation The Mean Squared Error for orientation.
    """
    # Create a figure with two subplots: one for trajectories and positions, and one for orientation
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))  # Create two subplots in a single figure

    # Plot planned vs executed trajectories in 3D
    ax1 = fig.add_subplot(121, projection='3d')  # Add a 3D subplot for trajectory visualization.
    ax1.plot(planned_coords[:, 0], planned_coords[:, 1], planned_coords[:, 2], label='Planned Trajectory', color='blue')  # Plot planned trajectory.
    ax1.plot(executed_coords[:, 0], executed_coords[:, 1], executed_coords[:, 2], label='Executed Trajectory', color='orange')  # Plot executed trajectory.
    ax1.set_xlabel('X')  # Set X-axis label.
    ax1.set_ylabel('Y')  # Set Y-axis label.
    ax1.set_zlabel('Z')  # Set Z-axis label.
    ax1.set_title('Planned vs Executed Trajectories')  # Set plot title.
    ax1.legend()  # Show legend.

    # Plot MSE for positions (X, Y, Z)
    ax2 = fig.add_subplot(122)  # Add a subplot for the MSE bar plot for positions.
    ax2.bar(['X', 'Y', 'Z'], mse_positions, color=['red', 'green', 'blue'])  # Create a bar plot for MSE (positions).
    ax2.set_title('Mean Squared Error (Positions)')  # Set plot title.
    ax2.set_xlabel('Dimension')  # Set X-axis label.
    ax2.set_ylabel('MSE')  # Set Y-axis label.

    # Set y-axis limits based on the maximum MSE value
    ymin = 0  # Start from 0
    ymax = max(mse_positions)  # Set the maximum limit as the highest MSE value
    ax2.set_ylim([ymin, ymax])

    plt.tight_layout()  # Adjust subplot parameters for better fit.
    
    # Create a new figure for the MSE for orientation
    fig, ax3 = plt.subplots(figsize=(6, 4))  # Create a new figure for orientation MSE
    ax3.bar(['Orientation'], [mse_orientation], color='purple')  # Create a bar plot for MSE (orientation).
    ax3.set_title('Mean Squared Error (Orientation)')  # Set plot title.
    ax3.set_xlabel('Orientation')  # Set X-axis label.
    ax3.set_ylabel('MSE')  # Set Y-axis label.

    # Set y-axis limits based on the orientation MSE
    ymax_orientation = mse_orientation  # Set the maximum limit as the MSE orientation value
    ax3.set_ylim([ymin, ymax_orientation])

    # Set the number of y-ticks to ensure readability
    ax3.yaxis.set_major_locator(plt.MaxNLocator(5))  # Limit the number of major ticks to 5

    plt.tight_layout()  # Adjust subplot parameters for better fit.
    plt.show()  # Display both plots at once.



def main():
    """
    @brief The main function that executes the program.
    
    Initializes ROS2, parses command-line arguments, reads the trajectories from the bag files, calculates MSE, and plots the trajectories.
    """
    rclpy.init()  # Initialize ROS2 communication.
    node = rclpy.create_node('trajectory_analyzer')  # Create a ROS2 node named 'trajectory_analyzer'.
    logger = node.get_logger()  # Create a logger for the node.
    logger.info('Starting trajectory analyzer')  # Log the start of the analysis.

    parser = argparse.ArgumentParser(description='Plot trajectories from two bag files.')  # Create an argument parser for command-line input.
    parser.add_argument('PlannedBagFile', metavar='planned_bagfile', type=str, help='The bag file that contains the planned trajectory')  # Define the planned bag file argument.
    parser.add_argument('ExecutedBagFile', metavar='executed_bagfile', type=str, help='The bag file that contains the executed trajectory')  # Define the executed bag file argument.
    parser.add_argument('--planned_topic', type=str, default='/planned_point_to_point', help='The topic of the planned trajectory')  # Define the planned topic argument.
    parser.add_argument('--executed_topic', type=str, default='/point_to_point', help='The topic of the executed trajectory')  # Define the executed topic argument.

    args = parser.parse_args()  # Parse command-line arguments.

    planned_bag_file = args.PlannedBagFile  # Get the planned bag file path.
    executed_bag_file = args.ExecutedBagFile  # Get the executed bag file path.
    planned_topic = args.planned_topic  # Get the planned trajectory topic.
    executed_topic = args.executed_topic  # Get the executed trajectory topic.

    planned_trajectory = []  # Initialize an empty list for the planned trajectory messages.
    executed_trajectory = []  # Initialize an empty list for the executed trajectory messages.

    # Read messages from the planned bag file
    for topic, message_deserialized, timestamp in read_messages(planned_bag_file, planned_topic):
        planned_trajectory.append(message_deserialized)  # Append each message to the planned trajectory list.

    # Read messages from the executed bag file
    for topic, message_deserialized, timestamp in read_messages(executed_bag_file, executed_topic):
        executed_trajectory.append(message_deserialized)  # Append each message to the executed trajectory list.

    logger.info('Trajectories read')  # Log that trajectories have been read.

    # Ensure both planned and executed trajectories are valid
    if planned_trajectory and executed_trajectory:
        planned_coords, planned_orientations = extract_positions_and_orientations_from_messages(planned_trajectory)  # Extract positions and orientations from planned trajectory messages.
        executed_coords, executed_orientations = extract_positions_and_orientations_from_messages(executed_trajectory)  # Extract positions and orientations from executed trajectory messages.

        # Calculate MSE for positions and orientation
        mse_positions, mse_orientation = calculate_mse_with_orientation(planned_coords, executed_coords, planned_orientations, executed_orientations)  # Calculate MSE between planned and executed trajectories.

        # logger.info(f"MSE - X: {mse_positions[0]}, Y: {mse_positions[1]}, Z: {mse_positions[2]}, Orientation: {mse_orientation}")  # Log the calculated MSE values.

        # Plot the trajectories and MSE separately for positions and orientation
        plot_trajectories_with_separate_errors(planned_coords, executed_coords, mse_positions, mse_orientation)  # Plot the trajectories and MSE separately.
    else:
        if not planned_trajectory:
            logger.error('No planned trajectory data available.')  # Log error if planned trajectory data is missing.
        if not executed_trajectory:
            logger.error('No executed trajectory data available.')  # Log error if executed trajectory data is missing.

if __name__ == "__main__":
    main()  # Run the main function if the script is executed directly.
