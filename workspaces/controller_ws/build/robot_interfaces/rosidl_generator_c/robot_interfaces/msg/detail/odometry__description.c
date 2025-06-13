// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from robot_interfaces:msg/Odometry.idl
// generated code does not contain a copyright notice

#include "robot_interfaces/msg/detail/odometry__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_robot_interfaces
const rosidl_type_hash_t *
robot_interfaces__msg__Odometry__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x0b, 0xd8, 0x07, 0x80, 0x32, 0x57, 0x99, 0x26,
      0x2c, 0xe3, 0x03, 0xba, 0xc0, 0x96, 0xa2, 0x1e,
      0x0d, 0x1a, 0xbe, 0xdc, 0xc3, 0x1f, 0x7d, 0x39,
      0x19, 0x82, 0x77, 0x11, 0xec, 0xd1, 0xb7, 0xe6,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char robot_interfaces__msg__Odometry__TYPE_NAME[] = "robot_interfaces/msg/Odometry";

// Define type names, field names, and default values
static char robot_interfaces__msg__Odometry__FIELD_NAME__x[] = "x";
static char robot_interfaces__msg__Odometry__FIELD_NAME__y[] = "y";
static char robot_interfaces__msg__Odometry__FIELD_NAME__theta[] = "theta";

static rosidl_runtime_c__type_description__Field robot_interfaces__msg__Odometry__FIELDS[] = {
  {
    {robot_interfaces__msg__Odometry__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__Odometry__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__Odometry__FIELD_NAME__theta, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
robot_interfaces__msg__Odometry__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {robot_interfaces__msg__Odometry__TYPE_NAME, 29, 29},
      {robot_interfaces__msg__Odometry__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 x\n"
  "float32 y\n"
  "float32 theta";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
robot_interfaces__msg__Odometry__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {robot_interfaces__msg__Odometry__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 33, 33},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
robot_interfaces__msg__Odometry__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *robot_interfaces__msg__Odometry__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
