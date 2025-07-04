#pragma once

#include <inttypes.h>

#include "rclcpp/rclcpp.hpp"

#include <opencv2/opencv.hpp>

#include "sensor_msgs/msg/image.hpp"

#include "robot_interfaces/msg/odometry.hpp"
#include "robot_interfaces/msg/command.hpp"
#include "robot_interfaces/msg/speed.hpp"

class ImageProcessorNode : public rclcpp::Node
{
  public:
    ImageProcessorNode();
   
    void publish_processed_image(cv::Mat &img) const;
    void process_image_callback(const sensor_msgs::msg::Image::SharedPtr msg) const;
    void publish_position(float x, float y, float theta) const;

  private:
    
    rclcpp::Publisher<robot_interfaces::msg::Odometry>::SharedPtr robot_position_publisher;
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber;
    
};

