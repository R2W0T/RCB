// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_interfaces:msg/Odometry.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/odometry.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__ODOMETRY__BUILDER_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__ODOMETRY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_interfaces/msg/detail/odometry__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_interfaces
{

namespace msg
{

namespace builder
{

class Init_Odometry_theta
{
public:
  explicit Init_Odometry_theta(::robot_interfaces::msg::Odometry & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::msg::Odometry theta(::robot_interfaces::msg::Odometry::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::msg::Odometry msg_;
};

class Init_Odometry_y
{
public:
  explicit Init_Odometry_y(::robot_interfaces::msg::Odometry & msg)
  : msg_(msg)
  {}
  Init_Odometry_theta y(::robot_interfaces::msg::Odometry::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Odometry_theta(msg_);
  }

private:
  ::robot_interfaces::msg::Odometry msg_;
};

class Init_Odometry_x
{
public:
  Init_Odometry_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Odometry_y x(::robot_interfaces::msg::Odometry::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Odometry_y(msg_);
  }

private:
  ::robot_interfaces::msg::Odometry msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::msg::Odometry>()
{
  return robot_interfaces::msg::builder::Init_Odometry_x();
}

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__MSG__DETAIL__ODOMETRY__BUILDER_HPP_
