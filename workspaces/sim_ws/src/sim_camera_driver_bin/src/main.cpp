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

    // ros init
    rclcpp::init(argc, argv);

    auto node = std::make_shared<CameraDriverBinNode>();

    rclcpp::spin(node);
    
    rclcpp::shutdown();

    
    cv::destroyAllWindows();


    return 0;
}
