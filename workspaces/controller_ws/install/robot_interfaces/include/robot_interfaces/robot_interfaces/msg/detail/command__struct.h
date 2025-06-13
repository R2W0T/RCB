// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_interfaces:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/command.h"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__COMMAND__STRUCT_H_
#define ROBOT_INTERFACES__MSG__DETAIL__COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'odometry'
#include "robot_interfaces/msg/detail/odometry__struct.h"

/// Struct defined in msg/Command in the package robot_interfaces.
typedef struct robot_interfaces__msg__Command
{
  uint8_t command;
  robot_interfaces__msg__Odometry odometry;
} robot_interfaces__msg__Command;

// Struct for a sequence of robot_interfaces__msg__Command.
typedef struct robot_interfaces__msg__Command__Sequence
{
  robot_interfaces__msg__Command * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_interfaces__msg__Command__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_INTERFACES__MSG__DETAIL__COMMAND__STRUCT_H_
