#pragma once

#include <inttypes.h>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include <opencv2/opencv.hpp>

#include "sensor_msgs/msg/compressed_image.hpp"
#include "sensor_msgs/msg/image.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/velocity.hpp"
#include "robot_interfaces/msg/bin_img.hpp"

class ImageProcessorNode : public rclcpp::Node
{
  public:
    ImageProcessorNode();
   
    void publish_processed_image(cv::Mat &img) const;
    void process_image_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg) const;
    void process_bin_image_callback(const robot_interfaces::msg::BinImg::SharedPtr msg) const;
    void publish_position(float x, float y, float theta) const;

    void decode_img(const std::vector<uint8_t> &encoded_img, cv::Mat &binary_img) const;

  private:
    
    rclcpp::Publisher<robot_interfaces::msg::Odometry>::SharedPtr robot_position_publisher;
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher;
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr image_subscriber;
    rclcpp::Subscription<robot_interfaces::msg::BinImg>::SharedPtr bin_image_subscriber;
    
};

