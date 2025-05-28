#include "camera/camera_node.hpp"
#include "ImageProcessor.hpp"

#include "rclcpp/rclcpp.hpp"

///////////////////////////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp> 
#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/videoio.hpp>

#include "ImageProcessor.hpp"

static int dict = cv::aruco::DICT_APRILTAG_25h9;
static std::array<int, 4> markers_cw_ids = {0, 1, 2, 3};
static int robot_marker_id = 4;


//////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {
    // cam init
    cv::Mat img, dst;
    
    int api_id = cv::CAP_ANY; 
    int device_id = 2;
    cv::VideoCapture cap;
    cap.open(device_id, api_id);
    
    if(!cap.isOpened()) {
        std::cerr << "failed to open vid capture dvice\n";
        return -1;
    }

    std::array<cv::Point2f, 4> src_corners, dst_corners = {cv::Point2f(0, 0), cv::Point2f(500, 0), cv::Point2f(0, 500), cv::Point2f(500, 500)};
    cv::Size size(500, 500);
    
    ImageProcessor::ImageProcessor img_proc(dict, img, markers_cw_ids, size, robot_marker_id);

    // ros init
    rclcpp::init(argc, argv);

    auto node = std::make_shared<CameraNode>();

    while(1) {
        cap.read(img);
        img_proc.image_update(img);
        img_proc.image_print();
        cv::imshow("img", img);       
        if(img_proc.get_is_robot_detected() && img_proc.get_is_transformed()) {
            ImageProcessor::Marker robot = img_proc.robot_get();
            
            node->publish(robot.center.x, robot.center.y, robot.yaw_degree);
        }

    }
   
    cv::destroyAllWindows();
    cap.release();
    return 0;

    rclcpp::shutdown();

}
