#pragma once

#include <inttypes.h>

#include "rclcpp/rclcpp.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/speed.hpp"

class JoystickControlNode : public rclcpp::Node
{
  public:
    JoystickControlNode();
   
    void publish(int32_t linear_speed, int32_t rotational_speed);

  private:
    
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<robot_interfaces::msg::Speed>::SharedPtr joystick_publisher;
    
};

