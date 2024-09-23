import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.conditions import IfCondition
from launch.actions import DeclareLaunchArgument, RegisterEventHandler, IncludeLaunchDescription, GroupAction
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.event_handlers import OnProcessExit

from launch_ros.actions import Node, SetParameter
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    # Value argument from launch configuration
    gui = LaunchConfiguration("gui")

    # Declare arguments
    declared_arguments = []
    declared_arguments.append(
        DeclareLaunchArgument(
            "gui",
            default_value="true",
            description="Start RViz2 automatically with this launch file.",
        )
    )

    # Get URDF via xacro
    xacro_file = PathJoinSubstitution(
        [
            FindPackageShare("acg_resources_panda_moveit_config"),
            "config",
            "panda.urdf.xacro",
        ]
    )

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

    # Prepare Gazebo resources and launch path
    os.environ['IGN_GAZEBO_RESOURCE_PATH'] = get_package_share_directory("acg_resources_panda_description") + "/.."

    gazebo_launch_file = PathJoinSubstitution(
        [
            FindPackageShare('ros_ign_gazebo'),
            'launch', 
            'ign_gazebo.launch.py'
        ]
    )

    # Prepare other launch paths
    move_group_launch_file = PathJoinSubstitution(
        [
            FindPackageShare('acg_resources_panda_moveit_config'),
            'launch',
            'move_group.launch.py'
        ]
    )

    rviz_launch_file = PathJoinSubstitution(
        [
            FindPackageShare('acg_resources_panda_moveit_config'),
            'launch',
            'moveit_rviz.launch.py'
        ]
    )

    # Include launch files in this one
    launches = []

    launches.append(
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(gazebo_launch_file),
            launch_arguments=[('gz_args', ['-r -v 4 empty.sdf'])],
        )
    )

    move_group_launch_description = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(move_group_launch_file),
        launch_arguments=[('moveit_manage_controllers', 'false')],
    ) 

    rviz_launch_description = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(rviz_launch_file),
        condition=IfCondition(gui)
    )

    # Define Node actions
    
    # Spawn the model in Gazebo. This also loads the plugin and starts the control node.
    # At the time of writing this script, the 'create' command does not allow spawning
    # the robot at a specific joint configuration
    ignition_spawn_entity = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=['-string', robot_description_content,
                   '-name', 'panda',
                   '-allow_renaming', 'true'],
    )

    robot_state_pub_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="both",
        parameters=[robot_description],
    )

    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
    )

    impedance_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["panda_impedance_controller", "--controller-manager", "/controller_manager"],
    )

    hand_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["hand_controller", "--controller-manager", "/controller_manager"],
    )

    # Define GroupAction actions (needed to enforce use_sim_time)
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

    # Load controllers after spawning the model in Gazebo
    delay_controllers_after_ignition_spawn = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=ignition_spawn_entity,
            on_exit=[joint_state_broadcaster_spawner]
        )
    )

    # After the joint state broadcaster, the trajectory and hand controllers can be activated
    delay_trajectory_and_hand_controllers_after_joint_state_broadcaster = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=joint_state_broadcaster_spawner,
            on_exit=[impedance_controller_spawner, hand_controller_spawner]
        )
    )

    # Delay RViz start after spawning impedance_controller
    delay_rviz_after_impedance_controller_spawner = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=impedance_controller_spawner,
            on_exit=[rviz_launch_description],
        )
    )

    nodes = [
        ignition_spawn_entity,
        delay_controllers_after_ignition_spawn,
        delay_trajectory_and_hand_controllers_after_joint_state_broadcaster,
        delay_rviz_after_impedance_controller_spawner
    ]

    return LaunchDescription(declared_arguments + launches + group_actions + nodes)
