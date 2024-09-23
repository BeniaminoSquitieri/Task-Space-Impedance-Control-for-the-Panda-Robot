cmake_minimum_required(VERSION 3.5)
project(panda_impedance_controller)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Compiler options
set(ADDITIONAL_COMPILE_OPTIONS -Wall -Wextra -Wpedantic -Wno-unused-parameter)
add_compile_options(${ADDITIONAL_COMPILE_OPTIONS})

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(cartesian_control_msgs REQUIRED)
find_package(controller_interface REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(generate_parameter_library REQUIRED)
find_package(orocos_kdl REQUIRED)
find_package(kdl_parser REQUIRED)
find_package(urdf REQUIRED)
find_package(inverse_dynamics_solver REQUIRED)
find_package(kdl_inverse_dynamics_solver REQUIRED)
find_package(moveit_core REQUIRED)
find_package(moveit_ros_planning REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_kinematics REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_kdl REQUIRED)
find_package(realtime_tools REQUIRED)
find_package(control_toolbox REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
  angles
  control_msgs
  control_toolbox
  controller_interface
  cartesian_control_msgs
  generate_parameter_library
  geometry_msgs
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  realtime_tools
  tf2
  tf2_eigen
  tf2_geometry_msgs
  tf2_ros
  trajectory_msgs
  orocos_kdl
  kdl_parser
  urdf
  inverse_dynamics_solver
  kdl_inverse_dynamics_solver
  moveit_core
  moveit_ros_planning
  moveit_ros_planning_interface
  moveit_kinematics
)

ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})

# Generate parameter libraries
generate_parameter_library(
  ${PROJECT_NAME}_parameters
  src/impedance_controller_parameters.yaml
)

add_library(${PROJECT_NAME} SHARED 
  src/impedance_controller.cpp
  src/calculate_pose.cpp
)

add_executable(calculate_pose src/calculate_pose.cpp)
ament_target_dependencies(calculate_pose
  rclcpp
  moveit_core
  moveit_ros_planning
  moveit_ros_planning_interface
  geometry_msgs
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${EIGEN3_INCLUDE_DIR}
    ${${PROJECT_NAME}_parameters_INCLUDE_DIRS}
)

target_include_directories(calculate_pose
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${EIGEN3_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC ${PROJECT_NAME}_parameters
)

ament_target_dependencies(${PROJECT_NAME}
  PUBLIC
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS"
)

pluginlib_export_plugin_description_file(controller_interface panda_impedance_controller.xml)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

install(TARGETS calculate_pose
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include/
)

install(FILES panda_impedance_controller.xml
  DESTINATION share/${PROJECT_NAME}/
)

ament_export_include_directories(
  include
)

ament_export_libraries(
  ${PROJECT_NAME}
)

ament_package()
