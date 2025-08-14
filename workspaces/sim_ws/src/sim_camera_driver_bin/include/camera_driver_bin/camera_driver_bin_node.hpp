#pragma once

#include <inttypes.h>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/speed.hpp"
#include "robot_interfaces/msg/bin_img.hpp"

#include <opencv2/opencv.hpp>

class CameraDriverBinNode : public rclcpp::Node
{
  public:
    CameraDriverBinNode();
   
    void publish(cv::Mat &img) const;
    void encode_img(const cv::Mat &binary_img, std::vector<uint8_t> &encoded_img) const;
    void process_image_callback(const sensor_msgs::msg::Image::SharedPtr msg) const;

  private:
    
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<robot_interfaces::msg::BinImg>::SharedPtr bin_image_publisher;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber;
};

