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
    void process_image(cv::Mat &img, uint8_t &counter) const; 
    void publish_position(float x, float y, float theta) const;

  private:
    
    rclcpp::Publisher<robot_interfaces::msg::Odometry>::SharedPtr robot_position_publisher;
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher;
    
};

