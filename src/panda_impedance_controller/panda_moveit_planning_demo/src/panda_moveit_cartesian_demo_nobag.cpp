#include <thread>  // Include thread library for managing threading
#include <rclcpp/rclcpp.hpp>  // Include ROS 2 C++ API for node creation
#include <rclcpp_action/rclcpp_action.hpp>  // Include ROS 2 C++ API for action clients
#include <moveit/move_group_interface/move_group_interface.h>  // Include MoveIt! MoveGroup interface for planning and execution
#include <moveit_visual_tools/moveit_visual_tools.h>  // Include MoveIt! Visual Tools for RViz visualization
#include <moveit/planning_scene_interface/planning_scene_interface.h>  // Include planning scene interface to manage collision objects
#include <moveit/robot_state/conversions.h>  // Include conversions for robot states
#include <rosbag2_cpp/reader.hpp>  // Include ROS 2 bag reader for reading data from ROS bags
#include <geometry_msgs/msg/pose_array.hpp>  // Include PoseArray message type from geometry_msgs package
#include "moveit_utils.hpp"  // Include custom MoveIt! utilities
#include "cartesian_control_msgs/action/follow_cartesian_trajectory.hpp"  // Include FollowCartesianTrajectory action message
#include "moveit_msgs/msg/cartesian_trajectory_point.hpp"  // Include CartesianTrajectoryPoint message type
#include "task_space_client_utils.hpp"  // Include custom utilities for task space client
#include "bag_file_utils.hpp"  // Include custom utilities for handling bag files
#include <moveit_msgs/msg/constraints.hpp>  // Include Constraints message type for setting motion constraints


using FollowCartesianTrajectory = cartesian_control_msgs::action::FollowCartesianTrajectory;  // Alias for the FollowCartesianTrajectory action type
using namespace std::chrono_literals;  // Use literals from std::chrono for time durations

/**
 * @brief Executes a Cartesian trajectory using the action client.
 *
 * This function triggers the execution of a planned Cartesian trajectory by prompting the user for confirmation in RViz.
 *
 * @param moveit_visual_tools A reference to the MoveItVisualTools object used for visualization.
 * @param trajectory The Cartesian trajectory to execute.
 * @param node Shared pointer to the TaskSpaceClient node handling the trajectory execution.
 */
void execute_trajectory(moveit_visual_tools::MoveItVisualTools &moveit_visual_tools, const moveit_msgs::msg::CartesianTrajectory &trajectory, std::shared_ptr<task_space_client_utils::TaskSpaceClient> node) {
    prompt(moveit_visual_tools, "Press 'Next' in the RvizVisualToolsGui window to execute the planned trajectory");  // Display prompt in RViz to user
    draw_title(moveit_visual_tools, "Executing");  // Display the "Executing" title in RViz
    moveit_visual_tools.trigger();  // Trigger RViz to display the updated visual elements
    auto next = node->execute_trajectory(trajectory);  // Execute the Cartesian trajectory using the TaskSpaceClient node
    next.wait();  // Wait for the trajectory execution to complete
}

/**
 * @brief Generates a Cartesian trajectory with increased density and constrains the orientation of the end-effector.
 *
 * @param move_group_interface MoveGroup interface used to obtain the current pose of the robot.
 * @return std::vector<geometry_msgs::msg::Pose> A vector of poses representing the trajectory.
 */
std::vector<geometry_msgs::msg::Pose> generate_oblique_trajectory(moveit::planning_interface::MoveGroupInterface& move_group_interface) {
    std::vector<geometry_msgs::msg::Pose> waypoints;  // Initialize the pose vector for the trajectory

    // Force an update of the robot's current state to get the latest pose
    move_group_interface.startStateMonitor();
    rclcpp::sleep_for(1s); // Wait for a second to ensure the data is updated
    
    // Get the current pose of the robot
    geometry_msgs::msg::Pose current_pose = move_group_interface.getCurrentPose().pose;

    // Log the current pose for confirmation
    RCLCPP_INFO(rclcpp::get_logger("generate_oblique_trajectory"), "Current position: x: %f, y: %f, z: %f", 
                current_pose.position.x, current_pose.position.y, current_pose.position.z);
    
    // Save the robot's current (initial) orientation to use for all waypoints
    geometry_msgs::msg::Quaternion initial_orientation = current_pose.orientation;

    // Set the total trajectory length to 60 cm
    double total_distance = 0.60;

    // Ratio between movements along the x and y axes
    double ratio_x = 1.0;  // Movement along X will be 1 unit
    double ratio_y = 3.0;  // Movement along Y will be 3 times that of X

    // Calculate the individual displacements based on total length and ratio
    double delta_x = (total_distance * ratio_x) / sqrt(pow(ratio_x, 2) + pow(ratio_y, 2));
    double delta_y = (total_distance * ratio_y) / sqrt(pow(ratio_x, 2) + pow(ratio_y, 2));

    // Add the initial pose to the waypoints
    waypoints.push_back(current_pose);  // First waypoint (initial position)

    // Calculate the final position
    geometry_msgs::msg::Pose final_pose = current_pose;
    final_pose.position.x += delta_x;  // Move along the X axis
    final_pose.position.y += delta_y;  // Move along the Y axis

    // Keep the same initial orientation for the final waypoint
    final_pose.orientation = initial_orientation;

    // Add the final pose to the waypoints
    waypoints.push_back(final_pose);  // Second waypoint (final position)

    // Log the target pose for confirmation
    RCLCPP_INFO(rclcpp::get_logger("generate_oblique_trajectory"), "Target position: x: %f, y: %f, z: %f", 
                waypoints.back().position.x, waypoints.back().position.y, waypoints.back().position.z);

    return waypoints;  // Return the vector of waypoints
}


/**
 * @brief Visualizes the waypoints in RViz as colored spheres.
 *
 * @param moveit_visual_tools MoveItVisualTools object for visualizing the waypoints.
 * @param waypoints The waypoints to visualize.
 */
void visualize_waypoints(moveit_visual_tools::MoveItVisualTools &moveit_visual_tools, const std::vector<geometry_msgs::msg::Pose> &waypoints) {
    for (const auto &waypoint : waypoints) {
        moveit_visual_tools.publishSphere(waypoint, rviz_visual_tools::GREEN, rviz_visual_tools::LARGE);  // Publish each waypoint as a green sphere in RViz
    }
    moveit_visual_tools.trigger();  // Update RViz visualization
}

/**
 * @brief Main function for executing robot trajectory planning and execution.
 *
 * This function initializes the ROS2 node, sets up the MoveIt! environment, reads trajectory data from a bag file, and executes the planned trajectories.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Program exit status.
 */
int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);  // Initialize ROS 2

    auto planning_node = std::make_shared<task_space_client_utils::TaskSpaceClient>("task_space_client_utils");  // Create a shared pointer to the TaskSpaceClient node
    
    auto const logger = planning_node->get_logger();  // Get the logger for logging messages
    
    rclcpp::executors::SingleThreadedExecutor executor;  // Create a single-threaded executor
    executor.add_node(planning_node);  // Add the planning node to the executor
    auto spinner = std::thread([&executor]() {  // Start a new thread for spinning the executor
        executor.spin();  // Spin the executor to handle incoming messages
        rclcpp::shutdown();  // Shutdown ROS 2 after spinning
    });

    std::string base_frame = planning_node->get_parameter("base_frame").as_string(); 
    std::string planning_group = planning_node->get_parameter("planning_group").as_string();  // Get the planning group parameter
    // Create a MoveGroupInterface instance using the planning group obtained from the node's parameter
    moveit::planning_interface::MoveGroupInterface move_group_interface (planning_node, planning_group);

    // Create a MoveItVisualTools object
    moveit_visual_tools::MoveItVisualTools moveit_visual_tools(planning_node, base_frame, rviz_visual_tools::RVIZ_MARKER_TOPIC, move_group_interface.getRobotModel());
    moveit_visual_tools.loadRemoteControl();  // Load remote control for MoveItVisualTools
    std::string end_effector_link_name = move_group_interface.getEndEffectorLink();  // Get the end effector link name
    RCLCPP_INFO(logger, "End effector name: %s", end_effector_link_name.c_str());  // Log the end effector link name
    moveit::planning_interface::MoveGroupInterface::Plan plan;  // Declare a plan object for storing the planned trajectory
    auto robot_state = moveit::core::RobotState(move_group_interface.getRobotModel());  // Create a robot state object
    moveit::core::MoveItErrorCode success;  // Declare a variable for storing the success status of planning

    std::vector<std::string> topics = {
        planning_node->get_parameter("planned_trajectories_topic.cartesian").as_string()
    };

    std::string base_filename = planning_node->get_parameter("planned_trajectory_file").as_string();  // Get the planned trajectory file parameter
    auto bag_file_handler = std::make_shared<bag_file_utils::BagFileHandler>(base_filename);  // Create a bag file handler for reading/writing bag files

    bag_file_handler->create_bag_topics(topics, "moveit_msgs/msg/CartesianTrajectory");  // Create bag topics for storing trajectories
    // Set the parameter for recording the plan using the cartesian_topic
    planning_node->set_parameter(rclcpp::Parameter("writer_topic", planning_node->get_parameter("executed_trajectories_topic.cartesian_topic").as_string()));
    moveit_visual_tools.deleteAllMarkers();  // Delete all markers in RViz
    moveit_visual_tools.prompt("Press 'Next' in the RvizVisualToolsGui window to plan a Cartesian path");  // Prompt the user in RViz to plan a Cartesian path
    draw_title(moveit_visual_tools, "Planning cartesian path");  // Draw "Planning cartesian path" title in RViz

    auto waypoints = generate_oblique_trajectory(move_group_interface);  // Generate oblique trajectory with waypoints

    // Visualize waypoints in RViz
    visualize_waypoints(moveit_visual_tools, waypoints);

    if (waypoints.empty() || waypoints.size() <= 1) {
        RCLCPP_ERROR(logger, "Generated waypoints are insufficient. Only %zu waypoints generated. Aborting...", waypoints.size());  // Log an error if there are insufficient waypoints
        rclcpp::shutdown();  // Shutdown ROS 2
        spinner.join();  // Join the spinner threads
        return 1;  // Return with error status
    }

    auto [fraction, cartesian_plan] = planning_node->cartesian_path_generation(waypoints, &logger, &move_group_interface);  // Generate a Cartesian path
    success = fraction == 1.0;  // Check if the fraction of the planned path is 1.0 (complete path planned)
    display_planned_trajectory(moveit_visual_tools, move_group_interface, planning_group, cartesian_plan.trajectory_);  // Display the planned Cartesian trajectory in RViz
    if (!success) {
        RCLCPP_ERROR(logger, "Planning failed. Aborting...");  // Log an error if planning fails
        draw_title(moveit_visual_tools, "Planning Failed!");  // Draw "Planning Failed!" title in RViz
        rclcpp::shutdown();  // Shutdown ROS 2
        return 1;  // Return with error status
    }

    // Execute the Cartesian path
    moveit_msgs::msg::CartesianTrajectory planned_trajectory; 
    planned_trajectory = planning_node->get_task_space_trajectory(cartesian_plan.trajectory_, robot_state, &logger, end_effector_link_name, base_frame, planning_group);  // Generate a task space trajectory    

    // Write each waypoint of the planned_trajectory as a separate message to the bag file
    for (const auto& waypoint : planned_trajectory.points) {
        auto serialized_trajectory = std::make_shared<rclcpp::SerializedMessage>();  // Create a shared pointer to a serialized message
        moveit_msgs::msg::CartesianTrajectory single_waypoint_trajectory;  // Declare a CartesianTrajectory message to store a single waypoint
        single_waypoint_trajectory.header = planned_trajectory.header;  // Set the header of the single waypoint trajectory
        single_waypoint_trajectory.points.push_back(waypoint);  // Add the waypoint to the single waypoint trajectory
        rclcpp::Serialization<moveit_msgs::msg::CartesianTrajectory> trajectory_serialization;  // Declare a serialization object for CartesianTrajectory
        trajectory_serialization.serialize_message(&single_waypoint_trajectory, serialized_trajectory.get());  // Serialize the single waypoint trajectory
        bag_file_handler->write_trajectory(
            *serialized_trajectory,  // Write the serialized trajectory to the bag file
            planning_node->get_parameter("planned_trajectories_topic.cartesian").as_string(),
            "moveit_msgs/msg/CartesianTrajectory",
            planning_node->now());
    }

    // Log the robot's current orientation before execution
    geometry_msgs::msg::Pose current_pose = move_group_interface.getCurrentPose().pose;
    RCLCPP_INFO(logger, "Robot current orientation before execution: x: %f, y: %f, z: %f, w: %f", 
                current_pose.orientation.x, current_pose.orientation.y, current_pose.orientation.z, current_pose.orientation.w);

    // Log the orientation of the first waypoint in the planned trajectory
    if (!cartesian_plan.trajectory_.joint_trajectory.points.empty()) {
        const auto& first_point = cartesian_plan.trajectory_.joint_trajectory.points.front();
        RCLCPP_INFO(logger, "First waypoint orientation: x: %f, y: %f, z: %f, w: %f", 
                    first_point.positions[0], first_point.positions[1], first_point.positions[2], first_point.positions[3]);
    }

    // Execute the planned trajectory
    execute_trajectory(moveit_visual_tools, planned_trajectory, planning_node);

    moveit_visual_tools.deleteAllMarkers();  // Delete all markers in RViz

    rclcpp::shutdown();  // Shutdown ROS 2

    spinner.join();  // Join the spinner thread

    return 0;  // Return with success status
}
