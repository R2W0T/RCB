#pragma once

#include "ImageProcessor.hpp"

namespace ImageProcessor {

    struct Marker {
            int marker_id;
            
            cv::Point2f center;
            cv::Point2f main_corner;
            
            float yaw_degree;
        
        Marker();

        Marker( int marker_id, 
                cv::Point2f center, 
                cv::Point2f main_corner, 
                float yaw_degree);


        static Marker marker_create(int marker_id, std::vector<cv::Point2f> corners);
    };



};
