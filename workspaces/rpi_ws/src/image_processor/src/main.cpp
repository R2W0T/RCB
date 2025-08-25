#include "image_processor/image_processor_node.hpp"

#include "rclcpp/rclcpp.hpp"

///////////////////////////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp> 
//#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/videoio.hpp>

#include <chrono>
#include <thread>


//////////////////////////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
volatile const int dict = cv::aruco::DICT_APRILTAG_25h9;
volatile const int robot_marker_id = 9;//4;
volatile const int markers_cw_ids[4] = {5, 6, 7, 8};//{0, 1, 2, 3};//{5, 6, 7, 8};//
volatile const uint32_t width = 500, height = 500;

// initialize markers dictionary
cv::Ptr<cv::aruco::Dictionary> dictionary;
cv::Ptr<cv::aruco::DetectorParameters> detectorParams;

//cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(dict);
//cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();


//volatile const cv::aruco::ArucoDetector detector(dictionary, detectorParams);

int main(int argc, char *argv[]) {

    dictionary = cv::aruco::getPredefinedDictionary(dict);
    detectorParams = cv::aruco::DetectorParameters::create();

    //dictionary = cv::aruco::getPredefinedDictionary(dict);
    //detectorParams = cv::aruco::DetectorParameters();
    cv::Mat img;

    // open video device 
    int api_id = cv::CAP_ANY; 
    int device_id = 0;
    cv::VideoCapture cap;
    cap.open(device_id, api_id);

    if(!cap.isOpened()) {
        std::cerr << "failed to open vid capture dvice\n";
        return -1;
    }
    
    // ros init
    rclcpp::init(argc, argv);

    auto node = std::make_shared<ImageProcessorNode>();

    uint8_t counter = 0;
    while(true) {        
      std::this_thread::sleep_for(std::chrono::milliseconds(30));    
      
      cap.read(img);
        
      // check if all markers are detected
      node->process_image(img, counter);
      counter++;
    }
    
    rclcpp::shutdown();

    
    cv::destroyAllWindows();
    cap.release();


    return 0;
}
