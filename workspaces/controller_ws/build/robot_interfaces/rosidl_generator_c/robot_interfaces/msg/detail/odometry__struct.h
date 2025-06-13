// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_interfaces:msg/Odometry.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/odometry.h"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__ODOMETRY__STRUCT_H_
#define ROBOT_INTERFACES__MSG__DETAIL__ODOMETRY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Odometry in the package robot_interfaces.
typedef struct robot_interfaces__msg__Odometry
{
  float x;
  float y;
  float theta;
} robot_interfaces__msg__Odometry;

// Struct for a sequence of robot_interfaces__msg__Odometry.
typedef struct robot_interfaces__msg__Odometry__Sequence
{
  robot_interfaces__msg__Odometry * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_interfaces__msg__Odometry__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_INTERFACES__MSG__DETAIL__ODOMETRY__STRUCT_H_
