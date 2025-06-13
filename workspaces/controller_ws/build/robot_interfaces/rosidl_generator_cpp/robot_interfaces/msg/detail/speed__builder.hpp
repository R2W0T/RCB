// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_interfaces:msg/Speed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/speed.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__SPEED__BUILDER_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__SPEED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_interfaces/msg/detail/speed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_interfaces
{

namespace msg
{

namespace builder
{

class Init_Speed_rotational_speed
{
public:
  explicit Init_Speed_rotational_speed(::robot_interfaces::msg::Speed & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::msg::Speed rotational_speed(::robot_interfaces::msg::Speed::_rotational_speed_type arg)
  {
    msg_.rotational_speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::msg::Speed msg_;
};

class Init_Speed_linear_speed
{
public:
  Init_Speed_linear_speed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Speed_rotational_speed linear_speed(::robot_interfaces::msg::Speed::_linear_speed_type arg)
  {
    msg_.linear_speed = std::move(arg);
    return Init_Speed_rotational_speed(msg_);
  }

private:
  ::robot_interfaces::msg::Speed msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::msg::Speed>()
{
  return robot_interfaces::msg::builder::Init_Speed_linear_speed();
}

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__MSG__DETAIL__SPEED__BUILDER_HPP_
