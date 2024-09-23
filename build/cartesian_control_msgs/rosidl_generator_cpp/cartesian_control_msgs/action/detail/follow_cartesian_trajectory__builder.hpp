// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cartesian_control_msgs:action/FollowCartesianTrajectory.idl
// generated code does not contain a copyright notice

#ifndef CARTESIAN_CONTROL_MSGS__ACTION__DETAIL__FOLLOW_CARTESIAN_TRAJECTORY__BUILDER_HPP_
#define CARTESIAN_CONTROL_MSGS__ACTION__DETAIL__FOLLOW_CARTESIAN_TRAJECTORY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cartesian_control_msgs
{

namespace action
{

namespace builder
{

class Init_FollowCartesianTrajectory_Goal_trajectory
{
public:
  Init_FollowCartesianTrajectory_Goal_trajectory()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Goal trajectory(::cartesian_control_msgs::action::FollowCartesianTrajectory_Goal::_trajectory_type arg)
  {
    msg_.trajectory = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cartesian_control_msgs::action::FollowCartesianTrajectory_Goal>()
{
  return cartesian_control_msgs::action::builder::Init_FollowCartesianTrajectory_Goal_trajectory();
}

}  // namespace cartesian_control_msgs


namespace cartesian_control_msgs
{

namespace action
{

namespace builder
{

class Init_FollowCartesianTrajectory_Result_error_string
{
public:
  explicit Init_FollowCartesianTrajectory_Result_error_string(::cartesian_control_msgs::action::FollowCartesianTrajectory_Result & msg)
  : msg_(msg)
  {}
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Result error_string(::cartesian_control_msgs::action::FollowCartesianTrajectory_Result::_error_string_type arg)
  {
    msg_.error_string = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Result msg_;
};

class Init_FollowCartesianTrajectory_Result_error_code
{
public:
  explicit Init_FollowCartesianTrajectory_Result_error_code(::cartesian_control_msgs::action::FollowCartesianTrajectory_Result & msg)
  : msg_(msg)
  {}
  Init_FollowCartesianTrajectory_Result_error_string error_code(::cartesian_control_msgs::action::FollowCartesianTrajectory_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_FollowCartesianTrajectory_Result_error_string(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Result msg_;
};

class Init_FollowCartesianTrajectory_Result_success
{
public:
  Init_FollowCartesianTrajectory_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowCartesianTrajectory_Result_error_code success(::cartesian_control_msgs::action::FollowCartesianTrajectory_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_FollowCartesianTrajectory_Result_error_code(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cartesian_control_msgs::action::FollowCartesianTrajectory_Result>()
{
  return cartesian_control_msgs::action::builder::Init_FollowCartesianTrajectory_Result_success();
}

}  // namespace cartesian_control_msgs


namespace cartesian_control_msgs
{

namespace action
{

namespace builder
{

class Init_FollowCartesianTrajectory_Feedback_error
{
public:
  explicit Init_FollowCartesianTrajectory_Feedback_error(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback & msg)
  : msg_(msg)
  {}
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback error(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback::_error_type arg)
  {
    msg_.error = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback msg_;
};

class Init_FollowCartesianTrajectory_Feedback_actual
{
public:
  explicit Init_FollowCartesianTrajectory_Feedback_actual(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback & msg)
  : msg_(msg)
  {}
  Init_FollowCartesianTrajectory_Feedback_error actual(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback::_actual_type arg)
  {
    msg_.actual = std::move(arg);
    return Init_FollowCartesianTrajectory_Feedback_error(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback msg_;
};

class Init_FollowCartesianTrajectory_Feedback_desired
{
public:
  explicit Init_FollowCartesianTrajectory_Feedback_desired(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback & msg)
  : msg_(msg)
  {}
  Init_FollowCartesianTrajectory_Feedback_actual desired(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback::_desired_type arg)
  {
    msg_.desired = std::move(arg);
    return Init_FollowCartesianTrajectory_Feedback_actual(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback msg_;
};

class Init_FollowCartesianTrajectory_Feedback_controlled_frame
{
public:
  explicit Init_FollowCartesianTrajectory_Feedback_controlled_frame(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback & msg)
  : msg_(msg)
  {}
  Init_FollowCartesianTrajectory_Feedback_desired controlled_frame(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback::_controlled_frame_type arg)
  {
    msg_.controlled_frame = std::move(arg);
    return Init_FollowCartesianTrajectory_Feedback_desired(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback msg_;
};

class Init_FollowCartesianTrajectory_Feedback_header
{
public:
  Init_FollowCartesianTrajectory_Feedback_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowCartesianTrajectory_Feedback_controlled_frame header(::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_FollowCartesianTrajectory_Feedback_controlled_frame(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cartesian_control_msgs::action::FollowCartesianTrajectory_Feedback>()
{
  return cartesian_control_msgs::action::builder::Init_FollowCartesianTrajectory_Feedback_header();
}

}  // namespace cartesian_control_msgs


namespace cartesian_control_msgs
{

namespace action
{

namespace builder
{

class Init_FollowCartesianTrajectory_SendGoal_Request_goal
{
public:
  explicit Init_FollowCartesianTrajectory_SendGoal_Request_goal(::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Request goal(::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Request msg_;
};

class Init_FollowCartesianTrajectory_SendGoal_Request_goal_id
{
public:
  Init_FollowCartesianTrajectory_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowCartesianTrajectory_SendGoal_Request_goal goal_id(::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_FollowCartesianTrajectory_SendGoal_Request_goal(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Request>()
{
  return cartesian_control_msgs::action::builder::Init_FollowCartesianTrajectory_SendGoal_Request_goal_id();
}

}  // namespace cartesian_control_msgs


namespace cartesian_control_msgs
{

namespace action
{

namespace builder
{

class Init_FollowCartesianTrajectory_SendGoal_Response_stamp
{
public:
  explicit Init_FollowCartesianTrajectory_SendGoal_Response_stamp(::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Response stamp(::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Response msg_;
};

class Init_FollowCartesianTrajectory_SendGoal_Response_accepted
{
public:
  Init_FollowCartesianTrajectory_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowCartesianTrajectory_SendGoal_Response_stamp accepted(::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_FollowCartesianTrajectory_SendGoal_Response_stamp(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cartesian_control_msgs::action::FollowCartesianTrajectory_SendGoal_Response>()
{
  return cartesian_control_msgs::action::builder::Init_FollowCartesianTrajectory_SendGoal_Response_accepted();
}

}  // namespace cartesian_control_msgs


namespace cartesian_control_msgs
{

namespace action
{

namespace builder
{

class Init_FollowCartesianTrajectory_GetResult_Request_goal_id
{
public:
  Init_FollowCartesianTrajectory_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Request goal_id(::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Request>()
{
  return cartesian_control_msgs::action::builder::Init_FollowCartesianTrajectory_GetResult_Request_goal_id();
}

}  // namespace cartesian_control_msgs


namespace cartesian_control_msgs
{

namespace action
{

namespace builder
{

class Init_FollowCartesianTrajectory_GetResult_Response_result
{
public:
  explicit Init_FollowCartesianTrajectory_GetResult_Response_result(::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Response result(::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Response msg_;
};

class Init_FollowCartesianTrajectory_GetResult_Response_status
{
public:
  Init_FollowCartesianTrajectory_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowCartesianTrajectory_GetResult_Response_result status(::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_FollowCartesianTrajectory_GetResult_Response_result(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cartesian_control_msgs::action::FollowCartesianTrajectory_GetResult_Response>()
{
  return cartesian_control_msgs::action::builder::Init_FollowCartesianTrajectory_GetResult_Response_status();
}

}  // namespace cartesian_control_msgs


namespace cartesian_control_msgs
{

namespace action
{

namespace builder
{

class Init_FollowCartesianTrajectory_FeedbackMessage_feedback
{
public:
  explicit Init_FollowCartesianTrajectory_FeedbackMessage_feedback(::cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage feedback(::cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage msg_;
};

class Init_FollowCartesianTrajectory_FeedbackMessage_goal_id
{
public:
  Init_FollowCartesianTrajectory_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowCartesianTrajectory_FeedbackMessage_feedback goal_id(::cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_FollowCartesianTrajectory_FeedbackMessage_feedback(msg_);
  }

private:
  ::cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage>()
{
  return cartesian_control_msgs::action::builder::Init_FollowCartesianTrajectory_FeedbackMessage_goal_id();
}

}  // namespace cartesian_control_msgs

#endif  // CARTESIAN_CONTROL_MSGS__ACTION__DETAIL__FOLLOW_CARTESIAN_TRAJECTORY__BUILDER_HPP_
