// auto-generated DO NOT EDIT

#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <limits>
#include <mutex>
#include <rclcpp/node.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <rclcpp/logger.hpp>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <parameter_traits/parameter_traits.hpp>

#include <rsl/static_string.hpp>
#include <rsl/static_vector.hpp>
#include <rsl/parameter_validators.hpp>



namespace impedance_controller {

// Use validators from RSL
using rsl::unique;
using rsl::subset_of;
using rsl::fixed_size;
using rsl::size_gt;
using rsl::size_lt;
using rsl::not_empty;
using rsl::element_bounds;
using rsl::lower_element_bounds;
using rsl::upper_element_bounds;
using rsl::bounds;
using rsl::lt;
using rsl::gt;
using rsl::lt_eq;
using rsl::gt_eq;
using rsl::one_of;
using rsl::to_parameter_result_msg;

// temporarily needed for backwards compatibility for custom validators
using namespace parameter_traits;

template <typename T>
[[nodiscard]] auto to_parameter_value(T value) {
    return rclcpp::ParameterValue(value);
}

template <size_t capacity>
[[nodiscard]] auto to_parameter_value(rsl::StaticString<capacity> const& value) {
    return rclcpp::ParameterValue(rsl::to_string(value));
}

template <typename T, size_t capacity>
[[nodiscard]] auto to_parameter_value(rsl::StaticVector<T, capacity> const& value) {
    return rclcpp::ParameterValue(rsl::to_vector(value));
}
    struct Params {
        std::string robot_description = "robot_description";
        std::string robot_base_link;
        std::string end_effector_link;
        std::string joint_model_group_name;
        std::vector<double> desired_joint_positions;
        double nullspace_stiffness;
        bool gravity_compensation;
        bool use_nullspace_optimization = true;
        struct DesiredOrientationRpy {
            double roll;
            double pitch;
            double yaw;
        } desired_orientation_rpy;
        struct Gains {
            struct Stiffness {
                double x;
                double y;
                double z;
                double orientation_x;
                double orientation_y;
                double orientation_z;
            } stiffness;
        } gains;
        // for detecting if the parameter struct has been updated
        rclcpp::Time __stamp;
    };
    struct StackParams {
        double nullspace_stiffness;
        bool gravity_compensation;
        bool use_nullspace_optimization = true;
        struct DesiredOrientationRpy {
            double roll;
            double pitch;
            double yaw;
        } desired_orientation_rpy;
        struct Gains {
            struct Stiffness {
                double x;
                double y;
                double z;
                double orientation_x;
                double orientation_y;
                double orientation_z;
            } stiffness;
        } gains;
    };

  class ParamListener{
  public:
    // throws rclcpp::exceptions::InvalidParameterValueException on initialization if invalid parameter are loaded
    ParamListener(rclcpp::Node::SharedPtr node, std::string const& prefix = "")
    : ParamListener(node->get_node_parameters_interface(), node->get_logger(), prefix) {}

    ParamListener(rclcpp_lifecycle::LifecycleNode::SharedPtr node, std::string const& prefix = "")
    : ParamListener(node->get_node_parameters_interface(), node->get_logger(), prefix) {}

    ParamListener(const std::shared_ptr<rclcpp::node_interfaces::NodeParametersInterface>& parameters_interface,
                  std::string const& prefix = "")
    : ParamListener(parameters_interface, rclcpp::get_logger("impedance_controller"), prefix) {
      RCLCPP_DEBUG(logger_, "ParameterListener: Not using node logger, recommend using other constructors to use a node logger");
    }

    ParamListener(const std::shared_ptr<rclcpp::node_interfaces::NodeParametersInterface>& parameters_interface,
                  rclcpp::Logger logger, std::string const& prefix = "") {
      logger_ = logger;
      prefix_ = prefix;
      if (!prefix_.empty() && prefix_.back() != '.') {
        prefix_ += ".";
      }

      parameters_interface_ = parameters_interface;
      declare_params();
      auto update_param_cb = [this](const std::vector<rclcpp::Parameter> &parameters){return this->update(parameters);};
      handle_ = parameters_interface_->add_on_set_parameters_callback(update_param_cb);
      clock_ = rclcpp::Clock();
    }

    Params get_params() const{
      std::lock_guard<std::mutex> lock(mutex_);
      return params_;
    }

    bool is_old(Params const& other) const {
      std::lock_guard<std::mutex> lock(mutex_);
      return params_.__stamp != other.__stamp;
    }

    StackParams get_stack_params() {
      Params params = get_params();
      StackParams output;
      output.desired_orientation_rpy.roll = params.desired_orientation_rpy.roll;
      output.desired_orientation_rpy.pitch = params.desired_orientation_rpy.pitch;
      output.desired_orientation_rpy.yaw = params.desired_orientation_rpy.yaw;
      output.gains.stiffness.x = params.gains.stiffness.x;
      output.gains.stiffness.y = params.gains.stiffness.y;
      output.gains.stiffness.z = params.gains.stiffness.z;
      output.gains.stiffness.orientation_x = params.gains.stiffness.orientation_x;
      output.gains.stiffness.orientation_y = params.gains.stiffness.orientation_y;
      output.gains.stiffness.orientation_z = params.gains.stiffness.orientation_z;
      output.nullspace_stiffness = params.nullspace_stiffness;
      output.gravity_compensation = params.gravity_compensation;
      output.use_nullspace_optimization = params.use_nullspace_optimization;

      return output;
    }

    void refresh_dynamic_parameters() {
      auto updated_params = get_params();
      // TODO remove any destroyed dynamic parameters

      // declare any new dynamic parameters
      rclcpp::Parameter param;

    }

    rcl_interfaces::msg::SetParametersResult update(const std::vector<rclcpp::Parameter> &parameters) {
      auto updated_params = get_params();

      for (const auto &param: parameters) {
        if (param.get_name() == (prefix_ + "robot_description")) {
            updated_params.robot_description = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "robot_base_link")) {
            updated_params.robot_base_link = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "end_effector_link")) {
            updated_params.end_effector_link = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "joint_model_group_name")) {
            updated_params.joint_model_group_name = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "desired_joint_positions")) {
            updated_params.desired_joint_positions = param.as_double_array();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "desired_orientation_rpy.roll")) {
            updated_params.desired_orientation_rpy.roll = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "desired_orientation_rpy.pitch")) {
            updated_params.desired_orientation_rpy.pitch = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "desired_orientation_rpy.yaw")) {
            updated_params.desired_orientation_rpy.yaw = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "gains.stiffness.x")) {
            updated_params.gains.stiffness.x = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "gains.stiffness.y")) {
            updated_params.gains.stiffness.y = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "gains.stiffness.z")) {
            updated_params.gains.stiffness.z = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "gains.stiffness.orientation_x")) {
            updated_params.gains.stiffness.orientation_x = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "gains.stiffness.orientation_y")) {
            updated_params.gains.stiffness.orientation_y = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "gains.stiffness.orientation_z")) {
            updated_params.gains.stiffness.orientation_z = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "nullspace_stiffness")) {
            updated_params.nullspace_stiffness = param.as_double();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "gravity_compensation")) {
            updated_params.gravity_compensation = param.as_bool();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "use_nullspace_optimization")) {
            updated_params.use_nullspace_optimization = param.as_bool();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
      }

      updated_params.__stamp = clock_.now();
      update_internal_params(updated_params);
      return rsl::to_parameter_result_msg({});
    }

    void declare_params(){
      auto updated_params = get_params();
      // declare all parameters and give default values to non-required ones
      if (!parameters_interface_->has_parameter(prefix_ + "robot_description")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Name of the topic where the robot_description is published";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.robot_description);
          parameters_interface_->declare_parameter(prefix_ + "robot_description", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "robot_base_link")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The base link of the robot used as the reference frame for calculations";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_STRING;
          parameters_interface_->declare_parameter(prefix_ + "robot_base_link", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "end_effector_link")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The link of the robot that acts as the end effector";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_STRING;
          parameters_interface_->declare_parameter(prefix_ + "end_effector_link", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "joint_model_group_name")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The joint model group for which the controller is configured";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_STRING;
          parameters_interface_->declare_parameter(prefix_ + "joint_model_group_name", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "desired_joint_positions")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The desired positions for each joint in the joint space";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE_ARRAY;
          parameters_interface_->declare_parameter(prefix_ + "desired_joint_positions", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "desired_orientation_rpy.roll")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Desired roll angle of the end-effector in radians";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "desired_orientation_rpy.roll", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "desired_orientation_rpy.pitch")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Desired pitch angle of the end-effector in radians";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "desired_orientation_rpy.pitch", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "desired_orientation_rpy.yaw")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Desired yaw angle of the end-effector in radians";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "desired_orientation_rpy.yaw", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "gains.stiffness.x")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Stiffness of the impedance controller along the x-axis";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "gains.stiffness.x", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "gains.stiffness.y")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Stiffness of the impedance controller along the y-axis";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "gains.stiffness.y", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "gains.stiffness.z")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Stiffness of the impedance controller along the z-axis";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "gains.stiffness.z", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "gains.stiffness.orientation_x")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Stiffness of the impedance controller for orientation about the x-axis";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "gains.stiffness.orientation_x", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "gains.stiffness.orientation_y")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Stiffness of the impedance controller for orientation about the y-axis";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "gains.stiffness.orientation_y", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "gains.stiffness.orientation_z")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Stiffness of the impedance controller for orientation about the z-axis";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "gains.stiffness.orientation_z", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "nullspace_stiffness")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_DOUBLE;
          parameters_interface_->declare_parameter(prefix_ + "nullspace_stiffness", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "gravity_compensation")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Flag to determine whether to calculate gravity compensation in the control law";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_BOOL;
          parameters_interface_->declare_parameter(prefix_ + "gravity_compensation", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "use_nullspace_optimization")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "Whether or not to use nullspace optimization during trajectory execution.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.use_nullspace_optimization);
          parameters_interface_->declare_parameter(prefix_ + "use_nullspace_optimization", parameter, descriptor);
      }
      // get parameters and fill struct fields
      rclcpp::Parameter param;
      param = parameters_interface_->get_parameter(prefix_ + "robot_description");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.robot_description = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "robot_base_link");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.robot_base_link = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "end_effector_link");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.end_effector_link = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "joint_model_group_name");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.joint_model_group_name = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "desired_joint_positions");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.desired_joint_positions = param.as_double_array();
      param = parameters_interface_->get_parameter(prefix_ + "desired_orientation_rpy.roll");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.desired_orientation_rpy.roll = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "desired_orientation_rpy.pitch");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.desired_orientation_rpy.pitch = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "desired_orientation_rpy.yaw");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.desired_orientation_rpy.yaw = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "gains.stiffness.x");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.gains.stiffness.x = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "gains.stiffness.y");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.gains.stiffness.y = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "gains.stiffness.z");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.gains.stiffness.z = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "gains.stiffness.orientation_x");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.gains.stiffness.orientation_x = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "gains.stiffness.orientation_y");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.gains.stiffness.orientation_y = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "gains.stiffness.orientation_z");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.gains.stiffness.orientation_z = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "nullspace_stiffness");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.nullspace_stiffness = param.as_double();
      param = parameters_interface_->get_parameter(prefix_ + "gravity_compensation");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.gravity_compensation = param.as_bool();
      param = parameters_interface_->get_parameter(prefix_ + "use_nullspace_optimization");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.use_nullspace_optimization = param.as_bool();


      updated_params.__stamp = clock_.now();
      update_internal_params(updated_params);
    }

    private:
      void update_internal_params(Params updated_params) {
        std::lock_guard<std::mutex> lock(mutex_);
        params_ = updated_params;
      }

      std::string prefix_;
      Params params_;
      rclcpp::Clock clock_;
      std::shared_ptr<rclcpp::node_interfaces::OnSetParametersCallbackHandle> handle_;
      std::shared_ptr<rclcpp::node_interfaces::NodeParametersInterface> parameters_interface_;

      // rclcpp::Logger cannot be default-constructed
      // so we must provide a initialization here even though
      // every one of our constructors initializes logger_
      rclcpp::Logger logger_ = rclcpp::get_logger("impedance_controller");
      std::mutex mutable mutex_;
  };

} // namespace impedance_controller
