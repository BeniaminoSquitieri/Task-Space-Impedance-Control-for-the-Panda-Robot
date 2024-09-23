#include "task_space_client_utils.hpp"  // Include the header file for TaskSpaceClient utilities.
#include "task_space_client_utils_parameters.hpp"  // Include the parameters header file for TaskSpaceClient.
#include "bag_file_utils.hpp"  // Include the header file for bag file utilities.
#include <moveit_msgs/msg/move_it_error_codes.hpp>  // Include the header file for MoveIt error codes message type.

namespace task_space_client_utils {  // Start of the task_space_client_utils namespace.

/**
 * @brief Constructor for the TaskSpaceClient class.
 * 
 * Initializes the node parameters, sets up the action client for Cartesian control, 
 * and configures parameters for trajectory recording.
 * 
 * @param node_name Name of the ROS2 node.
 */
TaskSpaceClient::TaskSpaceClient(const std::string& node_name) : Node(node_name) {
    param_subscriber_ = std::make_shared<task_space_client_utils::ParamListener>(get_node_parameters_interface());  // Initialize parameter listener for node parameters.
    action_name_ = "/" + get_parameter("controller_name").as_string() + "/follow_cartesian_trajectory";  // Construct the action name for the Cartesian control.
    action_type_ = "cartesian_control_msgs/action/FollowCartesianTrajectory_FeedbackMessage";  // Define the action type for feedback messages.
    task_space_client_ptr_ = rclcpp_action::create_client<SendTaskSpaceTrajectory>(this, action_name_.c_str());  // Create an action client for sending Cartesian trajectory goals.

    // Initialize BagFileHandler
    bag_file_handler_ = std::make_unique<bag_file_utils::BagFileHandler>(get_parameter("executed_trajectory_file").as_string());  // Create a unique pointer for BagFileHandler to handle bag file operations.

    std::vector<std::string> topics = {  // Define topics for trajectory recording.
        get_parameter("executed_trajectories_topic.ready_topic").as_string(),  // Topic to record trajectory to the ready pose.
        get_parameter("executed_trajectories_topic.p2p_recorded_topic").as_string(),  // Topic to record point-to-point trajectory.
        get_parameter("executed_trajectories_topic.cartesian_topic").as_string(),  // Topic to record executed Cartesian trajectory.
    };

    bag_file_handler_->create_bag_topics(topics, action_type_);  // Create topics in the bag file for recording data.

    declare_parameter<std::string>("writer_topic", topics[0]);  // Declare a parameter for the writer topic, defaulting to the first topic in the list.
}

/**
 * @brief Sends a task space trajectory to the action server.
 * 
 * This function sends a Cartesian trajectory goal to the action server and waits for the response.
 * 
 * @param trajectory The Cartesian trajectory to be executed.
 * @return A future containing the result of the action.
 */
std::shared_future<rclcpp_action::ClientGoalHandle<TaskSpaceClient::SendTaskSpaceTrajectory>::WrappedResult> TaskSpaceClient::task_space_goal_forwarding(const moveit_msgs::msg::CartesianTrajectory& trajectory) {
    if (!task_space_client_ptr_->wait_for_action_server(std::chrono::seconds(10))) {  // Wait for the action server to become available.
        RCLCPP_ERROR(get_logger(), "Panda impedance controller action server not available. Check if controller is activated.");  // Log an error if the server is not available.
        throw std::runtime_error("Panda impedance controller action server not available.");  // Throw a runtime error if the server is not available.
    }

    auto goal_msg = SendTaskSpaceTrajectory::Goal();  // Create a new goal message for the trajectory.
    goal_msg.trajectory = trajectory;  // Set the trajectory in the goal message.

    RCLCPP_INFO(get_logger(), "Sending trajectory to action server with %zu points.", trajectory.points.size());  // Log the number of points in the trajectory.

    auto send_goal_options = rclcpp_action::Client<SendTaskSpaceTrajectory>::SendGoalOptions();  // Define options for sending the goal.
    send_goal_options.goal_response_callback = std::bind(&TaskSpaceClient::task_space_goal_response_callback, this, std::placeholders::_1);  // Bind the goal response callback.
    send_goal_options.feedback_callback = std::bind(&TaskSpaceClient::task_space_feedback_callback, this, std::placeholders::_1, std::placeholders::_2);  // Bind the feedback callback.
    send_goal_options.result_callback = std::bind(&TaskSpaceClient::task_space_result_callback, this, std::placeholders::_1);  // Bind the result callback.

    auto send_goal_future = task_space_client_ptr_->async_send_goal(goal_msg, send_goal_options);  // Send the goal asynchronously.

    if (!send_goal_future.valid()) {  // Check if the future is valid.
        RCLCPP_ERROR(get_logger(), "Goal rejected.");  // Log an error if the goal is rejected.
        throw std::runtime_error("Goal rejected.");  // Throw a runtime error if the goal is rejected.
    }

    send_goal_future.wait();  // Wait for the goal result.
    return task_space_client_ptr_->async_get_result(send_goal_future.get());  // Return the result future.
}

/**
 * @brief Callback for the goal response from the action server.
 * 
 * This function is called when the action server responds with acceptance or rejection of the sent goal.
 * 
 * @param goal_handle Handle for the goal received from the action server.
 */
void TaskSpaceClient::task_space_goal_response_callback(const GoalHandleSendTaskSpaceTrajectory::SharedPtr& goal_handle) {
    if (!goal_handle) {  // Check if the goal handle is null.
        RCLCPP_ERROR(get_logger(), "Goal rejected by server.");  // Log an error if the goal is rejected by the server.
    } else {
        RCLCPP_INFO(get_logger(), "Trajectory received and goal accepted by server.");  // Log a message if the goal is accepted.
    }
}

/**
 * @brief Feedback callback for the Cartesian control action server.
 * 
 * This function is called periodically with feedback from the action server and records the feedback to the bag file.
 * 
 * @param goal_handle Handle for the current goal.
 * @param feedback Feedback from the action server.
 */
void TaskSpaceClient::task_space_feedback_callback(GoalHandleSendTaskSpaceTrajectory::SharedPtr, const std::shared_ptr<const cartesian_control_msgs::action::FollowCartesianTrajectory::Feedback> feedback) {
    std::string writer_topic = get_parameter("writer_topic").as_string();  // Get the writer topic parameter.
    bag_file_handler_->write_feedback(feedback, writer_topic, action_type_, now());  // Write the feedback to the bag file. / Executed trajectory
}

/**
 * @brief Callback for the result of the action.
 * 
 * This function is called when the action server finishes executing the goal and returns the result.
 * 
 * @param result The result of the action sent by the server.
 */
void TaskSpaceClient::task_space_result_callback(const GoalHandleSendTaskSpaceTrajectory::WrappedResult& result) {
    switch (result.code) {  // Check the result code of the action.
        case rclcpp_action::ResultCode::SUCCEEDED:
            RCLCPP_INFO(get_logger(), "Panda impedance controller goal succeeded.");  // Log a message if the goal succeeded.
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(get_logger(), "Panda impedance controller goal aborted.");  // Log an error if the goal was aborted.
            break;
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_ERROR(get_logger(), "Panda impedance controller goal canceled.");  // Log an error if the goal was canceled.
            break;
        default:
            RCLCPP_ERROR(get_logger(), "Unknown task space goal result.");  // Log an error for an unknown result.
            break;
    }
}

/**
 * @brief Generates a Cartesian trajectory from a joint space trajectory for the controller.
 * 
 * This function converts a joint space trajectory into a Cartesian trajectory usable by the controller.
 * 
 * @param trajectory The joint space trajectory.
 * @param robot_state Current state of the robot.
 * @param logger Logger for printing messages.
 * @param target_frame The target frame for the trajectory.
 * @param frame_id The frame ID for the trajectory.
 * @param planning_group The planning group used.
 * @return The generated Cartesian trajectory.
 */
moveit_msgs::msg::CartesianTrajectory TaskSpaceClient::get_task_space_trajectory(const moveit_msgs::msg::RobotTrajectory& trajectory,moveit::core::RobotState& robot_state,const rclcpp::Logger* logger,const std::string& target_frame,const std::string& frame_id,const std::string& planning_group) {

    std::vector<moveit_msgs::msg::CartesianTrajectoryPoint> cartesian_trajectory_points;  // Initialize vector to store Cartesian trajectory points.
    cartesian_trajectory_points.reserve(trajectory.joint_trajectory.points.size());  // Reserve space in the vector for efficiency.

    for (const auto& point : trajectory.joint_trajectory.points) {  // Iterate over each joint trajectory point.
        const auto pose = direct_kinematic_computation(robot_state, target_frame, trajectory.joint_trajectory.joint_names, point.positions);  // Compute end-effector pose using direct kinematics.
        const auto velocity = first_order_kinematic_computation(robot_state, trajectory.joint_trajectory.joint_names, point.positions, point.velocities, planning_group);  // Compute end-effector velocity.

        moveit_msgs::msg::CartesianTrajectoryPoint cartesian_point;  // Initialize a Cartesian trajectory point.
        cartesian_point.point.pose = pose;  // Set the pose for the Cartesian trajectory point.
        cartesian_point.point.velocity = velocity;  // Set the velocity for the Cartesian trajectory point.
        cartesian_point.time_from_start = point.time_from_start;  // Set the time from the start for the Cartesian trajectory point.

        cartesian_trajectory_points.push_back(std::move(cartesian_point));  // Add the Cartesian point to the trajectory vector.
    }

    moveit_msgs::msg::CartesianTrajectory cartesian_trajectory_msg;  // Initialize a Cartesian trajectory message.
    cartesian_trajectory_msg.header.frame_id = frame_id;  // Set the frame ID for the trajectory.
    cartesian_trajectory_msg.tracked_frame = target_frame;  // Set the tracked frame for the trajectory.
    cartesian_trajectory_msg.points = std::move(cartesian_trajectory_points);  // Assign the computed points to the trajectory message.

    RCLCPP_INFO(*logger, "Task space trajectory successfully extracted: number of points: %zu", cartesian_trajectory_msg.points.size());  // Log the number of points in the trajectory.

    return cartesian_trajectory_msg;  // Return the generated Cartesian trajectory.
}

/**
 * @brief Direct kinematics computation to calculate the end-effector pose.
 * 
 * This function uses the current robot state to compute the global transformation of the end-effector link.
 * 
 * @param robot_state The current robot state.
 * @param target_frame The target frame for the pose.
 * @param joint_names The names of the joints involved in the planning.
 * @param positions The positions of the joints.
 * @return The planned end-effector pose.
 */
geometry_msgs::msg::Pose TaskSpaceClient::direct_kinematic_computation(moveit::core::RobotState& robot_state, const std::string& target_frame, const std::vector<std::string>& joint_names, 
    const trajectory_msgs::msg::JointTrajectoryPoint::_positions_type& positions) 
{
    // Set the robot state to the specified joint positions
    set_joint_positions(robot_state, joint_names, positions);

    // Update the robot state with the new joint positions
    robot_state.update();

    // Get the global transformation (isometry) of the target frame in the robot's workspace
    const auto isometry = robot_state.getGlobalLinkTransform(target_frame);

    // Convert the isometry transformation to a TF2 transform (which includes position and orientation)
    const auto tf2 = tf2::eigenToTransform(isometry);

    // Initialize a Pose message to represent the end-effector's planned pose
    geometry_msgs::msg::Pose planned_eef_pose;

    // Set the position (translation) of the end-effector based on the computed transformation
    planned_eef_pose.position.x = tf2.transform.translation.x;
    planned_eef_pose.position.y = tf2.transform.translation.y;
    planned_eef_pose.position.z = tf2.transform.translation.z;

    // Set the orientation (rotation) of the end-effector based on the computed transformation
    planned_eef_pose.orientation.x = tf2.transform.rotation.x;
    planned_eef_pose.orientation.y = tf2.transform.rotation.y;
    planned_eef_pose.orientation.z = tf2.transform.rotation.z;
    planned_eef_pose.orientation.w = tf2.transform.rotation.w;

    // Return the computed pose of the end-effector
    return planned_eef_pose;
}

/**
 * @brief First-order kinematic computation to calculate Cartesian space velocities.
 * 
 * Uses the Jacobian matrix to compute task space velocities given joint velocities.
 * 
 * @param robot_state The current robot state.
 * @param joint_names The names of the joints involved in the planning.
 * @param positions The positions of the joints.
 * @param velocities The velocities of the joints.
 * @param planning_group The planning group used.
 * @return The velocities in Cartesian space.
 */
geometry_msgs::msg::Twist TaskSpaceClient::first_order_kinematic_computation(moveit::core::RobotState& robot_state,const std::vector<std::string>& joint_names,const trajectory_msgs::msg::JointTrajectoryPoint::_positions_type& positions,const trajectory_msgs::msg::JointTrajectoryPoint::_velocities_type& velocities,const std::string& planning_group) 
{
    // Set the joint positions in the robot state
    set_joint_positions(robot_state, joint_names, positions);
    robot_state.update();  // Update the robot state to reflect the new joint positions

    // Get the joint model group for the specified planning group
    const auto* joint_model_group = robot_state.getJointModelGroup(planning_group);
    if (!joint_model_group) {
        throw std::runtime_error("Failed to get joint model group for planning group: " + planning_group);
    }

    // Compute the Jacobian matrix for the planning group
    const auto& jacobian = robot_state.getJacobian(joint_model_group);
    if (jacobian.size() == 0) {
        throw std::runtime_error("Failed to compute the Jacobian matrix for planning group: " + planning_group);
    }

    // Ensure that the size of the velocities matches the size of the joint names
    if (velocities.size() != joint_names.size()) {
        throw std::runtime_error("Mismatch between joint names and velocities sizes.");
    }

    // Create an Eigen matrix to store joint velocities
    Eigen::Matrix<double, Eigen::Dynamic, 1> joints_velocities(joint_names.size());
    for (size_t i = 0; i < joint_names.size(); ++i) {
        joints_velocities(i) = velocities[i];  // Assign the joint velocities to the matrix
    }

    // Compute the Cartesian velocities using the Jacobian matrix
    const auto v = jacobian * joints_velocities;

    // Initialize a Twist message for Cartesian velocities
    geometry_msgs::msg::Twist task_space_velocities;
    task_space_velocities.linear.x = v(0, 0);  // Set the linear x-velocity
    task_space_velocities.linear.y = v(1, 0);  // Set the linear y-velocity
    task_space_velocities.linear.z = v(2, 0);  // Set the linear z-velocity
    task_space_velocities.angular.x = v(3, 0);  // Set the angular x-velocity
    task_space_velocities.angular.y = v(4, 0);  // Set the angular y-velocity
    task_space_velocities.angular.z = v(5, 0);  // Set the angular z-velocity

    return task_space_velocities;  // Return the computed Cartesian velocities
}


/**
 * @brief Helper function to set joint positions.
 * 
 * This function sets the joint positions of the robot state to the specified positions.
 * 
 * @param robot_state The current robot state.
 * @param joint_names The names of the joints to set.
 * @param positions The positions to set for the joints.
 */
void TaskSpaceClient::set_joint_positions(
    moveit::core::RobotState& robot_state,
    const std::vector<std::string>& joint_names,
    const trajectory_msgs::msg::JointTrajectoryPoint::_positions_type& positions) {

    // Iterate over each joint name and corresponding position in the positions vector
    for (size_t i = 0; i < joint_names.size(); ++i) {
        // Set the position of the current joint in the robot state
        // 'joint_names[i]' specifies the joint, and '&positions[i]' points to its corresponding position
        robot_state.setJointPositions(joint_names[i], &positions[i]);
    }
}



/**
 * @brief Generates a Cartesian path for the robot end-effector using a series of waypoints.
 * 
 * This function computes a Cartesian path for the end-effector based on the provided waypoints and constraints.
 * 
 * @param waypoints A vector of poses representing the Cartesian waypoints.
 * @param logger Logger for printing messages.
 * @param move_group_interface Pointer to the MoveGroupInterface used for motion planning.
 * @return A pair containing the fraction of the path achieved and the motion plan.
 */
std::pair<double, moveit::planning_interface::MoveGroupInterface::Plan> TaskSpaceClient::cartesian_path_generation(
    std::vector<geometry_msgs::msg::Pose> waypoints, 
    const rclcpp::Logger *logger, 
    moveit::planning_interface::MoveGroupInterface *move_group_interface/*, moveit_msgs::msg::Constraints &constraints*/) {
    
    moveit::planning_interface::MoveGroupInterface::Plan plan;  // Initialize a motion plan.
    moveit_msgs::msg::RobotTrajectory trajectory;  // Initialize a robot trajectory.
    moveit_msgs::msg::MoveItErrorCodes error_code;  // Initialize a MoveIt error codes message.
    const double jump_threshold = 0.0;  // Set the jump threshold for Cartesian path planning.
    const double eef_step = 0.008;  // Set the end-effector step size for Cartesian path planning.

    if (waypoints.size() < 2) {
        RCLCPP_ERROR(*logger, "Not enough waypoints to perform Cartesian path planning. At least two waypoints are required.");
        return std::make_pair(0.0, plan);
    }
    // Print planning parameters
    RCLCPP_INFO(*logger, "Planning with eef_step: %f, jump_threshold: %f", eef_step, jump_threshold);

    // Execute Cartesian path planning
    double fraction = move_group_interface->computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory, false, &error_code);  // Compute the Cartesian path for the reduced waypoints.
    RCLCPP_INFO(*logger, "Fraction value: %f", fraction);  // Print the fraction of the path achieved.

    // Print the result of the planned path fraction
    RCLCPP_INFO(*logger, "Achieved %.2f%% of Cartesian path", fraction * 100.0);

    // Print the planning result
    if (fraction == -1.0) {
        RCLCPP_ERROR(*logger, "computeCartesianPath failed with error code: %d", error_code.val);  // Log an error if the path planning failed.
    } else if (fraction < 1.0) {
        RCLCPP_WARN(*logger, "Only %.2f%% of Cartesian path was achieved. Planning may not be successful.", fraction * 100.0);  // Log a warning if only part of the path was achieved.
    } else {
        RCLCPP_INFO(*logger, "Full Cartesian path planned successfully.");  // Log a message if the full path was planned successfully.
    }

    // Convert the current robot state to a RobotState message
    robotStateToRobotStateMsg(*move_group_interface->getCurrentState(), plan.start_state_);  // Convert the current robot state to a RobotState message.
    
    // Assign the planned trajectory to the plan
    plan.trajectory_ = trajectory;  // Assign the computed trajectory to the plan.

    // Print the size of the planned trajectory
    RCLCPP_INFO(*logger, "Planned trajectory has %zu points.", plan.trajectory_.joint_trajectory.points.size());  // Log the number of points in the planned trajectory.

    return std::make_pair(fraction, plan);  // Return the fraction of the path achieved and the motion plan.
}



} // namespace task_space_client_utils
