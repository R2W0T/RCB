#include "image_processor/image_processor_node.hpp"
#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/aruco.hpp>

using std::placeholders::_1;

extern const int robot_marker_id;
extern const int markers_cw_ids[4];
extern const uint32_t width;
extern const uint32_t height;
    
extern cv::Ptr<cv::aruco::Dictionary> dictionary;
extern cv::Ptr<cv::aruco::DetectorParameters> detectorParams;


ImageProcessorNode::ImageProcessorNode() : Node("image_processor_node")
{

  this->state = PUBLISH;

  robot_position_publisher = this->create_publisher<robot_interfaces::msg::Odometry>("robot_position", 10);
  ////////////////////////////////////////////////////////////////////////////////////
  
  rclcpp::QoS video_qos_profile(1); // Queue depth of 1 for the latest frame
  video_qos_profile.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
  video_qos_profile.durability(RMW_QOS_POLICY_DURABILITY_VOLATILE);
  video_qos_profile.history(RMW_QOS_POLICY_HISTORY_KEEP_LAST);

  compressed_image_publisher = this->create_publisher<sensor_msgs::msg::CompressedImage>("compressed_processed_image", video_qos_profile);
  command_subscription = this->create_subscription<robot_interfaces::msg::Command>(
      "image_command", 10, std::bind(&ImageProcessorNode::command_subscription_callback, this, _1));
}

void ImageProcessorNode::command_subscription_callback(const robot_interfaces::msg::Command::SharedPtr msg) {
  this->state = msg->command;
}

void ImageProcessorNode::publish_compressed_processed_image(cv::Mat &img) const {

  cv_bridge::CvImage cv_image;
  cv_image.encoding = "mono8";
  cv_image.header.stamp = rclcpp::Clock().now();
  cv_image.header.frame_id = "camera_frame";
  cv_image.image = img;

  auto message = sensor_msgs::msg::CompressedImage();
  cv_image.toCompressedImageMsg(message, cv_bridge::Format::JPEG); 
  
  compressed_image_publisher->publish(message);
}

void ImageProcessorNode::publish_position(float x, float y, float theta) const {
    auto message = robot_interfaces::msg::Odometry();
    message.x = x;
    message.y = y;
    message.theta = theta;

    RCLCPP_INFO(this->get_logger(), "Publishing:\n x: '%f', y: '%f', theta: '%f'", message.x, message.y, message.theta);

    robot_position_publisher->publish(message);
}

void ImageProcessorNode::process_image(cv::Mat& img) {
  cv::imshow("hell", img);
  cv::waitKey(2);
  cv::Mat gray_img, binary_img;
  cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
  //cv::threshold(gray_img, gray_img, 70, 1, cv::THRESH_BINARY);
    
  cv::imshow("hel", gray_img);

  if(this->state == PUBLISH_MAIN) {
    this->publish_compressed_processed_image(gray_img);
    RCLCPP_INFO(this->get_logger(), "Publishing: 4");
    // return;
  }
  std::vector<int> markerIds;
  std::vector<std::vector<cv::Point2f>> markerCorners;

  cv::Mat dst, p_matrix;

  // initialize transformation points
  cv::Point2f src_pts[4];
  const cv::Point2f dst_pts[4] = {cv::Point2f(0, 0), cv::Point2f(width, 0), cv::Point2f(0, height), cv::Point2f(width, height)};

        
  cv::aruco::detectMarkers(gray_img, dictionary, markerCorners, markerIds, detectorParams);

  RCLCPP_INFO(this->get_logger(), "Publishing: 1, %ld", markerIds.size());
  // check if all markers are detected
  if(markerIds.size() < 5)
    return; 


  RCLCPP_INFO(this->get_logger(), "Publishing: 2");
  // get markers positions
  for(int i = 0; i < markerIds.size(); i++) {
    RCLCPP_INFO(this->get_logger(), "Publishing: 2");
    for(int j = 0; j < 4 ; j++) {
      if(markerIds[i] == markers_cw_ids[j]) {
        src_pts[j] = markerCorners[i][0];
      }
    }
  }

  RCLCPP_INFO(this->get_logger(), "Publishing: 0, (%f, %f), (%f, %f), (%f, %f), (%f, %f)", src_pts[0].x, src_pts[0].y, src_pts[1].x, src_pts[1].y, src_pts[2].x, src_pts[2].y, src_pts[3].x, src_pts[3].y);

  // get transformation matrix     
  p_matrix = cv::getPerspectiveTransform(src_pts, dst_pts);

  cv::warpPerspective(gray_img, dst, p_matrix, cv::Size(width, height));

  cv::aruco::detectMarkers(dst, dictionary, markerCorners, markerIds, detectorParams);
        
  cv::imshow("hl", dst);
  cv::aruco::detectMarkers(dst, dictionary, markerCorners, markerIds);
  cv::imshow("h", dst);


  for(int i = 0; i < markerIds.size(); i++)
    if(markerIds[i] == robot_marker_id) {
      float theta = std::atan2((markerCorners[i][0].y - markerCorners[i][1].y), (markerCorners[i][1].x - markerCorners[i][0].x));
      theta *=  180 / M_PI;
      theta = theta >= 0 ?  theta : 360 + theta;
      this->publish_position(((markerCorners[i][0].x + markerCorners[i][2].x) / 2), 
                      ((markerCorners[i][0].y + markerCorners[i][2].y) / 2),
                      theta);
      break;
    }

  cv::imshow("he", dst);
  if(this->state == PUBLISH) {
    this->publish_compressed_processed_image(dst);
    RCLCPP_INFO(this->get_logger(), "Publishing: 3");
  }
}
