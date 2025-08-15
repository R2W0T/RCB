#pragma once

#include <inttypes.h>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/velocity.hpp"
#include "robot_interfaces/msg/bin_img.hpp"

#include <opencv2/opencv.hpp>

class CameraDriverBinNode : public rclcpp::Node
{
  public:
    CameraDriverBinNode();
   
    void publish(cv::Mat &img);
    void encode_img(const cv::Mat &binary_img, std::vector<uint8_t> &encoded_img);

  private:
    
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<robot_interfaces::msg::BinImg>::SharedPtr bin_image_publisher;
    
};

