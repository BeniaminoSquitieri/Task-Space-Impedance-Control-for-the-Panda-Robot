from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    """
    Generate a ROS 2 LaunchDescription for starting nodes.
    
    This function initializes and returns a LaunchDescription object that
    specifies which ROS 2 nodes to start and how to configure them.
    
    Returns:
        LaunchDescription: The launch description object containing node start configurations.
    """

    # Create a LaunchDescription object that will hold the nodes to launch
    return LaunchDescription([
        Node(
            package='panda_moveit_planning_demo',  # The ROS 2 package containing the node executable
            executable='panda_moveit_planning_node',  # The name of the node executable to launch
            output='screen',  # Optional: Direct output to the screen
            parameters=[  # Optional: Specify parameters to be passed to the node
                {'use_sim_time': False},  # Example parameter
            ],
            remappings=[  # Optional: Remap topics
                # ('/original_topic', '/new_topic')
            ],
            name='panda_planning_node',  # Optional: Specify a unique name for the node
            namespace='panda_ns',  # Optional: Define a namespace for the node
        )
    ])
