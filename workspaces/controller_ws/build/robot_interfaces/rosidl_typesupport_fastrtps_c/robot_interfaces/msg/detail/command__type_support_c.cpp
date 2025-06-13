// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from robot_interfaces:msg/Command.idl
// generated code does not contain a copyright notice
#include "robot_interfaces/msg/detail/command__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "robot_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robot_interfaces/msg/detail/command__struct.h"
#include "robot_interfaces/msg/detail/command__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "robot_interfaces/msg/detail/odometry__functions.h"  // odometry

// forward declare type support functions

bool cdr_serialize_robot_interfaces__msg__Odometry(
  const robot_interfaces__msg__Odometry * ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool cdr_deserialize_robot_interfaces__msg__Odometry(
  eprosima::fastcdr::Cdr & cdr,
  robot_interfaces__msg__Odometry * ros_message);

size_t get_serialized_size_robot_interfaces__msg__Odometry(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_robot_interfaces__msg__Odometry(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool cdr_serialize_key_robot_interfaces__msg__Odometry(
  const robot_interfaces__msg__Odometry * ros_message,
  eprosima::fastcdr::Cdr & cdr);

size_t get_serialized_size_key_robot_interfaces__msg__Odometry(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_key_robot_interfaces__msg__Odometry(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_interfaces, msg, Odometry)();


using _Command__ros_msg_type = robot_interfaces__msg__Command;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
bool cdr_serialize_robot_interfaces__msg__Command(
  const robot_interfaces__msg__Command * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: command
  {
    cdr << ros_message->command;
  }

  // Field name: odometry
  {
    cdr_serialize_robot_interfaces__msg__Odometry(
      &ros_message->odometry, cdr);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
bool cdr_deserialize_robot_interfaces__msg__Command(
  eprosima::fastcdr::Cdr & cdr,
  robot_interfaces__msg__Command * ros_message)
{
  // Field name: command
  {
    cdr >> ros_message->command;
  }

  // Field name: odometry
  {
    cdr_deserialize_robot_interfaces__msg__Odometry(cdr, &ros_message->odometry);
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
size_t get_serialized_size_robot_interfaces__msg__Command(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Command__ros_msg_type * ros_message = static_cast<const _Command__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: command
  {
    size_t item_size = sizeof(ros_message->command);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: odometry
  current_alignment += get_serialized_size_robot_interfaces__msg__Odometry(
    &(ros_message->odometry), current_alignment);

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
size_t max_serialized_size_robot_interfaces__msg__Command(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: command
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: odometry
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_robot_interfaces__msg__Odometry(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robot_interfaces__msg__Command;
    is_plain =
      (
      offsetof(DataType, odometry) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
bool cdr_serialize_key_robot_interfaces__msg__Command(
  const robot_interfaces__msg__Command * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: command
  {
    cdr << ros_message->command;
  }

  // Field name: odometry
  {
    cdr_serialize_key_robot_interfaces__msg__Odometry(
      &ros_message->odometry, cdr);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
size_t get_serialized_size_key_robot_interfaces__msg__Command(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Command__ros_msg_type * ros_message = static_cast<const _Command__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: command
  {
    size_t item_size = sizeof(ros_message->command);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: odometry
  current_alignment += get_serialized_size_key_robot_interfaces__msg__Odometry(
    &(ros_message->odometry), current_alignment);

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
size_t max_serialized_size_key_robot_interfaces__msg__Command(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: command
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: odometry
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_robot_interfaces__msg__Odometry(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robot_interfaces__msg__Command;
    is_plain =
      (
      offsetof(DataType, odometry) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _Command__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const robot_interfaces__msg__Command * ros_message = static_cast<const robot_interfaces__msg__Command *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_robot_interfaces__msg__Command(ros_message, cdr);
}

static bool _Command__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  robot_interfaces__msg__Command * ros_message = static_cast<robot_interfaces__msg__Command *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_robot_interfaces__msg__Command(cdr, ros_message);
}

static uint32_t _Command__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robot_interfaces__msg__Command(
      untyped_ros_message, 0));
}

static size_t _Command__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robot_interfaces__msg__Command(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Command = {
  "robot_interfaces::msg",
  "Command",
  _Command__cdr_serialize,
  _Command__cdr_deserialize,
  _Command__get_serialized_size,
  _Command__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _Command__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Command,
  get_message_typesupport_handle_function,
  &robot_interfaces__msg__Command__get_type_hash,
  &robot_interfaces__msg__Command__get_type_description,
  &robot_interfaces__msg__Command__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_interfaces, msg, Command)() {
  return &_Command__type_support;
}

#if defined(__cplusplus)
}
#endif
