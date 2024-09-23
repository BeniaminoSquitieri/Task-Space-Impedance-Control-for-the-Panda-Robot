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

using FollowCartesianTrajectory = cartesian_control_msgs::action::FollowCartesianTrajectory;  // Define alias for the FollowCartesianTrajectory action type
using namespace std::chrono_literals;  // Use literals from std::chrono for time duration

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
    draw_title(moveit_visual_tools, "Executing");  // Draw the "Executing" title in RViz
    moveit_visual_tools.trigger();  // Trigger RViz to display the updated visual elements
    auto next = node->execute_trajectory(trajectory);  // Execute the Cartesian trajectory using the TaskSpaceClient node
    next.wait();  // Wait for the trajectory execution to complete
}

/**
 * @brief Generates waypoints while maintaining the current robot orientation.
 *
 * This function generates waypoints for a Cartesian path from a PoseArray but uses the current robot orientation to avoid planning extra orientation corrections.
 *
 * @param cartesian_path_poses A shared pointer to a PoseArray containing the desired path positions.
 * @param move_group_interface Pointer to the MoveGroupInterface instance for obtaining the current robot state.
 * @return A vector of geometry_msgs::msg::Pose with the generated waypoints and the current robot orientation.
 */
const std::vector<geometry_msgs::msg::Pose> generate_waypoints(
    const std::shared_ptr<geometry_msgs::msg::PoseArray> cartesian_path_poses,
    moveit::planning_interface::MoveGroupInterface* move_group_interface,
    const rclcpp::Logger &logger) {

    std::vector<geometry_msgs::msg::Pose> waypoints;  // Initialize a vector to store the waypoints

    auto current_state = move_group_interface->getCurrentState();  // Get the current state of the robot

    // Obtain the current orientation of the end-effector
    Eigen::Matrix3d current_rotation = current_state->getGlobalLinkTransform(
        move_group_interface->getEndEffectorLink()).rotation();

    Eigen::Quaterniond current_orientation(current_rotation);  // Convert rotation matrix to quaternion

    // Loop over the received poses and set their orientation to match the current robot orientation
    for (const auto& pose_msg : cartesian_path_poses->poses) {
        geometry_msgs::msg::Pose pose = pose_msg;  // Copy pose data from PoseArray
        pose.orientation = tf2::toMsg(current_orientation);  // Override the orientation with the current robot orientation
        waypoints.push_back(pose);  // Add the modified pose to the waypoints vector
    }

    // Log the number of waypoints generated
    RCLCPP_INFO(logger, "Number of waypoints generated: %zu", waypoints.size());

    return waypoints;  // Return the updated waypoints
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

    // Check if sufficient arguments are provided
    if (argc < 2) {
        RCLCPP_ERROR(logger, "Insufficient number of arguments. Requested 2 arguments but %d were given", argc);  // Log an error if arguments are insufficient
        return 1;  // Return with error status
    }

    const std::string bag_filename = argv[1];  // Get the bag filename from command-line arguments
    RCLCPP_INFO(logger, "Reading path from bagfile: %s", bag_filename.c_str());  // Log the bag file path

    // Fetch parameters from node
    std::string bag_topic = planning_node->get_parameter("input_bag_file_topic").as_string();  // Get the input bag file topic parameter
    std::string base_filename = planning_node->get_parameter("planned_trajectory_file").as_string();  // Get the planned trajectory file parameter

    auto bag_file_handler = std::make_shared<bag_file_utils::BagFileHandler>(base_filename);  // Create a bag file handler for reading/writing bag files
    auto cartesian_path_poses = bag_file_handler->bag_file_path(logger, bag_filename, bag_topic);  // Read the Cartesian path poses from the bag file

    // Check that the file contains at least one pose
    if (cartesian_path_poses->poses.size() < 1) {
        RCLCPP_ERROR(logger, "The bag file does not contain a valid trajectory or is empty. Aborting...");  // Log error if no valid trajectory is found
        rclcpp::shutdown();  // Shutdown ROS 2
        return 1;  // Return with error status
    }
    RCLCPP_INFO(logger, "Number of waypoints read from bagfile: %zu", cartesian_path_poses->poses.size());


    std::string base_frame = planning_node->get_parameter("base_frame").as_string();  // Get the base frame parameter
    geometry_msgs::msg::PoseStamped cartesian_path_first_pose;  // Create a PoseStamped message for the first pose in the Cartesian path
    cartesian_path_first_pose.pose = cartesian_path_poses->poses[0];  // Set the first pose from the Cartesian path
    
    std_msgs::msg::Header header;  // Create a header message
    header.stamp.sec = 0;  // Set the timestamp to 0
    header.frame_id = base_frame;  // Set the frame ID to the base frame
    cartesian_path_first_pose.header = header;  // Assign the header to the first pose

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

    // Set up topics for recording the planned trajectory
    std::vector<std::string> topics = {
        planning_node->get_parameter("planned_trajectories_topic.p2p").as_string()
    };

    bag_file_handler->create_bag_topics(topics, "moveit_msgs/msg/CartesianTrajectory");  // Create bag topics for storing trajectories

    // Set the parameter for recording the plan using p2p_recorded_topic
    planning_node->set_parameter(rclcpp::Parameter("writer_topic", planning_node->get_parameter("executed_trajectories_topic.p2p_recorded_topic").as_string()));

    visualize_path(moveit_visual_tools, cartesian_path_poses);  // Visualize the path in RViz
    
    move_group_interface.setPoseTarget(cartesian_path_first_pose);  // Set the pose target to the first point in the path
    
    prompt(moveit_visual_tools, "Press 'Next' in the RvizVisualToolsGui window to plan to the target pose");  // Prompt the user in RViz to plan to the target pose

    success = move_group_interface.plan(plan);  // Perform the motion planning
    if (!success) {
        RCLCPP_ERROR(logger, "Planning failed. Aborting...");  // Log an error if planning fails
        draw_title(moveit_visual_tools, "Planning Failed!");  // Draw "Planning Failed!" title in RViz
        rclcpp::shutdown();  // Shutdown ROS 2
        return 1;  // Return with error status
    }

    display_planned_trajectory(moveit_visual_tools, move_group_interface, planning_group, plan.trajectory_);  // Display the planned trajectory in RViz

    // double position_goal_tolerance = planning_node->get_parameter("position_goal_tolerance").as_double();  // Get the position goal tolerance parameter
    if (cartesian_path_first_pose.pose.position.x == 0 && cartesian_path_first_pose.pose.position.y == 0 && cartesian_path_first_pose.pose.position.z == 0) 
    {
        RCLCPP_ERROR(logger, "Desired position might not be correctly set");  // Log a warning if the desired position might not be set correctly
    } 

    moveit_msgs::msg::CartesianTrajectory planned_trajectory;  // Declare a CartesianTrajectory message to store the planned trajectory
    planned_trajectory = planning_node->get_task_space_trajectory(plan.trajectory_, robot_state, &logger, end_effector_link_name, base_frame, planning_group);  // Generate a task space trajectory from the planned trajectory

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
            planning_node->get_parameter("planned_trajectories_topic.p2p").as_string(),
            "moveit_msgs/msg/CartesianTrajectory",
            planning_node->now());
    }
      
    execute_trajectory(moveit_visual_tools, planned_trajectory, planning_node);  // Execute the planned trajectory

    /*
     * PLAN AND EXECUTE THE REST OF THE TRAJECTORY
     */

    // Set the parameter for recording the plan using cartesian_topic
    planning_node->set_parameter(rclcpp::Parameter("writer_topic", planning_node->get_parameter("executed_trajectories_topic.cartesian_topic").as_string()));
    moveit_visual_tools.deleteAllMarkers();  // Delete all markers in RViz
    moveit_visual_tools.prompt("Press 'Next' in the RvizVisualToolsGui window to plan a Cartesian path");  // Prompt the user in RViz to plan a Cartesian path
    draw_title(moveit_visual_tools, "Planning cartesian path");  // Draw "Planning cartesian path" title in RViz

    auto waypoints = generate_waypoints(cartesian_path_poses, &move_group_interface, logger);
    auto current_orientation = move_group_interface.getCurrentPose().pose.orientation;
    RCLCPP_INFO(logger, "Current robot orientation: [x: %f, y: %f, z: %f, w: %f]",
                current_orientation.x, current_orientation.y, current_orientation.z, current_orientation.w);

    // Check that there are generated waypoints
    if (waypoints.empty() || waypoints.size() <= 1) {
        RCLCPP_ERROR(logger, "Generated waypoints are insufficient. Only %zu waypoints generated. Aborting...", waypoints.size());  // Log an error if there are insufficient waypoints
        rclcpp::shutdown();  // Shutdown ROS 2
        spinner.join();  // Join the spinner thread
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
    execute_trajectory(moveit_visual_tools, planned_trajectory, planning_node);  // Execute the planned trajectory

    // COME BACK TO READY POSITION
    prompt(moveit_visual_tools, "Press 'Next' in the RvizVisualToolsGui window to plan to the target pose");  // Prompt the user in RViz to plan to the target pose
    auto targets = move_group_interface.getNamedTargets();  // Get named targets from the MoveGroup interface
    std::string ready = planning_node->get_parameter("established_poses.ready_pose").as_string();  // Get the "ready" pose parameter
    if (std::find(targets.begin(), targets.end(), ready) != targets.end()) {
        planning_node->set_parameter(rclcpp::Parameter("writer_topic", planning_node->get_parameter("executed_trajectories_topic.ready_topic").as_string().c_str()));  // Set the parameter for recording the plan using ready_topic
        moveit_visual_tools.deleteAllMarkers();  // Delete all markers in RViz
        move_group_interface.setNamedTarget(ready);  // Set the named target to "ready"
        success = move_group_interface.plan(plan);  // Perform the motion planning to the "ready" pose
        if (!success) {
            RCLCPP_ERROR(logger, "Planning failed. Aborting...");  // Log an error if planning fails
            draw_title(moveit_visual_tools, "Planning Failed!");  // Draw "Planning Failed!" title in RViz
            rclcpp::shutdown();  // Shutdown ROS 2
            exit(1);  // Exit with error status
        }
        display_planned_trajectory(moveit_visual_tools, move_group_interface, planning_group, plan.trajectory_);  // Display the planned trajectory to the "ready" pose in RViz
        moveit_visual_tools.trigger();  // Trigger RViz to display the updated visual elements
    }

    planned_trajectory = planning_node->get_task_space_trajectory(plan.trajectory_, robot_state, &logger, end_effector_link_name, base_frame, planning_group);  // Generate a task space trajectory to the "ready" pose

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
            planning_node->get_parameter("planned_trajectories_topic.ready").as_string(),
            "moveit_msgs/msg/CartesianTrajectory",
            planning_node->now());
    }

    execute_trajectory(moveit_visual_tools, planned_trajectory, planning_node);  // Execute the planned trajectory to the "ready" pose
    moveit_visual_tools.deleteAllMarkers();  // Delete all markers in RViz

    rclcpp::shutdown();  // Shutdown ROS 2

    spinner.join();  // Join the spinner thread

    return 0;  // Return with success status
}
