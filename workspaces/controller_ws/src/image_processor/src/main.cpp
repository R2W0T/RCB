#include "image_processor/image_processor_node.hpp"

#include "rclcpp/rclcpp.hpp"

///////////////////////////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp> 
#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/videoio.hpp>

#include <chrono>
#include <thread>


//////////////////////////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
volatile const int dict = cv::aruco::DICT_APRILTAG_25h9;
volatile const int robot_marker_id = 4;
volatile const int markers_cw_ids[4] = {0, 1, 2, 3};
volatile const uint32_t width = 480, height = 480;

// initialize markers dictionary
cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(dict);

    
// initialize marker detector
cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
volatile const cv::aruco::ArucoDetector detector(dictionary, detectorParams);

int main(int argc, char *argv[]) {



    // initialize markers dictionary
//    const cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(dict);

    
    // initialize marker detector
  //  const cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    //const cv::aruco::ArucoDetector detector(dictionary, detectorParams);

    // ros init
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<ImageProcessorNode>());

    
    rclcpp::shutdown();

    
    cv::destroyAllWindows();


    return 0;
}
