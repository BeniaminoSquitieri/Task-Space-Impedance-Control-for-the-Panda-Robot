/**
 * @file ImpedanceController.hpp
 * @brief Defines the ImpedanceController class for robotic manipulation.
 *
 * This file contains the ImpedanceController class which implements an impedance control
 * strategy for a robotic arm, providing functionalities for dynamic parameter updates,
 * trajectory following, and interaction with MoveIt and ROS2.
 */

#ifndef PANDA_IMPEDANCE_CONTROLLER__IMPEDANCE_CONTROLLER_HPP_
#define PANDA_IMPEDANCE_CONTROLLER__IMPEDANCE_CONTROLLER_HPP_

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include "controller_interface/controller_interface.hpp"
#include "kdl_inverse_dynamics_solver/kdl_inverse_dynamics_solver.h"
#include "eigen3/Eigen/Core"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "moveit_msgs/msg/cartesian_trajectory.hpp"
#include "moveit/robot_model/robot_model.h"
#include "moveit/robot_model_loader/robot_model_loader.h"
#include "moveit/robot_state/robot_state.h"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp/duration.hpp"
#include "rclcpp/subscription.hpp"
#include "rclcpp/time.hpp"
#include "rclcpp/timer.hpp"
#include "realtime_tools/realtime_buffer.h"
#include "realtime_tools/realtime_publisher.h"
#include "realtime_tools/realtime_server_goal_handle.h"
#include "tf2_ros/transform_broadcaster.h"
#include "panda_impedance_controller_parameters.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "cartesian_control_msgs/action/follow_cartesian_trajectory.hpp"

using namespace std::chrono_literals;

namespace panda_impedance_controller
{
using FollowCartesianTrajectoryAction = cartesian_control_msgs::action::FollowCartesianTrajectory;

/**
 * @class ImpedanceController
 * @brief A controller implementing impedance control for a robotic manipulator.
 *
 * The ImpedanceController class provides methods and attributes to control a robotic arm
 * using impedance control strategies. This includes handling dynamic parameters, state
 * feedback, and action server for following Cartesian trajectories.
 */
class ImpedanceController : public controller_interface::ControllerInterface
{


enum class State {
    static_impedance_control,
    trajectory_execution_impedance_control,
};

public:
    /**
     * @brief Constructs the ImpedanceController with initial settings.
     */
    ImpedanceController()
    : internal_time_(rclcpp::Duration(0, 0)) // Inizializzazione di internal_time_
    {}

    /**
     * @brief Initializes the controller, setting up necessary parameters and configurations.
     * @return The status after initialization, either SUCCESS or FAILURE.
     */
    controller_interface::CallbackReturn on_init() override;

    /**
     * @brief Provides the configuration for command interfaces used by the controller.
     * @return Configuration struct specifying individual command interfaces.
     */
    controller_interface::InterfaceConfiguration command_interface_configuration() const override;

    /**
     * @brief Provides the configuration for state interfaces used by the controller.
     * @return Configuration struct specifying individual state interfaces.
     */
    controller_interface::InterfaceConfiguration state_interface_configuration() const override;

    /**
     * @brief Configures the controller based on the provided settings.
     * @param previous_state The state of the controller before this function is called.
     * @return The status after configuration, either SUCCESS or FAILURE.
     */
    controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State & previous_state) override;

    /**
     * @brief Activates the controller, making it ready to begin operation.
     * @param previous_state The state of the controller before this function is called.
     * @return The status after activation, either SUCCESS or FAILURE.
     */
    controller_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state) override;

    /**
     * @brief Deactivates the controller, stopping its operation.
     * @param previous_state The state of the controller before this function is called.
     * @return The status after deactivation, either SUCCESS or FAILURE.
     */
    controller_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state) override;

    /**
     * @brief Performs an update cycle of the controller, computing new commands.
     * @param time The current time.
     * @param period The duration since the last update.
     * @return The execution status of this update cycle.
     */
    controller_interface::return_type update(const rclcpp::Time & time, const rclcpp::Duration & period) override;

    /**
     * @brief Handles any errors encountered by the controller.
     * @param previous_state The state of the controller before this function is called.
     * @return The status after error handling, either SUCCESS or FAILURE.
     */
    controller_interface::CallbackReturn on_error(const rclcpp_lifecycle::State & previous_state) override;

    /**
     * @brief Shuts down the controller, performing any necessary cleanup.
     * @param previous_state The state of the controller before this function is called.
     * @return The status after shutdown, either SUCCESS or FAILURE.
     */
    controller_interface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State & previous_state) override;

private:
    /**
     * @brief Checks and loads required parameters from the parameter server.
     */
    void check_parameters();

    /**
     * @brief Updates dynamic parameters from the parameter server during runtime.
     */
    void update_dynamic_parameters();

    /**
     * @brief Computes the control efforts for the joints based on the current state and desired trajectory.
     * @param effort Output vector to store computed joint efforts.
     * @param positions Current joint positions.
     * @param velocities Current joint velocities.
     */
    void compute_effort(Eigen::VectorXd & effort, const Eigen::VectorXd & positions, const Eigen::VectorXd & velocities);

    /**
     * @brief Reads the state interfaces of the joints.
     */
    void read_state_interfaces();

    /**
     * @brief Checks the validity and configuration of the hardware interfaces.
     * @return The result of the check, either SUCCESS or ERROR.
     */
    controller_interface::CallbackReturn check_interfaces();

    /**
     * @brief Updates feedback for an ongoing trajectory following action.
     */
    void updateActionFeedback();

    /**
     * @brief Handles the reception of a new trajectory goal via the action server.
     * @param uuid The UUID of the received goal.
     * @param goal The goal message received.
     * @return The response to the goal request, either ACCEPT or REJECT.
     */
    rclcpp_action::GoalResponse received_goal_trajectory_callback(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const FollowCartesianTrajectoryAction::Goal> goal);

    /**
     * @brief Handles the cancellation of a trajectory goal.
     * @param goal_handle The handle to the goal being canceled.
     * @return The response to the cancel request, either ACCEPT or REJECT.
     */
    rclcpp_action::CancelResponse cancelled_goal_trajectory_callback(const std::shared_ptr<rclcpp_action::ServerGoalHandle<FollowCartesianTrajectoryAction>> goal_handle);

    /**
     * @brief Handles the acceptance of a trajectory goal, preparing to execute it.
     * @param goal_handle The handle to the accepted goal.
     */
    void accepted_goal_trajectory_callback(const std::shared_ptr<rclcpp_action::ServerGoalHandle<FollowCartesianTrajectoryAction>> goal_handle);

    /**
     * @brief Saturates the torque rate to avoid sudden changes in joint efforts.
     * @param tau_d_calculated The calculated torque vector.
     * @param tau_J_d The desired torque vector.
     * @param delta_tau_max The maximum allowable torque change.
     * @return The saturated torque vector.
     */
    Eigen::VectorXd saturateTorqueRate(const Eigen::VectorXd &tau_d_calculated, const Eigen::VectorXd &tau_J_d, double delta_tau_max);

        // Attributes
    std::vector<double> desired_position_;  ///< The desired joint positions.
    std::shared_ptr<inverse_dynamics_solver::InverseDynamicsSolverKDL> solver_;  ///< Inverse dynamics solver.
    std::string robot_description_;  ///< URDF description of the robot.
    std::string robot_description_semantic_;  ///< SRDF description of the robot.
    bool is_initialized = false;  ///< Flag indicating if the controller is initialized.
    bool is_configured = false;  ///< Flag indicating if the controller is configured.
    bool is_active = false;  ///< Flag indicating if the controller is active.
    std::vector<std::string> joint_names_;  ///< List of joint names for the robot.

    std::shared_ptr<impedance_controller::ParamListener> param_listener_;  ///< Listener for dynamic parameters.
    impedance_controller::Params ros_params_;  ///< Parameters for ROS configurations.
    std::shared_ptr<const moveit::core::RobotModel> kinematic_model_;  ///< Kinematic model of the robot.
    std::shared_ptr<moveit::core::RobotState> kinematic_state_;  ///< Current state of the robot's kinematics.
    const moveit::core::JointModelGroup *joint_model_group_;  ///< Joint model group used in the robot model.
    
    Eigen::VectorXd joint_lower_limits_;  ///< Lower joint limits.
    Eigen::VectorXd joint_upper_limits_;  ///< Upper joint limits.
    Eigen::VectorXd joint_default_values_;  ///< Default joint values.
    Eigen::VectorXd actual_joint_positions_;  ///< Actual joint positions.
    Eigen::VectorXd actual_joint_velocities_;  ///< Actual joint velocities.
    Eigen::VectorXd actual_ee_position_;  ///< Actual end-effector position.
    Eigen::Quaterniond actual_ee_orientation_;  ///< Actual end-effector orientation.
    Eigen::VectorXd actual_ee_velocity_;  ///< Actual end-effector velocity.
    
    std::vector<std::reference_wrapper<hardware_interface::LoanedCommandInterface>> joint_command_effort_handles_;  ///< Handles for commanding joint efforts.
    std::vector<std::reference_wrapper<hardware_interface::LoanedStateInterface>> joint_state_position_handles_;  ///< Handles for reading joint positions.
    std::vector<std::reference_wrapper<hardware_interface::LoanedStateInterface>> joint_state_velocity_handles_;  ///< Handles for reading joint velocities.
    
    Eigen::MatrixXd actual_jacobian_;  ///< Actual Jacobian matrix of the end-effector.
    Eigen::VectorXd stiffness_gains_;  ///< Stiffness gains for impedance control.
    Eigen::VectorXd damping_gains_;  ///< Damping gains for impedance control.
    Eigen::VectorXd desired_ee_position_;  ///< Desired end-effector position.
    Eigen::Quaterniond desired_ee_orientation_;  ///< Desired end-effector orientation.
    Eigen::VectorXd desired_joint_positions_;  ///< Desired joint positions.
    Eigen::Vector3d desired_ee_orientation_rpy_;  ///< Desired end-effector orientation in roll-pitch-yaw format.
    
    Eigen::VectorXd tau_J_d;  ///< Desired joint torques.
    double delta_tau_max_;  ///< Maximum change in joint torques allowed.
    Eigen::VectorXd q_d_nullspace_;  ///< Nullspace optimization joint configuration.
    double nullspace_stiffness_;  ///< Stiffness for nullspace optimization.
    double nullspace_damping_;  ///< Damping for nullspace optimization.
    
    Eigen::VectorXd gravity_vector_;  ///< Gravity vector for the robot.
    Eigen::MatrixXd inertia_matrix_;  ///< Inertia matrix of the robot.
    Eigen::VectorXd coriolis_vector_;  ///< Coriolis forces vector.
    Eigen::VectorXd joint_space_effort_;  ///< Computed joint space efforts.
    Eigen::VectorXd joint_effort_;  ///< Commanded joint efforts.
    Eigen::VectorXd saturated_joint_effort_;  ///< Saturated joint efforts to avoid excessive forces.
    
    State active_state_;  ///< Current state of the controller (static or trajectory execution).
    rclcpp::Duration internal_time_;  ///< Internal time tracker for trajectory execution.
    std::size_t number_reached_trajectory_points_ = 0;  ///< Number of trajectory points reached.
    
    moveit_msgs::msg::CartesianTrajectory goal_trajectory_;  ///< Goal trajectory for Cartesian control.
    bool trajectory_received_ = false;  ///< Flag indicating if a new trajectory has been received.
    
    std::shared_ptr<rclcpp_action::ServerGoalHandle<FollowCartesianTrajectoryAction>> goal_handle_;  ///< Handle for the current goal.
    std::shared_ptr<FollowCartesianTrajectoryAction::Result> result_;  ///< Result of the action goal.
    
    double waypoint_timestamp;  ///< Timestamp of the current waypoint.
    double waypoint_timestamp_last;  ///< Timestamp of the last waypoint.
    double internal_timestamp;  ///< Internal timestamp for trajectory timing.
    // double k0;  ///< Scaling factor for manipulability optimization.

    std::shared_ptr<rclcpp_action::Server<cartesian_control_msgs::action::FollowCartesianTrajectory>> action_server_;  ///< Action server for following Cartesian trajectories.

};

}  // namespace panda_impedance_controller

#endif  // PANDA_IMPEDANCE_CONTROLLER__IMPEDANCE_CONTROLLER_HPP_
