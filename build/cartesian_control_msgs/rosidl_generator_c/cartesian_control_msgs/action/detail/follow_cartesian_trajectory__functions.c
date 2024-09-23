// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cartesian_control_msgs:action/FollowCartesianTrajectory.idl
// generated code does not contain a copyright notice
#include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `trajectory`
#include "moveit_msgs/msg/detail/cartesian_trajectory__functions.h"

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__init(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // trajectory
  if (!moveit_msgs__msg__CartesianTrajectory__init(&msg->trajectory)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__fini(msg);
    return false;
  }
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * msg)
{
  if (!msg) {
    return;
  }
  // trajectory
  moveit_msgs__msg__CartesianTrajectory__fini(&msg->trajectory);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // trajectory
  if (!moveit_msgs__msg__CartesianTrajectory__are_equal(
      &(lhs->trajectory), &(rhs->trajectory)))
  {
    return false;
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // trajectory
  if (!moveit_msgs__msg__CartesianTrajectory__copy(
      &(input->trajectory), &(output->trajectory)))
  {
    return false;
  }
  return true;
}

cartesian_control_msgs__action__FollowCartesianTrajectory_Goal *
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * msg = (cartesian_control_msgs__action__FollowCartesianTrajectory_Goal *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal));
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence__init(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * data = NULL;

  if (size) {
    data = (cartesian_control_msgs__action__FollowCartesianTrajectory_Goal *)allocator.zero_allocate(size, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence *
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence * array = (cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cartesian_control_msgs__action__FollowCartesianTrajectory_Goal * data =
      (cartesian_control_msgs__action__FollowCartesianTrajectory_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `error_string`
#include "rosidl_runtime_c/string_functions.h"

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__init(cartesian_control_msgs__action__FollowCartesianTrajectory_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // error_string
  if (!rosidl_runtime_c__String__init(&msg->error_string)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Result__fini(msg);
    return false;
  }
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // error_string
  rosidl_runtime_c__String__fini(&msg->error_string);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_Result * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // error_string
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->error_string), &(rhs->error_string)))
  {
    return false;
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_Result * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_code
  output->error_code = input->error_code;
  // error_string
  if (!rosidl_runtime_c__String__copy(
      &(input->error_string), &(output->error_string)))
  {
    return false;
  }
  return true;
}

cartesian_control_msgs__action__FollowCartesianTrajectory_Result *
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result * msg = (cartesian_control_msgs__action__FollowCartesianTrajectory_Result *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result));
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence__init(cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result * data = NULL;

  if (size) {
    data = (cartesian_control_msgs__action__FollowCartesianTrajectory_Result *)allocator.zero_allocate(size, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cartesian_control_msgs__action__FollowCartesianTrajectory_Result__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cartesian_control_msgs__action__FollowCartesianTrajectory_Result__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence *
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence * array = (cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cartesian_control_msgs__action__FollowCartesianTrajectory_Result * data =
      (cartesian_control_msgs__action__FollowCartesianTrajectory_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cartesian_control_msgs__action__FollowCartesianTrajectory_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `controlled_frame`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `desired`
// Member `actual`
// Member `error`
#include "moveit_msgs/msg/detail/cartesian_trajectory_point__functions.h"

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__init(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(msg);
    return false;
  }
  // controlled_frame
  if (!rosidl_runtime_c__String__init(&msg->controlled_frame)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(msg);
    return false;
  }
  // desired
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__init(&msg->desired)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(msg);
    return false;
  }
  // actual
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__init(&msg->actual)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(msg);
    return false;
  }
  // error
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__init(&msg->error)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // controlled_frame
  rosidl_runtime_c__String__fini(&msg->controlled_frame);
  // desired
  moveit_msgs__msg__CartesianTrajectoryPoint__fini(&msg->desired);
  // actual
  moveit_msgs__msg__CartesianTrajectoryPoint__fini(&msg->actual);
  // error
  moveit_msgs__msg__CartesianTrajectoryPoint__fini(&msg->error);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // controlled_frame
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->controlled_frame), &(rhs->controlled_frame)))
  {
    return false;
  }
  // desired
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__are_equal(
      &(lhs->desired), &(rhs->desired)))
  {
    return false;
  }
  // actual
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__are_equal(
      &(lhs->actual), &(rhs->actual)))
  {
    return false;
  }
  // error
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__are_equal(
      &(lhs->error), &(rhs->error)))
  {
    return false;
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // controlled_frame
  if (!rosidl_runtime_c__String__copy(
      &(input->controlled_frame), &(output->controlled_frame)))
  {
    return false;
  }
  // desired
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__copy(
      &(input->desired), &(output->desired)))
  {
    return false;
  }
  // actual
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__copy(
      &(input->actual), &(output->actual)))
  {
    return false;
  }
  // error
  if (!moveit_msgs__msg__CartesianTrajectoryPoint__copy(
      &(input->error), &(output->error)))
  {
    return false;
  }
  return true;
}

cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback *
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * msg = (cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback));
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence__init(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * data = NULL;

  if (size) {
    data = (cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback *)allocator.zero_allocate(size, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence *
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence * array = (cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback * data =
      (cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__init(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__init(&msg->goal)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__fini(&msg->goal);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request *
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * msg = (cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request));
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence__init(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * data = NULL;

  if (size) {
    data = (cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request *)allocator.zero_allocate(size, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence *
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence * array = (cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request * data =
      (cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__init(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response *
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * msg = (cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response));
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence__init(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * data = NULL;

  if (size) {
    data = (cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response *)allocator.zero_allocate(size, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence *
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence * array = (cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response * data =
      (cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__init(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request *
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * msg = (cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request));
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence__init(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * data = NULL;

  if (size) {
    data = (cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request *)allocator.zero_allocate(size, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence *
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence * array = (cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request * data =
      (cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__init(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Result__init(&msg->result)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  cartesian_control_msgs__action__FollowCartesianTrajectory_Result__fini(&msg->result);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response *
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * msg = (cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response));
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence__init(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * data = NULL;

  if (size) {
    data = (cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response *)allocator.zero_allocate(size, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence *
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence * array = (cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response * data =
      (cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "cartesian_control_msgs/action/detail/follow_cartesian_trajectory__functions.h"

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__init(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__init(&msg->feedback)) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__fini(&msg->feedback);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!cartesian_control_msgs__action__FollowCartesianTrajectory_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage *
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * msg = (cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage));
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence__init(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * data = NULL;

  if (size) {
    data = (cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage *)allocator.zero_allocate(size, sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence__fini(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence *
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence * array = (cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence *)allocator.allocate(sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence__destroy(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence__are_equal(const cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence * lhs, const cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence__copy(
  const cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence * input,
  cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage * data =
      (cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cartesian_control_msgs__action__FollowCartesianTrajectory_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
