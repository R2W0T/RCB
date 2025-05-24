#pragma once

#include <inttypes.h>

#include "rclcpp/rclcpp.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/speed.hpp"

class CameraNode : public rclcpp::Node
{
  public:
    CameraNode();
   
    void publish(float x, float y, float theta);

  private:
    
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<robot_interfaces::msg::Odometry>::SharedPtr robot_position_publisher;
    
};

