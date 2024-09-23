"""
@file
This script generates a Launch Description for setting up a robotic simulation environment
using Gazebo, MoveIt, RViz, and ROS controllers.
"""

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, RegisterEventHandler, IncludeLaunchDescription, LogInfo, OpaqueFunction, GroupAction, ExecuteProcess
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessExit, OnProcessStart
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node, SetParameter
from launch_ros.substitutions import FindPackageShare

def spawn_controller_list(context):
    """
    @brief Function to generate a list of controller-spawning nodes.

    This function generates a list of ROS nodes responsible for spawning controllers
    based on the provided context.

    @param context: The context containing launch configurations.
    @type context: LaunchContext

    @return: A list of ROS nodes for spawning controllers.
    @rtype: list[Node]
    """
    # Creates a list of Nodes for each controller in the 'controller_list' from the context
    return [
        Node(package="controller_manager",
            executable="spawner",
            arguments=[controller, "--controller-manager", "/controller_manager"],
        )
        for controller in context.launch_configurations["controller_list"].split()
    ]


def generate_launch_description():
    """
    @brief Generate the launch description.

    This function creates a Launch Description for setting up a robotic simulation
    environment with Gazebo, MoveIt, and RViz.

    @return: The generated Launch Description.
    @rtype: LaunchDescription
    """
    # Declare launch arguments that can be configured from the command line or other launch files
    declared_arguments = []
    declared_arguments.append(
        DeclareLaunchArgument(
            "gui",
            default_value="true",
            description="Start RViz2 automatically with this launch file.",
        )
    )

    # Use xacro to generate the URDF (Unified Robot Description Format) file for the robot
    xacro_file = PathJoinSubstitution(
        [
            FindPackageShare("acg_resources_panda_moveit_config"),
            "config",
            "panda.urdf.xacro",
        ]
    )

    # Load robot description from the xacro file and set the 'use_mock_hardware' parameter to false
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            xacro_file,
            " ",
            "use_mock_hardware:=false",
        ]
    )
    robot_description = {"robot_description": robot_description_content}

    # Set the Gazebo resource path environment variable to find the meshes referenced by the URDF
    os.environ['IGN_GAZEBO_RESOURCE_PATH'] = get_package_share_directory("acg_resources_panda_description") + "/.."

    # Define the path to the Gazebo launch file
    gazebo_launch_file = PathJoinSubstitution(
        [
            FindPackageShare('ros_ign_gazebo'),
            'launch',
            'ign_gazebo.launch.py'
        ]
    )

    # Define the path to the MoveIt launch file
    move_group_launch_file = PathJoinSubstitution(
        [
            FindPackageShare('acg_resources_panda_moveit_config'),
            'launch',
            'move_group.launch.py'
        ]
    )

    # Define the path to the RViz configuration file
    rviz_config_file = PathJoinSubstitution(
        [
            FindPackageShare("acg_resources_panda_moveit_config"),
            "config",
            "cartesian_impedance_tuning.rviz"
        ]
    )

    # Define the RViz node to visualize the robot's state and trajectory in RViz
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        output="log",
        arguments=["-d", rviz_config_file]
    )

    # List to store launch files to be included in this launch description
    launches = []

    # Include Gazebo launch file to launch its environment
    launches.append(
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(gazebo_launch_file),
            # launch_arguments=[('gz_args', ['-r -v 4 empty.sdf'])],
            # launch_arguments=[('gz_args', [' -r -v 4 src/panda_impedance_controller/acg_resources_panda_moveit_config/config/panda_impedance_world.sdf'])],
            # launch_arguments=[('gz_args', ['-s -r -v 4 src/panda_impedance_controller/acg_resources_panda_moveit_config/config/panda_impedance_world.sdf'])],
            launch_arguments=[('gz_args', [' -r -v 4 src/panda_impedance_controller/acg_resources_panda_moveit_config/config/panda_impedance_world2box.sdf'])],
        )
    )

    # Include MoveIt launch file to set up motion planning
    move_group_launch_description = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(move_group_launch_file),
        launch_arguments=[('moveit_manage_controllers', 'false')],
    )

    # Define all nodes that have to be launched, including spawning the robot model in Gazebo
    ignition_spawn_entity = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=['-string', robot_description_content,
                   '-name', 'panda',
                   '-allow_renaming', 'true'],
    )

    # Node for publishing robot state information
    robot_state_pub_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="both",
        parameters=[robot_description],
    )

    # Nodes for spawning controllers
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
    )

    task_space_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["panda_impedance_controller", "--controller-manager", "/controller_manager"],
    )

    # Group actions to enforce the use of simulation time (sim_time)
    group_actions = []
    group_actions.append(
        GroupAction(
            actions=[
                SetParameter(name='use_sim_time', value=True),
                move_group_launch_description,
                robot_state_pub_node
            ]
        )
    )

    # Register event handlers to delay the start of controllers until after the robot model has been spawned
    delay_controllers_after_ignition_spawn = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=ignition_spawn_entity,
            on_exit=[joint_state_broadcaster_spawner, task_space_controller_spawner]
        )
    )

    # Register event handlers to delay the start of RViz until after the joint state broadcaster has started
    delay_rviz_after_controllers_spawner = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=joint_state_broadcaster_spawner,
            on_exit=[rviz_node],
        )
    )

    # List of all nodes to be launched
    nodes = [
        ignition_spawn_entity,
        delay_controllers_after_ignition_spawn,
        delay_rviz_after_controllers_spawner,
    ]

    # Combine all declared arguments, launch files, group actions, and nodes into a single Launch Description
    return LaunchDescription(declared_arguments + launches + group_actions + nodes)
