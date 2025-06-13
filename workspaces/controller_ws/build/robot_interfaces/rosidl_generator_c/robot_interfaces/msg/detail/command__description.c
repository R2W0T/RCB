// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from robot_interfaces:msg/Command.idl
// generated code does not contain a copyright notice

#include "robot_interfaces/msg/detail/command__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_robot_interfaces
const rosidl_type_hash_t *
robot_interfaces__msg__Command__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x9b, 0x3c, 0xff, 0xc8, 0x63, 0xe3, 0xb5, 0x39,
      0xfc, 0xde, 0x0a, 0x5d, 0x52, 0x29, 0x94, 0x85,
      0xa1, 0x91, 0x9a, 0x37, 0x14, 0xd7, 0xc4, 0xa1,
      0xe9, 0x9a, 0x22, 0xf7, 0x6f, 0x92, 0xdb, 0x57,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "robot_interfaces/msg/detail/odometry__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t robot_interfaces__msg__Odometry__EXPECTED_HASH = {1, {
    0x0b, 0xd8, 0x07, 0x80, 0x32, 0x57, 0x99, 0x26,
    0x2c, 0xe3, 0x03, 0xba, 0xc0, 0x96, 0xa2, 0x1e,
    0x0d, 0x1a, 0xbe, 0xdc, 0xc3, 0x1f, 0x7d, 0x39,
    0x19, 0x82, 0x77, 0x11, 0xec, 0xd1, 0xb7, 0xe6,
  }};
#endif

static char robot_interfaces__msg__Command__TYPE_NAME[] = "robot_interfaces/msg/Command";
static char robot_interfaces__msg__Odometry__TYPE_NAME[] = "robot_interfaces/msg/Odometry";

// Define type names, field names, and default values
static char robot_interfaces__msg__Command__FIELD_NAME__command[] = "command";
static char robot_interfaces__msg__Command__FIELD_NAME__odometry[] = "odometry";

static rosidl_runtime_c__type_description__Field robot_interfaces__msg__Command__FIELDS[] = {
  {
    {robot_interfaces__msg__Command__FIELD_NAME__command, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__Command__FIELD_NAME__odometry, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {robot_interfaces__msg__Odometry__TYPE_NAME, 29, 29},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription robot_interfaces__msg__Command__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {robot_interfaces__msg__Odometry__TYPE_NAME, 29, 29},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
robot_interfaces__msg__Command__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {robot_interfaces__msg__Command__TYPE_NAME, 28, 28},
      {robot_interfaces__msg__Command__FIELDS, 2, 2},
    },
    {robot_interfaces__msg__Command__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&robot_interfaces__msg__Odometry__EXPECTED_HASH, robot_interfaces__msg__Odometry__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = robot_interfaces__msg__Odometry__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint8 command\n"
  "robot_interfaces/Odometry odometry";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
robot_interfaces__msg__Command__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {robot_interfaces__msg__Command__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 48, 48},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
robot_interfaces__msg__Command__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *robot_interfaces__msg__Command__get_individual_type_description_source(NULL),
    sources[1] = *robot_interfaces__msg__Odometry__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
