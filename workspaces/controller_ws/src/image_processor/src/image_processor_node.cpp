#include "image_processor/image_processor_node.hpp"
#include <cv_bridge/cv_bridge.hpp>

using std::placeholders::_1;

extern const int robot_marker_id;
extern const int markers_cw_ids[4];
extern const uint32_t width;
extern const uint32_t height;

// initialize markers dictionary

    
// initialize marker detector
extern const cv::aruco::ArucoDetector detector;


ImageProcessorNode::ImageProcessorNode() : Node("image_processor_node")
{

  robot_position_publisher = this->create_publisher<robot_interfaces::msg::Odometry>("robot_position", 10);
  ////////////////////////////////////////////////////////////////////////////////////
  image_publisher = this->create_publisher<sensor_msgs::msg::Image>("processed_image", 10);
  image_subscriber = this->create_subscription<sensor_msgs::msg::Image>("image", 10, std::bind(&ImageProcessorNode::process_image_callback, this, _1));

}

void ImageProcessorNode::publish_processed_image(cv::Mat &img) const {

  cv_bridge::CvImage cv_image;
  cv_image.encoding = "bgr8";
  cv_image.header.stamp = rclcpp::Clock().now();
  cv_image.header.frame_id = "camera_frame";
  cv_image.image = img;
  
  auto message = sensor_msgs::msg::Image();
  cv_image.toImageMsg(message); 
    
  image_publisher->publish(message);
}

void ImageProcessorNode::publish_position(float x, float y, float theta) const {
    auto message = robot_interfaces::msg::Odometry();
    message.x = x;
    message.y = y;
    message.theta = theta;

    RCLCPP_INFO(this->get_logger(), "Publishing:\n x: '%f', y: '%f', theta: '%f'", message.x, message.y, message.theta);

    robot_position_publisher->publish(message);
}

void ImageProcessorNode::process_image_callback(const sensor_msgs::msg::Image::SharedPtr msg) const {

    
  std::vector<int> markerIds;
  std::vector<std::vector<cv::Point2f>> markerCorners;




  cv::Mat img, dst, p_matrix;

  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
  } catch(cv_bridge::Exception& e) {
    RCLCPP_ERROR(this->get_logger(), "cv_bridge exception %s", e.what());
    return;
  }

  img = cv_ptr->image;

  // initialize transformation points
  cv::Point2f src_pts[4];
  const cv::Point2f dst_pts[4] = {cv::Point2f(0, 0), cv::Point2f(width, 0), cv::Point2f(0, height), cv::Point2f(width, height)};

        
  detector.detectMarkers(img, markerCorners, markerIds);
        
  // check if all markers are detected
  if(markerIds.size() < 5)
    return; 


  // get markers positions
  for(int i = 0; i < markerIds.size(); i++) 
    if(markerIds[i] < 4)
      src_pts[markerIds[i]] = markerCorners[i][0];

  // get transformation matrix     
  p_matrix = cv::getPerspectiveTransform(src_pts, dst_pts);

  cv::warpPerspective(img, dst, p_matrix, cv::Size(width, height));

  detector.detectMarkers(dst, markerCorners, markerIds);
        
  cv::imshow("dst", dst);

  for(int i = 0; i < markerIds.size(); i++)
    if(markerIds[i] == robot_marker_id)
      this->publish_position(  ((markerCorners[i][0].x + markerCorners[i][2].x) / 2), 
                      ((markerCorners[i][0].y + markerCorners[i][2].y) / 2),
                      std::atan2((markerCorners[i][1].y - markerCorners[i][0].y), (markerCorners[i][1].x - markerCorners[i][0].x)) * 180 / M_PI );
 
  this->publish_processed_image(img);

}
