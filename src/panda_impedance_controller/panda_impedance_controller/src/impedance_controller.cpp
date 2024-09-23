#include "panda_impedance_controller/impedance_controller.hpp"
#include "pluginlib/class_list_macros.hpp"
#include <rclcpp/rclcpp.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include <Eigen/Dense>
#include <thread>
#include "controller_interface/controller_interface.hpp"
#include "controller_interface/helpers.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "tf2_eigen/tf2_eigen.hpp"
#include <sstream>

using namespace std::chrono_literals;

namespace panda_impedance_controller
{

/**
 * @brief Initializes the ImpedanceController.
 * 
 * This method is called during the initialization phase of the controller.
 * It sets up necessary parameters and configurations required for the controller.
 * 
 * @return CallbackReturn::SUCCESS if initialization is successful, otherwise an appropriate error code.
 */
controller_interface::CallbackReturn ImpedanceController::on_init()
{
  // Log the initialization process
  RCLCPP_INFO(get_node()->get_logger(), "Initializing controller");

  // Check if the controller is already initialized
  if (is_initialized)
  {
    // Return success if already initialized
    return CallbackReturn::SUCCESS;
  }

  // Validate that all required parameters are set
  check_parameters();

  // Create a parameter listener for dynamic parameter updates
  param_listener_ = std::make_shared<impedance_controller::ParamListener>(get_node());

  // Set the controller state to initialized
  is_initialized = true;

  // Set the initial state of the controller to static impedance control
  active_state_ = State::static_impedance_control;

  // Return success to indicate successful initialization
  return CallbackReturn::SUCCESS;
}

/**
 * @brief Checks for required parameters in the ROS node.
 * 
 * This function iterates through a list of required parameters and verifies that they are set in the ROS node.
 * If any required parameter is not set, an error message is logged.
 */
void ImpedanceController::check_parameters()
{
  // Retrieve the ROS node handle
  auto node = get_node();

  // List of required parameters for the controller
  std::vector<std::string> required_params = {
      "robot_base_link",
      "end_effector_link",
      "joint_model_group_name",
      "desired_joint_positions",
      "desired_orientation_rpy.roll",
      "desired_orientation_rpy.pitch",
      "desired_orientation_rpy.yaw",
      "gains.stiffness.x",
      "gains.stiffness.y",
      "gains.stiffness.z",
      "gains.stiffness.orientation_x",
      "gains.stiffness.orientation_y",
      "gains.stiffness.orientation_z",
      "gravity_compensation"
      };

  // Iterate over each required parameter
  for (const auto &param : required_params)
  {
    // Check if the parameter is set in the node
    if (!node->has_parameter(param))
    {
      // Log an error message if the parameter is not set
      RCLCPP_ERROR(node->get_logger(), "Parameter '%s' not set", param.c_str());
    }
  }
}

/**
 * @brief Configures the command interfaces for the controller.
 * 
 * This function specifies the command interfaces required by the controller, such as joint efforts.
 * 
 * @return An InterfaceConfiguration object containing the configuration for command interfaces.
 */
controller_interface::InterfaceConfiguration ImpedanceController::command_interface_configuration() const
{
  // Create an interface configuration object
  controller_interface::InterfaceConfiguration interface_configuration;

  // Set the interface type to INDIVIDUAL, indicating specific interfaces for each joint
  interface_configuration.type = controller_interface::interface_configuration_type::INDIVIDUAL;

  // Reserve space in the names vector for the number of joints
  interface_configuration.names.reserve(joint_names_.size());

  // Iterate over each joint name and add the effort interface
  for (const auto &joint_name : joint_names_)
  {
    interface_configuration.names.push_back(joint_name + "/effort");
  }

  // Return the populated interface configuration
  return interface_configuration;
}

/**
 * @brief Configures the state interfaces for the controller.
 * 
 * This function specifies the state interfaces required by the controller, such as joint positions and velocities.
 * 
 * @return An InterfaceConfiguration object containing the configuration for state interfaces.
 */
controller_interface::InterfaceConfiguration ImpedanceController::state_interface_configuration() const
{
  // Create an interface configuration object
  controller_interface::InterfaceConfiguration interface_configuration;

  // Set the interface type to INDIVIDUAL, indicating specific interfaces for each joint
  interface_configuration.type = controller_interface::interface_configuration_type::INDIVIDUAL;

  // Reserve space in the names vector for the number of joints
  interface_configuration.names.reserve(joint_names_.size() * 2);

  // Iterate over each joint name and add the position and velocity interfaces
  for (const auto &joint_name : joint_names_)
  {
    interface_configuration.names.push_back(joint_name + "/position");
    interface_configuration.names.push_back(joint_name + "/velocity");
  }

  // Return the populated interface configuration
  return interface_configuration;
}

/**
 * @brief Configures the ImpedanceController.
 *
 * This method is called during the configuration phase of the controller's lifecycle.
 * It initializes the robot model, sets up necessary parameters, and prepares the controller for activation.
 * 
 * @param previous_state The previous state of the controller before configuration.
 * @return CallbackReturn::SUCCESS if configuration is successful, otherwise CallbackReturn::ERROR.
 */
controller_interface::CallbackReturn ImpedanceController::on_configure(const rclcpp_lifecycle::State & /*previous_state*/)
{
    // Log the configuration process
    RCLCPP_INFO(get_node()->get_logger(), "Configuring controller");

    // Check if the controller is already configured
    if (is_configured)
    {
        // Return success if already configured
        return CallbackReturn::SUCCESS;
    }

    // Retrieve the ROS parameters from the parameter listener
    ros_params_ = param_listener_->get_params();

    // Create a new ROS node for loading the robot model
    rclcpp::Node::SharedPtr node = std::make_shared<rclcpp::Node>("robot_model_loader");

    // Flag to keep the robot model loader node alive
    bool keep_slave_alive = true;

    // Create a separate thread to spin the robot model loader node
    std::thread t([node, &keep_slave_alive, this]()
    {
        // Create a single-threaded executor for the node
        rclcpp::executors::SingleThreadedExecutor executor;

        // Add the node to the executor
        executor.add_node(node);

        // Log that the node is spinning
        RCLCPP_INFO(get_node()->get_logger(), "Spinning up robot model loader node");

        // Spin the node while the flag is true
        while (keep_slave_alive)
        {
            executor.spin_some(100ms);
        }

        // Log that the node has stopped spinning
        RCLCPP_INFO(get_node()->get_logger(), "Robot model loader node stopped spinning");
    });

    // Load the robot model using the robot model loader
    std::shared_ptr<const robot_model_loader::RobotModelLoader> robot_model_loader = std::make_shared<robot_model_loader::RobotModelLoader>(node, ros_params_.robot_description, true);

    // Retrieve the robot model
    kinematic_model_ = robot_model_loader->getModel();

    // Check if the robot model was loaded successfully
    if (kinematic_model_ == nullptr)
    {
        // Log an error if the robot model could not be loaded
        RCLCPP_ERROR(get_node()->get_logger(), "Failed to load robot model. Check that /robot_description and /robot_description_semantic are correctly set.");

        // Stop the robot model loader node
        keep_slave_alive = false;
        t.join();

        // Return error if robot model loading fails
        return CallbackReturn::ERROR;
    }

    // Log that the robot model has been loaded
    RCLCPP_INFO(get_node()->get_logger(), "Loaded robot model. Killing robot model loader node...");

    // Stop the robot model loader node
    keep_slave_alive = false;
    t.join();

    // Initialize the robot state with the loaded robot model
    kinematic_state_ = std::make_shared<moveit::core::RobotState>(kinematic_model_);

    // Get the joint model group from the robot model
    joint_model_group_ = kinematic_model_->getJointModelGroup(ros_params_.joint_model_group_name);

    // Retrieve the active joint names from the joint model group
    joint_names_ = joint_model_group_->getActiveJointModelNames();

    // Initialize joint limit vectors
    joint_lower_limits_ = Eigen::VectorXd(joint_names_.size());
    joint_upper_limits_ = Eigen::VectorXd(joint_names_.size());
    joint_default_values_ = Eigen::VectorXd(joint_names_.size());

    // Retrieve joint bounds from the joint model group
    const moveit::core::JointBoundsVector joint_bounds = joint_model_group_->getActiveJointModelsBounds();
    joint_model_group_->getVariableDefaultPositions(joint_default_values_.data());

    // Set joint limits based on the robot model
    for (size_t i = 0; i < joint_bounds.size(); i++)
    {
        const moveit::core::VariableBounds bounds = joint_bounds[i]->at(0);
        if (bounds.position_bounded_)
        {
            // Log the joint bounds if they are bounded
            RCLCPP_INFO(get_node()->get_logger(), "Joint %s bounds: [%f, %f]", joint_names_.at(i).c_str(), bounds.min_position_, bounds.max_position_);
            joint_lower_limits_(i) = bounds.min_position_;
            joint_upper_limits_(i) = bounds.max_position_;
        }
        else
        {
            // Log that the joint is unbounded
            RCLCPP_INFO(get_node()->get_logger(), "Joint %s is unbounded", joint_names_.at(i).c_str());
            joint_lower_limits_(i) = -std::numeric_limits<double>::infinity();
            joint_upper_limits_(i) = std::numeric_limits<double>::infinity();
        }
    }

    // Initialize actual joint positions, velocities, and end-effector state
    actual_joint_positions_ = Eigen::VectorXd(joint_names_.size());
    actual_joint_velocities_ = Eigen::VectorXd(joint_names_.size());
    actual_ee_position_ = Eigen::VectorXd(3);

    // Initialize the inverse dynamics solver
    solver_ = std::make_shared<inverse_dynamics_solver::InverseDynamicsSolverKDL>();

    // Set stiffness and damping gains
    stiffness_gains_ = Eigen::VectorXd(6);
    stiffness_gains_ << ros_params_.gains.stiffness.x, ros_params_.gains.stiffness.y, ros_params_.gains.stiffness.z, ros_params_.gains.stiffness.orientation_x, ros_params_.gains.stiffness.orientation_y, ros_params_.gains.stiffness.orientation_z;

    damping_gains_ = Eigen::VectorXd(6);
    // damping_gains_ = 2.0 * stiffness_gains_.cwiseSqrt();  // Damping gains are set proportional to stiffness gains
    damping_gains_ = 1.0 * stiffness_gains_.cwiseSqrt();  // Damping gains are set proportional to stiffness gains

    // Set nullspace stiffness and damping
    nullspace_stiffness_ = ros_params_.nullspace_stiffness;
    // nullspace_damping_ = 2.0 * sqrt(nullspace_stiffness_);
    nullspace_damping_ = 1.0 * sqrt(nullspace_stiffness_); 
    // Initialize desired joint positions
    desired_joint_positions_ = Eigen::VectorXd(joint_names_.size());
    for (size_t i = 0; i < joint_names_.size(); ++i)
    {
        desired_joint_positions_(i) = ros_params_.desired_joint_positions[i];
    }

    // Set the desired end-effector orientation in roll, pitch, and yaw
    desired_ee_orientation_rpy_ = Eigen::Vector3d(ros_params_.desired_orientation_rpy.roll, ros_params_.desired_orientation_rpy.pitch, ros_params_.desired_orientation_rpy.yaw);

    // Set the kinematic state to the desired joint positions
    kinematic_state_->setJointGroupPositions(joint_model_group_, desired_joint_positions_);
    kinematic_state_->update();

    // Get the current end-effector state
    const Eigen::Isometry3d &end_effector_state = kinematic_state_->getGlobalLinkTransform(ros_params_.end_effector_link);

    // Set the desired end-effector position and orientation
    desired_ee_position_ = end_effector_state.translation();
    desired_ee_orientation_ = Eigen::Quaterniond(Eigen::AngleAxisd(desired_ee_orientation_rpy_[0], Eigen::Vector3d::UnitX()) *
                                                Eigen::AngleAxisd(desired_ee_orientation_rpy_[1], Eigen::Vector3d::UnitY()) *
                                                Eigen::AngleAxisd(desired_ee_orientation_rpy_[2], Eigen::Vector3d::UnitZ()));

    // Log the desired end-effector position and orientation
    RCLCPP_INFO(get_node()->get_logger(), "Desired end-effector position task space: [%f, %f, %f]", desired_ee_position_(0), 
                                                                                                    desired_ee_position_(1), 
                                                                                                    desired_ee_position_(2));
    RCLCPP_INFO(get_node()->get_logger(), "Desired end-effector orientation (quaternion): [w: %f, x: %f, y: %f, z: %f]",
     desired_ee_orientation_.w(), desired_ee_orientation_.x(), desired_ee_orientation_.y(), desired_ee_orientation_.z());

    // Initialize joint efforts and torque limits
    tau_J_d = Eigen::VectorXd::Zero(joint_names_.size());
    delta_tau_max_ = 1.0;

    // Define the robot links for inverse dynamics
    std::vector<std::string> link_names = {ros_params_.robot_base_link, ros_params_.end_effector_link};

    // Initialize the inverse dynamics solver
    try
    {
        solver_->initialize(link_names);
    }
    catch (const std::exception &e)
    {
        RCLCPP_ERROR(get_node()->get_logger(), "Failed to initialize solver: %s", e.what());
        return CallbackReturn::ERROR;
    }

        // Create the action server for handling trajectory execution
    action_server_ = rclcpp_action::create_server<FollowCartesianTrajectoryAction>(
        get_node(), "panda_impedance_controller/follow_cartesian_trajectory",
        std::bind(&ImpedanceController::received_goal_trajectory_callback, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ImpedanceController::cancelled_goal_trajectory_callback, this, std::placeholders::_1),
        std::bind(&ImpedanceController::accepted_goal_trajectory_callback, this, std::placeholders::_1)
    );

    // Log that the controller was configured successfully
    RCLCPP_INFO(get_node()->get_logger(), "Controller configured successfully");

    // Set the configured flag to true
    is_configured = true;

    // Return success to indicate that the configuration was successful
    return CallbackReturn::SUCCESS;
}



/**
 * @brief Updates dynamic parameters of the controller if there are any changes in the parameter server.
 * 
 * This function checks if the parameters have been updated in the ROS parameter server and,
 * if so, updates the internal parameters of the impedance controller, including stiffness and
 * damping gains, nullspace stiffness, and damping, and computes the new desired end-effector
 * position and orientation based on the updated parameters.
 */
void ImpedanceController::update_dynamic_parameters()
{
    // Check if the parameters have changed using the parameter listener
    if (param_listener_->is_old(ros_params_))
    {
        // Retrieve the updated parameters
        ros_params_ = param_listener_->get_params();

        // Update stiffness gains based on new parameters
        stiffness_gains_ << ros_params_.gains.stiffness.x, ros_params_.gains.stiffness.y,
            ros_params_.gains.stiffness.z, ros_params_.gains.stiffness.orientation_x,
            ros_params_.gains.stiffness.orientation_y, ros_params_.gains.stiffness.orientation_z;

        // Update damping gains based on new stiffness gains
        // damping_gains_ = 1.0 * stiffness_gains_.cwiseSqrt();
        damping_gains_ = 1.0 * stiffness_gains_.cwiseSqrt();
        // Update nullspace stiffness and damping
        nullspace_stiffness_ = ros_params_.nullspace_stiffness;
        // nullspace_damping_ = 2.0 * sqrt(nullspace_stiffness_);
        nullspace_damping_ = 1.0 * sqrt(nullspace_stiffness_);

        // Update the robot's kinematic state with the new desired joint positions
        kinematic_state_->setJointGroupPositions(joint_model_group_, desired_joint_positions_);
        kinematic_state_->update();

        // Compute the new desired end-effector position and orientation
        const Eigen::Isometry3d &end_effector_state = kinematic_state_->getGlobalLinkTransform(ros_params_.end_effector_link);
        desired_ee_position_ = end_effector_state.translation();
        desired_ee_orientation_ = Eigen::Quaterniond(
            Eigen::AngleAxisd(desired_ee_orientation_rpy_[0], Eigen::Vector3d::UnitX()) *
            Eigen::AngleAxisd(desired_ee_orientation_rpy_[1], Eigen::Vector3d::UnitY()) *
            Eigen::AngleAxisd(desired_ee_orientation_rpy_[2], Eigen::Vector3d::UnitZ()));

        // Log updated parameters and states
        RCLCPP_INFO(get_node()->get_logger(), "Updated stiffness gains: [%f, %f, %f, %f, %f, %f]",
                    stiffness_gains_(0), stiffness_gains_(1), stiffness_gains_(2),
                    stiffness_gains_(3), stiffness_gains_(4), stiffness_gains_(5));
        RCLCPP_INFO(get_node()->get_logger(), "Updated damping gains: [%f, %f, %f, %f, %f, %f]",
                    damping_gains_(0), damping_gains_(1), damping_gains_(2),
                    damping_gains_(3), damping_gains_(4), damping_gains_(5));
        RCLCPP_INFO(get_node()->get_logger(), "Updated nullspace stiffness: [%f]", nullspace_stiffness_);
        RCLCPP_INFO(get_node()->get_logger(), "Current end-effector position: [%f, %f, %f]",
                    actual_ee_position_(0), actual_ee_position_(1), actual_ee_position_(2));
        RCLCPP_INFO(get_node()->get_logger(), "Desired end-effector position: [%f, %f, %f]",
                    desired_ee_position_(0), desired_ee_position_(1), desired_ee_position_(2));
        RCLCPP_INFO(get_node()->get_logger(), "Current end-effector orientation: [w: %f, x: %f, y: %f, z: %f]",
                    actual_ee_orientation_.w(), actual_ee_orientation_.x(),
                    actual_ee_orientation_.y(), actual_ee_orientation_.z());
        RCLCPP_INFO(get_node()->get_logger(), "Desired end-effector orientation: [w: %f, x: %f, y: %f, z: %f]",
                    desired_ee_orientation_.w(), desired_ee_orientation_.x(),
                    desired_ee_orientation_.y(), desired_ee_orientation_.z());
        RCLCPP_INFO(get_node()->get_logger(), "Gravity compensation: %s",
                    ros_params_.gravity_compensation ? "Enabled" : "Disabled");
    }
}


/**
 * @brief Saturates the rate of change in joint torques to avoid abrupt changes.
 * 
 * This function limits the difference between the desired torque and the current torque
 * to a specified maximum value (delta_tau_max), ensuring smooth transitions and avoiding
 * abrupt changes in joint efforts.
 * 
 * @param tau_d_calculated The desired joint torques.
 * @param tau_J_d The current joint torques.
 * @param delta_tau_max The maximum allowable change in joint torque per control loop.
 * @return Eigen::VectorXd The saturated joint torques.
 */
Eigen::VectorXd ImpedanceController::saturateTorqueRate(const Eigen::VectorXd &tau_d_calculated, const Eigen::VectorXd &tau_J_d, double delta_tau_max)
{
    // Ensure the size of the calculated and current torques are the same
    assert(tau_d_calculated.size() == tau_J_d.size());

    // Initialize the saturated torque vector with the current torque values
    Eigen::VectorXd tau_d_saturated = tau_J_d;

    // Loop through each joint to compute the saturated torque
    for (Eigen::Index i = 0; i < tau_d_calculated.size(); ++i)
    {
        // Compute the difference between the desired and current torque
        double difference = tau_d_calculated[i] - tau_J_d[i];

        // Saturate the torque difference to the maximum allowable change
        tau_d_saturated[i] = tau_J_d[i] + std::max(std::min(difference, delta_tau_max), -delta_tau_max);
    }

    // Return the saturated joint torques
    return tau_d_saturated;
}


/**
 * @brief Computes the joint efforts required to achieve the desired end-effector position and orientation.
 * 
 * This function calculates the necessary joint torques based on the position and orientation errors
 * between the desired and actual end-effector states. It also takes into account the task-space dynamics
 * defined by stiffness and damping gains, and includes nullspace control for redundancy resolution.
 * 
 * @param joint_space_effort Output vector for the computed joint efforts.
 * @param current_positions_eigen Current joint positions.
 * @param current_velocities_eigen Current joint velocities.
 */
void ImpedanceController::compute_effort(Eigen::VectorXd &joint_space_effort, const Eigen::VectorXd &current_positions_eigen, const Eigen::VectorXd &current_velocities_eigen)
{
    // Compute the position error between the desired and actual end-effector positions
    Eigen::VectorXd position_error = desired_ee_position_ - actual_ee_position_;

    // Debug: Print position error (this line is commented out, remove the comment to enable logging)
    // RCLCPP_INFO(get_node()->get_logger(), "Position error: [%f, %f, %f]", position_error(0), position_error(1), position_error(2));

    // Ensure quaternion sign consistency to avoid discontinuities in orientation representation
    if (desired_ee_orientation_.coeffs().dot(actual_ee_orientation_.coeffs()) < 0.0)
    {
        actual_ee_orientation_.coeffs() = -actual_ee_orientation_.coeffs();
    }

    // Compute the orientation error using quaternion difference
    // Eigen::Quaterniond error_quaternion = actual_ee_orientation_.inverse() * desired_ee_orientation_;
    Eigen::Quaterniond error_quaternion(actual_ee_orientation_ * desired_ee_orientation_.inverse());
    Eigen::VectorXd orientation_error(3);
    orientation_error << error_quaternion.x(), error_quaternion.y(), error_quaternion.z();
    // Convert quaternion error to a vector representation in the task space
    orientation_error = -actual_ee_orientation_.toRotationMatrix() * orientation_error;

    // Debug: Print orientation error (this line is commented out, remove the comment to enable logging)
    // RCLCPP_INFO(get_node()->get_logger(), "Orientation error: [%f, %f, %f]", orientation_error(0), orientation_error(1), orientation_error(2));

    // Compute task-space forces using proportional-derivative control
    Eigen::VectorXd f_task(6);
    f_task.head(3) = stiffness_gains_.head(3).asDiagonal() * position_error 
                     + damping_gains_.head(3).asDiagonal() * (-actual_ee_velocity_.head(3));
    f_task.tail(3) = stiffness_gains_.tail(3).asDiagonal() * orientation_error 
                     + damping_gains_.tail(3).asDiagonal() * (-actual_ee_velocity_.tail(3));

    // Debug: Print task-space forces (this line is commented out, remove the comment to enable logging)
    // RCLCPP_INFO(get_node()->get_logger(), "Task-space forces: [%f, %f, %f, %f, %f, %f]", f_task(0), f_task(1), f_task(2), f_task(3), f_task(4), f_task(5));

    // Compute the transpose of the Jacobian matrix
    Eigen::MatrixXd jacobian_transpose = actual_jacobian_.transpose();

    // Compute the pseudo-inverse of the Jacobian transpose
    Eigen::MatrixXd jacobian_transpose_pseudo_inverse = jacobian_transpose.completeOrthogonalDecomposition().pseudoInverse();
    Eigen::MatrixXd identity = Eigen::MatrixXd::Identity(joint_names_.size(), joint_names_.size());
    Eigen::VectorXd q_d_nullspace_ = desired_joint_positions_;
    Eigen::VectorXd manipulability_velocity;

    Eigen::VectorXd tau_nullspace = (identity - jacobian_transpose * jacobian_transpose_pseudo_inverse) *
                                    (nullspace_stiffness_ * (q_d_nullspace_ - current_positions_eigen) +
                                     nullspace_damping_ * (-current_velocities_eigen));


    // Calculate the total joint-space effort required
    joint_space_effort = jacobian_transpose * f_task + tau_nullspace;

    // Apply gravity compensation if enabled
    if (ros_params_.gravity_compensation)
    {
        joint_effort_ = joint_space_effort + coriolis_vector_ + gravity_vector_;
    }
    else
    {
        joint_effort_ = joint_space_effort + coriolis_vector_;
    }

    // Apply torque rate saturation to avoid abrupt changes in torque
    saturateTorqueRate(joint_effort_, tau_J_d, delta_tau_max_);
    tau_J_d = joint_effort_;  // Update the desired joint torque for the next iteration
}



/**
 * @brief Updates the state of the impedance controller at each time step.
 *
 * This function is called periodically to update the controller's internal state and compute the required
 * joint efforts to follow a desired trajectory or maintain a desired pose. It checks the current state, updates
 * dynamic parameters, reads the state interfaces, computes the control efforts, and applies them to the robot.
 *
 * @param time The current time.
 * @param period The duration of the control period.
 * @return controller_interface::return_type Returns OK if the update was successful, otherwise ERROR.
 */
controller_interface::return_type ImpedanceController::update(const rclcpp::Time &time, const rclcpp::Duration &period)
{
  // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  // Check if the controller is active. If not, return OK without performing any operations.
  if (!is_active)
  {
    return controller_interface::return_type::OK;
  }

  // Update dynamic parameters if needed (e.g., gains, stiffness).
  update_dynamic_parameters();
  
  // Read the current state of the robot from the hardware interfaces.
  read_state_interfaces();

  // Initialize vectors to store current joint positions and velocities.
  Eigen::VectorXd current_positions_eigen(joint_names_.size());
  Eigen::VectorXd current_velocities_eigen(joint_names_.size());
  
  // Populate the position and velocity vectors with data from the state interfaces.
  for (size_t i = 0; i < joint_names_.size(); ++i)
  {
    current_positions_eigen(i) = state_interfaces_[i].get_value();
    current_velocities_eigen(i) = state_interfaces_[i + joint_names_.size()].get_value();
  }

  try
  {
    // Compute the dynamic parameters such as gravity, inertia, and Coriolis effects.
    gravity_vector_ = solver_->getGravityVector(current_positions_eigen);
    // inertia_matrix_ = solver_->getInertiaMatrix(current_positions_eigen);
    coriolis_vector_ = solver_->getCoriolisVector(current_positions_eigen, current_velocities_eigen);
  }
  catch (const std::exception &e)
  {
    // Log an error message if there is a failure in computing dynamic parameters.
    RCLCPP_ERROR(get_node()->get_logger(), "Failed to compute dynamic parameters: %s", e.what());
    return controller_interface::return_type::ERROR;
  }

  // Check if the current state is not for executing a trajectory.
  if (active_state_ != State::trajectory_execution_impedance_control)
  {
    // Check if a new trajectory has been received.
    if (trajectory_received_)
    {
      // If the trajectory contains only one point, set the desired end-effector position and orientation.
      if (goal_trajectory_.points.size() == 1)
      {
        desired_ee_position_ = Eigen::Vector3d(
            goal_trajectory_.points[0].point.pose.position.x,
            goal_trajectory_.points[0].point.pose.position.y,
            goal_trajectory_.points[0].point.pose.position.z);

        desired_ee_orientation_ = Eigen::Quaterniond(
            goal_trajectory_.points[0].point.pose.orientation.w,
            goal_trajectory_.points[0].point.pose.orientation.x,
            goal_trajectory_.points[0].point.pose.orientation.y,
            goal_trajectory_.points[0].point.pose.orientation.z);

        // Change state to static impedance control.
        active_state_ = State::static_impedance_control;
      }
      else
      {
        // If the trajectory has multiple points, reset the internal time and start executing the trajectory.
        internal_time_ = rclcpp::Duration(0, 0);
        number_reached_trajectory_points_ = 0;
        active_state_ = State::trajectory_execution_impedance_control;
      }

      // Mark the trajectory as no longer received.
      trajectory_received_ = false;
    }
  }
  else // The controller is in the state to handle trajectory execution.
  {
    // Update the internal time by adding the current control period.
    internal_time_ = internal_time_ + period;
    
    // Update action feedback to provide real-time feedback to the action client.
    updateActionFeedback();

    // Start checking trajectory points to determine if we have reached or passed any new points.
    std::size_t i = number_reached_trajectory_points_;
    while (i < goal_trajectory_.points.size() && rclcpp::Duration(goal_trajectory_.points[i].time_from_start) <= internal_time_)
    {
      ++i;
    }

    // If a new trajectory point is reached, update the desired end-effector position and orientation.
    if (i > 0 && i != number_reached_trajectory_points_)
    {
      --i;
      number_reached_trajectory_points_ = i;

      desired_ee_position_ = Eigen::Vector3d(
          goal_trajectory_.points[number_reached_trajectory_points_].point.pose.position.x,
          goal_trajectory_.points[number_reached_trajectory_points_].point.pose.position.y,
          goal_trajectory_.points[number_reached_trajectory_points_].point.pose.position.z);
      desired_ee_orientation_ = Eigen::Quaterniond(
          goal_trajectory_.points[number_reached_trajectory_points_].point.pose.orientation.w,
          goal_trajectory_.points[number_reached_trajectory_points_].point.pose.orientation.x,
          goal_trajectory_.points[number_reached_trajectory_points_].point.pose.orientation.y,
          goal_trajectory_.points[number_reached_trajectory_points_].point.pose.orientation.z);

      waypoint_timestamp = rclcpp::Duration(goal_trajectory_.points[number_reached_trajectory_points_].time_from_start).seconds();
      internal_timestamp = internal_time_.seconds();
      
      // Debugging: Log information about the waypoint change.
      // RCLCPP_INFO(get_node()->get_logger(), "Waypoint %zu changed. Waypoint timestamp [sec: %f], Internal timestamp [sec: %f]",
      //             number_reached_trajectory_points_, waypoint_timestamp, internal_timestamp);
    }

    // If the last trajectory point is reached, log information and mark the action as successful.
    if (i == goal_trajectory_.points.size() - 1)
    {
      RCLCPP_INFO(get_node()->get_logger(), "Trajectory execution complete. Reached last waypoint.");

      // Log the current end-effector position.
      RCLCPP_INFO(get_node()->get_logger(), "Current end-effector position: [%f, %f, %f]", actual_ee_position_(0), actual_ee_position_(1), actual_ee_position_(2));
      
      // Log the current end-effector orientation.
      RCLCPP_INFO(get_node()->get_logger(), "Current end-effector orientation: [w: %f, x: %f, y: %f, z: %f]", actual_ee_orientation_.w(), actual_ee_orientation_.x(), actual_ee_orientation_.y(), actual_ee_orientation_.z());

      result_->success = true;  
      goal_handle_->succeed(result_);
      
      // Change state to static impedance control after trajectory execution.
      active_state_ = State::static_impedance_control;
    }
  }

  // Compute the joint-space effort required to achieve the desired end-effector position and orientation.
  compute_effort(joint_space_effort_, current_positions_eigen, current_velocities_eigen);
  
  // Set the computed joint efforts to the command interfaces.
  for (Eigen::Index i = 0; i < joint_effort_.size(); ++i)
  {
    command_interfaces_[i].set_value(joint_effort_(i));
  }
  // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  // double cycle_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;
  // RCLCPP_INFO(get_node()->get_logger(), "Cycle time: %f seconds", cycle_time);
  return controller_interface::return_type::OK;
}



/**
 * @brief Updates the feedback to the action client with the current state of the end-effector.
 *
 * This function publishes the current position and orientation of the end-effector as feedback
 * to the action client. It checks if the action server and goal handle are valid and active before
 * publishing the feedback.
 */
void ImpedanceController::updateActionFeedback()
{
  // Check if the action server or goal handle is not set, or if the goal is not active.
  // If any of these conditions are true, the function returns without doing anything.
  if (!action_server_ || !goal_handle_ || !goal_handle_->is_active())
  {
    return;
  }

  // Create a shared pointer for feedback of type FollowCartesianTrajectoryAction::Feedback.
  auto feedback = std::make_shared<FollowCartesianTrajectoryAction::Feedback>();

  // Update the feedback with the current end-effector position.
  feedback->actual.point.pose.position.x = actual_ee_position_(0);
  feedback->actual.point.pose.position.y = actual_ee_position_(1);
  feedback->actual.point.pose.position.z = actual_ee_position_(2);

  // Update the feedback with the current end-effector orientation.
  feedback->actual.point.pose.orientation.w = actual_ee_orientation_.w();
  feedback->actual.point.pose.orientation.x = actual_ee_orientation_.x();
  feedback->actual.point.pose.orientation.y = actual_ee_orientation_.y();
  feedback->actual.point.pose.orientation.z = actual_ee_orientation_.z();

  // Publish the feedback to the action client.
  goal_handle_->publish_feedback(feedback);
}



/**
 * @brief Reads the current state from the hardware interfaces and updates the kinematic state of the robot.
 *
 * This function retrieves the current joint positions and velocities from the hardware interfaces,
 * updates the internal kinematic state, and computes the current end-effector position, orientation,
 * and velocity using the Jacobian.
 */
void ImpedanceController::read_state_interfaces()
{
  // Loop through each joint and update the current positions and velocities from the state interfaces.
  for (unsigned int i = 0; i < joint_names_.size(); i++)
  {
    actual_joint_positions_(i) = joint_state_position_handles_[i].get().get_value();
    actual_joint_velocities_(i) = joint_state_velocity_handles_[i].get().get_value();
  }

  // Update the kinematic state with the current joint positions.
  kinematic_state_->setJointGroupPositions(joint_model_group_, actual_joint_positions_);
  kinematic_state_->update();

  // Get the current end-effector transformation (position and orientation) in space.
  Eigen::Isometry3d actual_ee_isometry = kinematic_state_->getGlobalLinkTransform(ros_params_.end_effector_link);
  actual_ee_position_(0) = actual_ee_isometry.translation().x();
  actual_ee_position_(1) = actual_ee_isometry.translation().y();
  actual_ee_position_(2) = actual_ee_isometry.translation().z();

  // Update the end-effector orientation as a quaternion.
  actual_ee_orientation_ = Eigen::Quaterniond(actual_ee_isometry.rotation());

  // Compute the Jacobian matrix for the current configuration.
  actual_jacobian_ = kinematic_state_->getJacobian(joint_model_group_);

  // Compute the end-effector velocity using the Jacobian and joint velocities.
  actual_ee_velocity_ = actual_jacobian_ * actual_joint_velocities_;
}


/**
 * @brief Checks and validates the required hardware interfaces for the controller.
 *
 * This function ensures that the necessary hardware interfaces for effort, position, and velocity
 * are available and correctly loaded. If any interface is missing or not in the expected order,
 * the function logs an error and returns an error status.
 *
 * @return controller_interface::CallbackReturn Returns SUCCESS if all interfaces are valid, otherwise ERROR.
 */
controller_interface::CallbackReturn ImpedanceController::check_interfaces()
{
  // Check if the effort command interfaces are available and correctly ordered.
  if (!controller_interface::get_ordered_interfaces(command_interfaces_, joint_names_, hardware_interface::HW_IF_EFFORT, joint_command_effort_handles_))
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Expected %zu effort command interfaces, got %zu.", joint_names_.size(), joint_command_effort_handles_.size());
    return CallbackReturn::ERROR;
  }
  else
  {
    RCLCPP_INFO(get_node()->get_logger(), "Effort command interfaces loaded successfully.");
  }

  // Check if the position state interfaces are available and correctly ordered.
  if (!controller_interface::get_ordered_interfaces(state_interfaces_, joint_names_, hardware_interface::HW_IF_POSITION, joint_state_position_handles_))
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Expected %zu position state interfaces, got %zu.", joint_names_.size(), joint_state_position_handles_.size());
    return CallbackReturn::ERROR;
  }
  else
  {
    RCLCPP_INFO(get_node()->get_logger(), "Position state interfaces loaded successfully.");
  }

  // Check if the velocity state interfaces are available and correctly ordered.
  if (!controller_interface::get_ordered_interfaces(state_interfaces_, joint_names_, hardware_interface::HW_IF_VELOCITY, joint_state_velocity_handles_))
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Expected %zu velocity state interfaces, got %zu.", joint_names_.size(), joint_state_velocity_handles_.size());
    return CallbackReturn::ERROR;
  }
  else
  {
    RCLCPP_INFO(get_node()->get_logger(), "Velocity state interfaces loaded successfully.");
  }

  // If all interfaces are valid, return SUCCESS.
  return CallbackReturn::SUCCESS;
}


/**
 * @brief Activates the impedance controller and prepares it for operation.
 *
 * This function is called when the controller is activated. It checks the necessary hardware interfaces,
 * reads the initial state from the robot, updates dynamic parameters, and sets the controller to active.
 *
 * @param previous_state The previous state of the controller (unused).
 * @return controller_interface::CallbackReturn Returns SUCCESS if the activation was successful, otherwise ERROR.
 */
controller_interface::CallbackReturn ImpedanceController::on_activate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(get_node()->get_logger(), "Activating controller");
  
  // If the controller is already active, return SUCCESS.
  if (is_active)
  {
    return CallbackReturn::SUCCESS;
  }

  // Check if all necessary hardware interfaces are available and valid.
  auto result = check_interfaces();
  if (result != CallbackReturn::SUCCESS)
  {
    return result;
  }

  // Read the current state from the hardware interfaces.
  read_state_interfaces();
  
  // Update any dynamic parameters that may have changed.
  update_dynamic_parameters();

  // Set the controller as active.
  is_active = true;
  RCLCPP_INFO(get_node()->get_logger(), "Controller activated ");

  // Return SUCCESS to indicate successful activation.
  return CallbackReturn::SUCCESS;
}


/**
 * @brief Deactivates the impedance controller and releases resources.
 *
 * This function is called when the controller is being deactivated. It clears the command and state handles,
 * releases any hardware interfaces, and sets the controller state to inactive.
 *
 * @param previous_state The previous state of the controller (unused).
 * @return controller_interface::CallbackReturn Returns SUCCESS if the deactivation was successful.
 */
controller_interface::CallbackReturn ImpedanceController::on_deactivate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  // Log message indicating the controller is being deactivated.
  RCLCPP_INFO(get_node()->get_logger(), "Deactivating controller");

  // Check if the controller is currently active.
  if (is_active)
  {
    // Clear all command and state handles to release the resources.
    joint_command_effort_handles_.clear();
    joint_state_position_handles_.clear();
    joint_state_velocity_handles_.clear();

    // Release any interfaces that were claimed during activation.
    release_interfaces();

    // Set the controller state to inactive.
    is_active = false;
  }

  // Log message indicating the controller has been successfully deactivated.
  RCLCPP_INFO(get_node()->get_logger(), "Controller deactivated");

  // Return SUCCESS to indicate successful deactivation.
  return CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn ImpedanceController::on_error(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_ERROR(get_node()->get_logger(), "Error in ImpedanceController. Moving to error state.");
  return CallbackReturn::SUCCESS;
}

/**
 * @brief Shuts down the impedance controller.
 *
 * This function is called when the controller is being shut down. It logs the shutdown event.
 *
 * @param previous_state The previous state of the controller (unused).
 * @return controller_interface::CallbackReturn Returns SUCCESS to indicate successful shutdown.
 */
controller_interface::CallbackReturn ImpedanceController::on_shutdown(const rclcpp_lifecycle::State & /*previous_state*/)
{
  // Log a message indicating the controller is shutting down.
  RCLCPP_INFO(get_node()->get_logger(), "Shutting down ImpedanceController.");

  // Return SUCCESS to indicate that the shutdown process was completed successfully.
  return CallbackReturn::SUCCESS;
}


/**
 * @brief Callback function to handle received goal trajectories for the impedance controller.
 *
 * This function is called when a new goal trajectory is received from the action client. It checks if the controller
 * is active, logs the received trajectory, and stores it for execution.
 *
 * @param uuid The unique identifier for the goal.
 * @param goal The goal message containing the trajectory.
 * @return rclcpp_action::GoalResponse Returns ACCEPT_AND_EXECUTE if the controller is active, otherwise REJECT.
 */
rclcpp_action::GoalResponse ImpedanceController::received_goal_trajectory_callback(
  const rclcpp_action::GoalUUID &uuid,
  std::shared_ptr<const FollowCartesianTrajectoryAction::Goal> goal)
{
  // Check if the controller is active. If not, log an error and reject the goal.
  if (!is_active)
  {
    RCLCPP_ERROR(get_node()->get_logger(), "Rejecting action goal because controller is not active");
    return rclcpp_action::GoalResponse::REJECT;
  }

  // Log a message indicating that a goal trajectory has been received.
  RCLCPP_INFO(get_node()->get_logger(), "Received goal trajectory");

  // Store the received trajectory in the controller's internal goal_trajectory_ variable.
  goal_trajectory_ = goal->trajectory;

  // Mark that a new trajectory has been received.
  trajectory_received_ = true;

  // Reset the internal time for trajectory execution.
  internal_time_ = rclcpp::Duration(0, 0);

  // Return ACCEPT_AND_EXECUTE to indicate that the goal has been accepted and will be executed.
  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}




/**
 * @brief Callback function to handle requests to cancel the current goal trajectory.
 *
 * This function is called when a cancellation request for the current goal is received.
 * It logs the cancellation request and accepts the cancellation.
 *
 * @param goal_handle The handle to the goal that is being cancelled.
 * @return rclcpp_action::CancelResponse Returns ACCEPT to indicate the cancellation request is accepted.
 */
rclcpp_action::CancelResponse ImpedanceController::cancelled_goal_trajectory_callback(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<FollowCartesianTrajectoryAction>> goal_handle)
{
  // Log the reception of a cancellation request for the goal.
  RCLCPP_INFO(get_node()->get_logger(), "Received request to cancel goal");

  // Log the UUID of the goal being cancelled for tracking and debugging purposes.
  RCLCPP_INFO(get_node()->get_logger(), "Cancelling goal with UUID: %s", rclcpp_action::to_string(goal_handle->get_goal_id()).c_str());

  // Suppress unused parameter warning by casting to void. 
  (void)goal_handle;

  // Return ACCEPT to indicate that the cancellation request is accepted.
  return rclcpp_action::CancelResponse::ACCEPT;
}


/**
 * @brief Callback function to handle the acceptance of a goal trajectory.
 *
 * This function is called when a new goal trajectory is accepted by the action server.
 * It initializes the goal handle and prepares the controller to execute the trajectory.
 *
 * @param goal_handle The handle to the accepted goal.
 */
void ImpedanceController::accepted_goal_trajectory_callback(
    std::shared_ptr<rclcpp_action::ServerGoalHandle<FollowCartesianTrajectoryAction>> goal_handle)
{
  // Log the acceptance of the goal with its UUID for tracking and debugging purposes.
  RCLCPP_INFO(get_node()->get_logger(), "Accepted goal with UUID: %s", rclcpp_action::to_string(goal_handle->get_goal_id()).c_str());

  // Log a message indicating that the goal has been accepted and trajectory execution will start.
  RCLCPP_INFO(get_node()->get_logger(), "Goal accepted. Executing trajectory.");

  // Initialize the goal handle and result with the accepted goal.
  goal_handle_ = goal_handle;
  result_ = std::make_shared<FollowCartesianTrajectoryAction::Result>();

  // Check if the controller is in a state to handle a static impedance control.
  if (active_state_ == State::static_impedance_control)
  {
      // Mark that a trajectory has been received from the action client.
      trajectory_received_ = true;
  }
}



} // namespace panda_impedance_controller

PLUGINLIB_EXPORT_CLASS(panda_impedance_controller::ImpedanceController, controller_interface::ControllerInterface)