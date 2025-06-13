// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_interfaces:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/command.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__COMMAND__TRAITS_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_interfaces/msg/detail/command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'odometry'
#include "robot_interfaces/msg/detail/odometry__traits.hpp"

namespace robot_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Command & msg,
  std::ostream & out)
{
  out << "{";
  // member: command
  {
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << ", ";
  }

  // member: odometry
  {
    out << "odometry: ";
    to_flow_style_yaml(msg.odometry, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Command & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << "\n";
  }

  // member: odometry
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "odometry:\n";
    to_block_style_yaml(msg.odometry, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Command & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace robot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_interfaces::msg::Command & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_interfaces::msg::Command & msg)
{
  return robot_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_interfaces::msg::Command>()
{
  return "robot_interfaces::msg::Command";
}

template<>
inline const char * name<robot_interfaces::msg::Command>()
{
  return "robot_interfaces/msg/Command";
}

template<>
struct has_fixed_size<robot_interfaces::msg::Command>
  : std::integral_constant<bool, has_fixed_size<robot_interfaces::msg::Odometry>::value> {};

template<>
struct has_bounded_size<robot_interfaces::msg::Command>
  : std::integral_constant<bool, has_bounded_size<robot_interfaces::msg::Odometry>::value> {};

template<>
struct is_message<robot_interfaces::msg::Command>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_INTERFACES__MSG__DETAIL__COMMAND__TRAITS_HPP_
