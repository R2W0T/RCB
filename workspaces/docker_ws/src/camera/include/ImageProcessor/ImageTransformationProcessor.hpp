#pragma once

#include "ImageProcessor.hpp"

namespace ImageProcessor {

    class ImageTransformationProcessor {
        public:
            static void perspective_transform(   cv::Mat &img, 
                                                cv::Mat &dst, 
                                                std::array<cv::Point2f, 4> &src_corners, 
                                                std::array<cv::Point2f, 4> &dst_corners, cv::Size size
                                            );
            // ClockWise starting from top left 
            static void get_corner_markers(std::array<cv::Point2f, 4> &src_corners, std::array<int, 4> &corner_cw_ids, std::vector<Marker> &markers);
    
    };



};
