#pragma once

#include <inttypes.h>

#include <cv_bridge/cv_bridge.hpp>
#include "rclcpp/rclcpp.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/speed.hpp"

#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/image.hpp>

class CameraDriverNode : public rclcpp::Node
{
  public:
    CameraDriverNode();
   
    void publish(cv::Mat &img);

  private:
    
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher;
    
};

