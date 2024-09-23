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



namespace task_space_client_utils {

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
        std::string planning_group = "panda_arm";
        std::string controller_name;
        std::string base_frame = "world";
        std::string executed_trajectory_file = "executed_line_trajectory";
        std::string planned_trajectory_file = "planned_line_trajectory";
        std::string input_bag_file_topic = "cartesian_path";
        struct PlannedTrajectoriesTopic {
            std::string p2p = "/planned_point_to_point";
            std::string ready = "/planned_ready_feedback";
            std::string cartesian = "/planned_panda_feed";
        } planned_trajectories_topic;
        struct ExecutedTrajectoriesTopic {
            std::string ready_topic = "/ready_feedback";
            std::string p2p_recorded_topic = "/point_to_point";
            std::string cartesian_topic = "/panda_feed";
        } executed_trajectories_topic;
        struct EstablishedPoses {
            std::string ready_pose = "ready";
        } established_poses;
        // for detecting if the parameter struct has been updated
        rclcpp::Time __stamp;
    };
    struct StackParams {
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
    : ParamListener(parameters_interface, rclcpp::get_logger("task_space_client_utils"), prefix) {
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
        if (param.get_name() == (prefix_ + "planning_group")) {
            updated_params.planning_group = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "controller_name")) {
            updated_params.controller_name = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "base_frame")) {
            updated_params.base_frame = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "executed_trajectory_file")) {
            updated_params.executed_trajectory_file = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "planned_trajectory_file")) {
            updated_params.planned_trajectory_file = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "planned_trajectories_topic.p2p")) {
            updated_params.planned_trajectories_topic.p2p = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "planned_trajectories_topic.ready")) {
            updated_params.planned_trajectories_topic.ready = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "planned_trajectories_topic.cartesian")) {
            updated_params.planned_trajectories_topic.cartesian = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "input_bag_file_topic")) {
            updated_params.input_bag_file_topic = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "executed_trajectories_topic.ready_topic")) {
            updated_params.executed_trajectories_topic.ready_topic = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "executed_trajectories_topic.p2p_recorded_topic")) {
            updated_params.executed_trajectories_topic.p2p_recorded_topic = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "executed_trajectories_topic.cartesian_topic")) {
            updated_params.executed_trajectories_topic.cartesian_topic = param.as_string();
            RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
        }
        if (param.get_name() == (prefix_ + "established_poses.ready_pose")) {
            updated_params.established_poses.ready_pose = param.as_string();
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
      if (!parameters_interface_->has_parameter(prefix_ + "planning_group")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The name of the planning group for which motion planning is to be performed.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.planning_group);
          parameters_interface_->declare_parameter(prefix_ + "planning_group", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "controller_name")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The name of the motion controller.";
          descriptor.read_only = false;
          auto parameter = rclcpp::ParameterType::PARAMETER_STRING;
          parameters_interface_->declare_parameter(prefix_ + "controller_name", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "base_frame")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The reference frame for the robot's base.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.base_frame);
          parameters_interface_->declare_parameter(prefix_ + "base_frame", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "executed_trajectory_file")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The name of the file where executed trajectory data is saved.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.executed_trajectory_file);
          parameters_interface_->declare_parameter(prefix_ + "executed_trajectory_file", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "planned_trajectory_file")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The name of the file where executed trajectory data is saved.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.planned_trajectory_file);
          parameters_interface_->declare_parameter(prefix_ + "planned_trajectory_file", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "planned_trajectories_topic.p2p")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The topic for saving the planned trajectory in the bag file.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.planned_trajectories_topic.p2p);
          parameters_interface_->declare_parameter(prefix_ + "planned_trajectories_topic.p2p", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "planned_trajectories_topic.ready")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The topic for feedback on the trajectory to the ready pose.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.planned_trajectories_topic.ready);
          parameters_interface_->declare_parameter(prefix_ + "planned_trajectories_topic.ready", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "planned_trajectories_topic.cartesian")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The topic for feedback on cartesian trajectories executed by the robot.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.planned_trajectories_topic.cartesian);
          parameters_interface_->declare_parameter(prefix_ + "planned_trajectories_topic.cartesian", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "input_bag_file_topic")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The topic name for the input bag file containing path data.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.input_bag_file_topic);
          parameters_interface_->declare_parameter(prefix_ + "input_bag_file_topic", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "executed_trajectories_topic.ready_topic")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The topic for feedback on the trajectory to the ready pose.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.executed_trajectories_topic.ready_topic);
          parameters_interface_->declare_parameter(prefix_ + "executed_trajectories_topic.ready_topic", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "executed_trajectories_topic.p2p_recorded_topic")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The topic for feedback on point-to-point trajectories.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.executed_trajectories_topic.p2p_recorded_topic);
          parameters_interface_->declare_parameter(prefix_ + "executed_trajectories_topic.p2p_recorded_topic", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "executed_trajectories_topic.cartesian_topic")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The topic for feedback on cartesian trajectories executed by the robot.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.executed_trajectories_topic.cartesian_topic);
          parameters_interface_->declare_parameter(prefix_ + "executed_trajectories_topic.cartesian_topic", parameter, descriptor);
      }
      if (!parameters_interface_->has_parameter(prefix_ + "established_poses.ready_pose")) {
          rcl_interfaces::msg::ParameterDescriptor descriptor;
          descriptor.description = "The robot's named position for its 'ready' pose.";
          descriptor.read_only = false;
          auto parameter = to_parameter_value(updated_params.established_poses.ready_pose);
          parameters_interface_->declare_parameter(prefix_ + "established_poses.ready_pose", parameter, descriptor);
      }
      // get parameters and fill struct fields
      rclcpp::Parameter param;
      param = parameters_interface_->get_parameter(prefix_ + "planning_group");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.planning_group = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "controller_name");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.controller_name = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "base_frame");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.base_frame = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "executed_trajectory_file");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.executed_trajectory_file = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "planned_trajectory_file");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.planned_trajectory_file = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "planned_trajectories_topic.p2p");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.planned_trajectories_topic.p2p = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "planned_trajectories_topic.ready");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.planned_trajectories_topic.ready = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "planned_trajectories_topic.cartesian");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.planned_trajectories_topic.cartesian = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "input_bag_file_topic");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.input_bag_file_topic = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "executed_trajectories_topic.ready_topic");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.executed_trajectories_topic.ready_topic = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "executed_trajectories_topic.p2p_recorded_topic");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.executed_trajectories_topic.p2p_recorded_topic = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "executed_trajectories_topic.cartesian_topic");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.executed_trajectories_topic.cartesian_topic = param.as_string();
      param = parameters_interface_->get_parameter(prefix_ + "established_poses.ready_pose");
      RCLCPP_DEBUG_STREAM(logger_, param.get_name() << ": " << param.get_type_name() << " = " << param.value_to_string());
      updated_params.established_poses.ready_pose = param.as_string();


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
      rclcpp::Logger logger_ = rclcpp::get_logger("task_space_client_utils");
      std::mutex mutable mutex_;
  };

} // namespace task_space_client_utils
