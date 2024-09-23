#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_state/conversions.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit_utils.hpp>

int main(int argc, char* argv[])
{
    // Initialize ROS
    rclcpp::init(argc, argv);

    // Create the node and iterate through node's parameter overrides
    auto const node = std::make_shared<rclcpp::Node>("panda_moveit_planning_demo", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

    // Create a ROS logger
    auto const logger = rclcpp::get_logger("panda_moveit_planning_demo");

    // Start an AsyncSpinner before creating the MoveGroupInterface
    rclcpp::executors::MultiThreadedExecutor executor;
    std::thread spinner_thread([&executor, node]() {
        executor.add_node(node);
        executor.spin();
    });

    // Load the robot model using robot_model_loader
    std::shared_ptr<const robot_model_loader::RobotModelLoader> robot_model_loader = std::make_shared<robot_model_loader::RobotModelLoader>(node, "robot_description", true);
    auto kinematic_model = robot_model_loader->getModel();

    if (kinematic_model == nullptr)
    {
        RCLCPP_ERROR(logger, "Failed to load robot model. Check that /robot_description and /robot_description_semantic are correctly set.");
        rclcpp::shutdown();
        return 1;
    }

    RCLCPP_INFO(logger, "Loaded robot model.");

    // Construct and initialize MoveItVisualTools
    auto moveit_visual_tools = moveit_visual_tools::MoveItVisualTools{ node, "panda_link0", rviz_visual_tools::RVIZ_MARKER_TOPIC, kinematic_model };
    moveit_visual_tools.loadRemoteControl();

    // Construct a planning scene interface to manage objects in the scene
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

    // Create the MoveIt MoveGroup Interface
    using moveit::planning_interface::MoveGroupInterface;
    auto move_group_interface = MoveGroupInterface(node, "panda_arm");

    //*******************************************************************
    // PLAN TO A TARGET JOINT-SPACE CONFIGURATION
    //*******************************************************************

    // Wait for user input, then clean the scene from previous executions
    prompt(moveit_visual_tools, "Press 'Next' in the RvizVisualToolsGui window to plan to the target joint-space configuration");
    moveit_visual_tools.deleteAllMarkers();
    draw_title(moveit_visual_tools, "Planning");
    moveit_visual_tools.trigger();
    remove_collision_objects(planning_scene_interface);

    // Set a target joint-space configuration
    auto const target_joints_1 = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.571 };
    bool within_bounds = move_group_interface.setJointValueTarget(target_joints_1);
    if (!within_bounds)
    {
        RCLCPP_WARN(logger, "Target joint position(s) were outside of limits, but we will plan and clamp to the limits ");
    }

    // Scale velocity and acceleration
    move_group_interface.setMaxVelocityScalingFactor(0.05);
    move_group_interface.setMaxAccelerationScalingFactor(0.05);

    // Create a plan to the target joint-space configuration
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    auto success = move_group_interface.plan(plan);

    // Execute the plan
    execute(logger, move_group_interface, moveit_visual_tools, success == moveit::core::MoveItErrorCode::SUCCESS, plan);

    //*******************************************************************
    // PLAN TO A TARGET POSE
    //*******************************************************************

    // Clean the scene
    prompt(moveit_visual_tools, "Press 'Next' in the RvizVisualToolsGui window to plan to the target pose");
    moveit_visual_tools.deleteAllMarkers();
    draw_title(moveit_visual_tools, "Planning");
    moveit_visual_tools.trigger();

    // Set a target Pose
    geometry_msgs::msg::Pose target_pose_1;
    target_pose_1.orientation.w = 1.0;
    target_pose_1.position.x = 0.28;
    target_pose_1.position.y = -0.2;
    target_pose_1.position.z = 0.5;
    move_group_interface.setPoseTarget(target_pose_1);

    // Scale velocity and acceleration to move faster
    move_group_interface.setMaxVelocityScalingFactor(0.3);
    move_group_interface.setMaxAccelerationScalingFactor(0.3);

    // Create a plan to the target pose
    success = move_group_interface.plan(plan);

    // Execute the plan
    execute(logger, move_group_interface, moveit_visual_tools, success == moveit::core::MoveItErrorCode::SUCCESS, plan);

    //*******************************************************************
    // PLAN TO A TARGET POSE WITH PATH CONSTRAINTS
    //*******************************************************************

    // Clean the scene
    prompt(moveit_visual_tools, "Press 'Next' in the RvizVisualToolsGui window to plan to the target pose with path constraints");
    moveit_visual_tools.deleteAllMarkers();
    draw_title(moveit_visual_tools, "Planning");
    moveit_visual_tools.trigger();

    // Set a target Pose
    geometry_msgs::msg::Pose target_pose_2;
    target_pose_2.orientation.w = 1.0;
    target_pose_2.position.x = 0.2;
    target_pose_2.position.y = -0.4;
    target_pose_2.position.z = 0.7;
    move_group_interface.setPoseTarget(target_pose_2);

    // Set a constraint to keep the gripper's fingers up
    moveit_msgs::msg::Constraints constraints;
    moveit_msgs::msg::OrientationConstraint ocm;
    ocm.link_name = "panda_link7";
    ocm.header.frame_id = "panda_link0";
    ocm.orientation.w = 1.0;
    ocm.absolute_x_axis_tolerance = 0.1;
    ocm.absolute_y_axis_tolerance = 0.1;
    ocm.absolute_z_axis_tolerance = 0.1;
    ocm.weight = 1.0;
    constraints.orientation_constraints.push_back(ocm);
    move_group_interface.setPathConstraints(constraints);

    // Create a plan to the target pose
    success = move_group_interface.plan(plan);

    // Execute the plan
    execute(logger, move_group_interface, moveit_visual_tools, success == moveit::core::MoveItErrorCode::SUCCESS, plan);

    // Remove path constraints
    move_group_interface.clearPathConstraints();

    //*******************************************************************
    // PLAN TO A TARGET POSE WITH OBSTACLES
    //*******************************************************************

    // Clean the scene
    prompt(moveit_visual_tools, "Press 'Next' in the RvizVisualToolsGui window to plan with obstacles");
    moveit_visual_tools.deleteAllMarkers();
    draw_title(moveit_visual_tools, "Planning");
    moveit_visual_tools.trigger();

    
    // Set a target Pose
    geometry_msgs::msg::Pose target_pose_3;
    target_pose_3.orientation.w = 1.0;
    target_pose_3.position.x = 0.28;
    target_pose_3.position.y = 0.4;
    target_pose_3.position.z = 0.5;
    move_group_interface.setPoseTarget(target_pose_3);

    // Create collision object for the robot to avoid
    moveit_msgs::msg::CollisionObject collision_object;
    collision_object.header.frame_id = move_group_interface.getPlanningFrame();
    collision_object.id = "box1";
    shape_msgs::msg::SolidPrimitive primitive;

    // Define the size of the box in meters
    primitive.type = primitive.BOX;
    primitive.dimensions.resize(3);
    primitive.dimensions[primitive.BOX_X] = 0.5;
    primitive.dimensions[primitive.BOX_Y] = 0.1;
    primitive.dimensions[primitive.BOX_Z] = 0.5;

    // Define the pose of the box (relative to the frame_id)
    geometry_msgs::msg::Pose box_pose;
    box_pose.orientation.w = 1.0;
    box_pose.position.x = 0.2;
    box_pose.position.y = 0.2;
    box_pose.position.z = 0.25;

    collision_object.primitives.push_back(primitive);
    collision_object.primitive_poses.push_back(box_pose);
    collision_object.operation = collision_object.ADD;

    // Add the collision object to the scene
    planning_scene_interface.applyCollisionObject(collision_object);

    // Create a plan to the target pose
    success = move_group_interface.plan(plan);

    // Execute the plan
    execute(logger, move_group_interface, moveit_visual_tools, success == moveit::core::MoveItErrorCode::SUCCESS, plan);

    //*******************************************************************
    // PLAN A CARTESIAN PATH
    //*******************************************************************

    // Clean the scene
    prompt(moveit_visual_tools, "Press 'Next' in the RvizVisualToolsGui window to plan a Cartesian path");
    moveit_visual_tools.deleteAllMarkers();
    draw_title(moveit_visual_tools, "Moving\xa0to\xa0home\xa0\x63onfiguration\xa0\x61nd\xa0planning");
    moveit_visual_tools.trigger();
    remove_collision_objects(planning_scene_interface);

    // Move to home configuration
    move_group_interface.setNamedTarget("ready");
    move_group_interface.move();

    std::vector<geometry_msgs::msg::Pose> waypoints;

    // Set first waypoint to current robot pose
    auto target_pose_4 = move_group_interface.getCurrentPose().pose;
    waypoints.push_back(target_pose_4);  // start

    target_pose_4.position.z -= 0.2;
    waypoints.push_back(target_pose_4);  // down

    target_pose_4.position.y -= 0.2;
    waypoints.push_back(target_pose_4);  // right

    target_pose_4.position.z += 0.2;
    target_pose_4.position.y += 0.2;
    target_pose_4.position.x -= 0.2;
    waypoints.push_back(target_pose_4);  // up and left

    moveit::planning_interface::MoveGroupInterface::Plan cartesian_plan;
    moveit_msgs::msg::RobotTrajectory trajectory;
    const double jump_threshold = 0.0;
    const double eef_step = 0.01;
    double fraction = move_group_interface.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
    RCLCPP_INFO(logger, "Achieved %.2f%% of Cartesian path", fraction * 100.0);
    robotStateToRobotStateMsg(*move_group_interface.getCurrentState(), cartesian_plan.start_state_);
    cartesian_plan.trajectory_ = trajectory;

    // Execute the plan
    execute(logger, move_group_interface, moveit_visual_tools, fraction == 1.0, cartesian_plan);

    // Shutdown ROS
    rclcpp::shutdown();
    return 0;
}
