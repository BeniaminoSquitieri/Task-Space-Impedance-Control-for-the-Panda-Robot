/**
 * @file planning_node.hpp
 * @brief Declaration of the TaskSpaceClient class for managing workspace planning using ROS2 and MoveIt.
 *
 * This file contains the declaration of the TaskSpaceClient class, which manages the planning and execution 
 * of trajectories in the workspace using ROS2 and MoveIt. The class provides functionality for forwarding trajectory goals,
 * generating Cartesian paths, and managing the robot state.
 */

#ifndef PLANNING_NODE_HPP_
#define PLANNING_NODE_HPP_

#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>
#include "rosbag2_cpp/reader.hpp"
#include <rosbag2_cpp/writer.hpp>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "rosbag2_cpp/reader.hpp"
#include "cartesian_control_msgs/action/follow_cartesian_trajectory.hpp"
#include "moveit_msgs/msg/robot_trajectory.hpp"
#include "eigen3/Eigen/Core"
#include "tf2_eigen/tf2_eigen.hpp"
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_state/conversions.h>
#include "task_space_client_utils_parameters.hpp"
#include "bag_file_utils.hpp" 

namespace task_space_client_utils {

/**
 * @class TaskSpaceClient
 * @brief Class to manage the planning and execution of trajectories in the workspace using ROS2 and MoveIt.
 */
class TaskSpaceClient : public rclcpp::Node {
public:
    using SendTaskSpaceTrajectory = cartesian_control_msgs::action::FollowCartesianTrajectory;
    using GoalHandleSendTaskSpaceTrajectory = rclcpp_action::ClientGoalHandle<SendTaskSpaceTrajectory>;

    /**
     * @brief Explicit constructor for the TaskSpaceClient class.
     * @param node_name Name of the ROS node.
     */
    explicit TaskSpaceClient(const std::string& node_name);

    /**
     * @brief Forwards a workspace trajectory goal to the action server.
     * @param trajectory The Cartesian trajectory to follow.
     * @return A future object representing the result of the action.
     */
    std::shared_future<rclcpp_action::ClientGoalHandle<TaskSpaceClient::SendTaskSpaceTrajectory>::WrappedResult> task_space_goal_forwarding(const moveit_msgs::msg::CartesianTrajectory& trajectory);

    /**
     * @brief Generates a workspace trajectory using a robot trajectory.
     * @param trajectory The robot trajectory to convert.
     * @param robot_state The current state of the robot.
     * @param logger Logger for message logging.
     * @param target_frame The target frame for the trajectory.
     * @param frame_id The frame identifier.
     * @param planning_group The planning group.
     * @return The generated Cartesian trajectory.
     */
    moveit_msgs::msg::CartesianTrajectory get_task_space_trajectory(const moveit_msgs::msg::RobotTrajectory& trajectory, moveit::core::RobotState& robot_state, const rclcpp::Logger* logger, const std::string& target_frame, const std::string& frame_id, const std::string& planning_group);

    /**
     * @brief Executes a Cartesian trajectory by forwarding the goal to the action server.
     * @param trajectory The Cartesian trajectory to execute.
     * @return A future object representing the result of the trajectory execution.
     */
    auto execute_trajectory(const moveit_msgs::msg::CartesianTrajectory &trajectory) {
        auto result = this->task_space_goal_forwarding(trajectory); 
        return result;
    }

    /**
     * @brief Generates a Cartesian path given a set of waypoints.
     * @param waypoints Vector of poses representing the waypoints for the path.
     * @param logger Logger for message logging.
     * @param move_group_interface Pointer to the MoveGroup interface used for planning.
     * @return A pair containing the fraction of the path generated and the movement plan.
     */
    std::pair<double, moveit::planning_interface::MoveGroupInterface::Plan> cartesian_path_generation(std::vector<geometry_msgs::msg::Pose> waypoints, const rclcpp::Logger *logger, moveit::planning_interface::MoveGroupInterface *move_group_interface/*, moveit_msgs::msg::Constraints &constraints*/);

private:
    /**
     * @brief Callback for the workspace trajectory goal response.
     * @param goal_handle Shared pointer to the goal handle.
     */
    void task_space_goal_response_callback(const GoalHandleSendTaskSpaceTrajectory::SharedPtr &goal_handle);

    /**
     * @brief Callback for the workspace trajectory goal feedback.
     * @param goal_handle Shared pointer to the goal handle.
     * @param feedback Shared constant pointer to the received feedback.
     */
    void task_space_feedback_callback(GoalHandleSendTaskSpaceTrajectory::SharedPtr, const std::shared_ptr<const cartesian_control_msgs::action::FollowCartesianTrajectory::Feedback> /*feedback*/);

    /**
     * @brief Callback for the workspace trajectory goal result.
     * @param result Result of the trajectory goal.
     */
    void task_space_result_callback(const GoalHandleSendTaskSpaceTrajectory::WrappedResult &result);

    /**
     * @brief Sets the joint positions in the robot state.
     * @param robot_state The robot state to update.
     * @param joint_names Vector of joint names.
     * @param positions Joint positions to set.
     */
    void set_joint_positions(moveit::core::RobotState& robot_state, const std::vector<std::string>& joint_names, const trajectory_msgs::msg::JointTrajectoryPoint::_positions_type& positions);

    /**
     * @brief Performs direct kinematic computation.
     * @param robot_state The robot state to use for computation.
     * @param target_frame The target frame.
     * @param joint_names Names of the joints involved in the computation.
     * @param positions Joint positions for the computation.
     * @return The resulting pose in 3D coordinates.
     */
    geometry_msgs::msg::Pose direct_kinematic_computation(moveit::core::RobotState& robot_state, const std::string& target_frame, const std::vector<std::string>& joint_names, const trajectory_msgs::msg::JointTrajectoryPoint::_positions_type& positions);

    /**
     * @brief Performs first-order kinematic computation.
     * @param robot_state The robot state to use for computation.
     * @param joint_names Names of the joints involved in the computation.
     * @param positions Joint positions for the computation.
     * @param velocities Joint velocities for the computation.
     * @param planning_group The planning group to use.
     * @return The resulting velocity in 3D coordinates.
     */
    geometry_msgs::msg::Twist first_order_kinematic_computation(moveit::core::RobotState& robot_state, const std::vector<std::string>& joint_names, const trajectory_msgs::msg::JointTrajectoryPoint::_positions_type& positions, const trajectory_msgs::msg::JointTrajectoryPoint::_velocities_type& velocities, const std::string& planning_group);

    std::shared_ptr<task_space_client_utils::ParamListener> param_subscriber_; /**< Subscriber to the node's parameters. */
    rclcpp_action::Client<SendTaskSpaceTrajectory>::SharedPtr task_space_client_ptr_; /**< Shared pointer to the task space trajectory action client. */
    moveit_msgs::msg::CartesianTrajectory trajectory_; /**< Current Cartesian trajectory. */
    std::string action_name_; /**< Name of the current action. */
    std::string action_type_; /**< Type of the current action. */
    std::unique_ptr<bag_file_utils::BagFileHandler> bag_file_handler_; /**< Bag file handler for recording trajectories. */

};

}  // namespace task_space_client_utils

#endif  // PLANNING_NODE_HPP_
