#include "camera_driver/camera_driver_node.hpp"


using std::placeholders::_1;

CameraDriverNode::CameraDriverNode() : Node("camera_driver_node") {
    ////////////////////////////////////////////////////////////////////////////////////
    image_publisher = this->create_publisher<sensor_msgs::msg::Image>("image", 10);

        
}

void CameraDriverNode::publish(cv::Mat &img) {
    
    cv_bridge::CvImage cv_image;
    cv_image.encoding = "bgr8";
    cv_image.header.stamp = rclcpp::Clock().now();
    cv_image.header.frame_id = "camera_frame";
    cv_image.image = img;
    
    auto message = sensor_msgs::msg::Image();
    cv_image.toImageMsg(message); 
    
    image_publisher->publish(message);
}
