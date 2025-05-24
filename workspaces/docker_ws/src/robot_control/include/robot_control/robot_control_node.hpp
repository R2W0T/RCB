#pragma once

#include <inttypes.h>

#include "rclcpp/rclcpp.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/speed.hpp"

class RobotControlNode : public rclcpp::Node
{
  public:
    RobotControlNode();
   
    void publish(int32_t linear_speed, int32_t rotational_speed);

  private:
    
    void position_topic_callback(const robot_interfaces::msg::Odometry::SharedPtr msg) const;
    
    void command_topic_callback(const robot_interfaces::msg::Command::SharedPtr msg) const;
    
    void joystick_topic_callback(const robot_interfaces::msg::Speed::SharedPtr msg) const;
    
    rclcpp::Subscription<robot_interfaces::msg::Odometry>::SharedPtr position_subscription;
    
    rclcpp::Subscription<robot_interfaces::msg::Command>::SharedPtr command_subscription;
    
    rclcpp::Subscription<robot_interfaces::msg::Speed>::SharedPtr joystick_subscription;
    
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<robot_interfaces::msg::Speed>::SharedPtr speed_publisher;
    
};

