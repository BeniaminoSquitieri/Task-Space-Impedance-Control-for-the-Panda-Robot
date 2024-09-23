cmake_minimum_required(VERSION 3.22)
project(panda_moveit_planning_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_visual_tools REQUIRED)
find_package(rosbag2_cpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(action_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(cartesian_control_msgs REQUIRED)
find_package(generate_parameter_library REQUIRED)

set(THIS_PACKAGE_DEPENDS
  ament_cmake
  rclcpp
  moveit_ros_planning_interface
  moveit_visual_tools
  rosbag2_cpp
  geometry_msgs
  action_msgs
  rclcpp_action
  cartesian_control_msgs
  generate_parameter_library
)

# Generate the parameter library
generate_parameter_library(
  task_space_client_utils_parameters             
  src/task_space_client_utils_parameters.yaml    
)

include_directories(include)
add_library(moveit_utils src/moveit_utils.cpp)
add_library(bag_file_utils src/bag_file_utils.cpp) 
add_library(task_space_client_utils src/task_space_client_utils.cpp)
ament_target_dependencies(moveit_utils ${THIS_PACKAGE_DEPENDS})
ament_target_dependencies(bag_file_utils ${THIS_PACKAGE_DEPENDS})
ament_target_dependencies(task_space_client_utils ${THIS_PACKAGE_DEPENDS})
target_link_libraries(task_space_client_utils task_space_client_utils_parameters)

target_compile_features(moveit_utils PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(task_space_client_utils PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(bag_file_utils PUBLIC c_std_99 cxx_std_17)

add_executable(panda_moveit_planning_node src/panda_moveit_planning_node.cpp)
ament_target_dependencies(panda_moveit_planning_node ${THIS_PACKAGE_DEPENDS})

target_link_libraries(panda_moveit_planning_node moveit_utils task_space_client_utils task_space_client_utils_parameters)
target_link_libraries(panda_moveit_planning_node bag_file_utils task_space_client_utils task_space_client_utils_parameters)

target_compile_features(panda_moveit_planning_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

add_executable(panda_moveit_cartesian_demo src/panda_moveit_cartesian_demo.cpp)
add_executable(panda_moveit_cartesian_demo_nobag src/panda_moveit_cartesian_demo_nobag.cpp)
ament_target_dependencies(panda_moveit_cartesian_demo ${THIS_PACKAGE_DEPENDS})
ament_target_dependencies(panda_moveit_cartesian_demo_nobag ${THIS_PACKAGE_DEPENDS})
target_link_libraries(panda_moveit_cartesian_demo moveit_utils task_space_client_utils task_space_client_utils_parameters)
target_link_libraries(panda_moveit_cartesian_demo bag_file_utils task_space_client_utils task_space_client_utils_parameters)
target_link_libraries(panda_moveit_cartesian_demo_nobag moveit_utils task_space_client_utils task_space_client_utils_parameters)
target_link_libraries(panda_moveit_cartesian_demo_nobag bag_file_utils task_space_client_utils task_space_client_utils_parameters)


target_compile_features(panda_moveit_cartesian_demo PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(panda_moveit_cartesian_demo_nobag PUBLIC c_std_99 cxx_std_17) 

install(TARGETS
  panda_moveit_planning_node
  panda_moveit_cartesian_demo
  panda_moveit_cartesian_demo_nobag
  moveit_utils
  bag_file_utils
  task_space_client_utils
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})
install(DIRECTORY launch/ DESTINATION share/${PROJECT_NAME}/launch)

ament_export_dependencies(
  ${THIS_PACKAGE_DEPENDS}
)

ament_package()
