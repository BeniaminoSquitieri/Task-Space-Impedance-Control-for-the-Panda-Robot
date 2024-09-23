# CMake generated Testfile for 
# Source directory: /home/beniamino/ros2_ws/src/panda_impedance_controller/kdl_inverse_dynamics_solver
# Build directory: /home/beniamino/ros2_ws/build/kdl_inverse_dynamics_solver
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(launch_test_kdl_inverse_dynamics_solver.py "/usr/bin/python3" "-u" "/opt/ros/humble/share/ament_cmake_test/cmake/run_test.py" "/home/beniamino/ros2_ws/build/kdl_inverse_dynamics_solver/test_results/kdl_inverse_dynamics_solver/launch_test_kdl_inverse_dynamics_solver.py.xunit.xml" "--package-name" "kdl_inverse_dynamics_solver" "--output-file" "/home/beniamino/ros2_ws/build/kdl_inverse_dynamics_solver/ros_test/launch_test_kdl_inverse_dynamics_solver.py.txt" "--command" "ros2" "test" "/home/beniamino/ros2_ws/src/panda_impedance_controller/kdl_inverse_dynamics_solver/launch/test_kdl_inverse_dynamics_solver.py" "--junit-xml=/home/beniamino/ros2_ws/build/kdl_inverse_dynamics_solver/test_results/kdl_inverse_dynamics_solver/launch_test_kdl_inverse_dynamics_solver.py.xunit.xml" "--package-name=kdl_inverse_dynamics_solver")
set_tests_properties(launch_test_kdl_inverse_dynamics_solver.py PROPERTIES  TIMEOUT "60" WORKING_DIRECTORY "/home/beniamino/ros2_ws/build/kdl_inverse_dynamics_solver" _BACKTRACE_TRIPLES "/opt/ros/humble/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/opt/ros/humble/share/ros_testing/cmake/add_ros_test.cmake;73;ament_add_test;/home/beniamino/ros2_ws/src/panda_impedance_controller/kdl_inverse_dynamics_solver/CMakeLists.txt;90;add_ros_test;/home/beniamino/ros2_ws/src/panda_impedance_controller/kdl_inverse_dynamics_solver/CMakeLists.txt;0;")
subdirs("gtest")
