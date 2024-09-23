#include "moveit_utils.hpp"

/**
 * @brief Displays a title in the RViz viewer.
 * 
 * This function draws text (a title) in the RViz viewer using the `MoveItVisualTools` class.
 * The text is positioned 1.5 meters above the robot's base link.
 * 
 * @param moveit_visual_tools Reference to a `MoveItVisualTools` object used to publish the text.
 * @param text Text to display in the viewer.
 */
void draw_title(moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, const std::string& text)
{
  auto const text_pose = [] {
    auto msg = Eigen::Isometry3d::Identity();
    msg.translation().z() = 1.5;  // Place text 1.5m above the base link
    return msg;
  }();
  moveit_visual_tools.publishText(text_pose, text, rviz_visual_tools::WHITE, rviz_visual_tools::XLARGE);
}

/**
 * @brief Shows a prompt in the RViz viewer.
 * 
 * Prompts the user to interact with the RViz viewer, waiting for input from the RViz GUI.
 * 
 * @param moveit_visual_tools Reference to a `MoveItVisualTools` object used to display the prompt.
 * @param text Text of the prompt to display.
 */
void prompt(moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, const std::string& text)
{
  moveit_visual_tools.prompt(text);
}

/**
 * @brief Displays the planned trajectory in the RViz viewer.
 * 
 * This function publishes the robot's planned trajectory line in the RViz viewer.
 * 
 * @param moveit_visual_tools Reference to a `MoveItVisualTools` object used to publish the trajectory.
 * @param plan The trajectory plan to display.
 * @param jmg Joint Model Group of the robot used for planning.
 */
void draw_trajectory_tool_path(moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, const moveit::planning_interface::MoveGroupInterface::Plan& plan, const moveit::core::JointModelGroup* jmg)
{
  moveit_visual_tools.publishTrajectoryLine(plan.trajectory_, jmg);
}

/**
 * @brief Executes the planned trajectory.
 * 
 * This function checks the success of the planning and, if successful, visualizes and executes the trajectory.
 * If the planning fails, it shows an error message.
 * 
 * @param logger ROS2 logger for printing messages.
 * @param move_group_interface MoveGroup interface for executing the plan.
 * @param moveit_visual_tools MoveIt visualization tool to display the trajectory.
 * @param success Flag indicating whether the planning was successfully completed.
 * @param plan The trajectory plan to execute.
 */
void execute(const rclcpp::Logger& logger, moveit::planning_interface::MoveGroupInterface& move_group_interface, moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, bool success, const moveit::planning_interface::MoveGroupInterface::Plan& plan)
{
  if (success)
  {
    draw_trajectory_tool_path(moveit_visual_tools, plan, move_group_interface.getRobotModel()->getJointModelGroup("panda_arm"));
    moveit_visual_tools.trigger();
    draw_title(moveit_visual_tools, "Executing");
    moveit_visual_tools.trigger();
    move_group_interface.execute(plan);
  }
  else
  {
    draw_title(moveit_visual_tools, "Planning Failed!");
    moveit_visual_tools.trigger();
    RCLCPP_ERROR(logger, "Planning failed!");
  }
}

/**
 * @brief Displays a path of poses in the RViz viewer.
 * 
 * Publishes a specified path of poses in the RViz viewer for visualization.
 * 
 * @param moveit_visual_tools MoveIt visualization tool to publish the path.
 * @param path_poses Shared pointer to PoseArray representing the path to visualize.
 */
void visualize_path(moveit_visual_tools::MoveItVisualTools &moveit_visual_tools, const std::shared_ptr<geometry_msgs::msg::PoseArray> path_poses){
  moveit_visual_tools.publishPath(path_poses->poses);
  moveit_visual_tools.trigger();
}

/**
 * @brief Removes all collision objects from the planning scene.
 * 
 * This function removes all currently present collision objects from the planning scene.
 * 
 * @param planning_scene_interface Planning scene interface to remove collision objects.
 */
void remove_collision_objects(moveit::planning_interface::PlanningSceneInterface& planning_scene_interface)
{
  std::vector<std::string> keys;
  for (auto entry : planning_scene_interface.getObjects())
    keys.push_back(entry.first);
  planning_scene_interface.removeCollisionObjects(keys);
}

/**
 * @brief Displays the planned trajectory in the RViz viewer.
 * 
 * Publishes the line of the planned trajectory for a specific planning group in the RViz viewer.
 * 
 * @param moveit_visual_tools MoveIt visualization tool to publish the trajectory.
 * @param move_group_interface MoveGroup interface used for planning.
 * @param planning_group Name of the planning group used.
 * @param trajectory The planned trajectory to display.
 */
void display_planned_trajectory(moveit_visual_tools::MoveItVisualTools &moveit_visual_tools, moveit::planning_interface::MoveGroupInterface &move_group_interface, const std::string &planning_group, const moveit_msgs::msg::RobotTrajectory &trajectory){
  const moveit::core::RobotModelConstPtr robot_model = move_group_interface.getRobotModel();
  const moveit::core::JointModelGroup *jmg = robot_model->getJointModelGroup(planning_group);
  const moveit::core::LinkModel *link = robot_model->getLinkModel(move_group_interface.getEndEffectorLink());
  moveit_visual_tools.publishTrajectoryLine(trajectory, link, jmg);
  moveit_visual_tools.trigger();
}

/**
 * @brief Adds collision objects to the planning scene.
 * 
 * This function adds a collision object (a box) to the planning scene to avoid collisions during path planning.
 * 
 * @param planning_scene_interface Planning scene interface to add collision objects.
 */
void add_collision_objects(moveit::planning_interface::PlanningSceneInterface& planning_scene_interface)
{
  std::vector<moveit_msgs::msg::CollisionObject> collision_objects;
  collision_objects.resize(1);

  // Define the collision object for the box
  collision_objects[0].id = "box1";
  collision_objects[0].header.frame_id = "panda_link0";

  // Define the shape and size of the box
  shape_msgs::msg::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  primitive.dimensions[0] = 0.4;
  primitive.dimensions[1] = 0.1;
  primitive.dimensions[2] = 0.4;

  // Define the pose of the box (relative to panda_link0)
  geometry_msgs::msg::Pose box_pose;
  box_pose.orientation.w = 1.0;
  box_pose.position.x = 0.6;
  box_pose.position.y = 0.0;
  box_pose.position.z = 0.2;

  collision_objects[0].primitives.push_back(primitive);
  collision_objects[0].primitive_poses.push_back(box_pose);
  collision_objects[0].operation = collision_objects[0].ADD;

  planning_scene_interface.applyCollisionObjects(collision_objects);
}

/**
 * @brief Publishes waypoints in the RViz viewer.
 * 
 * Displays the specified waypoints as colored spheres in the RViz viewer.
 * 
 * @param moveit_visual_tools MoveIt visualization tool to publish the waypoints.
 * @param waypoints Vector of poses representing the waypoints to display.
 */
void publish_waypoints(moveit_visual_tools::MoveItVisualTools& moveit_visual_tools, const std::vector<geometry_msgs::msg::Pose>& waypoints)
{
    for (const auto& waypoint : waypoints) {
        moveit_visual_tools.publishSphere(waypoint, rviz_visual_tools::BLUE, rviz_visual_tools::LARGE);
    }
    moveit_visual_tools.trigger();
}
