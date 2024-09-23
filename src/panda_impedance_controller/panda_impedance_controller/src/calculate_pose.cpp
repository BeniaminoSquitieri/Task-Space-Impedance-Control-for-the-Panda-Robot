#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_model/robot_model.h>
#include <Eigen/Geometry>

class ComputeForwardKinematics : public rclcpp::Node {
public:
  ComputeForwardKinematics() : Node("compute_forward_kinematics") {
    auto node = std::make_shared<rclcpp::Node>("robot_model_loader_node");
    robot_model_loader::RobotModelLoader robot_model_loader(node, "robot_description");
    robot_model_ = robot_model_loader.getModel();
    
    if (!robot_model_) {
      RCLCPP_ERROR(get_logger(), "Failed to load robot model");
      return;
    }
    
    RCLCPP_INFO(this->get_logger(), "Model frame: %s", robot_model_->getModelFrame().c_str());

    kinematic_state_ = std::make_shared<moveit::core::RobotState>(robot_model_);
    kinematic_state_->setToDefaultValues();

    joint_model_group_ = robot_model_->getJointModelGroup("panda_arm");

    if (!joint_model_group_) {
      RCLCPP_ERROR(get_logger(), "Failed to get joint model group");
      return;
    }

    const std::vector<std::string>& joint_names = joint_model_group_->getVariableNames();
    RCLCPP_INFO(this->get_logger(), "Joint names:");
    for (const auto& joint_name : joint_names) {
      RCLCPP_INFO(this->get_logger(), "%s", joint_name.c_str());
    }

    // Initialize joint values with default values
    joint_values_ = std::vector<double>(joint_model_group_->getVariableCount(), 0.0);

    // Create a subscriber to the joint_states topic
    joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>(
      "/joint_states", 10,
      std::bind(&ComputeForwardKinematics::jointStateCallback, this, std::placeholders::_1)
    );
  }

private:
  void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) {
    const std::vector<std::string>& joint_names = joint_model_group_->getVariableNames();
    for (size_t i = 0; i < joint_names.size(); ++i) {
      auto it = std::find(msg->name.begin(), msg->name.end(), joint_names[i]);
      if (it != msg->name.end()) {
        size_t index = std::distance(msg->name.begin(), it);
        joint_values_[i] = msg->position[index];
      }
    }

    kinematic_state_->setJointGroupPositions(joint_model_group_, joint_values_);

    const Eigen::Isometry3d& end_effector_state = kinematic_state_->getGlobalLinkTransform("panda_link8");

    // Extract translation and rotation
    Eigen::Vector3d translation = end_effector_state.translation();
    Eigen::Matrix3d rotation = end_effector_state.rotation();

    // Convert rotation matrix to quaternion
    Eigen::Quaterniond quaternion(rotation);

    // Convert rotation matrix to Euler angles (Roll, Pitch, Yaw)
    Eigen::Vector3d euler_angles = rotation.eulerAngles(0, 1, 2);

    // Log translation, quaternion, and Euler angles
    std::ostringstream translation_stream;
    translation_stream << translation.format(Eigen::IOFormat(Eigen::FullPrecision));
    RCLCPP_INFO(this->get_logger(), "Translation: \n%s", translation_stream.str().c_str());

    RCLCPP_INFO(this->get_logger(), "Quaternion: x=%f, y=%f, z=%f, w=%f", quaternion.x(), quaternion.y(), quaternion.z(), quaternion.w());
    RCLCPP_INFO(this->get_logger(), "Euler angles: roll=%f, pitch=%f, yaw=%f", euler_angles[0], euler_angles[1], euler_angles[2]);
  }

  moveit::core::RobotModelPtr robot_model_;
  moveit::core::RobotStatePtr kinematic_state_;
  const moveit::core::JointModelGroup* joint_model_group_;
  std::vector<double> joint_values_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ComputeForwardKinematics>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
