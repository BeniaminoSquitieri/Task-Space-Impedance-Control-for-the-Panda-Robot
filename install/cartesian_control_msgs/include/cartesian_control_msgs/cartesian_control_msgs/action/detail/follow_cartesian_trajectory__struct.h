// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cartesian_control_msgs:action/FollowCartesianTrajectory.idl
// generated code does not contain a copyright notice

#ifndef CARTESIAN_CONTROL_MSGS__ACTION__DETAIL__FOLLOW_CARTESIAN_TRAJECTORY__STRUCT_H_
#define CARTESIAN_CONTROL_MSGS__ACTION__DETAIL__FOLLOW_CARTESIAN_TRAJECTORY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'trajectory'
#include "moveit_msgs/msg/detail/cartesian_trajectory__struct.h"

/// Struct defined in action/FollowCartesianTrajectory in the package cartesian_control_msgs.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_Goal
{
  moveit_msgs__msg__CartesianTrajectory trajectory;
} cartesian_control_msgs__action__FollowCartesianTrajectory_Goal;

// Struct for a sequence of cartesian_control_msgs__action__FollowCartesianTrajectory_Goal.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence;


// Constants defined in the message

/// Constant 'SUCCESS'.
enum
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__SUCCESS = 0l
};

/// Constant 'INVALID_GOAL'.
enum
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__INVALID_GOAL = -1l
};

/// Constant 'REQUESTED_CANCEL'.
enum
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__REQUESTED_CANCEL = -2l
};

/// Constant 'OLD_HEADER_TIMESTAMP'.
enum
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__OLD_HEADER_TIMESTAMP = -3l
};

/// Constant 'INVALID_POSTURE'.
enum
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__INVALID_POSTURE = -4l
};

// Include directives for member types
// Member 'error_string'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/FollowCartesianTrajectory in the package cartesian_control_msgs.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_Result
{
  bool success;
  int32_t error_code;
  rosidl_runtime_c__String error_string;
} cartesian_control_msgs__action__FollowCartesianTrajectory_Result;

// Struct for a sequence of cartesian_control_msgs__action__FollowCartesianTrajectory_Result.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'controlled_frame'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'desired'
// Member 'actual'
// Member 'error'
#include "moveit_msgs/msg/detail/cartesian_trajectory_point__struct.h"

/// Struct defined in action/FollowCartesianTrajectory in the package cartesian_control_msgs.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String controlled_frame;
  moveit_msgs__msg__CartesianTrajectoryPoint desired;
  moveit_msgs__msg__CartesianTrajectoryPoint actual;
  moveit_msgs__msg__CartesianTrajectoryPoint error;
} cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback;

// Struct for a sequence of cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"

/// Struct defined in action/FollowCartesianTrajectory in the package cartesian_control_msgs.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal goal;
} cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request;

// Struct for a sequence of cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/FollowCartesianTrajectory in the package cartesian_control_msgs.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response;

// Struct for a sequence of cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/FollowCartesianTrajectory in the package cartesian_control_msgs.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request;

// Struct for a sequence of cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"

/// Struct defined in action/FollowCartesianTrajectory in the package cartesian_control_msgs.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response
{
  int8_t status;
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result result;
} cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response;

// Struct for a sequence of cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.h"

/// Struct defined in action/FollowCartesianTrajectory in the package cartesian_control_msgs.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback feedback;
} cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage;

// Struct for a sequence of cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage.
typedef struct cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence
{
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CARTESIAN_CONTROL_MSGS__ACTION__DETAIL__FOLLOW_CARTESIAN_TRAJECTORY__STRUCT_H_
