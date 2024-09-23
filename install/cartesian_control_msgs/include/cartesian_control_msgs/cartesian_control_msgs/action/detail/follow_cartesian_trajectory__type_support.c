// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cartesian_control_msgs:action/FollowCartesianTrajectory.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
#include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"
#include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"


// Include directives for member types
// Member `trajectory`
#include "moveit_msgs/msg/cartesian_trajectory.h"
// Member `trajectory`
#include "moveit_msgs/msg/detail/cartesian_trajectory__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__init(message_memory);
}

void cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_fini_function(void * message_memory)
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_member_array[1] = {
  {
    "trajectory",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal, trajectory),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_members = {
  "cartesian_control_msgs__action",  // message namespace
  "FollowCartesianTrajectory_Goal",  // message name
  1,  // number of fields
  sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal),
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_member_array,  // message members
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_type_support_handle = {
  0,
  &cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_Goal)() {
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, moveit_msgs, msg, CartesianTrajectory)();
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"


// Include directives for member types
// Member `error_string`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__init(message_memory);
}

void cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_fini_function(void * message_memory)
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_message_member_array[3] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result, error_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_string",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result, error_string),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_message_members = {
  "cartesian_control_msgs__action",  // message namespace
  "FollowCartesianTrajectory_Result",  // message name
  3,  // number of fields
  sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result),
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_message_member_array,  // message members
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_message_type_support_handle = {
  0,
  &cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_Result)() {
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_message_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cartesian_control_msgs__action__FollowCartesianTrajectory_Result__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `controlled_frame`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `desired`
// Member `actual`
// Member `error`
#include "moveit_msgs/msg/cartesian_trajectory_point.h"
// Member `desired`
// Member `actual`
// Member `error`
#include "moveit_msgs/msg/detail/cartesian_trajectory_point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__init(message_memory);
}

void cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_fini_function(void * message_memory)
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_member_array[5] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "controlled_frame",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback, controlled_frame),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "desired",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback, desired),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "actual",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback, actual),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback, error),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_members = {
  "cartesian_control_msgs__action",  // message namespace
  "FollowCartesianTrajectory_Feedback",  // message name
  5,  // number of fields
  sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback),
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_member_array,  // message members
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_type_support_handle = {
  0,
  &cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_Feedback)() {
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, moveit_msgs, msg, CartesianTrajectoryPoint)();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, moveit_msgs, msg, CartesianTrajectoryPoint)();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, moveit_msgs, msg, CartesianTrajectoryPoint)();
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "cartesian_control_msgs/action/follow_cartesian_trajectory.h"
// Member `goal`
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__init(message_memory);
}

void cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_fini_function(void * message_memory)
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_members = {
  "cartesian_control_msgs__action",  // message namespace
  "FollowCartesianTrajectory_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request),
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_member_array,  // message members
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_type_support_handle = {
  0,
  &cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_SendGoal_Request)() {
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_Goal)();
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__init(message_memory);
}

void cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_fini_function(void * message_memory)
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_members = {
  "cartesian_control_msgs__action",  // message namespace
  "FollowCartesianTrajectory_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response),
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_member_array,  // message members
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_type_support_handle = {
  0,
  &cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_SendGoal_Response)() {
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_service_members = {
  "cartesian_control_msgs__action",  // service namespace
  "FollowCartesianTrajectory_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_service_type_support_handle = {
  0,
  &cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_SendGoal)() {
  if (!cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_service_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_SendGoal_Response)()->data;
  }

  return &cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__init(message_memory);
}

void cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_fini_function(void * message_memory)
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_members = {
  "cartesian_control_msgs__action",  // message namespace
  "FollowCartesianTrajectory_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request),
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_member_array,  // message members
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_type_support_handle = {
  0,
  &cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_GetResult_Request)() {
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "cartesian_control_msgs/action/follow_cartesian_trajectory.h"
// Member `result`
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__init(message_memory);
}

void cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_fini_function(void * message_memory)
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_members = {
  "cartesian_control_msgs__action",  // message namespace
  "FollowCartesianTrajectory_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response),
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_member_array,  // message members
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_type_support_handle = {
  0,
  &cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_GetResult_Response)() {
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_Result)();
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_service_members = {
  "cartesian_control_msgs__action",  // service namespace
  "FollowCartesianTrajectory_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_service_type_support_handle = {
  0,
  &cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_GetResult)() {
  if (!cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_service_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_GetResult_Response)()->data;
  }

  return &cartesian_control_msgs__action__detail__follow_cartesian_trajectory__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cartesian_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "cartesian_control_msgs/action/follow_cartesian_trajectory.h"
// Member `feedback`
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__init(message_memory);
}

void cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_fini_function(void * message_memory)
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_members = {
  "cartesian_control_msgs__action",  // message namespace
  "FollowCartesianTrajectory_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage),
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_member_array,  // message members
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_type_support_handle = {
  0,
  &cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cartesian_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_FeedbackMessage)() {
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cartesian_control_msgs, action, FollowCartesianTrajectory_Feedback)();
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__rosidl_typesupport_introspection_c__FollowCartesianTrajectory_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
