// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_interfaces:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/command.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__COMMAND__BUILDER_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_interfaces/msg/detail/command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_interfaces
{

namespace msg
{

namespace builder
{

class Init_Command_odometry
{
public:
  explicit Init_Command_odometry(::robot_interfaces::msg::Command & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::msg::Command odometry(::robot_interfaces::msg::Command::_odometry_type arg)
  {
    msg_.odometry = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::msg::Command msg_;
};

class Init_Command_command
{
public:
  Init_Command_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Command_odometry command(::robot_interfaces::msg::Command::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_Command_odometry(msg_);
  }

private:
  ::robot_interfaces::msg::Command msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::msg::Command>()
{
  return robot_interfaces::msg::builder::Init_Command_command();
}

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__MSG__DETAIL__COMMAND__BUILDER_HPP_
