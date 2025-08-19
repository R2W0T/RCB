#include "camera_driver_bin/camera_driver_bin_node.hpp"

#include "rclcpp/rclcpp.hpp"

///////////////////////////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp> 
#include <opencv2/videoio.hpp>

#include <chrono>
#include <thread>


//////////////////////////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

    cv::Mat img;

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

    auto node = std::make_shared<CameraDriverBinNode>();

    while(true) { //cv::pollKey() == -1) {
        
      std::this_thread::sleep_for(std::chrono::milliseconds(30));    
      
      cap.read(img);
      //cv::imshow("img", img);
        
      // check if all markers are detected
      node->publish(img);     
    }
    
    rclcpp::shutdown();

    
    cv::destroyAllWindows();
    cap.release();


    return 0;
}
