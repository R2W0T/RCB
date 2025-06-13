// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_interfaces:msg/Speed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/speed.h"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__SPEED__STRUCT_H_
#define ROBOT_INTERFACES__MSG__DETAIL__SPEED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Speed in the package robot_interfaces.
typedef struct robot_interfaces__msg__Speed
{
  int32_t linear_speed;
  int32_t rotational_speed;
} robot_interfaces__msg__Speed;

// Struct for a sequence of robot_interfaces__msg__Speed.
typedef struct robot_interfaces__msg__Speed__Sequence
{
  robot_interfaces__msg__Speed * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_interfaces__msg__Speed__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_INTERFACES__MSG__DETAIL__SPEED__STRUCT_H_
