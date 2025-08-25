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

enum state {
  SLEEP = 0,
  PUBLISH = 1
};

class ImageProcessorNode : public rclcpp::Node
{
  public:
    ImageProcessorNode();
   
    void publish_processed_image(cv::Mat &img) const; 
    void process_image(cv::Mat &img); 
    void publish_position(float x, float y, float theta) const;

     

  private:
    uint8_t state;

    void command_subscription_callback(const robot_interfaces::msg::Command::SharedPtr msg);
    
    rclcpp::Publisher<robot_interfaces::msg::Odometry>::SharedPtr robot_position_publisher;
    //////////////////////////////////////////////////////////////////////////////////////
    rclcpp::Publisher<sensor_msgs::msg::CompressedImage>::SharedPtr image_publisher;
    
    rclcpp::Subscription<robot_interfaces::msg::Command>::SharedPtr command_subscription;
    
};

