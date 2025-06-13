// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_interfaces:msg/Speed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/speed.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__SPEED__TRAITS_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__SPEED__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_interfaces/msg/detail/speed__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Speed & msg,
  std::ostream & out)
{
  out << "{";
  // member: linear_speed
  {
    out << "linear_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.linear_speed, out);
    out << ", ";
  }

  // member: rotational_speed
  {
    out << "rotational_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.rotational_speed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Speed & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: linear_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linear_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.linear_speed, out);
    out << "\n";
  }

  // member: rotational_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rotational_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.rotational_speed, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Speed & msg, bool use_flow_style = false)
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
  const robot_interfaces::msg::Speed & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_interfaces::msg::Speed & msg)
{
  return robot_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_interfaces::msg::Speed>()
{
  return "robot_interfaces::msg::Speed";
}

template<>
inline const char * name<robot_interfaces::msg::Speed>()
{
  return "robot_interfaces/msg/Speed";
}

template<>
struct has_fixed_size<robot_interfaces::msg::Speed>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robot_interfaces::msg::Speed>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robot_interfaces::msg::Speed>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_INTERFACES__MSG__DETAIL__SPEED__TRAITS_HPP_
