#include "camera_driver_bin/camera_driver_bin_node.hpp"
#include <cstring> 

using std::placeholders::_1;

CameraDriverBinNode::CameraDriverBinNode() : Node("camera_driver_bin_node") {
    rclcpp::QoS video_qos_profile(1); // Queue depth of 1 for the latest frame
    video_qos_profile.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
    video_qos_profile.durability(RMW_QOS_POLICY_DURABILITY_VOLATILE);
    video_qos_profile.history(RMW_QOS_POLICY_HISTORY_KEEP_LAST);

    ////////////////////////////////////////////////////////////////////////////////////
    bin_image_publisher = this->create_publisher<robot_interfaces::msg::BinImg>("bin_image", video_qos_profile);

        
}

void CameraDriverBinNode::encode_img(const cv::Mat &binary_img, std::vector<uint8_t> &encoded_img) {
    const uint8_t *data_ptr = binary_img.data;
    for(uint32_t i = 0; i < encoded_img.size(); i++) {
        encoded_img[i] = 0;
        for(uint8_t j = 0; j < 8; j++) {
            encoded_img[i] |= (data_ptr[(i * 8) + j]) << (7 - j);
	}
    }
}

void CameraDriverBinNode::publish(cv::Mat &img) {
    
    cv::Mat gray_img, binary_img;

    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::threshold(gray_img, binary_img, 70, 1, cv::THRESH_BINARY);
    
    std::vector<uint8_t> encoded_img((int)(binary_img.rows * binary_img.cols / 8));
    this->encode_img(binary_img, encoded_img);   
    
    auto message = robot_interfaces::msg::BinImg();
    message.data = encoded_img;
    message.image_rows = binary_img.rows;
    message.image_cols = binary_img.cols;
    
    bin_image_publisher->publish(message);
}


