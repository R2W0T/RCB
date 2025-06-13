// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_interfaces:msg/Speed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/speed.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__SPEED__STRUCT_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__SPEED__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_interfaces__msg__Speed __attribute__((deprecated))
#else
# define DEPRECATED__robot_interfaces__msg__Speed __declspec(deprecated)
#endif

namespace robot_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Speed_
{
  using Type = Speed_<ContainerAllocator>;

  explicit Speed_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->linear_speed = 0l;
      this->rotational_speed = 0l;
    }
  }

  explicit Speed_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->linear_speed = 0l;
      this->rotational_speed = 0l;
    }
  }

  // field types and members
  using _linear_speed_type =
    int32_t;
  _linear_speed_type linear_speed;
  using _rotational_speed_type =
    int32_t;
  _rotational_speed_type rotational_speed;

  // setters for named parameter idiom
  Type & set__linear_speed(
    const int32_t & _arg)
  {
    this->linear_speed = _arg;
    return *this;
  }
  Type & set__rotational_speed(
    const int32_t & _arg)
  {
    this->rotational_speed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_interfaces::msg::Speed_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_interfaces::msg::Speed_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_interfaces::msg::Speed_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_interfaces::msg::Speed_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_interfaces::msg::Speed_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_interfaces::msg::Speed_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_interfaces::msg::Speed_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_interfaces::msg::Speed_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_interfaces::msg::Speed_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_interfaces::msg::Speed_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_interfaces__msg__Speed
    std::shared_ptr<robot_interfaces::msg::Speed_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_interfaces__msg__Speed
    std::shared_ptr<robot_interfaces::msg::Speed_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Speed_ & other) const
  {
    if (this->linear_speed != other.linear_speed) {
      return false;
    }
    if (this->rotational_speed != other.rotational_speed) {
      return false;
    }
    return true;
  }
  bool operator!=(const Speed_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Speed_

// alias to use template instance with default allocator
using Speed =
  robot_interfaces::msg::Speed_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__MSG__DETAIL__SPEED__STRUCT_HPP_
