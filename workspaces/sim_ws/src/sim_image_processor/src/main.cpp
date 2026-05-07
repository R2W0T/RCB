#include "image_processor/image_processor_node.hpp"

#include "rclcpp/rclcpp.hpp"

///////////////////////////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp> 
#include <opencv2/aruco.hpp>
#include <opencv2/videoio.hpp>

#include <chrono>
#include <thread>


//////////////////////////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
volatile const int dict = cv::aruco::DICT_APRILTAG_25h9;
volatile const int robot_marker_id = 4;
volatile const int markers_cw_ids[4] = {0, 1, 2, 3};//{5, 6, 7, 8};//
volatile const uint32_t width = 640, height = 480;

cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(dict);
cv::Ptr<cv::aruco::DetectorParameters> detectorParams = cv::aruco::DetectorParameters::create();


int main(int argc, char *argv[]) {

    rclcpp::init(argc, argv);

    auto node = std::make_shared<ImageProcessorNode>();
    
    rclcpp::spin(node);
   
    rclcpp::shutdown();

    std::cout << "Hell" << std::endl;

    return 0;
}
