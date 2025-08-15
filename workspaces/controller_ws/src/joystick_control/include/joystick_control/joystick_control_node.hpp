#pragma once

#include <inttypes.h>

#include "rclcpp/rclcpp.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/velocity.hpp"

class JoystickControlNode : public rclcpp::Node
{
  public:
    JoystickControlNode();
   
    void publish(int32_t linear_velocity, int32_t angular_velocity);

  private:
    
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<robot_interfaces::msg::Velocity>::SharedPtr joystick_publisher;
    
};

