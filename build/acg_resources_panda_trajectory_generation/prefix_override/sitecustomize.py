import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/beniamino/ros2_ws/install/acg_resources_panda_trajectory_generation'
