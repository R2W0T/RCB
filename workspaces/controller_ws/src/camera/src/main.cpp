#include "camera/camera_node.hpp"

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

int main(int argc, char *argv[]) {



    const int dict = cv::aruco::DICT_APRILTAG_25h9;
    const int robot_marker_id = 4;
    const int markers_cw_ids[4] = {0, 1, 2, 3};
    const uint32_t width = 480, height = 480;

    // initialize markers dictionary
    const cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(dict);

    
    // initialize marker detector
    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners;
    const cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    const cv::aruco::ArucoDetector detector(dictionary, detectorParams);



    cv::Mat img, dst, p_matrix;

    // initialize transformation points
    cv::Point2f src_pts[4];
    const cv::Point2f dst_pts[4] = {cv::Point2f(0, 0), cv::Point2f(width, 0), cv::Point2f(0, height), cv::Point2f(width, height)};

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

    auto node = std::make_shared<CameraNode>();

    while(cv::pollKey() == -1) {
        
        cap.read(img);
        cv::imshow("img", img);
        detector.detectMarkers(img, markerCorners, markerIds);
        
        // check if all markers are detected
        if(markerIds.size() < 5)
            continue;


        // get markers positions
        for(int i = 0; i < markerIds.size(); i++) 
            if(markerIds[i] < 4)
                src_pts[markerIds[i]] = markerCorners[i][0];

        // get transformation matrix     
        p_matrix = cv::getPerspectiveTransform(src_pts, dst_pts);

        cv::warpPerspective(img, dst, p_matrix, cv::Size(width, height));

        detector.detectMarkers(dst, markerCorners, markerIds);
        
        cv::imshow("dst", dst);

        for(int i = 0; i < markerIds.size(); i++)
            if(markerIds[i] == robot_marker_id)
                node->publish(  ((markerCorners[i][0].x + markerCorners[i][2].x) / 2), 
                                ((markerCorners[i][0].y + markerCorners[i][2].y) / 2),
                                std::atan2((markerCorners[i][1].y - markerCorners[i][0].y), (markerCorners[i][1].x - markerCorners[i][0].x)) * 180 / M_PI );

    }
    
    rclcpp::shutdown();

    
    cv::destroyAllWindows();
    cap.release();


    return 0;
}
