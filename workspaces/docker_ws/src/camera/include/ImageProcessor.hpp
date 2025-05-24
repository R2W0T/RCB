#pragma once

#include <opencv2/opencv.hpp> 
#include <opencv2/objdetect/aruco_detector.hpp>
#include <vector>
#include <array>
#include <string>

#include "ImageProcessor/Marker.hpp"
#include "ImageProcessor/ImageTransformationProcessor.hpp"
#include "ImageProcessor/ArucoMarkerProcessor.hpp"
#define PRINT_DETECTED_MARKERS

namespace ImageProcessor {
    class ImageProcessor {
        private:
            ArucoMarkerProcessor aruco_proc;
            cv::Mat img;
            std::array<cv::Point2f, 4> dst_points;
            std::array<int, 4> markers_cw_ids;
            cv::Size size;
            Marker robot;

            // used to check if the 4 corner markers are detected to publish data
            bool is_transformed = false;

            // used to check if the robot marker is detected to publish position data
            bool is_robot_detected = false;
            // ///////////////////////////
            cv::Mat camera_matrix;
            cv::Mat distortion_coefficient;

        public:
            
            ImageProcessor( int dict, 
                            cv::Mat &img,
                            std::array<int, 4> &markers_cw_ids,
                            cv::Size size,
                            int robot_marker_id
                        );
            // this method will update the image and perform perspective transformation on it 
            // for further processing and calculate robot position relative to the transformed image
            void image_update(cv::Mat &img);
            void image_print();
            
            Marker& robot_get();
            cv::Mat& img_get();

            bool get_is_transformed();
            bool get_is_robot_detected();

    };
};
