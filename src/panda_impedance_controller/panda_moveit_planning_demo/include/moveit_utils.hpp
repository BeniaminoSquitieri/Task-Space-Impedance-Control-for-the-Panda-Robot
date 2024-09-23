/**
 * @file planning_helpers.hpp
 * @brief Declarations of helper functions for planning with MoveIt.
 *
 * This file contains declarations of helper functions used for visualization,
 * execution, and management of paths and collision objects during planning
 * with MoveIt in ROS2.
 */

#ifndef PLANNING_HELPERS_HPP
#define PLANNING_HELPERS_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_state/conversions.h>

/**
 * @brief Draws a title in the RViz visualization.
 * @param moveit_visual_tools MoveItVisualTools object used for visualization.
 * @param text The title text to display.
 */
void draw_title(moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, const std::string& text);

/**
 * @brief Displays a prompt in the RViz visualization.
 * @param moveit_visual_tools MoveItVisualTools object used for visualization.
 * @param text The prompt text to display.
 */
void prompt(moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, const std::string& text);

/**
 * @brief Draws the tool path in RViz using the provided plan.
 * @param moveit_visual_tools MoveItVisualTools object used for visualization.
 * @param plan Movement plan that contains the path to be drawn.
 * @param jmg Joint model group used for planning.
 */
void draw_trajectory_tool_path(moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, const moveit::planning_interface::MoveGroupInterface::Plan& plan, const moveit::core::JointModelGroup* jmg);

/**
 * @brief Executes the movement plan and visualizes the result in RViz.
 * @param logger Logger for recording messages.
 * @param move_group_interface MoveGroupInterface used for planning and execution.
 * @param moveit_visual_tools MoveItVisualTools object used for visualization.
 * @param success Indicates whether the plan was successfully planned.
 * @param plan Movement plan to execute.
 */
void execute(const rclcpp::Logger& logger, moveit::planning_interface::MoveGroupInterface& move_group_interface, moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, bool success, const moveit::planning_interface::MoveGroupInterface::Plan& plan);

/**
 * @brief Removes all collision objects from the planning scene.
 * @param planning_scene_interface PlanningSceneInterface used for managing collision objects.
 */
void remove_collision_objects(moveit::planning_interface::PlanningSceneInterface& planning_scene_interface);

/**
 * @brief Adds collision objects to the planning scene.
 * @param planning_scene_interface PlanningSceneInterface used for managing collision objects.
 */
void add_collision_objects(moveit::planning_interface::PlanningSceneInterface& planning_scene_interface);

/**
 * @brief Publishes the waypoints in the RViz visualization.
 * @param moveit_visual_tools MoveItVisualTools object used for visualization.
 * @param waypoints Vector of poses representing the waypoints to be published.
 */
void publish_waypoints(moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, const std::vector<geometry_msgs::msg::Pose>& waypoints);

/**
 * @brief Visualizes the path of poses in the RViz visualization.
 * @param moveit_visual_tools MoveItVisualTools object used for visualization.
 * @param path_poses Shared pointer to PoseArray representing the path to be visualized.
 */
void visualize_path(moveit_visual_tools::MoveItVisualTools &moveit_visual_tools, const std::shared_ptr<geometry_msgs::msg::PoseArray> path_poses);

/**
 * @brief Displays the planned trajectory in the RViz visualization.
 * @param moveit_visual_tools MoveItVisualTools object used for visualization.
 * @param move_group_interface MoveGroupInterface used for planning.
 * @param planning_group Name of the planning group.
 * @param trajectory Robot trajectory to be displayed.
 */
void display_planned_trajectory(moveit_visual_tools::MoveItVisualTools &moveit_visual_tools, moveit::planning_interface::MoveGroupInterface &move_group_interface, const std::string &planning_group, const moveit_msgs::msg::RobotTrajectory &trajectory);

#endif // PLANNING_HELPERS_HPP
