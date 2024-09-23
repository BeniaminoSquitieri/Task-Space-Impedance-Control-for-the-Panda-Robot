# from launch import LaunchDescription
# from launch.actions import DeclareLaunchArgument
# from launch.substitutions import LaunchConfiguration
# from launch_ros.actions import Node

# def generate_launch_description():
#     """
#     Generate the launch description to run the panda_moveit_cartesian_demo node with the path to the bag file.
#     """
#     # Declare the launch argument for the bagfile
#     bagfile_path_name = LaunchConfiguration('bagfile_path_name')
    
#     # Node configuration for the demo planning node
#     planning_node_action = Node(
#         package='panda_moveit_planning_demo',
#         executable='panda_moveit_cartesian_demo',
#         output='screen',
#         arguments=[bagfile_path_name],
#         parameters=[{
#             'controller_name': 'panda_impedance_controller', 
#             'use_sim_time': True  # Use simulation time, adjust as necessary
#         }]
#     )
    
#     # Return the LaunchDescription object containing all launch actions
#     return LaunchDescription([
#         DeclareLaunchArgument(
#             "bagfile_path_name",
#             description="Path to the bag file containing the trajectory to plan and execute"
#         ),
#         planning_node_action
#     ])



from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def launch_setup(context, *args, **kwargs):
    # Get the bagfile path from the launch configuration
    bagfile_path_name = LaunchConfiguration('bagfile_path_name').perform(context)
    
    # Node parameters
    parameters = {
        'controller_name': 'panda_impedance_controller',
        'use_sim_time': True  # Use simulation time, adjust as necessary
    }

    # Create node action based on whether the bagfile_path_name is provided or not
    if bagfile_path_name:  # If a bagfile is provided, use the default executable
        executable_name = 'panda_moveit_cartesian_demo'
    else:  # If no bagfile is provided, use the alternative executable
        executable_name = 'panda_moveit_cartesian_demo_nobag'

    node_action = Node(
        package='panda_moveit_planning_demo',
        executable=executable_name,
        output='screen',
        arguments=[bagfile_path_name] if bagfile_path_name else [],
        parameters=[parameters]
    )

    return [node_action]

def generate_launch_description():
    """
    Generate the launch description to run the panda_moveit_cartesian_demo node with or without the path to the bag file.
    """
    return LaunchDescription([
        DeclareLaunchArgument(
            "bagfile_path_name",
            default_value='',
            description="(Optional) Path to the bag file containing the trajectory to plan and execute"
        ),
        OpaqueFunction(function=launch_setup)
    ])

