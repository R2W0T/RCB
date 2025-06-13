// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from robot_interfaces:msg/Speed.idl
// generated code does not contain a copyright notice

#include "robot_interfaces/msg/detail/speed__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_robot_interfaces
const rosidl_type_hash_t *
robot_interfaces__msg__Speed__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x0f, 0xae, 0x75, 0x03, 0xfc, 0x20, 0x57, 0x5c,
      0xf6, 0x4d, 0xba, 0x2f, 0x13, 0xb9, 0x2f, 0x7c,
      0x70, 0x36, 0xbf, 0x19, 0x9c, 0x60, 0xa5, 0xb9,
      0x34, 0x00, 0x5e, 0xc4, 0x58, 0x71, 0x79, 0xb5,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char robot_interfaces__msg__Speed__TYPE_NAME[] = "robot_interfaces/msg/Speed";

// Define type names, field names, and default values
static char robot_interfaces__msg__Speed__FIELD_NAME__linear_speed[] = "linear_speed";
static char robot_interfaces__msg__Speed__FIELD_NAME__rotational_speed[] = "rotational_speed";

static rosidl_runtime_c__type_description__Field robot_interfaces__msg__Speed__FIELDS[] = {
  {
    {robot_interfaces__msg__Speed__FIELD_NAME__linear_speed, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__Speed__FIELD_NAME__rotational_speed, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
robot_interfaces__msg__Speed__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {robot_interfaces__msg__Speed__TYPE_NAME, 26, 26},
      {robot_interfaces__msg__Speed__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 linear_speed\n"
  "int32 rotational_speed";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
robot_interfaces__msg__Speed__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {robot_interfaces__msg__Speed__TYPE_NAME, 26, 26},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 41, 41},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
robot_interfaces__msg__Speed__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *robot_interfaces__msg__Speed__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
