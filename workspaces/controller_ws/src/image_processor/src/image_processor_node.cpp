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
  
  rclcpp::QoS video_qos_profile(1); // Queue depth of 1 for the latest frame
  video_qos_profile.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
  video_qos_profile.durability(RMW_QOS_POLICY_DURABILITY_VOLATILE);
  video_qos_profile.history(RMW_QOS_POLICY_HISTORY_KEEP_LAST);

  image_publisher = this->create_publisher<sensor_msgs::msg::Image>("processed_image", video_qos_profile);
  image_subscriber = this->create_subscription<sensor_msgs::msg::CompressedImage>("compressed_image", video_qos_profile, std::bind(&ImageProcessorNode::process_image_callback, this, _1));
  bin_image_subscriber = this->create_subscription<robot_interfaces::msg::BinImg>("bin_image", video_qos_profile, std::bind(&ImageProcessorNode::process_bin_image_callback, this, _1));

}

void ImageProcessorNode::publish_processed_image(cv::Mat &img) const {

  cv_bridge::CvImage cv_image;
  cv_image.encoding = "mono8";
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

void ImageProcessorNode::decode_img(const std::vector<uint8_t> &encoded_img, cv::Mat &binary_img) const {
    uint8_t *data_ptr = binary_img.data;
    for(uint32_t i = 0; i < encoded_img.size(); i++) {
        for(uint8_t j = 0; j < 8; j++) {
            data_ptr[(i * 8) + j] = ((encoded_img[i] >> (7 - j)) & 0x01) * 255;
	}
    }
}

void ImageProcessorNode::process_bin_image_callback(const robot_interfaces::msg::BinImg::SharedPtr msg) const {

  std::vector<int> markerIds;
  std::vector<std::vector<cv::Point2f>> markerCorners;

  cv::Mat dst, p_matrix;

  cv::Mat img(msg->image_rows, msg->image_cols, CV_8UC1);

  this->decode_img(msg->data, img);

  // initialize transformation points
  cv::Point2f src_pts[4];
  const cv::Point2f dst_pts[4] = {cv::Point2f(0, 0), cv::Point2f(width, 0), cv::Point2f(0, height), cv::Point2f(width, height)};

        
  detector.detectMarkers(img, markerCorners, markerIds);
  //cv::aruco::drawDetectedMarkers(img, markerCorners, markerIds);

  // check if all markers are detected
  if(markerIds.size() < 5)
    return; 


  // get markers positions
  for(int i = 0; i < markerIds.size(); i++) 
    if(markerIds[i] < 4)//9) // 4
      src_pts[markerIds[i]]/* - 5]*/ = markerCorners[i][0]; // no -5

  // get transformation matrix     
  p_matrix = cv::getPerspectiveTransform(src_pts, dst_pts);

  cv::warpPerspective(img, dst, p_matrix, cv::Size(width, height));

  detector.detectMarkers(dst, markerCorners, markerIds);
        
  cv::imshow("dst", dst);
  cv::waitKey(1);

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

  this->publish_processed_image(dst);

}

void ImageProcessorNode::process_image_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg) const {

    
  std::vector<int> markerIds;
  std::vector<std::vector<cv::Point2f>> markerCorners;

  cv::Mat img, dst, p_matrix;

  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(msg, "mono8");
  } catch(cv_bridge::Exception& e) {
    RCLCPP_ERROR(this->get_logger(), "cv_bridge exception %s", e.what());
    return;
  }

  img = cv_ptr->image;
  cv::imshow("img", img);
  RCLCPP_INFO(this->get_logger(), "recieved image");
  cv::waitKey(2);
/*  //
  // initialize transformation points
  cv::Point2f src_pts[4];
  const cv::Point2f dst_pts[4] = {cv::Point2f(0, 0), cv::Point2f(width, 0), cv::Point2f(0, height), cv::Point2f(width, height)};

        
  detector.detectMarkers(img, markerCorners, markerIds);
//  cv::aruco::drawDetectedMarkers(img, markerCorners, markerIds);
        
  // check if all markers are detected
  if(markerIds.size() < 5)
    return; 


  // get markers positions
  for(int i = 0; i < markerIds.size(); i++) 
    if(markerIds[i] < 9) // 4
      src_pts[markerIds[i] - 5] = markerCorners[i][0]; // no -5

  // get transformation matrix     
  p_matrix = cv::getPerspectiveTransform(src_pts, dst_pts);

  cv::warpPerspective(img, dst, p_matrix, cv::Size(width, height));

  detector.detectMarkers(dst, markerCorners, markerIds);
        
  cv::imshow("dst", dst);
  cv::waitKey(1);

  for(int i = 0; i < markerIds.size(); i++)
    if(markerIds[i] == robot_marker_id) {
      float theta = std::atan2((markerCorners[i][1].y - markerCorners[i][0].y), (markerCorners[i][1].x - markerCorners[i][0].x));
      theta *=  180 / M_PI;
      theta = theta >= 0 ? theta : 360 + theta;
      this->publish_position(((markerCorners[i][0].x + markerCorners[i][2].x) / 2), 
                      ((markerCorners[i][0].y + markerCorners[i][2].y) / 2),
                      theta);
      break;
    }

  this->publish_processed_image(dst);
*/
}
