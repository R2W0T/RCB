#include "camera_driver/camera_driver_node.hpp"


using std::placeholders::_1;

CameraDriverNode::CameraDriverNode() : Node("camera_driver_node") {
    rclcpp::QoS video_qos_profile(1); // Queue depth of 1 for the latest frame
    video_qos_profile.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
    video_qos_profile.durability(RMW_QOS_POLICY_DURABILITY_VOLATILE);
    video_qos_profile.history(RMW_QOS_POLICY_HISTORY_KEEP_LAST);

    ////////////////////////////////////////////////////////////////////////////////////
    image_publisher = this->create_publisher<sensor_msgs::msg::CompressedImage>("image", video_qos_profile);

        
}

void CameraDriverNode::publish(cv::Mat &img) {
    
    cv_bridge::CvImage cv_image;
    cv_image.encoding = "mono8";
    cv_image.header.stamp = rclcpp::Clock().now();
    cv_image.header.frame_id = "camera_frame";
    
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    
    cv_image.image = gray_img;
    
    auto message = sensor_msgs::msg::CompressedImage();
    cv_image.toCompressedImageMsg(message); 
    
    image_publisher->publish(message);
}
