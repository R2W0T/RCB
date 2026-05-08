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
// volatile const int dict = cv::aruco::DICT_APRILTAG_25h9;
volatile const int dict = cv::aruco::DICT_APRILTAG_36h11;
volatile const int robot_marker_id = 10;//5;//9;
volatile const int markers_cw_ids[4] = {0, 1, 8, 7};//{0, 1, 2, 3};//{5, 6, 7, 8};//
volatile const uint32_t width = 640, height = 480;

// initialize markers dictionary
cv::Ptr<cv::aruco::Dictionary> dictionary;
cv::Ptr<cv::aruco::DetectorParameters> detectorParams;

int main(int argc, char *argv[]) {

    dictionary = cv::aruco::getPredefinedDictionary(dict);
    detectorParams = cv::aruco::DetectorParameters::create();

    cv::Mat img;//(480, 640, CV_8UC1, cv::Scalar(255));

    // open video device 

    int api_id = cv::CAP_ANY; 
    int device_id = 2;
    cv::VideoCapture cap;
    cap.open(device_id, api_id);

    if(!cap.isOpened()) {
        std::cerr << "failed to open vid capture dvice\n";
        return -1;
    }

    // ros init
    rclcpp::init(argc, argv);

    auto node = std::make_shared<ImageProcessorNode>();
    
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);

    // In a loop or integrated with another event loop:
    while (rclcpp::ok()) {
        executor.spin_some();
        

	// cap.read(img);

	cap >> img;
	
	// check if all markers are detected
        node->process_image(img);
        
	// Do other non-ROS related work or sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
   
    rclcpp::shutdown();

    
    cv::destroyAllWindows();
    cap.release();


    return 0;
}
