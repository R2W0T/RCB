#pragma once

#include <inttypes.h>

#include "rclcpp/rclcpp.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/velocity.hpp"

#include <memory>

class RobotControlNode : public rclcpp::Node
{
  public:
    RobotControlNode();
   
    void publish(int32_t linear_velocity, int32_t angular_velocity);

  private:
    
    void position_topic_callback(const robot_interfaces::msg::Odometry::SharedPtr msg) const;
    
    void command_topic_callback(const robot_interfaces::msg::Command::SharedPtr msg) const;
    
    void joystick_topic_callback(const robot_interfaces::msg::Velocity::SharedPtr msg) const;
    
    rclcpp::Subscription<robot_interfaces::msg::Odometry>::SharedPtr position_subscription;
    
    rclcpp::Subscription<robot_interfaces::msg::Command>::SharedPtr command_subscription;
    
    rclcpp::Subscription<robot_interfaces::msg::Velocity>::SharedPtr joystick_subscription;
    
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<robot_interfaces::msg::Velocity>::SharedPtr velocity_publisher;
    
};

